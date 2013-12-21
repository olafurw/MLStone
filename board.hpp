#ifndef MLSTONE_BOARD
#define MLSTONE_BOARD

#include <vector>
#include <map>
#include <algorithm>

#include "card.hpp"

class player;

class board
{
public:
	board();
	void register_player(int id, player* p);

	bool can_add(int id);
	void add(int id, card c);
	void refresh(int id);
	card& at(int id, int index);

	bool is_taunt(int id);
	bool can_be_attacked(int id, int index);
	void attack(int aid, int attacker_index, int bid, int target_index);

	std::vector<int> cards(int id);
	std::vector<int> cards_can_attack(int id);

	friend std::ostream& operator<<(std::ostream& out, board& b);
private:

	std::vector<card> m_board_one;
	std::vector<card> m_board_two;

	std::map<int, std::vector<card>*> m_board;
	std::map<int, player*> m_players;

	unsigned int m_limit;
};

std::ostream& operator<<(std::ostream& out, board& b);

#endif
