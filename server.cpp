//server

#include "server_player.h"

int main()
{
	io_service io;
	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
	player pl1(io, acc);
	pl1.registration();
	player pl2(io, acc);
	pl2.registration();
	pl2.set_are_connected(true);
	string opp = pl2.choose_opponent();

	bool answer = pl1.send_req(pl2.get_name());
	pl1.accept_or_reject(answer);
	pl2.accept_or_reject(answer);

	if (answer == true)
	{
		int num_of_ground = pl1.choose_ground();
		ground g(num_of_ground);
		pl2.inform_chosen_ground(num_of_ground);
		pl1.playgame(&pl2, num_of_ground, g);
	}
	else
		exit(0);
}