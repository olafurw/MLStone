#ifndef MLSTONE_DESTROY_EFFECT
#define MLSTONE_DESTROY_EFFECT

#include "../effect.hpp"

class destroy_effect : public effect
{
public:
    destroy_effect();
    destroy_effect(const destroy_effect& e);
    destroy_effect(destroy_effect&& e);

    virtual ~destroy_effect();

    destroy_effect& operator =(const destroy_effect& e);
    destroy_effect& operator =(destroy_effect&& e);

    virtual void process();
};

#endif
