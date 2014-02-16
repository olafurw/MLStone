#include "effect.hpp"
#include "card.hpp"

effect::effect(card* p, target* t):
    m_parent(p),
    m_target(t)
{
}

effect::effect(const effect& e)
{
    m_parent = e.m_parent;
    m_target = e.m_target;
}

effect::effect(effect&& e)
{
    m_parent = e.m_parent;
    m_target = e.m_target;
}

effect::~effect()
{

}

effect& effect::operator =(const effect& e)
{
    if(this != &e)
    {
        m_parent = e.m_parent;
        m_target = e.m_target;
    }

    return *this;
}

effect& effect::operator =(effect&& e)
{
    if(this != &e)
    {
        m_parent = e.m_parent;
        m_target = e.m_target;
    }

    return *this;
}

void effect::set_target(target* t)
{
    m_target = t;
}

target* effect::get_target()
{
    return m_target;
}
