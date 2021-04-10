//server
// player1:O,-1    player2:x,-2
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace boost::asio;
using namespace ip;
//ground class
class ground
{
public:
	ground(int n);
	void update_ground(int numblock, int who);
	int judge(int n);
private:
	vector<int> blocks;
	int cntblocks;
	int judge1();
	int judge2();
	int judge3();
};
ground::ground(int n)
{
	switch (n) {
	case 1:
		cntblocks = 9;
		break;
	case 2:
		cntblocks = 16;
		break;
	case 3:
		cntblocks = 24;
		break;

	}
	for (int i = 0; i < cntblocks; i++)
		blocks.push_back(i + 1);
}
void ground::update_ground(int numblock, int who)
{
	blocks[numblock] = who;
	//cout << blocks[numblock] << numblock;
}


//if first player wins,return 1.
//if second player wins,return 2.
//if draw return 0.
//otherwise return 3.
int ground::judge(int n)
{
	int i = -2;
	switch (n) {
	case 1:
		i = judge1();
		break;
	case 2:
		i = judge2();
		break;
	case 3:
		i = judge3();
		break;

	}
	//cout << i << endl;
	return i;
}
int ground::judge1()
{
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	for (int i = 0; i < winblocks.size(); i++)
		if (blocks[winblocks[i][0]] == blocks[winblocks[i][1]] && blocks[winblocks[i][0]] == blocks[winblocks[i][2]])
			if (blocks[winblocks[i][0]] == -1)
				return 1;
			else
				return 2;
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
		return 0;



	return 3;
}
int ground::judge2()
{
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{10,11,12},{13,14,15},{0,6,13},{3,7,10},{5,8,12},{2,9,15} };
	for (int i = 0; i < winblocks.size(); i++)
		if (blocks[winblocks[i][0]] == blocks[winblocks[i][1]] && blocks[winblocks[i][0]] == blocks[winblocks[i][2]])
			if (blocks[winblocks[i][0]] == -1)
				return 1;
			else
				return 2;
	bool flag = TRUE;
	for (int i = 0; i < 16; i++)
	{
		if (blocks[i] != -1 && blocks[i] != -2)
		{
			flag = FALSE;
			break;
		}
	}
	if (flag)
		return 0;
	return 3;
}
int ground::judge3()
{
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{6,7,8},{9,10,11},{12,13,14},{15,16,17},{18,19,20},{21,22,23}
									,{0,9,21},{3,10,18},{6,11,15},{1,4,7},{16,19,22},{8,12,17},{5,13,20},{2,14,23}
									,{0,3,6},{2,5,8},{17,20,23},{15,18,21} };
	for (int i = 0; i < winblocks.size(); i++)
		if (blocks[winblocks[i][0]] == blocks[winblocks[i][1]] && blocks[winblocks[i][0]] == blocks[winblocks[i][2]])
			if (blocks[winblocks[i][0]] == -1)
				return 1;
			else
				return 2;
	bool flag = TRUE;
	for (int i = 0; i < 24; i++)
	{
		if (blocks[i] != -1 && blocks[i] != -2)
		{
			flag = FALSE;
			break;
		}
	}
	if (flag)
		return 0;
	return 3;
}

//player class 
class player
{
public:
	player(io_service& io_service, tcp::acceptor& acc);
	void playgame(player* pl2, int n, ground g);
	void read_move(player* pl, string& s);
	tcp::socket* get_sock();
	int choose_ground();
	void inform_chosen_ground(int n);

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
void player::playgame(player* pl2, int n, ground g)
{
	string s;
	string msg;
	int i = 3;
	while (1)
	{
		this->read_move(pl2, s);
		if (s == "0\n")
			i = 2;
		else
		{
			g.update_ground(atoi(s.c_str()) - 1, -1);
			i = g.judge(n);
		}
		msg = s + '-' + to_string(i);
		write(*(pl2->get_sock()), boost::asio::buffer(msg));
		if (i != 3)
		{
			msg = s + '-' + to_string(i);
			write(sock, boost::asio::buffer(msg));
		}


		pl2->read_move(this, s);
		if (s == "0\n")
			i = 1;
		else
		{
			g.update_ground(atoi(s.c_str()) - 1, -2);
			i = g.judge(n);
		}
		msg = s + '-' + to_string(i);
		write(sock, boost::asio::buffer(msg));
		if (i != 3)
		{
			msg = s + '-' + to_string(i);
			write(*(pl2->get_sock()), boost::asio::buffer(msg));
		}
	}
}
void player::read_move(player* pl, string& s)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	s = buffer_cast<const char*>(buff.data());
}
int player::choose_ground()
{
	boost::asio::streambuf buff;
	string s = "one";
	s += "\n";
	write(sock, boost::asio::buffer(s));
	read_until(sock, buff, "\n");
	string num = buffer_cast<const char*>(buff.data());
	return atoi(num.c_str());
}
void player::inform_chosen_ground(int n)
{
	string s = "two";
	s += "\n";
	write(sock, boost::asio::buffer(s));
	s = to_string(n);
	s += "\n";
	write(sock, boost::asio::buffer(s));
}

//main function
int main()
{
	io_service io;
	tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
	player pl1(io, acc);
	player pl2(io, acc);
	int num_of_ground = pl1.choose_ground();
	ground g(num_of_ground);
	pl2.inform_chosen_ground(num_of_ground);
	pl1.playgame(&pl2, num_of_ground, g);
}