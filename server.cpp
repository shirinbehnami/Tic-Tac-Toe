//server
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace ip;

//functions
void init_ground(char ground[3][3]);
void update_ground(char ground[3][3],string s,int c);
void show_ground(char ground[3][3]);
void judge(char ground[3][3]);

int main()
{
	//first
	io_service io;
	tcp::socket server_sock(io);
	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
	acc.accept(server_sock);
	char ground[3][3];
	init_ground(ground);
	show_ground(ground);

	while (1)
	{
		
		boost::asio::streambuf buff;
		read_until(server_sock, buff, "\n");
		string s=buffer_cast<const char*>(buff.data());
		update_ground(ground,s,1);
		show_ground(ground);
		judge(ground);

		string msg;
		getline(cin, msg);
		msg += "\n";
		update_ground(ground, msg, 0);
		show_ground(ground);
		write(server_sock, boost::asio::buffer(msg));
		judge(ground);
	}



	//second

	//thread t1(sendTo, ref(server_sock));
	//thread t2(receiveFrom, ref(server_sock));

	//t1.join();
	//t2.join();

}
void init_ground(char ground[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j <3; j++)
			ground[i][j] =(char) 3 * (i + 1)+(j-2)+48;
	}
}
void update_ground(char ground[3][3], string s,int c)
{
	int num = atoi(s.c_str());
	int i;
	int j;
	if (num % 3 == 0)
	{
		j = 2;
		i = num / 3 - 1;
	}
	else
	{
		j = (num % 3) - 1;
		i = (num / 3);
	}
	if (c == 0)
		ground[i][j] = '#';
	else
		ground[i][j] = '*';

}
void show_ground(char ground[3][3])
{
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << ground[i][j]<<"  ";
		cout << endl;
	}
}
void judge(char ground[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		if (ground[i][0] == ground[i][1] && ground[i][0] == ground[i][2] && ground[i][0] == '#')
		{
			cout << "# won!" << endl;
		}
		if (ground[i][0] == ground[i][1] && ground[i][0] == ground[i][2] && ground[i][0] == '*')
		{
			cout << "* won!" << endl;
			exit(0);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (ground[0][i] == ground[1][i] && ground[0][i] == ground[2][i] && ground[0][i] == '#')
		{
			cout << "# won!" << endl;
		}
		if (ground[0][i] == ground[1][i] && ground[0][i] == ground[2][i] && ground[0][i] == '*')
		{
			cout << "* won!" << endl;
			exit(0);
		}
	}
	if (ground[0][0] == ground[1][1] && ground[0][0] == ground[2][2] && ground[0][0] == '#')
	{
		cout << "# won!" << endl;
	}
	if (ground[0][0] == ground[1][1] && ground[0][0] == ground[2][2] && ground[0][0] == '*')
	{
		cout << "* won!" << endl;
		exit(0);
	}

	if (ground[0][2] == ground[1][1] && ground[2][0] == ground[1][1] && ground[1][1] == '#')
	{
		cout << "# won!" << endl;
	}
	if (ground[0][2] == ground[1][1] && ground[2][0] == ground[1][1] && ground[1][1] == '*')
	{
		cout << "* won!" << endl;
		exit(0);
	}
}