#include "card_generator.hpp"

card_generator::card_generator()
{
    m_rnd = random_generator();

    for(int i = 1; i <= 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            // Mana
            int mana = i;

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

            m_cards.push_back(card("a", mana, damage, health, taunt, charge, shield, windfury));
        }
    }

    std::shuffle(m_cards.begin(), m_cards.end(), m_rnd);
}

std::vector<card> card_generator::get_deck()
{
    std::vector<card> deck;

    for(int i = 0; i < 30; ++i)
    {
        deck.push_back(m_cards.at(i));
    }

    return deck;
}
