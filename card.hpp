#ifndef MLSTONE_CARD
#define MLSTONE_CARD

#include <string>
#include <ostream>

class card
{
public:
	card() = delete;

	card(const std::string& name,
	     int mana,
	     int damage,
	     int health,
	     bool taunt);

	card(const card& c);
	card(card&& c);

	card& operator =(const card& c);
	card& operator =(card&& c);

	void attack(card& c);

	bool alive();
	bool awake();
	void wake_up();

	friend std::ostream& operator<<(std::ostream& out, const card& c);

private:
	void do_damage(int damage);

	int m_mana;
	int m_damage;
	int m_health;
	int m_max_health;

	bool m_taunt;

	bool m_awake;
	bool m_alive;

	std::string m_name;
};

std::ostream& operator<<(std::ostream& out, const card& c);

#endif
