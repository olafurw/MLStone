#include "board.hpp"
#include "player.hpp"

board::board()
{
	m_limit = 10;

	m_board[0] = &m_board_one;
	m_board[1] = &m_board_two;
}

bool board::can_add(int id)
{
	return m_board[id]->size() < m_limit;
}

void board::add(int id, card c)
{
	// Cannot add a card to a deck past the limit
	if(m_board[id]->size() == m_limit)
	{
		return;
	}

	m_board[id]->emplace_back(c);
}

void board::refresh(int id)
{
	for(auto& c : *(m_board[id]))
	{
		c.refresh();
	}
}

card& board::at(int id, int index)
{
	return m_board[id]->at(index);
}

bool board::is_taunt(int id)
{
	for(auto c : *(m_board[id]))
	{
		if(c.taunt())
		{
			return true;
		}
	}

	return false;
}

bool board::can_be_attacked(int id, int index)
{
	card& target_card = m_board[id]->at(index);

	// We can always attack taunt cards
	if(target_card.taunt())
	{
		return true;
	}

	// If there is no taunt card, then we can attack
	return !is_taunt(id);
}

void board::attack(int aid, int attacker_index, int bid, int target_index)
{
	card& attacker_card = m_board[aid]->at(attacker_index);
	card& target_card = m_board[bid]->at(target_index);

	// If the target is not a taunt, we need to go
	// through the other cards to see if there is any taunt card there
	if(can_be_attacked(bid, target_index))
	{
		attacker_card.attack(target_card);

		// If the attacker died during that strike, remove it
		if(!attacker_card.alive())
		{
			auto pos = std::find(m_board[aid]->begin(), m_board[aid]->end(), attacker_card);
			if(pos != m_board[aid]->end())
			{
				m_board[aid]->erase(pos);
			}
		}

		// If the target died during that strike, remove it
		if(!target_card.alive())
		{
			auto pos = std::find(m_board[bid]->begin(), m_board[bid]->end(), target_card);
			if(pos != m_board[bid]->end())
			{
				m_board[bid]->erase(pos);
			}
		}
	}
}

std::vector<int> board::cards(int id)
{
	std::vector<card>* brd = m_board[id];
	std::vector<int> list;

	for(unsigned int i = 0; i < brd->size(); ++i)
	{
		list.push_back(i);
	}

	return list;
}

std::vector<int> board::cards_can_attack(int id)
{
	std::vector<card>* brd = m_board[id];
	std::vector<int> list;

	for(unsigned int i = 0; i < brd->size(); ++i)
	{
		if(can_be_attacked(id, i))
		{
			list.push_back(i);
		}
	}

	return list;
}

void board::register_player(int id, player* p)
{
	if(id == 0)
	{
		m_players[0] = p;
	}
	else if(id == 1)
	{
		m_players[1] = p;
	}
}

std::ostream& operator<<(std::ostream& out, board& b)
{
	for(auto p : b.m_players)
	{
		out << p.second->name() << std::endl;

		for(auto c : *(b.m_board[p.first]))
		{
			out << c << std::endl;
		}
	}

	return out;
}
