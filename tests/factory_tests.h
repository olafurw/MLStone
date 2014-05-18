#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>
#include <memory>

#include <factories/factories.hpp>

class factory_tests : public CxxTest::TestSuite
{
public:
    void testCreate()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));
        
        card c = factory::create_damage_spell("super fireball", 1, 30, players.at(1).get());
        
        brd->add(0, c);
        
        TS_ASSERT_EQUALS(0, brd->count(0));
        
        TS_ASSERT_EQUALS(0, players.at(1)->health());
        TS_ASSERT_EQUALS(false, players.at(1)->alive());
        
        TS_ASSERT_EQUALS(30, players.at(0)->health());
        TS_ASSERT_EQUALS(true, players.at(0)->alive());
    }
};
