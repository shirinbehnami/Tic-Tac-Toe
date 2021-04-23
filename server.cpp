//server

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <cstdlib>
#include <thread>

using namespace std;
using namespace boost::asio;
using namespace ip;

class ground
{
public:

	ground(int n);

	void update_ground(int numblock, int who);
	int judge(int n);
private:
	int judge1();
	int judge2();
	int judge3();

	vector<int> blocks;
	int cntblocks;
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
}

int ground::judge(int n)
{
	/*if first player wins,return 1.
	if second player wins,return 2.
	if draw return 0.
	otherwise return 3.*/

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

	tcp::socket* get_sock();
	string get_name() { return name; };

	void set_are_connected(bool x) { are_connected = x; };

	void registration();
	string choose_opponent();
	bool send_req(string opp);
	bool accept_or_reject(bool ans);
	int choose_ground();
	void inform_chosen_ground(int n);
	void playgame(player* pl2, int n, ground g);

private:
	void read_move(player* pl, string& s);
	void after_game(player* pl2);
	void receive_ans(player* pl, player*& flag, player* firstpl, player* secondpl);
	void rematch(player* pl1, player* pl2);
	void chat(player* pl2);
	void chat_transition(player* p1, player* p2);

	string name;
	tcp::socket sock;
	static vector<string> names;
	static int are_connected;

};

//initialize
vector<string>player::names{};
int player::are_connected = false;

player::player(io_service& io_service, tcp::acceptor& acc)
	:sock(io_service)
{
	acc.accept(sock);
}

tcp::socket* player::get_sock()
{
	return &sock;
}

void player::registration()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	name = buffer_cast<const char*>(buff.data());
	name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
	names.push_back(name);
	cout << name<<endl;
}
string player::choose_opponent()
{
	string s = "two";
	s += "\n";
	write(sock, boost::asio::buffer(s));
	string msg;
	for (int i = 0; i < names.size(); i++)
		if (names[i] != name)
			msg += names[i];
	write(sock, boost::asio::buffer(msg + "\n"));


	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string opp = buffer_cast<const char*>(buff.data());
	return opp;
}
bool player::send_req(string opp)
{
	string s = "one";
	s += "\n";
	write(sock, boost::asio::buffer(s));
	write(sock, boost::asio::buffer(opp + "\n"));
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string answer = buffer_cast<const char*>(buff.data());
	if (answer == "1\n")
		return true;
	else
		return false;
}
bool player::accept_or_reject(bool ans)
{
	if (ans)
	{
		write(sock, boost::asio::buffer("1\n"));
		return true;
	}
	else
	{
		write(sock, boost::asio::buffer("0\n"));
		return false;
	}
}
int player::choose_ground()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string num = buffer_cast<const char*>(buff.data());
	return atoi(num.c_str());
}
void player::inform_chosen_ground(int n)
{

	string s = to_string(n);
	s += "\n";
	write(sock, boost::asio::buffer(s));
}

void player::playgame(player* pl2, int n, ground g)
{
	string s;
	string msg;
	int i = 3;
	while (i == 3)
	{
		try {
			this->read_move(pl2, s);
			if (s == "0\n" && are_connected)
				i = 2;
			else
			{
				g.update_ground(atoi(s.c_str()) - 1, -1);
				i = g.judge(n);
			}
			msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
		}
		catch (boost::system::system_error& e)//if a user disconnect,the other will win.
		{
			are_connected = false;
			s = "0\n";
			i = 2;
			msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
			write(*(pl2->get_sock()), boost::asio::buffer(msg));

		}
		try {
			write(*(pl2->get_sock()), boost::asio::buffer(msg));
			if (i != 3)
			{
				msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
				write(sock, boost::asio::buffer(msg));
			}
		}
		catch (boost::system::system_error& e)//if a user disconnect,the other will win.
		{
			are_connected = false;
			s = "0\n";
			i = 1;
			msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
			write(sock, boost::asio::buffer(msg));

		}

		//if the game is ended,break the loop.
		if (i != 3)
			break;

		try {
			pl2->read_move(this, s);
			if (s == "0\n" && are_connected)
				i = 1;
			else
			{
				g.update_ground(atoi(s.c_str()) - 1, -2);
				i = g.judge(n);
			}
			msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
		}
		catch (boost::system::system_error& e)//if a user disconnect,the other will win.
		{
			are_connected = false;
			s = "0\n";
			i = 1;
			msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
			write(sock, boost::asio::buffer(msg));

		}
		try {
			write(sock, boost::asio::buffer(msg));
			if (i != 3)
			{
				msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
				write(*(pl2->get_sock()), boost::asio::buffer(msg));
			}
		}
		catch (boost::system::system_error& e)//if a user disconnect,the other will win.
		{
			are_connected = false;
			s = "0\n";
			i = 2;
			msg = s + '-' + to_string(i) + '-' + to_string(are_connected);
			write(*(pl2->get_sock()), boost::asio::buffer(msg));

		}
	}
	this->after_game(pl2);
}
void player::read_move(player* pl, string& s)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	s = buffer_cast<const char*>(buff.data());
}

void player::after_game(player* pl2)
{
	player* flag = NULL;
	thread t1(&player::receive_ans, this, pl2, ref(flag), this, pl2);
	thread t2(&player::receive_ans, pl2, this, ref(flag), this, pl2);
	while (1)
	{
		if (flag == this)
		{
			t2.detach();
			t2.~thread();
			t1.join();
			break;
		}
		else if (flag == pl2)
		{
			t1.detach();
			t1.~thread();
			t2.join();
			break;
		}
	}
}
void player::receive_ans(player* pl, player*& flag, player* firstpl, player* secondpl)
{
	// Receive request of player1
	boost::asio::streambuf buff;
	read_until(this->sock, buff, "\n");
	string choice = buffer_cast<const char*>(buff.data());
	if (flag == NULL)
	{
		write(this->sock, boost::asio::buffer("welcome:)\n"));
		flag = this;
	}
	else
		return;
	//send request to player2
	write(*(pl->get_sock()), boost::asio::buffer(choice));

	if (choice != "3\n")
	{
		//Receive answer of player2
		boost::asio::streambuf buff;
		read_until(*(pl->get_sock()), buff, "\n");
		string answer = buffer_cast<const char*>(buff.data());

		//send answer to player1
		write(this->sock, boost::asio::buffer(answer));

		if (choice == "1\n" && answer == "1\n")
			rematch(secondpl, firstpl);
		else if (choice == "2\n" && answer == "1\n")
			this->chat(pl);
		else
			exit(0);
	}
	else
		exit(0);
}
void player::rematch(player* pl1, player* pl2)
{
	int num_of_ground = pl1->choose_ground();
	ground g(num_of_ground);
	pl2->inform_chosen_ground(num_of_ground);
	pl1->playgame(pl2, num_of_ground, g);
}
void player::chat(player* pl2)
{
	thread t3(&player::chat_transition, this, this, pl2);
	thread t4(&player::chat_transition, this, pl2, this);
	t3.join();
	t4.join();
}
void player::chat_transition(player* p1, player* p2)
{
	while (true) {
		boost::asio::streambuf buff;
		read_until(*(p1->get_sock()), buff, "\n");

		string recieve = buffer_cast<const char*>(buff.data());
		string send = p1->get_name() + " : " + recieve + "\n";
		cout << send;
		write(*(p2->get_sock()), boost::asio::buffer(send));
	}
}

//main function
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
	//inja ye tabe find ham mikhaim ke farz mikonim darim.

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