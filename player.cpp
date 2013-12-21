#include "player.hpp"

player::player(int id, std::string name, int health, int armor, std::shared_ptr<board> board):
		m_id(id),
		m_enemy_id(id + 1 % 2),
		m_name(name),
		m_health(health),
		m_max_health(health),
		m_mana(0),
		m_max_mana(0),
		m_armor(armor),
		m_alive(true),
		m_board(board)
{
	m_board->register_player(m_id, this);
}

player::player(const player& p)
{
	m_id = p.m_id;
	m_enemy_id = p.m_enemy_id;
	m_name = p.m_name;
	m_health = p.m_health;
	m_max_health = p.m_max_health;
	m_mana = p.m_mana;
	m_max_mana = p.m_max_mana;
	m_armor = p.m_armor;
	m_alive = p.m_alive;
	m_board = p.m_board;

	m_board->register_player(m_id, this);
}

player::player(player&& p)
{
	m_id = p.m_id;
	m_enemy_id = p.m_enemy_id;
	m_name = std::move(p.m_name);
	m_health = p.m_health;
	m_max_health = p.m_max_health;
	m_mana = p.m_mana;
	m_max_mana = p.m_max_mana;
	m_armor = p.m_armor;
	m_alive = p.m_alive;
	m_board = p.m_board;

	m_board->register_player(m_id, this);
}

player& player::operator =(const player& p)
{
	if(this != &p)
	{
		m_id = p.m_id;
		m_enemy_id = p.m_enemy_id;
		m_name = p.m_name;
		m_health = p.m_health;
		m_max_health = p.m_max_health;
		m_mana = p.m_mana;
		m_max_mana = p.m_max_mana;
		m_armor = p.m_armor;
		m_alive = p.m_alive;
		m_board = p.m_board;

		m_board->register_player(m_id, this);
	}

	return *this;
}

player& player::operator =(player&& p)
{
	if(this != &p)
	{
		m_id = p.m_id;
		m_enemy_id = p.m_enemy_id;
		m_name = std::move(p.m_name);
		m_health = p.m_health;
		m_max_health = p.m_max_health;
		m_mana = p.m_mana;
		m_max_mana = p.m_max_mana;
		m_armor = p.m_armor;
		m_alive = p.m_alive;
		m_board = p.m_board;

		m_board->register_player(m_id, this);
	}

	return *this;
}

void player::show_board()
{
	std::cout << *m_board;
}

void player::show_hand()
{
	for(const card& c : m_hand)
	{
		std::cout << c << std::endl;
	}
}

void player::update()
{
	if(m_max_mana < 10)
	{
		++m_max_mana;
	}

	// Replenish
	m_mana = m_max_mana;

	draw();
}

void player::play()
{

}

void player::draw()
{
	if(m_deck.can_draw())
	{
		m_hand.emplace_back(m_deck.draw());
	}
}

void player::add_to_board(int index)
{
	m_board->add(m_id, m_hand.at(index));
	m_hand.erase(m_hand.begin() + index);
}

void player::attack(int player_card, board& enemy_board, int enemy_card)
{
	m_board->attack(m_id, player_card, m_enemy_id, enemy_card);
}

std::ostream& operator<<(std::ostream& out, const player& p)
{
	out << "[Player " << (p.m_id + 1) << "] " << p.m_name
		<< " - [H] " << p.m_health
		<< " - [A] " << p.m_armor
		<< " - " << (p.m_alive ? "Alive" : "Dead");

	return out;
}
