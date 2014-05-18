#ifndef MLSTONE_DAMAGE_EFFECT
#define MLSTONE_DAMAGE_EFFECT

#include "../effect.hpp"

class damage_effect : public effect
{
public:
    damage_effect(int damage, unsigned int count);
    damage_effect(const damage_effect& e);
    damage_effect(damage_effect&& e);

    virtual ~damage_effect();

    damage_effect& operator =(const damage_effect& e);
    damage_effect& operator =(damage_effect&& e);

    virtual void process();

private:
    int m_damage;
    unsigned int m_count;
};

#endif
