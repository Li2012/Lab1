//Dealer.cpp

#include "Dealer.h"
#include <iostream>
#include "Fails.h"

// for string to integer atoi
#include <cstdlib>

//for find function
#include <algorithm>

Dealer::Dealer()
{	
}

Dealer::~Dealer()
{
}

//This method initializes the dealer and interprets
//the command line parameters
int Dealer::Init_Dealer(int argc, char *argv[])
{
	port = default_port;
	int error = 0;
	if((error = Check_Options(argc, argv)) < 0)
	{
		std::cout << "usage: server -n <dealer name> [-p <server port>]" << std::endl;
		return error;
	}
	else
	{
		//Check over the parameters in pairs (flag and value)
		int i, j;
		for(i = 1,j = 2; i < argc && j < argc; i+=2,j+=2)
		{
			if(strcmp(argv[i],"-n") == 0)
			{
				server_name = argv[j];
			}
			if(strcmp(argv[i],"-p") == 0)
			{
				//we assume the user always inputs a valid port number
				port = atoi(argv[j]);
			}
		}

		std::cout << "The server's name is " << server_name << "." << std::endl;
		
		return 0;
	}	
}

//This method checks the command line parameters for bad input
int Dealer::Check_Options(int argc,char* argv [])
{
	//We are expecting an even number of parameters and at least 2 parameters
	if(argc % 2 != 1 || argc < 3)
		return ERROR_BAD_PARAMETERS;

	for(int i = 1; i < argc; i+=2)
	{
		if(argc > 3 && strcmp(argv[i],"-n") != 0 && strcmp(argv[i],"-p") != 0 && strcmp(argv[i],"-i") == 0)
			return ERROR_BAD_PARAMETERS;
		if(argc == 3 && strcmp(argv[i],"-n") != 0)
			return ERROR_BAD_PARAMETERS;	
	}

	return 0;	
}
int Dealer::ErrorHandler(int error)
{
	const char* usageMsg = "usage: server -n <dealer name> [-p <server port>]";

	switch(error){
	case ERROR_BAD_PARAMETERS:
		std::cout << "Dealer Error: Failed to initialize player. Please check your parameters." << std::endl;
		std::cout << usageMsg << std::endl;
		break;
	case ERROR_GET_HOST_NAME:
		std::cout << "Dealer Error: Failed to get the host name." << std::endl;
		break;
	case ERROR_ADDR_SET:
		std::cout << "Dealer Error: Failed to set server address." << std::endl;
		break;
	case ERROR_ACCEPTOR_OPEN:
		std::cout << "Dealer Error: Failed to open socket with acceptor." << std::endl;
		break;
	case ERROR_ADDR_TO_STRING:
		std::cout << "Dealer Error: Failed to receive address as string." << std::endl;
		break;
	case ERROR_BIND_PORT:
		std::cout << "Dealer Error: Failed to bind to port." << std::endl;
		break;			
	case ERROR_ACCEPTOR_ACCEPT:
		std::cout << "Dealer Error: Acceptor accept failed while listening." << std::endl;
		break;	
	case ERROR_SEND_SERVER_NAME:
		std::cout << "Dealer Error: Failed to send the server name." << std::endl;
		break;	
	}

	return error;
}

int Dealer::Bind_To_Port()
{
	ACE_INET_Addr server_addr;
	char addr_string[string_length];
	int error = 0;
	
	if((error = server_addr.get_host_name(addr_string, string_length -1)) == -1)
		return ERROR_GET_HOST_NAME;
	
	if ((error = server_addr.set (port, addr_string)) == -1) 
		return ERROR_ADDR_SET;
	
	if((error = acceptor.open(server_addr)) == -1)
		return ERROR_ACCEPTOR_OPEN;
	
	if((error = server_addr.addr_to_string(addr_string, string_length -1)) == -1)
		return ERROR_ADDR_TO_STRING;
	
	server_address = addr_string;
	std::cout << "The host name and port is " << server_address << std::endl << std::endl;

	return 0;
}

