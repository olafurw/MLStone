#include "card.hpp"

#include <utility>
#include <iostream>

card::card(const std::string& name,
		   int mana,
		   int damage,
		   int health,
		   bool taunt):
	m_name(name),
	m_mana(mana), m_damage(damage),
	m_health(health), m_max_health(health),
	m_taunt(taunt),
	m_alive(true),
	m_awake(false)
{

}

card::card(const card& c)
{
	m_name = c.m_name;

	m_mana = c.m_mana;
	m_damage = c.m_damage;
	m_health = c.m_health;
	m_max_health = c.m_max_health;

	m_taunt = c.m_taunt;

	m_alive = c.m_alive;
	m_awake = c.m_awake;
}

card::card(card&& c)
{
	m_name = std::move(c.m_name);

	m_mana = c.m_mana;
	m_damage = c.m_damage;
	m_health = c.m_health;
	m_max_health = c.m_max_health;

	m_taunt = c.m_taunt;
	m_alive = c.m_alive;
	m_awake = c.m_awake;
}

card& card::operator =(const card& c)
{
	if(this != &c)
	{
		m_name = c.m_name;

		m_mana = c.m_mana;
		m_damage = c.m_damage;
		m_health = c.m_health;
		m_max_health = c.m_max_health;

		m_taunt = c.m_taunt;
		m_alive = c.m_alive;
		m_awake = c.m_awake;
	}

	return *this;
}

card& card::operator =(card&& c)
{
	if(this != &c)
	{
		m_name = std::move(c.m_name);

		m_mana = c.m_mana;
		m_damage = c.m_damage;
		m_health = c.m_health;
		m_max_health = c.m_max_health;

		m_taunt = c.m_taunt;
		m_alive = c.m_alive;
		m_awake = c.m_awake;
	}

	return *this;
}

void card::attack(card& c)
{
	if(m_awake)
	{
		c.do_damage(m_damage);
		do_damage(c.m_damage);
	}
}

void card::do_damage(int damage)
{
	// We do not want health to go below zero.
	// Here the card dies.
	if(m_health - damage <= 0)
	{
		m_health = 0;
		m_alive = false;
		return;
	}

	m_health -= damage;
}

bool card::alive()
{
	return m_alive;
}

bool card::awake()
{
	return m_awake;
}

void card::wake_up()
{
	m_awake = true;
}

std::ostream& operator<<(std::ostream& out, const card& c)
{
	out << "[Card] " << c.m_name
		<< " - [M] " << c.m_mana
		<< " - [D] " << c.m_damage
		<< " - [H] " << c.m_health
		<< " - " << (c.m_alive ? "Alive" : "Dead");

	return out;
}
