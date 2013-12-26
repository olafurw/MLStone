#include <cxxtest/TestSuite.h>
#include <utility>

#include "../card.hpp"

class card_tests : public CxxTest::TestSuite
{
public:
    void testCreate()
    {
        card c("test", 1, 2, 3, true, false);

        TS_ASSERT_EQUALS("test", c.name());
        TS_ASSERT_EQUALS(true, c.alive());
        TS_ASSERT_EQUALS(false, c.awake());
        TS_ASSERT_EQUALS(false, c.can_attack());
        TS_ASSERT_EQUALS(1, c.mana());
        TS_ASSERT_EQUALS(2, c.damage());
        TS_ASSERT_EQUALS(3, c.health());
        TS_ASSERT_EQUALS(true, c.taunt());
        TS_ASSERT_EQUALS(false, c.charge());
    }

    void testCopy()
    {
        card a("test", 1, 2, 3, true, false);
        card c(a);

        TS_ASSERT_EQUALS(a, c);
    }

    void testMove()
    {
        card a("test", 1, 2, 3, true, false);
        card c(std::move(a));

        TS_ASSERT_EQUALS("test", c.name());
        TS_ASSERT_EQUALS(true, c.alive());
        TS_ASSERT_EQUALS(false, c.awake());
        TS_ASSERT_EQUALS(false, c.can_attack());
        TS_ASSERT_EQUALS(1, c.mana());
        TS_ASSERT_EQUALS(2, c.damage());
        TS_ASSERT_EQUALS(3, c.health());
        TS_ASSERT_EQUALS(true, c.taunt());
        TS_ASSERT_EQUALS(false, c.charge());
    }

    void testRefresh()
    {
        card c("test", 1, 2, 3, true, false);

        TS_ASSERT_EQUALS(false, c.awake());
        TS_ASSERT_EQUALS(false, c.can_attack());

        c.refresh();

        TS_ASSERT_EQUALS(true, c.awake());
        TS_ASSERT_EQUALS(true, c.can_attack());
    }

    void testCharge()
    {
        card c("test", 1, 2, 3, false, true);

        TS_ASSERT_EQUALS(true, c.awake());
        TS_ASSERT_EQUALS(true, c.can_attack());
    }

    void testAttack()
    {
        card c1("test", 1, 2, 3, false, false);
        card c2("test", 1, 2, 3, false, false);

        c1.attack(c2);

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(3, c2.health());

        c1.refresh();
        c2.refresh();

        c1.attack(c2);

        TS_ASSERT_EQUALS(1, c1.health());
        TS_ASSERT_EQUALS(1, c2.health());
    }

    void testAttackDeath()
    {
        card c1("test", 1, 2, 3, false, true);
        card c2("test", 1, 2, 1, false, false);

        c1.attack(c2);

        TS_ASSERT_EQUALS(1, c1.health());
        TS_ASSERT_EQUALS(0, c2.health());
        TS_ASSERT_EQUALS(true, c1.alive());
        TS_ASSERT_EQUALS(false, c2.alive());
    }
};