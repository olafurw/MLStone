#include "board.hpp"

board::board()
{
	m_limit = 10;
}

void board::add(card c)
{
	if(m_board.size() == m_limit)
	{
		return;
	}

	c.wake_up();

	m_board.emplace_back(c);
}

card& board::at(int index)
{
	return m_board.at(index);
}

void board::attack(int index, board& enemy_board, int enemy_index)
{
	card& player_card = m_board.at(index);
	card& enemy_card = enemy_board.at(enemy_index);

	player_card.attack(enemy_card);
}

std::ostream& operator<<(std::ostream& out, const board& b)
{
	for(const card& c : b.m_board)
	{
		out << c << std::endl;
	}

	return out;
}
