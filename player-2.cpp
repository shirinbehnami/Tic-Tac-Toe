//player1
// player1:O,-1    player2:x,-2
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <iomanip>

using namespace std;
using namespace boost::asio;
using namespace ip;


//ground class
class ground
{
public:
	ground(int n);
	void show_ground(int n);
	void show_ground_timer(int n, int& flag);
	void update_ground(int numblock, int who);
	int get_block(int i) { return blocks[i]; }
	int get_cnt() { return cntblocks; }
private:
	void displayClock(int sec);
	vector<int> blocks;
	int cntblocks;
	void show_ground1();
	void show_ground2();
	void show_ground3();
};
//player class
class player
{
public:
	player(io_service& io_service);
	void playgame(ground gr, int i);
	void write_move(ground& gr, int& flag);
	void read_move(ground& gr, int n);
	int chosen_ground();
	void show_result(int n);
	//void error_handler(player* pl, ground& gr, int num);
	tcp::socket* get_sock();

private:
	tcp::socket sock;
};

///////////////////////////////////////////////////////////////////////////////////////////
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
void ground::show_ground(int n)
{
	switch (n) {
	case 1:
		show_ground1();
		break;
	case 2:
		show_ground2();
		break;
	case 3:
		show_ground3();
		break;
	}
}
void ground::show_ground_timer(int n, int& flag)
{
	int sec = 20;
	do
	{
		displayClock(sec);
		switch (n) {
		case 1:
			show_ground1();
			break;
		case 2:
			show_ground2();
			break;
		case 3:
			show_ground3();
			break;
		}
		Sleep(1000);
		sec--;
		if (sec < 0) {
			flag = -1;
			break;
		}
	} while (flag);
}
void ground::show_ground1()
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
void ground::show_ground2()
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
void ground::show_ground3()
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

	cout <<
		showground[0] << "____________" << showground[1] << "____________" << showground[2] << endl
		<< "| \\          |          / |" << endl
		<< "|   " << showground[3] << "________" << showground[4] << "________" << showground[5] << "   |" << endl
		<< "|   | \\      |      / |   |" << endl
		<< "|   |   " << showground[6] << "____" << showground[7] << "____" << showground[8] << "   |   |" << endl
		<< "|   |   |         |   |   |" << endl
		<< "|   |   |         |   |   |" << endl
		<< showground[9] << "___" << setw(2) << showground[10] << "__" << setw(2) << showground[11] << "       " << showground[12] << "___" << showground[13] << "___" << showground[14] << endl
		<< "|   |   |         |   |   |" << endl
		<< "|   |   |         |   |   |" << endl
		<< "|   |   " << showground[15] << "___" << showground[16] << "___" << showground[17] << "  |   |" << endl
		<< "|   |  /     |      \\ |   |" << endl
		<< "|   " << showground[18] << "_______" << showground[19] << "_______" << showground[20] << "  |" << endl
		<< "|  /         |         \\  |" << endl
		<< setw(2) << showground[21] << "___________" << showground[22] << "___________" << showground[23] << endl;




}
void ground::displayClock(int sec)
{
	system("cls");
	cout << "TIMER		 \n";
	cout << " --------\n";
	cout << "| " << sec << " sec | " << endl;
	cout << " --------\n";
}
void ground::update_ground(int numblock, int who)
{
	blocks[numblock] = who;
}
/////////////////////////////////////////////////////////////////////function of player class 
player::player(io_service& io_service)
	:sock(io_service)
{
	sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 1234));
}
void player::playgame(ground gr, int i)
{
	while (1)
	{
		read_move(gr, i);
		gr.show_ground(i);

		int flag = 1;
		thread t1(&player::write_move, this, ref(gr), ref(flag));
		gr.show_ground_timer(i, ref(flag));
		if (flag == -1)
		{
			cout << "Your time is up" << endl;
			t1.detach();
			t1.~thread();
			write(sock, boost::asio::buffer("4\n"));
		}
		else
			t1.join();
	}
}
void player::write_move(ground& gr, int& flag)
{
	string msg;
	getline(cin, msg);
	msg += "\n";
	int num = atoi(msg.c_str());
	//error_handler(this, gr, num);
	flag = 0;
	gr.update_ground(num - 1, -2);
	write(sock, boost::asio::buffer(msg));
}
void player::read_move(ground& gr, int n)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	int num, state;
	string sub = "-";
	for (int i = 0; i < 2; i++)
	{
		size_t pos = s.find(sub);
		stringstream geek(s.substr(0, pos));
		if (i == 0)
			geek >> num;
		if (i == 1)
			geek >> state;
		s.erase(0, pos + sub.length());
	}
	if (state != 2 && num != 4)
		gr.update_ground(num - 1, -1);
	if (state == 1 || state == 2 || state == 0)
	{
		gr.show_ground(n);
		show_result(state);
	}
}
tcp::socket* player::get_sock()
{
	return &sock;
}
int player::chosen_ground()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	cout << s << endl;

	boost::asio::streambuf buff2;
	read_until(sock, buff2, "\n");
	string msg = buffer_cast<const char*>(buff2.data());
	return atoi(msg.c_str());

}
//void player::error_handler(player* pl, ground& gr, int num)
//{
//	if (num<1 || num>gr.get_cnt())
//	{
//		cout << "this block doesn't exist.try another one." << endl;
//	}
//	else if (gr.get_block(num) == -1 || gr.get_block(num) == -2)
//	{
//		cout << "sorry this block is already full.try another one." << endl;
//
//	}
//	else return;
//}
void player::show_result(int num)
{
	switch (num) {
	case 2:
		cout << "congrajulations! you wiiiiiiin!" << endl;
		exit(0);
		break;
	case 1:
		cout << "Game over:(" << endl;
		exit(0);
		break;
	case 0:
		cout << "Draw!" << endl;
		exit(0);
		break;
	}
}
//main function
int main()
{
	io_service io;
	player pl(io);
	int i = pl.chosen_ground();
	ground gr(i);
	gr.show_ground(i);
	pl.playgame(gr, i);
}