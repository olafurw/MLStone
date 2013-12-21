#ifndef MLSTONE_PLAYER
#define MLSTONE_PLAYER

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "card.hpp"
#include "deck.hpp"
#include "board.hpp"

class player
{
public:
	player() = delete;
	player(int id, std::string name, int health, int armor, std::shared_ptr<board> board);
	player(const player& p);
	player(player&& p);

	player& operator =(const player& p);
	player& operator =(player&& p);

	void show_board();
	void show_hand();

	void update();
	void play();

	void draw();
	void add_to_board(int index);
	void attack(int player_card, board& enemy_board, int enemy_card);

	friend std::ostream& operator<<(std::ostream& out, const player& p);

private:
	int m_id;
	int m_enemy_id;
	std::string m_name;
	int m_health;
	int m_max_health;
	int m_mana;
	int m_max_mana;
	int m_armor;

	bool m_alive;

	std::vector<card> m_hand;
	deck m_deck;
	std::shared_ptr<board> m_board;
};

std::ostream& operator<<(std::ostream& out, const player& p);

#endif
