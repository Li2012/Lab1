//Dealer.h

#ifndef DEALER_H
#define DEALER_H

#include <string>
#include <vector>
#include "Connected_Player.h"
#include "Game.h"

#include "ace/INET_Addr.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Acceptor.h"

class Dealer 
{
public:
	Dealer();
	~Dealer();
	int Init_Dealer(int argc, char *argv[]);
	int Check_Options(int argc, char* argv[]);
	int ErrorHandler(int error);
	int Bind_To_Port();
	int Listen();
	int Send_Server_Name(ACE_SOCK_Stream peer);
	int Send_Game_List(Connected_Player new_player);
	void Add_Player_To_Games(Connected_Player new_player);
	void Add_Player(Connected_Player icn);
	void Print_All() ;
	Game Get_Game_By_Name(std::string game_name); 
private:
	std::string server_name;
	std::string server_address;
	ACE_SOCK_Acceptor acceptor;
	int port;
	std::vector<Connected_Player> vCP; //vector for connected player
	std::vector<Game> games;
};

const int default_port = 11111;
const int string_length = 200;

const std::string dealer_name_key = "DN";
const std::string games_key = "GM";
const std::string delimiter = "~$";
const std::string player_name_key = "PN";

#endif
