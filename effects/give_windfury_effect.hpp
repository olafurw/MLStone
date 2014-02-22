#ifndef MLSTONE_GIVE_WINDFURY_EFFECT
#define MLSTONE_GIVE_WINDFURY_EFFECT

#include "../effect.hpp"

class give_windfury_effect : public effect
{
public:
    give_windfury_effect();
    give_windfury_effect(const give_windfury_effect& e);
    give_windfury_effect(give_windfury_effect&& e);

    virtual ~give_windfury_effect();

    give_windfury_effect& operator =(const give_windfury_effect& e);
    give_windfury_effect& operator =(give_windfury_effect&& e);

    virtual void process();
};

#endif
