#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>
#include <memory>

#include "../board.hpp"
#include "../player.hpp"
#include "../card.hpp"
#include "../effect.hpp"
#include "../effects/destroy_effect.hpp"
#include "../effects/damage_effect.hpp"
#include "../effects/heal_effect.hpp"

class effect_tests : public CxxTest::TestSuite
{
public:
    void testDamageBattleCry()
    {
        card c1("test", 1, 2, 3, true, false, false, false);
        card c2("test", 1, 2, 3, true, false, false, false);

        auto de = std::make_shared<damage_effect>(1, 1);
        de->set_target(&c2);

        c1.add_battle_cry(de);

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(3, c2.health());

        c1.process_battle_cry();

        TS_ASSERT_EQUALS(3, c1.health());
        TS_ASSERT_EQUALS(2, c2.health());
    }

    void testDestroyEffect()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        TS_ASSERT_EQUALS(0, brd->count(0));

        card c("a", 1, 1, 1, false, false, false, false);

        c.add_battle_cry(std::make_shared<destroy_effect>());

        brd->add(0, c);

        TS_ASSERT_EQUALS(0, brd->count(0));
    }

    void testFireballSpell()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(30, players.at(1)->health());
        TS_ASSERT_EQUALS(30, players.at(0)->health());

        card c("fireball", 1, 1, 1, false, false, false, false);

        auto destroy = std::make_shared<destroy_effect>();
        auto damage = std::make_shared<damage_effect>(10, 1);
        damage->set_target(players.at(1).get());

        c.add_battle_cry(destroy);
        c.add_battle_cry(damage);

        brd->add(0, c);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(20, players.at(1)->health());
        TS_ASSERT_EQUALS(30, players.at(0)->health());
    }

    void testHealingSpell()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(30, players.at(1)->health());
        TS_ASSERT_EQUALS(30, players.at(0)->health());

        card c1("fireball", 1, 1, 1, false, false, false, false);

        auto destroy1 = std::make_shared<destroy_effect>();
        auto damage = std::make_shared<damage_effect>(10, 1);
        damage->set_target(players.at(1).get());

        c1.add_battle_cry(destroy1);
        c1.add_battle_cry(damage);

        brd->add(0, c1);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(20, players.at(1)->health());
        TS_ASSERT_EQUALS(30, players.at(0)->health());

        card c2("healing", 1, 1, 1, false, false, false, false);

        auto destroy2 = std::make_shared<destroy_effect>();
        auto heal = std::make_shared<heal_effect>(5, 1);
        heal->set_target(players.at(1).get());

        c2.add_battle_cry(destroy2);
        c2.add_battle_cry(heal);

        brd->add(0, c2);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(25, players.at(1)->health());
        TS_ASSERT_EQUALS(30, players.at(0)->health());
    }
};
