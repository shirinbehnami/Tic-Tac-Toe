//player
// player1:O,-1    player2:x,-2

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <iomanip>
#include<thread>
#include <conio.h>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace ip;

void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}

//general functions
int correct_input(int min, int max);
int correct_input(int min, int max, char input[]);

//ground class
class ground
{
public:
	ground(int n);

	int get_block(int i) { return blocks[i]; }
	int get_cnt() { return cntblocks; }
	int get_time(int i) { return time[i]; }

	void show_ground(int n);
	void show_ground_timer(int n, int& flag, char input_num[]);

	void update_ground(int numblock, int who);
	void displayClock(int min, int sec);
	int correct_block(char input_num[]);
private:
	void show_ground1();
	void show_ground2();
	void show_ground3();

	vector<int> blocks;
	int cntblocks;
	int time[2];
};

//player class
class player
{
public:
	player(io_service& io_service);

	tcp::socket* get_sock();

	void playgame(ground gr, int i);
	int start_game();
	void registeration();
	void choose_opponent();
	bool accept_or_reject();
	void goodbye();
private:
	void write_move(ground& gr, int& flag, char input_num[]);
	void read_move(ground& gr, int i);
	void show_all_grounds();
	void show_result(int n);
	void after_game();
	void send_ans(int& flag, string& choice);
	void receive_ans(int& flag, string& choice);
	void chat();
	void receiveFrom();
	void sendTo();
	void rematch();

	tcp::socket sock;
	int playernum;
	string name;
	static int are_connected;
};
//initialize
int player::are_connected = true;
//----------------------------------------------------------------------------
//function of ground class 

