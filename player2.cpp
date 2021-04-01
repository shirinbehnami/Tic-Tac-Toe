//player2
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
	player(io_service& io_service);
	void playgame();
	void write_move();
	void read_move();
private:
	tcp::socket sock;
};

//ground class
class ground
{
public:
	ground();
	void show_ground();
	void update_ground(int numblock, int who, player* pl);
	void judge();
private:
	int blocks[9];
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
}gr;

ground::ground()
{
	for (int i = 0; i < 9; i++)
		blocks[i] = i + 1;
}
void ground::show_ground()
{
	cout << endl;
	cout << "     |     |     " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (blocks[3 * i + j] == -1)
				cout << "  O";
			else if (blocks[3 * i + j] == -2)
				cout << "  X";
			else
				cout << "  " << blocks[3 * i + j];
			if (j != 2)
			{
				cout << "  |";
			}
		}
		cout << endl;
		if (i < 2)
		{
			cout << "_____|_____|_____" << endl;
			cout << "     |     |     " << endl;
		}
	}
	cout << "     |     |     " << endl << endl;
}
void ground::update_ground(int numblock, int who, player* pl)
{
	if (blocks[numblock] == -1 || blocks[numblock] == -2)
	{
		cout << "this block is full, please select another one" << endl;
		pl->write_move();
	}
	else
	{
		blocks[numblock] = who;
	}
}
void ground::judge()
{
	for (int i = 0; i < winblocks.size(); i++)
	{
		if (blocks[winblocks[i][0]] == blocks[winblocks[i][1]] && blocks[winblocks[i][1]] == blocks[winblocks[i][2]])
		{
			if (blocks[winblocks[i][0]] == -1)
			{
				cout << " congratulations, you wiiiiiiiin :))" << endl;
				exit(0);
			}
			else
			{
				cout << "oh no, you lose:((" << endl;
				exit(0);
			}
		}
	}
	bool flag = TRUE;
	for (int i = 0; i < 9; i++)
	{
		if (blocks[i] != -1 && blocks[i] != -2)
		{
			flag = FALSE;
			break;
		}
	}
	if (flag)
	{
		cout << "Draw:)!" << endl;
		exit(0);
	}
}

//function of player class 
player::player(io_service& io_service)
	:sock(io_service)
{
	sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 1234));
}
void player::playgame()
{
	while (1)
	{
		read_move();
		write_move();
	}
}
void player::write_move()
{
	string msg;
	getline(cin, msg);
	msg += "\n";
	int num = atoi(msg.c_str());
	if (num < 1 || num>9)
	{
		cout << "This block is not exist" << endl;
		write_move();
	}
	gr.update_ground(num - 1, -1, this);
	gr.show_ground();
	write(sock, boost::asio::buffer(msg));
	gr.judge();
}
void player::read_move()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	int num = atoi(s.c_str());
	gr.update_ground(num - 1, -2, this);
	gr.show_ground();
	gr.judge();
}

//main function
int main()
{
	gr.show_ground();
	io_service io;
	player pl(io);
	pl.playgame();
}
