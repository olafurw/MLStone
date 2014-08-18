#include "card.hpp"
#include "utils.hpp"
#include "player.hpp"

#include <utility>
#include <iostream>

card::card(const std::string& name,
		   int mana,
		   int damage,
		   int health,
		   bool taunt,
		   bool charge,
		   bool shield,
		   bool windfury):
	target(target::type::card),
	m_mana(mana), m_damage(damage),
	m_health(health), m_max_health(health),
	m_shield(shield),
	m_charge(charge),
	m_taunt(taunt),
	m_attack(charge),
	m_awake(charge),
	m_alive(true),
	m_windfury(windfury),
	m_placed(false),
	m_destroy(false),
	m_name(name)
{
	m_id = static_cast<unsigned int>(random_generator()());
	
	m_attack_count = (m_windfury ? 2 : 1);
	m_max_attack_count = m_attack_count;
}

card::card(const card& c): target(target::type::card)
{
	m_id = c.m_id;
	m_name = c.m_name;

	m_mana = c.m_mana;
	m_damage = c.m_damage;
	m_health = c.m_health;
	m_max_health = c.m_max_health;

	m_shield = c.m_shield;
	m_taunt = c.m_taunt;
	m_charge = c.m_charge;
	m_attack = c.m_attack;
	m_alive = c.m_alive;
	m_awake = c.m_awake;
	m_windfury = c.m_windfury;
	m_attack_count = c.m_attack_count;
	m_max_attack_count = c.m_max_attack_count;

	m_battle_cry = c.m_battle_cry;

	m_placed = c.m_placed;
	m_destroy = c.m_destroy;
}

card::card(card&& c): target(target::type::card)
{
	m_id = c.m_id;
	m_name = std::move(c.m_name);

	m_mana = c.m_mana;
	m_damage = c.m_damage;
	m_health = c.m_health;
	m_max_health = c.m_max_health;

	m_shield = c.m_shield;
	m_taunt = c.m_taunt;
	m_charge = c.m_charge;
	m_attack = c.m_attack;
	m_alive = c.m_alive;
	m_awake = c.m_awake;
	m_windfury = c.m_windfury;
	m_attack_count = c.m_attack_count;
	m_max_attack_count = c.m_max_attack_count;

	m_battle_cry = std::move(c.m_battle_cry);

	m_placed = c.m_placed;
	m_destroy = c.m_destroy;
}

card& card::operator =(const card& c)
{
	if(this == &c)
	{
		return *this;
	}
	
	m_type = c.get_type();
	m_id = c.m_id;
	m_name = c.m_name;

	m_mana = c.m_mana;
	m_damage = c.m_damage;
	m_health = c.m_health;
	m_max_health = c.m_max_health;

	m_shield = c.m_shield;
	m_taunt = c.m_taunt;
	m_charge = c.m_charge;
	m_attack = c.m_attack;
	m_alive = c.m_alive;
	m_awake = c.m_awake;
	m_windfury = c.m_windfury;
	m_attack_count = c.m_attack_count;
	m_max_attack_count = c.m_max_attack_count;

	m_battle_cry = c.m_battle_cry;

	m_placed = c.m_placed;
	m_destroy = c.m_destroy;
}

card& card::operator =(card&& c)
{
	if(this == &c)
	{
		return *this;
	}

	m_type = c.get_type();
	m_id = c.m_id;
	m_name = std::move(c.m_name);

	m_mana = c.m_mana;
	m_damage = c.m_damage;
	m_health = c.m_health;
	m_max_health = c.m_max_health;

	m_shield = c.m_shield;
	m_taunt = c.m_taunt;
	m_charge = c.m_charge;
	m_attack = c.m_attack;
	m_alive = c.m_alive;
	m_awake = c.m_awake;
	m_windfury = c.m_windfury;
	m_attack_count = c.m_attack_count;
	m_max_attack_count = c.m_max_attack_count;

	m_battle_cry = std::move(c.m_battle_cry);

	m_placed = c.m_placed;
	m_destroy = c.m_destroy;
}

