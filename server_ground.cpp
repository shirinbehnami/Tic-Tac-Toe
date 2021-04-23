#include "server_ground.h"

using namespace std;

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