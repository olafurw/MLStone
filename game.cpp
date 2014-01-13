#include "game.hpp"

game::game(card_generator& cg)
{
	m_board = std::make_shared<board>();

	m_players.emplace_back(std::make_shared<player>(0, "Waage", 30, 0, m_board, cg.get_deck()));
	m_players.emplace_back(std::make_shared<player>(1, "Maria", 30, 0, m_board, cg.get_deck()));
}

int game::play()
{
	int round = 0;

	m_players.at(0)->draw();
	m_players.at(0)->draw();
	m_players.at(0)->draw();

	m_players.at(1)->draw();
	m_players.at(1)->draw();
	m_players.at(1)->draw();

	// Game loop
	while(true)
	{
		round++;

		// Make them take turns
		for(auto& player : m_players)
		{
			// Awake all the minions on that players side.
			// Also enable them to attack
			m_board->refresh(player->id());

			// Do the player actions
			player->update();
		}

		// Game is over
		for(auto& player : m_players)
		{
			if(!player->alive())
			{
				return player->enemy_id();
			}
		}
	}
}
