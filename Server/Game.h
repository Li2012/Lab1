//Game.h

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Game
{
public:
	Game() {};
	Game(std::string game_name);
	//Game(const Game& game);
	~Game();
	void Add_Player(std::string player_name);
	const std::string& Get_Game_Name() const {	return game_name;	} 
	const std::vector<std::string>& Get_Player_Name_List() const  {	return player_name_list;	}
	bool Is_Game_Name(std::string gName) { return gName.compare(this->game_name)==0;	}
	bool Has_Player(std::string player_name);
	
private:
	std::string game_name;
	std::vector<std::string> player_name_list;
};

#endif
