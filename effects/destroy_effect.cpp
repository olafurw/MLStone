#include "destroy_effect.hpp"
#include "../card.hpp"

destroy_effect::destroy_effect(): effect()
{

}

destroy_effect::destroy_effect(const destroy_effect& e): effect(e)
{
}

destroy_effect::destroy_effect(destroy_effect&& e): effect(e)
{
}

destroy_effect::~destroy_effect()
{

}

destroy_effect& destroy_effect::operator =(const destroy_effect& e)
{
    if(this != &e)
    {
        effect::operator=(e);
    }

    return *this;
}

destroy_effect& destroy_effect::operator =(destroy_effect&& e)
{
    if(this != &e)
    {
        effect::operator=(e);
    }

    return *this;
}

void destroy_effect::process()
{
    m_parent->set_destroy(true);
}
