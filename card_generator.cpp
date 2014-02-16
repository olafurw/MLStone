#include "card_generator.hpp"

card_generator::card_generator()
{
    m_rnd = random_generator();

    unsigned int card_id = 0;

    for(int i = 0; i < 382; ++i)
    {
        // Mana
        int mana = ((m_rnd() % 10) + 1);

        // Damage
        int damage = (m_rnd() % 8);

        // Health
        int health = ((m_rnd() % 8) + 1);

        // Taunt
        bool taunt = (m_rnd() % 2 > 0);

        // Charge
        bool charge = (m_rnd() % 2 > 0);

        // Shield
        bool shield = (m_rnd() % 2 > 0);

        // Windfury
        bool windfury = (m_rnd() % 2 > 0);

        card c(std::to_string(card_id), mana, damage, health, taunt, charge, shield, windfury);

        card_id++;

        m_cards.emplace_back(c);
    }

    std::shuffle(m_cards.begin(), m_cards.end(), m_rnd);
}

std::vector<card> card_generator::get_deck()
{
    std::shuffle(m_cards.begin(), m_cards.end(), m_rnd);

    std::vector<card> deck;

    for(int i = 0; i < 30; ++i)
    {
        deck.push_back(m_cards.at(i));
    }

    return deck;
}

void card_generator::print_deck()
{
    std::sort(m_cards.begin(), m_cards.end(), [](const card& a, const card& b){ return a.name() < b.name(); });

    for(int i = 0; i < 382; ++i)
    {
        std::cout << m_cards.at(i) << std::endl;
    }
}
