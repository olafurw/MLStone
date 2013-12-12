#ifndef MLSTONE_PLAYER
#define MLSTONE_PLAYER

#include <vector>
#include <string>
#include <iostream>

#include "card.hpp"
#include "deck.hpp"
#include "board.hpp"

class player
{
public:
	player() = delete;
	player(std::string name, int health, int armor);
	player(const player& p);
	player(player&& p);

	player& operator =(const player& p);
	player& operator =(player&& p);

	void show_board();
	void show_hand();

	void draw();
	void add_to_board(int index);
	void attack(int player_card, board& enemy_board, int enemy_card);
	void attack(int player_card);

	board& get_board();

	friend std::ostream& operator<<(std::ostream& out, const player& p);

private:
	std::string m_name;
	int m_health;
	int m_max_health;
	int m_armor;

	bool m_alive;

	std::vector<card> m_hand;
	deck m_deck;
	board m_board;
};

std::ostream& operator<<(std::ostream& out, const player& p);

#endif
