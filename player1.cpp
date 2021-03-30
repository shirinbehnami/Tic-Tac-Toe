//second player
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

using namespace std;
using namespace boost::asio;
using namespace ip;

//functions
void init_ground(char ground[3][3]);
void update_ground(char ground[3][3], string s, int c);
void show_ground(char ground[3][3]);
void judge(char ground[3][3]);

int main()
{
	io_service io;
	tcp::socket sock(io);
	sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 1234));
	char ground[3][3];
	init_ground(ground);
	show_ground(ground);
	while (1)
	{
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		string s = buffer_cast<const char*>(buff.data());
		update_ground(ground, s, 0);
		show_ground(ground);
		judge(ground);


		string msg;
		getline(cin, msg);
		msg += "\n";
		update_ground(ground, msg, 1);
		show_ground(ground);
		judge(ground);
		write(sock, boost::asio::buffer(msg));


	}



	//second

	//thread t1(sendTo, ref(sock));
	//thread t2(receiveFrom, ref(sock));

	//t1.join();
	//t2.join();


}
void init_ground(char ground[3][3])
{
	char c = '1';
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ground[i][j] = c;
			c++;
		}
	}
}
void update_ground(char ground[3][3], string s, int c)
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
			cout << ground[i][j] << "  ";
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
			exit(0);
		}
		if (ground[i][0] == ground[i][1] && ground[i][0] == ground[i][2] && ground[i][0] == '*')
		{
			cout << "* won!" << endl;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (ground[0][i] == ground[1][i] && ground[0][i] == ground[2][i] && ground[0][i] == '#')
		{
			cout << "# won!" << endl;
			exit(0);
		}
		if (ground[0][i] == ground[1][i] && ground[0][i] == ground[2][i] && ground[0][i] == '*')
		{
			cout << "* won!" << endl;
		}
	}
	if (ground[0][0] == ground[1][1] && ground[0][0] == ground[2][2] && ground[0][0] == '#')
	{
		cout << "# won!" << endl;
		exit(0);
	}
	if (ground[0][0] == ground[1][1] && ground[0][0] == ground[2][2] && ground[0][0] == '*')
	{
		cout << "* won!" << endl;
	}

	if (ground[0][2] == ground[1][1] && ground[2][0] == ground[1][1] && ground[1][1] == '#')
	{
		cout << "# won!" << endl;
		exit(0);
	}
	if (ground[0][2] == ground[1][1] && ground[2][0] == ground[1][1] && ground[1][1] == '*')
	{
		cout << "* won!" << endl;
	}
	bool flag = TRUE;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!(ground[i][j] == '*' || ground[i][j] == '#'))
			{
				flag = FALSE;
				break;
			}
		}
		if (!flag)
			break;
	}
	if (flag)
	{
		cout << "Draw:)!" << endl;
		//exit(0);
	}
}