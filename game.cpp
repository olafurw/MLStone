#include "game.hpp"

game::game()
{
	m_board = std::make_shared<board>();

	m_players.emplace_back(std::make_shared<player>(0, "Waage", 30, 0, m_board));
	m_players.emplace_back(std::make_shared<player>(1, "Maria", 30, 0, m_board));
}

int game::play()
{
	int round = 0;

	// Game loop
	while(true)
	{
		round++;

		//std::cout << "--- Round " << round << " ---" << std::endl;

		// Make them take turns
		for(auto& player : m_players)
		{
			// Awake all the minions on that players side.
			// Also enable them to attack
			m_board->refresh(player->id());

			// Do the player actions
			player->update();

			// Display the result
			/*std::cout << *player << std::endl;
			player->show_hand();
			std::cout << std::endl;*/
		}

		// Display the board
		/*std::cout << "Board" << std::endl;
		std::cout << std::endl;
		std::cout << *m_board << std::endl;*/

		for(auto& player : m_players)
		{
			if(!player->alive())
			{
				return player->enemy_id();
			}
		}
	}
}
