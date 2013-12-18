#include <memory>
#include <map>
#include <iostream>

#include "board.hpp"
#include "player.hpp"

class game
{
public:
	game();

	void update();

private:
	std::shared_ptr<board> m_board;

	std::shared_ptr<player> m_player_1;
	std::shared_ptr<player> m_player_2;
	std::map<int, std::shared_ptr<player>> m_players;
};
