INCLUDE_DIRECTORIES( . .. )

SET(MLSTONE_CORE ../board.cpp ../card.cpp ../deck.cpp ../game.cpp ../player.cpp ../utils.cpp)

CXXTEST_ADD_TEST(card_tests card_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/card_tests.h)
CXXTEST_ADD_TEST(deck_tests deck_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/deck_tests.h)