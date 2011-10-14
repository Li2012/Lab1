//Game.cpp

#include "Game.h"
#include <algorithm>

Game::Game(std::string gName) : game_name(gName)
{
}

Game::~Game()
{
}

// Adds a new player's name to the game's list
void Game::Add_Player(std::string player_name)
{
	player_name_list.push_back(player_name);
}

// Check if the player is already in the game
bool Game::Has_Player(std::string player_name)
{
	//Use STL find() algorithm - if name is not in list, find will return end iterator
	if(player_name_list.end() == find(player_name_list.begin(), player_name_list.end(), player_name) )
		return false;
	else
		return true;
}
