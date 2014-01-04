#include "game.hpp"

int main()
{
    srand(time(NULL));

	int game_count = 0;
	int win_count = 0;

	for(int i = 0; i < 10000; ++i)
	{
		game g;
		int winner = g.play();

		if(winner == 1)
		{
			win_count++;
		}

		game_count++;
	}

	std::cout << win_count << std::endl;
	std::cout << game_count << std::endl;

	return 0;
}
