#include "game.hpp"

game::game()
{
	m_board = std::make_shared<board>();

	m_player_1 = std::make_shared<player>(0, "Waage", 30, 0, m_board);
	m_player_2 = std::make_shared<player>(1, "Maria", 30, 0, m_board);
}
