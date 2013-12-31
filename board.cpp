#include "board.hpp"
#include "player.hpp"

board::board()
{
	m_limit = 10;

	m_board[0] = &m_board_one;
	m_board[1] = &m_board_two;

	m_players[0] == nullptr;
	m_players[1] == nullptr;

	m_ready = false;
}

bool board::can_add(int id)
{
    if(!m_ready)
    {
        return false;
    }

	return m_board[id]->size() < m_limit;
}

void board::add(int id, card c)
{
    if(!m_ready)
    {
        return;
    }

	// Cannot add a card to a deck past the limit
	if(m_board[id]->size() == m_limit)
	{
		return;
	}

	m_board[id]->emplace_back(c);
}

void board::refresh(int id)
{
    if(!m_ready)
    {
        return;
    }

	for(auto& c : *(m_board[id]))
	{
		c.refresh();
	}
}

card& board::at(int id, int index)
{
    if(!m_ready)
    {
        throw std::logic_error("Players not registered");
    }

	return m_board[id]->at(index);
}

bool board::is_taunt(int id)
{
    if(!m_ready)
    {
        return false;
    }

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
    if(!m_ready)
    {
        return false;
    }

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
    if(!m_ready)
    {
        return;
    }

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
		    remove(aid, attacker_index);
		}

		// If the target died during that strike, remove it
		if(!target_card.alive())
		{
		    remove(bid, target_index);
		}
	}
}

void board::remove(int id, int index)
{
    if(!m_ready)
    {
        return;
    }

    std::vector<card>* target_board = m_board[id];

    // Index is not in the board
    if(target_board->size() <= index)
    {
        return;
    }

    // Find where the card is
    auto pos = std::find(target_board->begin(), target_board->end(), target_board->at(index));

    // If it is found somewhere, remove it
    if(pos != target_board->end())
    {
        target_board->erase(pos);
    }
}

void board::attack(int aid, int attacker_index, int bid)
{
    if(!m_ready)
    {
        return;
    }

	// Card to attack with
	card& attacker_card = m_board[aid]->at(attacker_index);

	// Player to attack
	attacker_card.attack(m_players[bid]);

	// If the attacker died during that strike, remove it
	if(!attacker_card.alive())
	{
	    remove(aid, attacker_index);
	}
}

bool board::alive(int id)
{
    if(!m_ready)
    {
        return false;
    }

	player* p = m_players[id];

	return p->alive();
}

int board::count(int id)
{
    if(!m_ready)
    {
        return 0;
    }

	std::vector<card>* brd = m_board[id];

	return brd->size();
}

void board::clear(int id)
{
    if(!m_ready)
    {
        return;
    }

    m_board[id]->clear();
}

void board::clear()
{
    if(!m_ready)
    {
        return;
    }

    m_board[0]->clear();
    m_board[1]->clear();
}

// TODO: Stupid design, remove and do something smarter, like just returning the cards
std::vector<int> board::cards(int id)
{
    std::vector<int> list;

    if(!m_ready)
    {
        return list;
    }

	std::vector<card>* brd = m_board[id];
	for(unsigned int i = 0; i < brd->size(); ++i)
	{
		list.push_back(i);
	}

	return list;
}

std::vector<int> board::cards_can_attack(int id)
{
    std::vector<int> list;

    if(!m_ready)
    {
        return list;
    }

	std::vector<card>* brd = m_board[id];
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
		m_ready = (m_players[0] != nullptr && m_players[1] != nullptr);

		return;
	}

	if(id == 1)
	{
		m_players[1] = p;
		m_ready = (m_players[0] != nullptr && m_players[1] != nullptr);

		return;
	}
}

std::ostream& operator<<(std::ostream& out, board& b)
{
    if(!b.m_ready)
    {
        return out;
    }

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
