#include <memory>
#include <vector>
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
	std::vector<std::shared_ptr<player>> m_players;
};
