#ifndef MLSTONE_TARGET
#define MLSTONE_TARGET

class target
{
public:
    enum class type
    {
        card,
        player
    };

    target(target::type t): m_type(t)
    {

    }

    virtual ~target(){}

    virtual void take_damage(int damage) = 0;
    virtual void give_health(int health) = 0;

    target::type m_type;
};



#endif
