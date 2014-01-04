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
	m_name(name),
	m_mana(mana), m_damage(damage),
	m_health(health), m_max_health(health),
	m_taunt(taunt),
	m_charge(charge),
	m_shield(shield),
	m_attack(charge),
	m_alive(true),
	m_awake(charge),
	m_windfury(windfury),
	m_attack_count((m_windfury ? 2 : 1)),
	m_max_attack_count(m_attack_count)
{
	m_id = random_generator()();
}

card::card(const card& c)
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
}

card::card(card&& c)
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
}

card& card::operator =(const card& c)
{
	if(this != &c)
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
	}

	return *this;
}

card& card::operator =(card&& c)
{
	if(this != &c)
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
	}

	return *this;
}

void card::attack(card& c)
{
	if(m_awake && m_attack && m_attack_count > 0)
	{
		c.do_damage(m_damage);
		do_damage(c.m_damage);

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

void card::do_damage(int damage)
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

bool card::can_attack()
{
	return m_attack;
}

bool card::alive()
{
	return m_alive;
}

bool card::awake()
{
	return m_awake;
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

bool card::operator ==(const card& c)
{
	return m_name == c.m_name &&
		   m_health == c.m_health &&
		   m_id == c.m_id;
}

std::ostream& operator<<(std::ostream& out, const card& c)
{
	out << "[Card] " << c.m_name
		<< (c.m_taunt ? " - [T]" : "")
		<< " - [M] " << c.m_mana
		<< " - [D] " << c.m_damage
		<< " - [H] " << c.m_health
		<< " - " << (c.m_alive ? "Alive" : "Dead");

	return out;
}
