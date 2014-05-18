#include "game.hpp"
#include "card_generator.hpp"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    bool run = true;
    
    while(run)
    {
        card_generator cg;

        int game_count = 0;
        int win_count = 0;

        for(int i = 0; i < 1000; ++i)
        {
            game g(cg);
            unsigned int winner = g.play();

            if(winner == 1)
            {
                win_count++;
            }

            game_count++;
        }


        std::cout << win_count << std::endl;
        std::cout << game_count << std::endl;

        if(win_count > 495 && win_count < 505)
        {
            cg.print_deck();
            std::cout << "-----------" << std::endl;
        }
    }

	return 0;
}
