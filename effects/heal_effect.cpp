#include "heal_effect.hpp"

heal_effect::heal_effect(int health, unsigned int count):
    effect(),
    m_health(health),
    m_count(count)
{

}

heal_effect::heal_effect(const heal_effect& e): effect(e)
{
    m_health = e.m_health;
    m_count = e.m_count;
}

heal_effect::heal_effect(heal_effect&& e): effect(e)
{
    m_health = e.m_health;
    m_count = e.m_count;
}

heal_effect::~heal_effect()
{

}

heal_effect& heal_effect::operator =(const heal_effect& e)
{
    if(this != &e)
    {
        effect::operator=(e);

        m_health = e.m_health;
        m_count = e.m_count;
    }

    return *this;
}

heal_effect& heal_effect::operator =(heal_effect&& e)
{
    if(this != &e)
    {
        effect::operator=(e);

        m_health = e.m_health;
        m_count = e.m_count;
    }

    return *this;
}

void heal_effect::process()
{
    if(!m_target)
    {
        return;
    }

    if(m_count > 0)
    {
        m_target->give_health(m_health);
    }

    m_count--;
}
