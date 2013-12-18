#include <memory>

#include "board.hpp"
#include "player.hpp"

class game
{
public:
	game();
private:
	std::shared_ptr<board> m_board;

	std::shared_ptr<player> m_player_1;
	std::shared_ptr<player> m_player_2;
};
