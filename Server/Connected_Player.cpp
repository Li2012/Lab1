//Connected_Player.cpp

#include "Connected_Player.h"

#include "Dealer.h"
#include <iostream>
//for strings like delimiter

Connected_Player::Connected_Player()
{
}
Connected_Player::~Connected_Player()
{
}

bool Connected_Player::If_In_Game(std::string game_name)
{
	for(std::vector<std::string>::iterator it = connected_games.begin(); it != connected_games.end(); ++it)
	{
		if(game_name == *it)
			return true;
	}
	return false;
}

//This method receives strings and then parses
//them out according to the scheme below
int Connected_Player::Receive()
{
	char buffer[string_length];
	if(peer.recv(buffer, string_length) > 0)
	{
		std::string temp(buffer);
		std::vector<std::string> vt;
		size_t length;
		//the received string looks like:
		//PN~$Alex~$GM~$poker~$GM~$heart~$
		//the vector looks like:
		// vt 0 is: PN
		// vt 1 is: Alex
		// vt 2 is: GM
		// vt 3 is: poker
		// vt 4 is: GM
		// vt 5 is: heart
		for(size_t pos = 0; pos < temp.size(); pos += (length + delimiter.size()))
		{
			length = temp.find(delimiter, pos) - pos;
			std::string sub_str(temp.substr(pos, length));
			vt.push_back(sub_str);
		}

		//handle the strings
		for(size_t i = 0; i < vt.size(); ++i)
		{
			if(vt[i]  == games_key)
				connected_games.push_back(vt[++i]);
			if(vt[i] == player_name_key)
				player_name = vt[++i];
		}
	}
	return 0;
}
