#include <factories/factories.hpp>

namespace factory
{
    
card create_damage_spell(const std::string& name,
                         int mana,
                         int damage,
                         target* const target)
{
    card c(name, mana, 0, 1, false, false, false, false);
    
    auto destroy_e = std::make_shared<destroy_effect>();
    auto damage_e = std::make_shared<damage_effect>(damage, 1);
    damage_e->set_target(target);

    c.add_battle_cry(destroy_e);
    c.add_battle_cry(damage_e);
    
    return c;
}

}
