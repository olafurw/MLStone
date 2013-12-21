#include "game.hpp"

game::game()
{
	m_board = std::make_shared<board>();

	m_players.emplace_back(std::make_shared<player>(0, "Waage", 30, 0, m_board));
	m_players.emplace_back(std::make_shared<player>(1, "Maria", 30, 0, m_board));
}

void game::update()
{
	int current = 0;

	// Game loop
	while(true)
	{
		// Make them take turns
		for(auto& player : m_players)
		{
			std::cout << *player << std::endl;
			player->play();
			player->update();
		}

		// Only play 1 round
		break;
	}
}
