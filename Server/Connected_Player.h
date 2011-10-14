//Connected_Player.h

#ifndef CONNECTED_PLAYER_H
#define CONNECTED_PLAYER_H

#include <string>
#include <vector>
#include "ace/SOCK_Stream.h"

class Connected_Player
{
public:
	Connected_Player();
	~Connected_Player();
	std::string Get_Player_Name() const	{	return player_name;	}
	void Set_Player_Name(std::string name)	{	player_name = name;	}
	std::vector<std::string> Get_Connected_Games() const	{ return connected_games; }
	ACE_SOCK_Stream Get_Peer() const { return peer;	}
	void Set_Peer (ACE_SOCK_Stream p)	{ peer = p;	}
	bool If_In_Game(std::string game_name);
	int Receive();
private:
	std::string player_name;
	std::vector<std::string> connected_games;
	ACE_SOCK_Stream peer;
};

#endif
