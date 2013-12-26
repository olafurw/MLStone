#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>
#include <memory>

#include "../board.hpp"
#include "../player.hpp"

class board_tests : public CxxTest::TestSuite
{
public:
    void testCreate()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        TS_ASSERT_EQUALS(true, brd->alive(0));
        TS_ASSERT_EQUALS(true, brd->alive(1));
    }
};