ground::ground(int n)
{
	switch (n) {
	case 1:
		cntblocks = 9;
		time[0] = 1;
		time[1] = 30;
		break;
	case 2:
		cntblocks = 16;
		time[0] = 2;
		time[1] = 30;
		break;
	case 3:
		cntblocks = 24;
		time[0] = 3;
		time[1] = 30;
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
void ground::show_ground_timer(int n, int& flag, char input_num[])
{
	do
	{
		displayClock(time[0], time[1]);
		this->show_ground(n);
		SetColorAndBackground(14, 0);
		cout << input_num;
		Sleep(1000);
		time[1]--;
		if (time[1] < 0) {
			time[0]--;
			if (time[0] < 0) {
				flag = -1;
				break;
			}
			time[1] = 59;
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
	SetColorAndBackground(6, 0);
	cout << endl << endl;
	cout << "    " << showground[0] << " _____ " << showground[1] << " _____ " << showground[2] << endl;
	cout << "    |       |       |" << endl;
	cout << "    |       |       |" << endl;
	cout << "    |       |       |" << endl;
	cout << "    " << showground[3] << " _____ " << showground[4] << " _____ " << showground[5] << endl;
	cout << "    |       |       |" << endl;
	cout << "    |       |       |" << endl;
	cout << "    |       |       |" << endl;
	cout << "    " << showground[6] << " _____ " << showground[7] << " _____ " << showground[8] << endl << endl;
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
	SetColorAndBackground(6, 0);
	cout << endl;
	cout << "    " << left << showground[0] << " _____ " << showground[1] << " _____ " << showground[2] << endl;
	cout << "    |       |       |" << endl;
	cout << "    |  " << showground[3] << "  _ " << showground[4] << " _  " << showground[5] << "  |" << endl;
	cout << "    |  |         |  |" << endl;
	cout << "    " << showground[6] << "__" << showground[7] << "         " << showground[8] << "__" << showground[9] << endl;
	cout << "    |  |         |  |" << endl;
	cout << "    |  " << setw(2) << showground[10] << " _ " << setw(2) << showground[11] << " _ " << setw(2) << showground[12] << " |" << endl;
	cout << "    |       |       |" << endl;
	cout << "    " << setw(2) << showground[13] << " ____ " << setw(2) << showground[14] << "_____ " << showground[15] << endl << endl;
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

	SetColorAndBackground(6, 0);
	cout << endl;
	cout <<
		"    " << showground[0] << " __________ " << showground[1] << " __________ " << showground[2] << endl
		<< "    | \\          |          / |" << endl
		<< "    |   " << showground[3] << " ______ " << showground[4] << " ______ " << showground[5] << "   |" << endl
		<< "    |   | \\      |      / |   |" << endl
		<< "    |   |   " << showground[6] << " __ " << showground[7] << " __ " << showground[8] << "   |   |" << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    " << showground[9] << "__" << setw(2) << showground[10] << "__" << setw(2) << showground[11] << "        " << showground[12] << "__" << showground[13] << "__" << showground[14] << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    |   |   " << showground[15] << "___" << showground[16] << "___" << showground[17] << "  |   |" << endl
		<< "    |   |  /     |      \\ |   |" << endl
		<< "    |   " << showground[18] << "_______" << showground[19] << "_______" << showground[20] << "  |" << endl
		<< "    |  /         |         \\  |" << endl
		<< "    " << setw(2) << showground[21] << "___________" << showground[22] << "___________" << showground[23] << endl << endl;

}

void ground::displayClock(int min, int sec)
{
	system("cls");
	SetColorAndBackground(1, 0);
	cout << "//tic tac toe" << endl << endl;
	SetColorAndBackground(2, 0);
	cout << "         TIME      \n";
	cout << "   ----------------\n";
	if (min == 0 && sec <= 20)
	{
		cout << "\a\a";
		cout << "  | ";
		SetColorAndBackground(4, 0);
		cout << min << " min ";
		SetColorAndBackground(2, 0);
		cout << "  | ";
		SetColorAndBackground(4, 0);
		cout << sec << " sec ";
		SetColorAndBackground(2, 0);
		cout << "| " << endl;
	}
	else
	{
		cout << "  | " << min << " min ";
		cout << "  | " << sec << " sec | " << endl;
	}
	cout << "   ----------------\n";
}
void ground::update_ground(int numblock, int who)
{
	blocks[numblock] = who;
}
int ground::correct_block(char input_num[])
{
	bool is_correct = false;
	int num;
	do {
		num = correct_input(1, cntblocks, input_num);
		if (blocks[num - 1] == -1 || blocks[num - 1] == -2)
		{
			SetColorAndBackground(4, 0);
			cout << "this block is full.try another one." << endl;
			input_num[0] = '\0';
		}
		else
			is_correct = true;
	} while (!is_correct);
	return num;
}

//---------------------------------------------------------------------------
//function of player class 

player::player(io_service& io_service)
	:sock(io_service)
{
	sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 1234));
}

tcp::socket* player::get_sock()
{
	return &sock;
}

void player::registeration()
{
	SetColorAndBackground(1, 0);
	cout << "//tic tac toe" << endl;
	SetColorAndBackground(2, 0);
	cout << "Hi! what's your name? >> ";
	SetColorAndBackground(14, 0);
	getline(cin, name);
	write(sock, boost::asio::buffer(name + "\n"));
	SetColorAndBackground(2, 0);
	cout << "registration completed.:)" << endl << endl;
}
void player::choose_opponent()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	if (s == "two\n")
	{

		//show options
		playernum = 2;
		SetColorAndBackground(2, 0);
		cout << "choose your opponent :(enter their name)" << endl;
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		string opp_name = buffer_cast<const char*>(buff.data());
		cout << "   " << opp_name;

		//choose opponent
		string msg;
		SetColorAndBackground(14, 0);
		getline(cin, msg);
		write(sock, boost::asio::buffer(msg + "\n"));
		SetColorAndBackground(2, 0);
		cout << "pending..." << endl;

	}
	else if (s == "one\n")
	{
		playernum = 1;

		//show request massage
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		string s = buffer_cast<const char*>(buff.data());
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		SetColorAndBackground(2, 0);
		cout << s << " wants to play." << endl;
		cout << "1-Accept" << endl << "2-Decline" << endl;

		//accept or decline
		int m = correct_input(1, 2);
		string msg = to_string(m);
		write(sock, boost::asio::buffer(msg + "\n"));
	}
}
bool player::accept_or_reject()
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	if (s == "1\n")
		return true;
	else
		return false;
}
int player::start_game()
{
	system("cls");
	SetColorAndBackground(1, 0);
	cout << "//tic tac toe" << endl;
	SetColorAndBackground(2, 0);
	if (playernum == 1)
	{
		cout << "you are the first player! choose the ground :)(enter its number)." << endl << endl << endl;
		show_all_grounds();
		int num = correct_input(1, 3);
		string msg = to_string(num) + "\n";
		write(sock, boost::asio::buffer(msg));
		return num;
	}
	else if (playernum == 2)
	{
		cout << "you 're the second player.your opponent chose ground :" << endl;
		boost::asio::streambuf buff2;
		read_until(sock, buff2, "\n");
		string msg = buffer_cast<const char*>(buff2.data());
		return atoi(msg.c_str());
	}

}
void player::show_all_grounds()
{
	SetColorAndBackground(6, 0);
	cout << "  O_______O_______O            O_______O_______O            O_______O_______O" << endl;
	cout << "  |       |       |            |       |       |            | \\     |     / |" << endl;
	cout << "  |       |       |            |       |       |            |  O____O____O  |" << endl;
	cout << "  |       |       |            |   O___O___O   |            |  |\\   |   /|  |" << endl;
	cout << "  |       |       |            |   |       |   |            |  | O__O__O |  |" << endl;
	cout << "  |       |       |            |   |       |   |            |  | |     | |  |" << endl;
	cout << "  O_______O_______O            O___O       O___O            O__O_O     O_O__O" << endl;
	cout << "  |       |       |            |   |       |   |            |  | |     | |  |" << endl;
	cout << "  |       |       |            |   |       |   |            |  | O__O__O |  |" << endl;
	cout << "  |       |       |            |   O___O___O   |            |  |/   |   \\|  |" << endl;
	cout << "  |       |       |            |       |       |            |  O____O____O  |" << endl;
	cout << "  |       |       |            |       |       |            | /     |     \\ |" << endl;
	cout << "  O_______O_______O            O_______O_______O            O_______O_______O" << endl << endl;
	cout << "         (1)                          (2)                          (3)          " << endl << endl;
}

