#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>

#include "../player.hpp"

class player_test : public CxxTest::TestSuite
{
public:
    void testCreate()
    {
        auto brd = std::make_shared<board>();

        std::vector<card> cards { card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false) };

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd, cards));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd, cards));

        auto player_1 = players.at(0);
        auto player_2 = players.at(1);

        TS_ASSERT_EQUALS(0, player_1->id());
        TS_ASSERT_EQUALS(1, player_2->id());

        TS_ASSERT_EQUALS(1, player_1->enemy_id());
        TS_ASSERT_EQUALS(0, player_2->enemy_id());

        TS_ASSERT_EQUALS("a", player_1->name());
        TS_ASSERT_EQUALS("b", player_2->name());

        TS_ASSERT_EQUALS(true, player_1->alive());
        TS_ASSERT_EQUALS(true, player_2->alive());
    }
};
