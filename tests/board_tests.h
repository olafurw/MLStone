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

    void testEmpty()
    {
        board b;

        TS_ASSERT_EQUALS(false, b.can_add(0));

        b.add(0, card("test", 1, 2, 3, false, false, false, false, false));

        TS_ASSERT_EQUALS(0, b.count(0));
        TS_ASSERT_THROWS_ANYTHING(b.at(0, 0));
        TS_ASSERT_EQUALS(false, b.is_taunt(0));
        TS_ASSERT_EQUALS(false, b.can_be_attacked(0, 0));
        TS_ASSERT_EQUALS(false, b.alive(0));
        TS_ASSERT_EQUALS(0, b.cards(0).size());
        TS_ASSERT_EQUALS(0, b.cards_can_attack(0).size());
    }

    void testAddCard()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(0, brd->count(1));

        brd->add(0, card("a", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("a", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("a", 1, 1, 1, false, false, false, false, false));

        TS_ASSERT_EQUALS(1, brd->count(0));
        TS_ASSERT_EQUALS(2, brd->count(1));
    }

    void testAttackCard()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        brd->add(0, card("a", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("a", 1, 1, 1, false, false, false, false, false));

        TS_ASSERT_EQUALS(1, brd->count(0));
        TS_ASSERT_EQUALS(1, brd->count(1));

        // Next round
        brd->refresh(0);
        brd->refresh(1);

        // Player 0's first card is attacking player 1's first card
        // They should both die
        brd->attack(0, 0, 1, 0);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(0, brd->count(1));
    }

    void testCardLists()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        brd->add(0, card("a_card", 1, 1, 1, false, false, false, false, false));
        brd->add(0, card("a_card", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("b_card", 2, 2, 2, false, false, false, false, false));

        auto card_list_one = brd->cards(0);
        auto card_list_two = brd->cards(1);

        TS_ASSERT_EQUALS(2, card_list_one.size());
        TS_ASSERT_EQUALS(1, card_list_two.size());
    }

    void testCardTaunt()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        brd->add(0, card("a_card", 3, 3, 3, false, false, false, false, false));
        brd->add(1, card("b_card", 1, 1, 1, true, false, false, false, false));
        brd->add(1, card("b_card", 2, 2, 2, false, false, false, false, false));

        TS_ASSERT_EQUALS(false, brd->is_taunt(0));
        TS_ASSERT_EQUALS(true, brd->is_taunt(1));
        TS_ASSERT_EQUALS(true, brd->can_be_attacked(0, 0));
        TS_ASSERT_EQUALS(true, brd->can_be_attacked(1, 0));
        TS_ASSERT_EQUALS(false, brd->can_be_attacked(1, 1));
    }

    void testCardRemove()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        brd->add(0, card("a_card", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("b_card", 1, 1, 1, false, false, false, false, false));

        TS_ASSERT_EQUALS(1, brd->count(0));
        TS_ASSERT_EQUALS(1, brd->count(1));

        brd->remove(0, 0);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(1, brd->count(1));

        brd->remove(1, 0);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(0, brd->count(1));

        brd->remove(0, 0);
        brd->remove(1, 0);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(0, brd->count(1));
    }

    void testBoardClear()
    {
        auto brd = std::make_shared<board>();

        std::vector<std::shared_ptr<player>> players;
        players.emplace_back(std::make_shared<player>(0, "a", 30, 0, brd));
        players.emplace_back(std::make_shared<player>(1, "b", 30, 0, brd));

        brd->add(0, card("a_card", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("b_card", 1, 1, 1, false, false, false, false, false));

        brd->clear(0);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(1, brd->count(1));

        brd->clear(1);

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(0, brd->count(1));

        brd->add(0, card("a_card", 1, 1, 1, false, false, false, false, false));
        brd->add(1, card("b_card", 1, 1, 1, false, false, false, false, false));

        TS_ASSERT_EQUALS(1, brd->count(0));
        TS_ASSERT_EQUALS(1, brd->count(1));

        brd->clear();

        TS_ASSERT_EQUALS(0, brd->count(0));
        TS_ASSERT_EQUALS(0, brd->count(1));
    }
};
