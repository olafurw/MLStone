#ifndef MLSTONE_BOARD
#define MLSTONE_BOARD

#include <vector>

#include "card.hpp"

class board
{
public:
	board();

	void add(card c);
	card& at(int index);
	void attack(int index, board& enemy_board, int enemy_index);

	friend std::ostream& operator<<(std::ostream& out, const board& b);
private:
	std::vector<card> m_board;
	int m_limit;
};

std::ostream& operator<<(std::ostream& out, const board& b);

#endif
