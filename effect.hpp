#ifndef MLSTONE_EFFECT
#define MLSTONE_EFFECT

#include "target.hpp"

class card;

class effect
{
public:
    effect(card* p, target* t);
    effect(const effect& e);
    effect(effect&& e);

    virtual ~effect();

    effect& operator =(const effect& e);
    effect& operator =(effect&& e);

    virtual void process(){};

    void set_target(target* t);
    target* get_target();

protected:
    target* m_target;
    card* m_parent;
};

#endif