void player::playgame(ground gr, int i)
{
	bool whilecnt = false;
	while (1)
	{
		if (playernum == 2 || whilecnt == true)
		{
			read_move(gr, i);
			gr.show_ground(i);
		}
		else
			whilecnt = true;

		int flag = 1;
		char input_num[1000];
		input_num[0] = '\0';
		thread t1(&player::write_move, this, ref(gr), ref(flag), input_num);
		gr.show_ground_timer(i, ref(flag), input_num);
		if (flag == -1)
		{
			SetColorAndBackground(4, 0);
			cout << "Your time is up" << endl;
			t1.detach();
			t1.~thread();
			write(sock, boost::asio::buffer("0\n"));
		}
		else
		{
			t1.join();
			gr.displayClock(gr.get_time(0), gr.get_time(1));
			gr.show_ground(i);
		}
	}
}
void player::write_move(ground& gr, int& flag, char input_num[])
{
	int num = gr.correct_block(input_num);
	string msg = to_string(num) + "\n";
	flag = 0;
	gr.update_ground(num - 1, -1 * (playernum));
	write(sock, boost::asio::buffer(msg));
}
void player::read_move(ground& gr, int n)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	string s = buffer_cast<const char*>(buff.data());
	int num = 0, state = 3;
	sscanf_s(s.c_str(), "%d\n-%d-%d", &num, &state, &are_connected);
	if (state != playernum && num != 0 && !(playernum == 1 && n == 1 && state == 0) && !(playernum == 2 && n != 1 && state == 0))
	{
		if (playernum == 1)
			gr.update_ground(num - 1, -2);
		else if (playernum == 2)
			gr.update_ground(num - 1, -1);
	}
	if (state != 3)
	{
		system("cls");
		gr.show_ground(n);
		this->show_result(state);
	}
}
void player::show_result(int state)
{
	{
		if (!are_connected)
			cout << "your opponent left the game.so..." << endl;
		if (state == playernum)
			cout << "congrajulations! you wiiiiiiin!" << endl;
		else if (state == 0)
			cout << "Draw!" << endl;
		else
			cout << "Game over:(" << endl;
		if (are_connected)
			after_game();
		else
			goodbye();
	}
}

