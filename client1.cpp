#include <iostream>
#include <boost/asio.hpp>
#include <thread>

using namespace std;
using namespace boost::asio;
using namespace ip;

void receiveFrom(tcp::socket& sock)
{
	while (1) {
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		cout << "Server: " << buffer_cast<const char*>(buff.data());
	}
}

void sendTo(tcp::socket& sock)
{
	while (1) {
		string msg;
		getline(cin, msg);
		msg += "\n";
		write(sock, boost::asio::buffer(msg));
	}
}

int main()
{
	io_service io;
	tcp::socket sock(io);
	sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 1234));


	while (1)
	{
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		cout << "Narges: " << buffer_cast<const char*>(buff.data());
		string msg;
		getline(cin, msg);
		msg += "\n";
		write(sock, boost::asio::buffer(msg));


	}




}