//This method listens to a Connected_Player over a socket
//stream. It receives over the socket, adds the player to their
//games, and sends out a game list to the player.
int Dealer::Listen()
{
	while (true) {
		Connected_Player player;
		ACE_SOCK_Stream peer; // temp peer.
		
		if(acceptor.accept(peer) == -1)
			return ERROR_ACCEPTOR_ACCEPT;

		player.Set_Peer(peer);
		if(Send_Server_Name(player.Get_Peer()) != 0)
			return ERROR_SEND_SERVER_NAME;

		player.Receive();
		Add_Player_To_Games(player);
		Send_Game_List(player);
		Add_Player(player);
		Print_All();
	}

	return 0;	
}

int Dealer::Send_Server_Name(ACE_SOCK_Stream peer)
{
	std::string to_send = dealer_name_key + delimiter + server_name;
	if(peer.send_n(to_send.c_str(), string_length) == -1)
	{
		std::cerr << "Sending Server Name Fails" << std::endl;
		return ERROR_SEND_SERVER_NAME;
	}
	return 0;
}

int Dealer::Send_Game_List(Connected_Player new_player) 
{
	std::vector<std::string> game_list_new_player(new_player.Get_Connected_Games());
	std::vector<std::string>::iterator it_game_name;
	std::vector<Connected_Player>::iterator it_connected_player;
	
	//Iterate over each game the newly joined player is playing
	for(it_game_name = game_list_new_player.begin(); it_game_name < game_list_new_player.end(); it_game_name++) 
	{
		//Iterate over each connected player to send out the list
		for(it_connected_player = vCP.begin(); it_connected_player != vCP.end(); it_connected_player++) 
		{
			std::vector<std::string> game_list(it_connected_player->Get_Connected_Games());
			if(game_list.end() == find(game_list.begin(), game_list.end(), *it_game_name))
				// if the player has not joined the game	
			{
				continue;
			}
			else //if the player is playing this game, we create a string with the
			{	 //information and then send that to the client
				std::string tmp(games_key + delimiter);
				tmp += *it_game_name;
				tmp += delimiter;
				tmp += player_name_key;
				tmp += delimiter;
				tmp += new_player.Get_Player_Name();
				tmp += delimiter;
				if(!(it_connected_player->Get_Peer().send_n(tmp.c_str(), string_length) > 0))
				{
					//Something bad happened with our send over the socket
					std::cerr << "Dealer: Send_Game_List: Failed to send to each member of the game." << std::endl;
					return ERROR_DEALER_SEND_LIST;
				}
			} 
		}
	}
	
	return 0;
}

//This method adds a player to their connected games
void Dealer::Add_Player_To_Games(Connected_Player new_player)
{
	std::vector<std::string> new_player_connected_games = new_player.Get_Connected_Games();
	std::vector<std::string>::iterator it;
	
	//Iterate over the list of the new players games
	for(it = new_player_connected_games.begin();it != new_player_connected_games.end(); it++)
	{
		bool found = false;
		//Iterate over all games
		for(std::vector<Game>::iterator it_game = games.begin(); it_game != games.end(); it_game++)
		{
			//If we have a match, add the player
			if(it_game->Is_Game_Name(*it))
			{
				found = true;
				it_game->Add_Player(new_player.Get_Player_Name());
			}
		}
		//If we didn't find a match, create a new game for that player
		if (found == false)
		{
			Game new_game(*it);
			new_game.Add_Player(new_player.Get_Player_Name());
			games.push_back(new_game);			
		}
	}
}

void Dealer::Add_Player(Connected_Player icn)
{
	vCP.push_back(icn);
}

void Dealer::Print_All() 
{
	std::cout << "The server is " << server_name << "." << std::endl;
	std::cout << "The host name and port is " << server_address << std::endl;
	std::vector<Game>::iterator it;
	for(it = games.begin(); it != games.end(); it++)
	{
		std::cout << "Game " << it->Get_Game_Name() << std::endl;
		std::vector<std::string> player_name_list = it->Get_Player_Name_List();
		std::vector<std::string>::iterator it_player_name;
		for(it_player_name = player_name_list.begin();it_player_name != player_name_list.end(); it_player_name++)
		{
			std::cout << *it_player_name << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Game Dealer::Get_Game_By_Name(std::string game_name)
{
	std::vector<Game>::iterator it_game;
	for(it_game = games.begin(); it_game < games.end(); it_game++)
	{
		if(it_game->Is_Game_Name(game_name))
		{
			return *it_game;
		}
	}
	return *it_game;
}