void player::after_game()
{
	string choice;
	int flag = 0;
	thread t1(&player::receive_ans, this, ref(flag), ref(choice));
	thread t2(&player::send_ans, this, ref(flag), ref(choice));
	while (flag == 0);
	t1.detach();
	t1.~thread();
	t2.join();


}
void player::send_ans(int& flag, string& choice)
{
	string ans;
	SetColorAndBackground(2, 0);
	cout << "\n";
	cout << "1-Rematch" << endl << "2-Chat" << endl << "3-Exit" << endl;
	int x = correct_input(1, 3);

	if (flag == 0)
	{
		choice = to_string(x) + "\n";
		write(sock, boost::asio::buffer(choice));
		flag = 2;
		SetColorAndBackground(2, 0);
		if (x != 3)
			cout << "pending..." << endl;
		else
			goodbye();

	}
	if (flag == 1)
	{
		ans = to_string(x) + "\n";
		write(sock, boost::asio::buffer("NULL\n"));
		write(sock, boost::asio::buffer(ans));
	}
	if (flag == 2)//who fisrt sent a reqe
	{
		bool x = accept_or_reject();
		if (x == 1)
			ans = "1\n";
		else
			ans = "2\n";
	}

	if (ans == "1\n")
	{
		if (choice == "1\n")
			rematch();
		else if (choice == "2\n")
			chat();
		else goodbye();
	}
	else
		goodbye();




}
void player::receive_ans(int& flag, string& choice)
{
	boost::asio::streambuf buff;
	read_until(sock, buff, "\n");
	if (flag != 0)
		return;
	flag = 1;
	choice = buffer_cast<const char*>(buff.data());
	SetColorAndBackground(2, 0);
	if (choice == "1\n")
	{
		cout << "Your opponent wants to play again." << endl;
	}
	else if (choice == "2\n")
	{
		cout << "Your opponent wants to chat." << endl;
	}
	cout << "1-Accept" << endl << "2-Decline" << endl << "3-exit" << endl;
}
void player::rematch()
{
	//change playernum
	playernum = (playernum == 1) ? 2 : 1;

	//restart the game
	int i = start_game();
	ground g(i);
	g.show_ground(i);
	playgame(g, i);
}
void player::chat()
{
	SetColorAndBackground(2, 0);
	system("cls");
	cout << "__________________________________________________________" << endl;
	cout << "|              Welcome to tictactoe chat                 |" << endl;
	cout << "|________________________________________________________|" << endl;
	thread t3(&player::sendTo, this);
	thread t4(&player::receiveFrom, this);

	t3.join();
	t4.join();

}
void player::receiveFrom()
{
	while (1) {
		boost::asio::streambuf buff;
		read_until(sock, buff, "\n");
		SetColorAndBackground(9, 0);
		cout << buffer_cast<const char*>(buff.data());
		SetColorAndBackground(14, 0);
	}
}
void player::sendTo()
{
	while (1) {
		string msg;
		SetColorAndBackground(14, 0);
		getline(cin, msg);
		msg += "\n";
		write(sock, boost::asio::buffer(msg));
		cout << endl;
	}
}

void player::goodbye()
{
	SetColorAndBackground(2, 0);
	cout << "felan khodahafezzzz" << endl;
	exit(0);
}

//---------------------------------------------------------------------------
//other function

int correct_input(int min, int max)
{
	bool is_correct = false;
	string msg;
	int num;
	char* ptr;
	do {
		SetColorAndBackground(2, 0);
		cout << ">> ";
		SetColorAndBackground(14, 0);
		getline(cin, msg);
		msg += "\n";
		num = strtol(msg.c_str(), &ptr, 10);
		if (num == 0)
		{
			SetColorAndBackground(4, 0);
			cout << "invalid input.try again" << endl;
		}
		else if (num<min || num>max)
		{
			SetColorAndBackground(4, 0);
			cout << "out of range.try again" << endl;
		}
		else
			is_correct = true;

	} while (!is_correct);
	return num;
}
int correct_input(int min, int max, char input[])
{
	bool is_correct = false;
	int num, cnt = 0;
	do {
		SetColorAndBackground(2, 0);
		cout << ">> ";
		while (1)
		{
			SetColorAndBackground(14, 0);
			char c = _getch();
			input[cnt] = c;
			input[cnt + 1] = '\0';
			if (input[cnt] == '\b')
			{
				cout << "\b \b";
				if (cnt != 0)
				{
					cnt--;
					input[cnt] = '\0';
				}
			}
			else if (input[cnt] != '\r')
			{
				cout << input[cnt];
				cnt++;
			}
			else
			{
				cnt++;
				break;
			}
		}
		input[cnt - 1] = '\0';
		num = atoi(input);
		if (num == 0 && input[0] != '0')
		{
			SetColorAndBackground(4, 0);
			cout << "invalid input.try again" << endl;
			input[0] = '\0';
			cnt = 0;
		}
		else if (num<min || num>max)
		{
			SetColorAndBackground(1, 0);
			cout << "out of range.try again" << endl;
			input[0] = '\0';
			cnt = 0;
		}
		else
			is_correct = true;

	} while (!is_correct);
	return num;
}

//main function
int main()
{
	io_service io;
	player pl(io);
	pl.registeration();
	pl.choose_opponent();
	bool ans = pl.accept_or_reject();
	if (ans)
	{
		int i = pl.start_game();
		ground gr(i);
		gr.show_ground(i);
		pl.playgame(gr, i);
	}
	else
	{
		pl.goodbye();
	}
}