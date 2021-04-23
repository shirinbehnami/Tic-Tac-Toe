
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
