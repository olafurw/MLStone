#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>
#include <memory>

#include "../card.hpp"
#include "../effect.hpp"
#include "../effects/damage_effect.hpp"

class effect_tests : public CxxTest::TestSuite
{
public:
    void testDamageBattleCry()
    {
        card c1("test", 1, 2, 3, true, false, false, false);
        card c2("test", 1, 2, 3, true, false, false, false);

        damage_effect de(&c1, &c2, 1, 1);

        c1.add_battle_cry(de);

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(3, c2.health());

        c1.process_battle_cry();

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(2, c2.health());
    }
};
