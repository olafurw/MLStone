#include "give_windfury_effect.hpp"
#include "../card.hpp"

give_windfury_effect::give_windfury_effect(): effect()
{

}

give_windfury_effect::give_windfury_effect(const give_windfury_effect& e): effect(e)
{
}

give_windfury_effect::give_windfury_effect(give_windfury_effect&& e): effect(e)
{
}

give_windfury_effect::~give_windfury_effect()
{

}

give_windfury_effect& give_windfury_effect::operator =(const give_windfury_effect& e)
{
    if(this != &e)
    {
        effect::operator=(e);
    }

    return *this;
}

give_windfury_effect& give_windfury_effect::operator =(give_windfury_effect&& e)
{
    if(this != &e)
    {
        effect::operator=(e);
    }

    return *this;
}

void give_windfury_effect::process()
{
    if(m_target->m_type == target::type::card)
    {
        card* target = static_cast<card*>(m_target);

        target->give_windfury();
    }
}