void card::attack(card& c)
{
	if(m_awake && m_attack && m_attack_count > 0)
	{
		c.take_damage(m_damage);
		take_damage(c.m_damage);

		--m_attack_count;

		// Cannot attack again this round until refreshed
		if(m_attack_count == 0)
		{
		    m_attack = false;
		}
	}
}

void card::attack(player* p)
{
	if(m_awake && m_attack && m_attack_count > 0)
	{
		p->take_damage(m_damage);

		--m_attack_count;

		// Cannot attack again this round until refreshed
		if(m_attack_count == 0)
		{
			m_attack = false;
		}
	}
}

void card::refresh()
{
	m_attack = true;
	m_awake = true;
	m_attack_count = m_max_attack_count;
}

void card::take_damage(int damage)
{
	if(m_shield)
	{
		m_shield = false;

		return;
	}

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

void card::give_health(int health)
{
	if(!m_alive)
	{
		return;
	}

	// We can not go over max health
	if(health + m_health > m_max_health)
	{
		m_health = m_max_health;

		return;
	}

	m_health += health;
}

bool card::can_attack() const
{
	return m_attack;
}

bool card::alive() const
{
	return m_alive;
}

bool card::awake() const
{
	return m_awake;
}

bool card::placed() const
{
	return m_placed;
}

void card::set_placed(bool p)
{
	m_placed = p;
}

bool card::destroy() const
{
	return m_destroy;
}

void card::set_destroy(bool d)
{
	m_destroy = d;
}

std::string card::name() const
{
	return m_name;
}

bool card::shield() const
{
	return m_shield;
}

void card::give_shield()
{
	m_shield = true;
}

bool card::taunt() const
{
	return m_taunt;
}

void card::give_taunt()
{
	m_taunt = true;
}

bool card::charge() const
{
	return m_charge;
}

void card::give_charge()
{
	m_charge = true;
}

bool card::windfury() const
{
	return m_windfury;
}

void card::give_windfury()
{
	m_windfury = true;
	m_attack_count = 2;
	m_max_attack_count = 2;
}

int card::mana() const
{
	return m_mana;
}

int card::damage() const
{
	return m_damage;
}

int card::health() const
{
	return m_health;
}

void card::add_battle_cry(std::shared_ptr<effect> e)
{
	m_battle_cry.push_back(e);
}

void card::process_battle_cry()
{
	for(auto& effect : m_battle_cry)
	{
		effect->set_parent(this);
		effect->process();
	}
}

void card::add_on_going(std::shared_ptr<effect> e)
{
	m_on_going.push_back(e);
}

void card::process_on_going()
{
	for(auto& effect : m_on_going)
	{
		effect->set_parent(this);
		effect->process();
	}
}

void card::add_death_rattle(std::shared_ptr<effect> e)
{
	m_death_rattle.push_back(e);
}

void card::process_death_rattle()
{
	for(auto& effect : m_death_rattle)
	{
		effect->set_parent(this);
		effect->process();
	}
}

bool card::operator ==(const card& c)
{
	return m_name == c.m_name &&
		   m_health == c.m_health &&
		   m_id == c.m_id;
}

std::ostream& operator<<(std::ostream& out, const card& c)
{
	out << "[Card] " << c.m_name
	    << " - ["
		<< (c.m_taunt ? "T/" : "0/")
		<< (c.m_charge ? "C/" : "0/")
		<< (c.m_shield ? "S/" : "0/")
		<< (c.m_windfury ? "W" : "0")
		<< "]"
		<< " - [Mana] " << c.m_mana
		<< " - [Dmg] " << c.m_damage
		<< " - [HP] " << c.m_health
		<< " - " << (c.m_alive ? "Alive" : "Dead");

	return out;
}
