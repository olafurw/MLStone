#include "player.hpp"

#include <iostream>

int main()
{
	player p1("Waage", 30, 0);
	player p2("Dummy", 30, 0);

	p1.draw();
	p2.draw();

	p1.add_to_board(0);
	p2.add_to_board(0);

	p1.show_board();
	p2.show_board();

	p1.attack(0, p2.get_board(), 0);

	p1.show_board();
	p2.show_board();

	return 0;
}
