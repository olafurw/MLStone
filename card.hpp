#ifndef MLSTONE_CARD
#define MLSTONE_CARD

#include <string>
#include <ostream>
#include <vector>

class player;

class card
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
         bool windfury);

    card(const card& c);
    card(card&& c);

    card& operator =(const card& c);
    card& operator =(card&& c);

	void attack(card& c);
	void attack(player* p);
	void refresh();

	bool can_attack();
	bool alive();
	bool awake();

	std::string name() const;
	bool shield() const;
	void give_shield();
	bool taunt() const;
	void give_taunt();
	bool charge() const;
	void give_charge();
	bool windfury() const;
	void give_windfury();
	int mana() const;
	int damage() const;
	int health() const;

	bool operator ==(const card& c);

	friend std::ostream& operator<<(std::ostream& out, const card& c);

private:
	void do_damage(int damage);

	int m_id;

	int m_mana;
	int m_damage;
	int m_health;
	int m_max_health;

	bool m_shield;
	bool m_charge;
	bool m_taunt;
	bool m_attack;
	bool m_awake;
	bool m_alive;
	bool m_windfury;

	int m_attack_count;
	int m_max_attack_count;

	std::string m_name;
};

std::ostream& operator<<(std::ostream& out, const card& c);

#endif
