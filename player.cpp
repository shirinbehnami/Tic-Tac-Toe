//player
// player1:O,-1    player2:x,-2

#include "player_player.h"

int main()
{
	io_service io;
	player pl(io);
	pl.show_logo();
	pl.registeration();
	pl.choose_opponent();
	bool ans = pl.accept_or_reject();
	if (ans)
	{
		int i = pl.start_game();
		ground gr(i);
		gr.show_ground(i);
		pl.playgame(gr, i);
	}
	else
	{
		pl.goodbye();
	}
}