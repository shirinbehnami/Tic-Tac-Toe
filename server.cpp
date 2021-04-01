//server
// player1:O,-1    player2:x,-2
#include <iostream>
#include <boost/asio.hpp>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace ip;

//player class 
class player
{
public:
	player(io_service& io_service, tcp::acceptor& acc);
	void playgame(player* pl2);
	void read_move(player* pl);
	tcp::socket* get_sock();
private:
	tcp::socket sock;
};

player::player(io_service& io_service, tcp::acceptor& acc)
	:sock(io_service)
{
	acc.accept(sock);
}
tcp::socket* player::get_sock()
{
	return &sock;
}
void player::playgame(player* pl2)
{
	while (1)
	{
		this->read_move(pl2);
		pl2->read_move(this);
	}
}
void player::read_move(player* pl)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	write(*(pl->get_sock()), boost::asio::buffer(s));
}

//main function
int main()
{
	io_service io;
	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
	player pl1(io, acc);

	player pl2(io, acc);
	pl1.playgame(&pl2);
}