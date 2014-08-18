#include <cxxtest/TestSuite.h>
#include <utility>

#include "../card.hpp"

class card_tests : public CxxTest::TestSuite
{
public:
    void testCreate()
    {
        card c("test", 1, 2, 3, true, false, false, false, false);

        TS_ASSERT_EQUALS("test", c.name());
        TS_ASSERT_EQUALS(true, c.alive());
        TS_ASSERT_EQUALS(false, c.awake());
        TS_ASSERT_EQUALS(false, c.can_attack());
        TS_ASSERT_EQUALS(1, c.mana());
        TS_ASSERT_EQUALS(2, c.damage());
        TS_ASSERT_EQUALS(3, c.health());
        TS_ASSERT_EQUALS(true, c.taunt());
        TS_ASSERT_EQUALS(false, c.charge());
        TS_ASSERT_EQUALS(false, c.shield());
        TS_ASSERT_EQUALS(false, c.windfury());
    }

    void testCopy()
    {
        card a("test", 1, 2, 3, true, false, false, false, false);
        card c(a);

        TS_ASSERT_EQUALS(a, c);
    }

    void testMove()
    {
        card a("test", 1, 2, 3, true, false, false, false, false);
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
        TS_ASSERT_EQUALS(false, c.shield());
        TS_ASSERT_EQUALS(false, c.windfury());
    }

    void testRefresh()
    {
        card c("test", 1, 2, 3, true, false, false, false, false);

        TS_ASSERT_EQUALS(false, c.awake());
        TS_ASSERT_EQUALS(false, c.can_attack());

        c.refresh();

        TS_ASSERT_EQUALS(true, c.awake());
        TS_ASSERT_EQUALS(true, c.can_attack());
    }

    void testCharge()
    {
        card c("test", 1, 2, 3, false, true, false, false, false);

        TS_ASSERT_EQUALS(true, c.awake());
        TS_ASSERT_EQUALS(true, c.can_attack());
    }

    void testAttack()
    {
        card c1("test", 1, 2, 3, false, false, false, false, false);
        card c2("test", 1, 2, 3, false, false, false, false, false);

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
        card c1("test", 1, 2, 3, false, true, false, false, false);
        card c2("test", 1, 2, 1, false, false, false, false, false);

        c1.attack(c2);

        TS_ASSERT_EQUALS(1, c1.health());
        TS_ASSERT_EQUALS(0, c2.health());
        TS_ASSERT_EQUALS(true, c1.alive());
        TS_ASSERT_EQUALS(false, c2.alive());
    }

    void testAttackShield()
    {
        card c1("test", 1, 1, 3, false, true, true, false, false);
        card c2("test", 1, 1, 3, false, false, false, false, false);

        TS_ASSERT_EQUALS(true, c1.shield());
        TS_ASSERT_EQUALS(false, c2.shield());

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(3, c2.health());

        c1.attack(c2);

        TS_ASSERT_EQUALS(false, c1.shield());
        TS_ASSERT_EQUALS(false, c2.shield());

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(2, c2.health());

        c1.refresh();
        c2.refresh();

        c1.attack(c2);

        TS_ASSERT_EQUALS(2, c1.health());
        TS_ASSERT_EQUALS(1, c2.health());
    }

    void testAttackWindfury()
    {
        card c1("test", 1, 1, 5, false, false, false, true, false);
        card c2("test", 1, 1, 5, false, false, false, false, false);

        TS_ASSERT_EQUALS(true, c1.windfury());
        TS_ASSERT_EQUALS(false, c2.windfury());

        TS_ASSERT_EQUALS(5, c1.health());
        TS_ASSERT_EQUALS(5, c2.health());

        c1.refresh();
        c2.refresh();

        c1.attack(c2);
        c1.attack(c2);

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(3, c2.health());

        c1.refresh();
        c2.refresh();

        c1.attack(c2);
        c1.attack(c2);

        TS_ASSERT_EQUALS(1, c1.health());
        TS_ASSERT_EQUALS(1, c2.health());
    }

    void testGiveModifiers()
    {
        card c1("test", 1, 1, 1, false, false, false, false, false);

        TS_ASSERT_EQUALS(false, c1.taunt());
        TS_ASSERT_EQUALS(false, c1.charge());
        TS_ASSERT_EQUALS(false, c1.shield());
        TS_ASSERT_EQUALS(false, c1.windfury());

        c1.give_taunt();
        c1.give_charge();
        c1.give_shield();
        c1.give_windfury();

        TS_ASSERT_EQUALS(true, c1.taunt());
        TS_ASSERT_EQUALS(true, c1.charge());
        TS_ASSERT_EQUALS(true, c1.shield());
        TS_ASSERT_EQUALS(true, c1.windfury());
    }
};
