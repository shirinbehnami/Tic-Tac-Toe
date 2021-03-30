#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace ip;

char msg[200];
void sendTo(tcp::socket& sock)
{
	while (1) {
		string s;
		getline(cin, s);
		s += msg;
		write(sock, boost::asio::buffer(s));
	}
}


void receiveFrom(tcp::socket& sock)
{
	while (1) {
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		strcpy_s(msg,buffer_cast<const char*>(buff.data()));
	}
}



int main()
{
	//first
	io_service io;
	tcp::socket server_sock(io);
	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
	acc.accept(server_sock);
	thread t1(sendTo, ref(server_sock));
	thread t2(receiveFrom, ref(server_sock));

	tcp::socket server_sock2(io);
	tcp::acceptor acc2(io, tcp::endpoint(tcp::v4(), 1234));
	acc.accept(server_sock2);
	thread t3(sendTo, ref(server_sock2));
	thread t4(receiveFrom, ref(server_sock2));
	


	t1.join();
	t2.join();
	t3.join();
	t4.join();

}