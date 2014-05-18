#ifndef MLSTONE_PLAYER
#define MLSTONE_PLAYER

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "card.hpp"
#include "deck.hpp"
#include "board.hpp"
#include "target.hpp"

class player : public target
{
public:
	player() = delete;
	player(unsigned int id, 
           std::string name, 
           int health, 
           int armor, 
           std::shared_ptr<board> board);

	player(unsigned int id, 
           std::string name,
           int health, 
           int armor, 
           std::shared_ptr<board> board, 
           const std::vector<card>& cards);

	player(const player& p);
	player(player&& p);

	player& operator =(const player& p);
	player& operator =(player&& p);

	void show_board();
	void show_hand();

	void update();

	void draw();
	bool can_add_to_board(unsigned int index);
	void add_to_board(unsigned int index);
	void attack(unsigned int player_card, unsigned int enemy_card);
	void attack(unsigned int player_card);
	void take_damage(int damage);
	void give_health(int health);

	std::string name() const;
	int health() const;
	unsigned int id() const;
	unsigned int enemy_id() const;
	bool alive() const;

	friend std::ostream& operator<<(std::ostream& out, const player& p);

private:
	unsigned int m_id;
	unsigned int m_enemy_id;
	int m_health;
	int m_max_health;
	int m_mana;
	int m_max_mana;
	int m_armor;
	int m_fatigue;

	bool m_alive;
    
    char _padd[7];
    
    std::string m_name;

    deck m_deck;
	std::vector<card> m_hand;
	std::shared_ptr<board> m_board;
};

std::ostream& operator<<(std::ostream& out, const player& p);

#endif
