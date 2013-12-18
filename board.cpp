#include "board.hpp"
#include "player.hpp"

board::board()
{
	m_limit = 10;
	m_player_one = nullptr;
	m_player_two = nullptr;

	m_board[0] = &m_board_one;
	m_board[1] = &m_board_two;

	std::vector<std::vector<card>*> m_board;
	std::vector<player*> m_players;
}

void board::add(int id, card c)
{
	if(m_board[id]->size() == m_limit)
	{
		return;
	}

	m_board[id]->emplace_back(c);
}

card& board::at(int id, int index)
{
	return m_board[id]->at(index);
}

void board::attack(int aid, int attacker_index, int bid, int target_index)
{
	card& attacker_card = m_board[aid]->at(attacker_index);
	card& target_card = m_board[bid]->at(target_index);

	attacker_card.attack(target_card);
}

void board::register_player(int id, player* p)
{
	if(id == 0)
	{
		m_player_one = p;
		m_players[0] = p;
	}
	else if(id == 1)
	{
		m_player_two = p;
		m_players[1] = p;
	}
}

std::ostream& operator<<(std::ostream& out, const board& b)
{
	out << "Player 1" << std::endl;
	for(auto c : b.m_board_one)
	{
		out << c << std::endl;
	}

	out << "Player 2" << std::endl;
	for(auto c : b.m_board_two)
	{
		out << c << std::endl;
	}

	return out;
}
