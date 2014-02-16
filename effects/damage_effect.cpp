#include "damage_effect.hpp"

damage_effect::damage_effect(card* p, target* t, int damage, unsigned int count):
    effect(p, t),
    m_damage(damage),
    m_count(count)
{

}

damage_effect::damage_effect(const damage_effect& e): effect(e)
{
    m_damage = e.m_damage;
    m_count = e.m_count;
}

damage_effect::damage_effect(damage_effect&& e): effect(e)
{
    m_damage = e.m_damage;
    m_count = e.m_count;
}

damage_effect::~damage_effect()
{

}

damage_effect& damage_effect::operator =(const damage_effect& e)
{
    if(this != &e)
    {
        effect::operator=(e);

        m_damage = e.m_damage;
        m_count = e.m_count;
    }

    return *this;
}

damage_effect& damage_effect::operator =(damage_effect&& e)
{
    if(this != &e)
    {
        effect::operator=(e);

        m_damage = e.m_damage;
        m_count = e.m_count;
    }

    return *this;
}

#include <iostream>

void damage_effect::process()
{
    std::cout << "a";
    if(m_count > 0)
    {
        std::cout << "b";
        m_target->take_damage(m_damage);
    }

    std::cout << "c";

    m_count--;
}
