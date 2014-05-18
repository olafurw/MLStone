#ifndef MLSTONE_HEAL_EFFECT
#define MLSTONE_HEAL_EFFECT

#include "../effect.hpp"

class heal_effect : public effect
{
public:
    heal_effect(int health, unsigned int count);
    heal_effect(const heal_effect& e);
    heal_effect(heal_effect&& e);

    virtual ~heal_effect();

    heal_effect& operator =(const heal_effect& e);
    heal_effect& operator =(heal_effect&& e);

    virtual void process();

private:
    int m_health;
    unsigned int m_count;
};

#endif
