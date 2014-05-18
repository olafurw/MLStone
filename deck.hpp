#ifndef MLSTONE_DECK
#define MLSTONE_DECK

#include <vector>

#include "card.hpp"

class deck
{
public:
	deck();
	deck(const std::vector<card>& cards);
	deck(const deck& d);
	deck(deck&& d);

	deck& operator =(const deck& d);
	deck& operator =(deck&& d);

	void insert(const std::vector<card>& cards);
	void insert(const std::string& filename);
	unsigned int count();
	bool can_draw();
	card draw();
	void shuffle();
	void clear();

private:
	std::vector<card> m_cards;
};

#endif
