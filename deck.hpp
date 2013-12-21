#ifndef MLSTONE_DECK
#define MLSTONE_DECK

#include <vector>

#include "card.hpp"

class deck
{
public:
	deck();
	deck(const deck& d);
	deck(deck&& d);

	deck& operator =(const deck& d);
	deck& operator =(deck&& d);

	bool can_draw();
	void insert(card c);
	card draw();
	void shuffle();

private:
	std::vector<card> m_cards;
};

#endif
