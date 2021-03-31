#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace ip;


int main()
{
	io_service io;
	tcp::socket server_sock(io);
	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
	acc.accept(server_sock);

	tcp::socket server_sock2(io);
	tcp::acceptor acc2(io, tcp::endpoint(tcp::v4(), 1234));
	acc.accept(server_sock2);

	while (1)
	{
		string msg;
		boost::asio::streambuf buff;
		read_until(server_sock, buff, "\n");
		msg=buffer_cast<const char*>(buff.data());

		write(server_sock2, boost::asio::buffer(msg));

		msg = "";
		boost::asio::streambuf buff2;
		read_until(server_sock2, buff2, "\n");
		msg=buffer_cast<const char*>(buff2.data());

		write(server_sock, boost::asio::buffer(msg));
	}




}