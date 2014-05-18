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
	void register_player(unsigned int id, player* p);

	bool can_add(unsigned int id);
	void add(unsigned int id, card c);
	void refresh(unsigned int id);
	card& at(unsigned int id, unsigned int index);

	bool is_taunt(unsigned int id);
	bool can_be_attacked(unsigned int id, unsigned int index);
	void remove(unsigned int id, unsigned int index);
	void attack(unsigned int aid, unsigned int attacker_index, unsigned int bid, unsigned int target_index);
	void attack(unsigned int aid, unsigned int attacker_index, unsigned int bid);

	bool alive(unsigned int id);
	unsigned int count(unsigned int id);
	void clear(unsigned int id);
	void clear();
	std::vector<unsigned int> cards(unsigned int id);
	std::vector<unsigned int> cards_can_attack(unsigned int id);

	friend std::ostream& operator<<(std::ostream& out, board& b);
private:

	std::vector<card> m_board_one;
	std::vector<card> m_board_two;

	std::map<unsigned int, std::vector<card>*> m_board;
	std::map<unsigned int, player*> m_players;

	unsigned int m_limit;
	bool m_ready;
    
    char _padd[3];
};

std::ostream& operator<<(std::ostream& out, board& b);

#endif
