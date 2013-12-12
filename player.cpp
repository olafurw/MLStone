#include "player.hpp"

player::player(std::string name, int health, int armor):
		m_name(name),
		m_health(health),
		m_max_health(health),
		m_armor(armor),
		m_alive(true)
{
}

player::player(const player& p)
{
	m_name = p.m_name;
	m_health = p.m_health;
	m_max_health = p.m_max_health;
	m_armor = p.m_armor;
	m_alive = p.m_alive;
}

player::player(player&& p)
{
	m_name = std::move(p.m_name);
	m_health = p.m_health;
	m_max_health = p.m_max_health;
	m_armor = p.m_armor;
	m_alive = p.m_alive;
}

player& player::operator =(const player& p)
{
	if(this != &p)
	{
		m_name = p.m_name;
		m_health = p.m_health;
		m_max_health = p.m_max_health;
		m_armor = p.m_armor;
		m_alive = p.m_alive;
	}

	return *this;
}

player& player::operator =(player&& p)
{
	if(this != &p)
	{
		m_name = std::move(p.m_name);
		m_health = p.m_health;
		m_max_health = p.m_max_health;
		m_armor = p.m_armor;
		m_alive = p.m_alive;
	}

	return *this;
}

void player::show_board()
{
	std::cout << m_board;
}

void player::show_hand()
{
	for(const card& c : m_hand)
	{
		std::cout << c << std::endl;
	}
}

void player::draw()
{
	m_hand.emplace_back(m_deck.draw());
}

void player::add_to_board(int index)
{
	m_board.add(m_hand.at(index));
	m_hand.erase(m_hand.begin() + index);
}

void player::attack(int player_card, board& enemy_board, int enemy_card)
{
	m_board.attack(player_card, enemy_board, enemy_card);
}

void player::attack(int player_card)
{

}

board& player::get_board()
{
	return m_board;
}

std::ostream& operator<<(std::ostream& out, const player& p)
{
	out << "[Player] " << p.m_name
		<< " - [H] " << p.m_health
		<< " - [A] " << p.m_armor
		<< " - " << (p.m_alive ? "Alive" : "Dead");

	return out;
}
