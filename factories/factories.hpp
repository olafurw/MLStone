#ifndef MLSTONE_FACTORIES
#define MLSTONE_FACTORIES

#include <player.hpp>
#include <card.hpp>
#include <effects/damage_effect.hpp>
#include <effects/destroy_effect.hpp>

namespace factory
{
    card create_damage_spell(const std::string& name,
                             int mana,
                             int damage,
                             target* const target);
}

#endif
