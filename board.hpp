#ifndef MLSTONE_BOARD
#define MLSTONE_BOARD

#include <vector>
#include <map>

#include "card.hpp"

class player;

class board
{
public:
	board();

	void add(int id, card c);
	card& at(int id, int index);
	void attack(int aid, int attacker_index, int bid, int target_index);

	void register_player(int id, player* p);

	friend std::ostream& operator<<(std::ostream& out, const board& b);
private:

	player* m_player_one;
	std::vector<card> m_board_one;

	player* m_player_two;
	std::vector<card> m_board_two;

	std::map<int, std::vector<card>*> m_board;
	std::map<int, player*> m_players;

	unsigned int m_limit;
};

std::ostream& operator<<(std::ostream& out, const board& b);

#endif
