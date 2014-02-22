INCLUDE_DIRECTORIES( . .. )

SET(MLSTONE_CORE ../board.cpp ../card.cpp ../effect.cpp ../effects/give_windfury_effect.cpp ../effects/damage_effect.cpp ../effects/heal_effect.cpp ../effects/destroy_effect.cpp ../deck.cpp ../game.cpp ../player.cpp ../card_generator.cpp ../utils.cpp)

CXXTEST_ADD_TEST(card_tests card_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/card_tests.h)
CXXTEST_ADD_TEST(deck_tests deck_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/deck_tests.h)
CXXTEST_ADD_TEST(board_tests board_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/board_tests.h)
CXXTEST_ADD_TEST(player_tests player_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/player_tests.h)
CXXTEST_ADD_TEST(effect_tests effect_tests.cpp ${MLSTONE_CORE} ${CMAKE_CURRENT_SOURCE_DIR}/effect_tests.h)