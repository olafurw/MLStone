INCLUDE_DIRECTORIES( . .. )

SET(MLSTONE_CORE ../board.cpp ../card.cpp ../deck.cpp ../game.cpp ../player.cpp ../utils.cpp)

CXXTEST_ADD_TEST(card_tests card_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/card_tests.h)
CXXTEST_ADD_TEST(deck_tests deck_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/deck_tests.h)
CXXTEST_ADD_TEST(board_tests board_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/board_tests.h)
CXXTEST_ADD_TEST(player_tests player_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/player_tests.h)