#include "game.hpp"

game::game()
{
	m_board = std::make_shared<board>();

	m_player_1 = std::make_shared<player>(0, "Waage", 30, 0, m_board);
	m_player_2 = std::make_shared<player>(1, "Maria", 30, 0, m_board);

	m_players[0] = m_player_1;
	m_players[1] = m_player_2;
}

void game::update()
{
	int current = 0;

	while(true)
	{
		std::cout << "Player " << (current + 1) << std::endl;
		std::cout << *m_players[current] << std::endl;

		m_players[current]->draw();
		m_players[current]->show_hand();

		std::cin.get();
		std::cin.ignore();
		current = (current + 1) % 2;
	}
}
