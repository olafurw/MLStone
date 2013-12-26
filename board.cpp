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
	// Only one taunt card on the board is enough
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
    std::vector<card>* attacker_board = m_board[aid];
    std::vector<card>* target_board = m_board[bid];

	card& attacker_card = attacker_board->at(attacker_index);
	card& target_card = target_board->at(target_index);

	// If the target is not a taunt, we need to go
	// through the other cards to see if there is any taunt card there
	if(can_be_attacked(bid, target_index))
	{
		attacker_card.attack(target_card);

		// If the attacker died during that strike, remove it
		if(!attacker_card.alive())
		{
			auto pos = std::find(attacker_board->begin(), attacker_board->end(), attacker_card);
			if(pos != attacker_board->end())
			{
			    attacker_board->erase(pos);
			}
		}

		// If the target died during that strike, remove it
		if(!target_card.alive())
		{
			auto pos = std::find(target_board->begin(), target_board->end(), target_card);
			if(pos != target_board->end())
			{
			    target_board->erase(pos);
			}
		}
	}
}

void board::attack(int aid, int attacker_index, int bid)
{
	// Card to attack with
	card& attacker_card = m_board[aid]->at(attacker_index);

	// Player to attack
	player* p = m_players[bid];
	attacker_card.attack(p);

	// If the attacker died during that strike, remove it
	if(!attacker_card.alive())
	{
		auto pos = std::find(m_board[aid]->begin(), m_board[aid]->end(), attacker_card);
		if(pos != m_board[aid]->end())
		{
			m_board[aid]->erase(pos);
		}
	}
}

bool board::alive(int id)
{
	player* p = m_players[id];

	return p->alive();
}

int board::count(int id)
{
	std::vector<card>* brd = m_board[id];

	return brd->size();
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

		return;
	}

	if(id == 1)
	{
		m_players[1] = p;

		return;
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
