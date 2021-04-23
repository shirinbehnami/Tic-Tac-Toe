
#include<iostream>
#include<vector>
#include <boost/asio.hpp>
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