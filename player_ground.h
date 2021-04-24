#include<iostream>
#include<vector>
#include <boost/asio.hpp>
#include <iomanip>
#include<thread>
#include <conio.h>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace ip;

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

//---------------------------------------------------------------------------
//other function
void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}
int correct_input(int min, int max)
{
	bool is_correct = false;
	string msg;
	int num;
	char* ptr;
	do {
		SetColorAndBackground(3, 0);
		cout << ">> ";
		SetColorAndBackground(15, 0);
		getline(cin, msg);
		msg += "\n";
		num = strtol(msg.c_str(), &ptr, 10);
		if (num == 0)
		{
			SetColorAndBackground(4, 0);
			cout << "\ninvalid input.try again" << endl;
		}
		else if (num<min || num>max)
		{
			SetColorAndBackground(4, 0);
			cout << "\nout of range.try again" << endl;
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
		SetColorAndBackground(3, 0);
		cout << ">> ";
		while (1)
		{
			SetColorAndBackground(15, 0);
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
			cout << "\ninvalid input.try again" << endl;
			input[0] = '\0';
			cnt = 0;
			Sleep(600);
		}
		else if (num<min || num>max)
		{
			SetColorAndBackground(4, 0);
			cout << "\nout of range.try again" << endl;
			input[0] = '\0';
			cnt = 0;
			Sleep(600);
		}
		else
			is_correct = true;

	} while (!is_correct);
	return num;
}

//---------------------------------------------------------------------------
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
		SetColorAndBackground(15, 0);
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
	SetColorAndBackground(5, 0);
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
	SetColorAndBackground(5, 0);
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

	SetColorAndBackground(5, 0);
	cout << endl;
	cout <<
		"    " << showground[0] << " __________ " << showground[1] << " __________ " << showground[2] << endl
		<< "    | \\          |          / |" << endl
		<< "    |   " << showground[3] << " ______ " << showground[4] << " ______ " << showground[5] << "   |" << endl
		<< "    |   | \\      |      / |   |" << endl
		<< "    |   |   " << showground[6] << " __ " << showground[7] << " __ " << showground[8] << "   |   |" << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    " << showground[9] << "__" << setw(2) << showground[10] << "__" << setw(2) << showground[11] << "        " << setw(2) << showground[12] << "__" << setw(2) << showground[13] << "__" << setw(2) << showground[14] << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    |   |   |         |   |   |" << endl
		<< "    |   |   " << setw(2) << showground[15] << "___" << setw(2) << showground[16] << "___" << setw(2) << showground[17] << "  |   |" << endl
		<< "    |   |  /     |      \\ |   |" << endl
		<< "    |   " << setw(2) << showground[18] << "_______" << setw(2) << showground[19] << "_______" << setw(2) << showground[20] << "  |" << endl
		<< "    |  /         |         \\  |" << endl
		<< "    " << setw(2) << showground[21] << "___________" << setw(2) << showground[22] << "___________" << setw(2) << showground[23] << endl << endl;

}

void ground::displayClock(int min, int sec)
{
	system("cls");
	SetColorAndBackground(8, 0);
	cout << "//OX" << endl << endl;
	SetColorAndBackground(7, 0);
	cout << "         TIME      \n";
	cout << "   ----------------\n";
	if (min == 0 && sec <= 20)
	{
		cout << "\a\a";
		cout << "  | ";
		SetColorAndBackground(4, 0);
		cout << min << " min ";
		SetColorAndBackground(7, 0);
		cout << "  | ";
		SetColorAndBackground(4, 0);
		cout << sec << " sec ";
		SetColorAndBackground(7, 0);
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
			cout << "\nthis block is full.try another one." << endl;
			input_num[0] = '\0';
			Sleep(600);
		}
		else
			is_correct = true;
	} while (!is_correct);
	return num;
}