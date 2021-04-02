//player2
// player1:O,-1    player2:x,-2
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <iomanip>

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

//ground1 class
class ground1
{
public:
	ground1();
	void show_ground();
	void update_ground(int numblock, int who, player* pl);
	void judge();
private:
	int blocks[9];
	int cntblocks;
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
}gr;

ground1::ground1()
{
	cntblocks = sizeof(blocks) / sizeof(blocks[0]);
	for (int i = 0; i < cntblocks; i++)
		blocks[i] = i + 1;
}
void ground1::show_ground()
{
	vector<string> showground;

	for (int i = 0; i < cntblocks; i++)
	{
		if (blocks[i] == -1)
			showground.push_back("O");
		else if (blocks[i] == -2)
			showground.push_back("X");
		else
			showground.push_back(to_string(blocks[i]));
	}
	cout << endl;
	cout << "     |     |     " << endl;
	cout << "  " << left << showground[0] << "  |  " << showground[1] << "  |  " << showground[2] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << showground[3] << "  |  " << showground[4] << "  |  " << showground[5] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << showground[6] << "  |  " << showground[7] << "  |  " << showground[8] << endl;
	cout << "     |     |     " << endl << endl;
}
void ground1::update_ground(int numblock, int who, player* pl)
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
void ground1::judge()
{
	for (int i = 0; i < winblocks.size(); i++)
	{
		if (blocks[winblocks[i][0]] == blocks[winblocks[i][1]] && blocks[winblocks[i][1]] == blocks[winblocks[i][2]])
		{
			if (blocks[winblocks[i][0]] == -2)
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

//ground2 class
class ground2
{
public:
	ground2();
	void show_ground();
	void update_ground(int numblock, int who, player* pl);
	void judge();
private:
	int blocks[16];
	int cntblocks;
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{10,11,12},{13,14,15},{0,6,13},{3,7,10},{5,8,12},{2,9,15} };
}gr1;

ground2::ground2()
{
	cntblocks = sizeof(blocks) / sizeof(blocks[0]);
	for (int i = 0; i < cntblocks; i++)
		blocks[i] = i + 1;
}
void ground2::show_ground()
{
	vector<string> showground;

	for (int i = 0; i < cntblocks; i++)
	{
		if (blocks[i] == -1)
			showground.push_back("O");
		else if (blocks[i] == -2)
			showground.push_back("X");
		else
			showground.push_back(to_string(blocks[i]));
	}
	cout << endl;
	cout << " " << left << showground[0] << " _____ " << showground[1] << " _____ " << showground[2] << endl;
	cout << " |       |       |" << endl;
	cout << " |  " << showground[3] << "  _ " << showground[4] << " _  " << showground[5] << "  |" << endl;
	cout << " |  |         |  |" << endl;
	cout << " " << showground[6] << "__" << showground[7] << "         " << showground[8] << "__" << showground[9] << endl;
	cout << " |  |         |  |" << endl;
	cout << " |  " << setw(2) << showground[10] << " _ " << setw(2) << showground[11] << " _ " << setw(2) << showground[12] << " |" << endl;
	cout << " |       |       |" << endl;
	cout << " " << setw(2) << showground[13] << " ____ " << setw(2) << showground[14] << "_____ " << showground[15] << endl;
}
void ground2::update_ground(int numblock, int who, player* pl)
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
void ground2::judge()
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
	gr.update_ground(num - 1, -2, this);
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
	gr.update_ground(num - 1, -1, this);
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
