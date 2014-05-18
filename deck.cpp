#include "deck.hpp"
#include "utils.hpp"

#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

deck::deck()
{
}

deck::deck(const std::vector<card>& cards)
{
    insert(cards);
}

deck::deck(const deck& d)
{
	for(card c : d.m_cards)
	{
		m_cards.push_back(c);
	}
}

deck::deck(deck&& d)
{
	m_cards = std::move(d.m_cards);
}

deck& deck::operator =(const deck& d)
{
	if(this != &d)
	{
		for(card c : d.m_cards)
		{
			m_cards.push_back(c);
		}
	}

	return *this;
}

deck& deck::operator =(deck&& d)
{
	if(this != &d)
	{
		m_cards = std::move(d.m_cards);
	}

	return *this;
}

void deck::insert(const std::vector<card>& cards)
{
    for(card c : cards)
    {
        m_cards.push_back(c);
    }

    shuffle();
}

void deck::insert(const std::string& filename)
{
    std::ifstream cards(filename);

    if(cards.is_open())
    {
        int mana;
        int damage;
        int health;
        int taunt;
        int charge;
        int shield;
        int windfury;
        std::string name;

        while(!cards.eof())
        {
            cards >> mana >> damage >> health >> taunt >> charge >> shield >> windfury;
            std::getline(cards, name);
            trim(name);

            card c(name, mana, damage, health, (taunt > 0 ? true : false), (charge > 0 ? true : false), (shield > 0 ? true : false), (windfury > 0 ? true : false));

            m_cards.emplace_back(c);
        }

        shuffle();
    }
}

unsigned int deck::count()
{
    return static_cast<unsigned int>(m_cards.size());
}

bool deck::can_draw()
{
	return !m_cards.empty();
}

card deck::draw()
{
	card c = m_cards.back();
	m_cards.pop_back();
	return c;
}

void deck::shuffle()
{
	// the deck is a vector so we can do this
	std::shuffle(m_cards.begin(), m_cards.end(), random_generator());
}

void deck::clear()
{
    m_cards.clear();
}
