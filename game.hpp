#include <memory>
#include <vector>
#include <iostream>

#include "board.hpp"
#include "player.hpp"
#include "card_generator.hpp"

class game
{
public:
	game(card_generator& cg);

	int play();

private:
	std::shared_ptr<board> m_board;
	std::vector<std::shared_ptr<player>> m_players;
};
