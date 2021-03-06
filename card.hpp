#ifndef MLSTONE_CARD
#define MLSTONE_CARD

#include <string>
#include <ostream>
#include <vector>
#include <memory>

#include "target.hpp"
#include "effect.hpp"

class player;

class card: public target
{
public:
	card() = delete;

	card(const std::string& name,
		 int mana,
		 int damage,
		 int health,
		 bool taunt,
		 bool charge,
		 bool shield,
		 bool windfury,
		 bool stealth);

	card(const card& c);
	card(card&& c);
	
	~card();

	card& operator =(const card& c);
	card& operator =(card&& c);

	void attack(card& c);
	void attack(player* p);
	void refresh();

	bool can_attack() const;
	void take_damage(int damage);
	void give_health(int health);
	bool alive() const;
	bool awake() const;

	bool placed() const;
	void set_placed(bool p);

	bool destroy() const;
	void set_destroy(bool d);

	std::string name() const;
	bool shield() const;
	void give_shield();
	bool taunt() const;
	void give_taunt();
	bool charge() const;
	void give_charge();
	bool windfury() const;
	void give_windfury();
	bool stealth() const;
	void give_stealth();
	int mana() const;
	int damage() const;
	int health() const;

	void add_battle_cry(std::shared_ptr<effect> e);
	void process_battle_cry();
    
	void add_on_going(std::shared_ptr<effect> e);
	void process_on_going();

	void add_death_rattle(std::shared_ptr<effect> e);
	void process_death_rattle();

	bool operator ==(const card& c);

	friend std::ostream& operator<<(std::ostream& out, const card& c);

private:

	unsigned int m_id;

	int m_mana;
	int m_damage;
	int m_health;
	int m_max_health;
    
	int m_attack_count;
	int m_max_attack_count;

	bool m_shield;
	bool m_charge;
	bool m_taunt;
	bool m_attack;
	bool m_awake;
	bool m_alive;
	bool m_windfury;
	bool m_stealth;

	bool m_placed;
	bool m_destroy;

	std::string m_name;

	std::vector<std::shared_ptr<effect>> m_battle_cry;
	std::vector<std::shared_ptr<effect>> m_on_going;
	std::vector<std::shared_ptr<effect>> m_death_rattle;
};

std::ostream& operator<<(std::ostream& out, const card& c);

#endif
