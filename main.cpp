#include "game.hpp"
#include "card_generator.hpp"

int main()
{
    srand(time(NULL));

    while(true)
    {
        card_generator cg;

        int game_count = 0;
        int win_count = 0;

        for(int i = 0; i < 1000; ++i)
        {
            game g(cg);
            int winner = g.play();

            if(winner == 1)
            {
                win_count++;
            }

            game_count++;
        }

        //if(win_count > 498 && win_count < 502)
        {
            std::cout << win_count << std::endl;
            std::cout << game_count << std::endl;
        }
    }

	return 0;
}
