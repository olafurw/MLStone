#include "player.hpp"

player::player(unsigned int id, std::string name, int health, int armor, std::shared_ptr<board> board):
        target(target::type::player),
		m_id(id),
		m_enemy_id((id + 1) % 2),
		m_health(health),
		m_max_health(health),
		m_mana(0),
		m_max_mana(0),
		m_armor(armor),
		m_fatigue(0),
		m_alive(true),
        m_name(name),
		m_board(board)
{
    m_deck.insert("cards.txt");
	m_board->register_player(m_id, this);
}

player::player(unsigned int id, std::string name, int health, int armor, std::shared_ptr<board> board, const std::vector<card>& cards):
        target(target::type::player),
        m_id(id),
        m_enemy_id((id + 1) % 2),
        m_health(health),
        m_max_health(health),
        m_mana(0),
        m_max_mana(0),
        m_armor(armor),
        m_fatigue(0),
        m_alive(true),
        m_name(name),
        m_board(board)
{
    m_deck.insert(cards);
    m_board->register_player(m_id, this);
}

player::player(const player& p): target(target::type::player)
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
	m_fatigue = p.m_fatigue;
	m_board = p.m_board;

	m_board->register_player(m_id, this);
}

player::player(player&& p): target(target::type::player)
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
	m_fatigue = p.m_fatigue;
	m_board = p.m_board;

	m_board->register_player(m_id, this);
}

player& player::operator =(const player& p)
{
	if(this != &p)
	{
	    m_type = p.m_type;
		m_id = p.m_id;
		m_enemy_id = p.m_enemy_id;
		m_name = p.m_name;
		m_health = p.m_health;
		m_max_health = p.m_max_health;
		m_mana = p.m_mana;
		m_max_mana = p.m_max_mana;
		m_armor = p.m_armor;
		m_alive = p.m_alive;
		m_fatigue = p.m_fatigue;
		m_board = p.m_board;

		m_board->register_player(m_id, this);
	}

	return *this;
}

player& player::operator =(player&& p)
{
	if(this != &p)
	{
	    m_type = p.m_type;
		m_id = p.m_id;
		m_enemy_id = p.m_enemy_id;
		m_name = std::move(p.m_name);
		m_health = p.m_health;
		m_max_health = p.m_max_health;
		m_mana = p.m_mana;
		m_max_mana = p.m_max_mana;
		m_armor = p.m_armor;
		m_alive = p.m_alive;
		m_fatigue = p.m_fatigue;
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
	if(m_hand.empty())
	{
		std::cout << "Hand empty" << std::endl;
		return;
	}

	for(const card& c : m_hand)
	{
		std::cout << c << std::endl;
	}
}

void player::update()
{
	// Add mana
	if(m_max_mana < 10)
	{
		++m_max_mana;
	}

	// Replenish it before the round
	m_mana = m_max_mana;

	// Get a card
	draw();

	//
	// Combat logic here below
	//

	// Add one the first card to the board you can
	for(unsigned int i = 0; i < m_hand.size(); ++i)
	{
		if(can_add_to_board(i))
		{
			add_to_board(i);
			break;
		}
	}

	// If there are no cards to attack, attack the player
	if(m_board->count(m_enemy_id) == 0)
	{
		for(auto player_card_id : m_board->cards(m_id))
		{
			// If the enemy is dead, we are done
			if(!m_board->alive(m_enemy_id))
			{
				return;
			}

			card& player_card = m_board->at(m_id, player_card_id);

			if(player_card.awake() && player_card.can_attack())
			{
				attack(player_card_id);
				return;
			}
		}
	}
	else
	{
		// Attack the first card that you can
		for(auto player_card_id : m_board->cards(m_id))
		{
			card& player_card = m_board->at(m_id, player_card_id);

			if(player_card.awake() && player_card.can_attack())
			{
                auto enemy_cards = m_board->cards_can_attack(m_enemy_id);
                if(enemy_cards.size() > 0)
                {
                    unsigned int enemy_card_id = enemy_cards.at(0);
                    attack(player_card_id, enemy_card_id);

                    return;
                }
			}
		}
	}
}

void player::draw()
{
	// Draw, else out of cards and will get fatigue
	if(m_deck.can_draw())
	{
		m_hand.emplace_back(m_deck.draw());
	}
	else
	{
		// Fatigued, since there are no more cards in the deck
		m_fatigue++;
		take_damage(m_fatigue);
	}
}

bool player::can_add_to_board(unsigned int index)
{
	return m_hand.at(index).mana() <= m_mana;
}

void player::add_to_board(unsigned int index)
{
	if(can_add_to_board(index))
	{
		int mana_cost = m_hand.at(index).mana();

		// Add to the board and remove it from the hand
		m_board->add(m_id, m_hand.at(index));
		m_hand.erase(m_hand.begin() + index);

		m_mana -= mana_cost;
	}
}

void player::attack(unsigned int player_card, unsigned int enemy_card)
{
	m_board->attack(m_id, player_card, m_enemy_id, enemy_card);
}

void player::attack(unsigned int player_card)
{
	m_board->attack(m_id, player_card, m_enemy_id);
}

void player::take_damage(int damage)
{
	// We do not want health to go below zero.
	// Here the player dies.
	if(m_health - damage <= 0)
	{
		m_health = 0;
		m_alive = false;

		return;
	}

	m_health -= damage;
}

void player::give_health(int health)
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

std::string player::name() const
{
	return m_name;
}

int player::health() const
{
    return m_health;
}

unsigned int player::id() const
{
	return m_id;
}

unsigned int player::enemy_id() const
{
	return m_enemy_id;
}

bool player::alive() const
{
	return m_alive;
}

std::ostream& operator<<(std::ostream& out, const player& p)
{
	out << "[Player " << (p.m_id + 1) << "] " << p.m_name
		<< " - [H] " << p.m_health << "/" << p.m_max_health
		<< " - [M] " << p.m_mana << "/" << p.m_max_mana
		<< " - [A] " << p.m_armor
		<< " - " << (p.m_alive ? "Alive" : "Dead");

	return out;
}
