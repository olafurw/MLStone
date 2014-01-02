#include <cxxtest/TestSuite.h>
#include <utility>
#include <vector>

#include "../deck.hpp"

class deck_tests : public CxxTest::TestSuite
{
public:
    void testCreate()
    {
        std::vector<card> cards { card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false) };

        deck d(cards);

        TS_ASSERT(d.can_draw());
    }

    void testCopy()
    {
        std::vector<card> cards { card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false) };

        deck d1(cards);
        deck d2(d1);

        TS_ASSERT_EQUALS(d1.count(), d2.count());
    }

    void testMove()
    {
        std::vector<card> cards { card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false) };

        deck d1(cards);
        deck d2(std::move(d1));

        TS_ASSERT_EQUALS(0, d1.count());
        TS_ASSERT_EQUALS(3, d2.count());
    }

    void testSize()
    {
        std::vector<card> cards { card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false) };

        deck d(cards);

        TS_ASSERT_EQUALS(3, d.count());
    }

    void testDraw()
    {
        std::vector<card> cards { card("test", 1, 2, 3, true, false, false) };

        deck d(cards);

        TS_ASSERT_EQUALS(1, d.count());

        card c = d.draw();

        TS_ASSERT_EQUALS(c, cards.at(0));
        TS_ASSERT_EQUALS(0, d.count());
        TS_ASSERT(!d.can_draw());
    }

    void testClear()
    {
        std::vector<card> cards { card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false),
                                  card("test", 1, 2, 3, true, false, false) };

        deck d(cards);

        TS_ASSERT_EQUALS(3, d.count());

        d.clear();

        TS_ASSERT_EQUALS(0, d.count());
    }
};
