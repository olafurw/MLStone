#ifndef MLSTONE_CARD_GENERATOR
#define MLSTONE_CARD_GENERATOR

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#include "utils.hpp"
#include "card.hpp"

class card_generator
{
public:
    card_generator();

    std::vector<card> get_deck();
    void print_deck();

private:
    std::mt19937 m_rnd;
    std::vector<card> m_cards;
};

#endif
