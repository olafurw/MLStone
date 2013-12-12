#include "deck.hpp"
#include "utils.hpp"

#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

deck::deck()
{
	srand(time(NULL));
	std::ifstream cards("cards.txt");

	if(cards.is_open())
	{
		int mana;
		int damage;
		int health;
		int taunt;
		std::string name;

		while(!cards.eof())
		{
			cards >> mana >> damage >> health >> taunt;
			std::getline(cards, name);
			trim(name);

			card c(name, mana, damage, health, (taunt > 0 ? true : false));

			m_cards.emplace_back(c);
		}

		shuffle();
	}
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

bool deck::empty()
{
	return m_cards.empty();
}

void deck::insert(card c)
{
	// This is more expensive than push_back
	// but we insert in bulk and remove one at a time
	// so it should be nicer.
	m_cards.insert(m_cards.begin(), c);
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
	std::random_shuffle(m_cards.begin(), m_cards.end());
}
