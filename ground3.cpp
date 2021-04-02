class ground3
{
public:
	ground3();
	void show_ground();
	void update_ground(int numblock, int who, player* pl);
	void judge();
private:
	int blocks[24];
	int cntblocks;
	const vector<vector<int>> winblocks = { {0,1,2},{3,4,5},{6,7,8},{9,10,11},{12,13,14},{15,16,17},{18,19,20},{21,22,23}
                                        {0,9,21},{3,10,18},{6,11,15},{1,4,7},{16,19,22},{8,12,17},{5,13,20}.{2,14,23}
                                        {0,3,6},{2,5,8},{17,20,23},{15,18,21}   };
};
ground3::ground3()
{
    cntblocks=sizeof(blocks)/sizeof(block[0]);
    for(int i=0;i<cntblocks;i++)
        blocks[i]=i+1;
}
void ground3::update_ground(int numblock, int who, player* pl)
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
void ground3::judge()
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
void ground3::show_ground()
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

 cout<<
    showground[0]<<"____________"<<showground[1]<<"____________"<<showground[2]<<endl
    <<"| \\          |          / |"<<endl
    <<"|   "<<showground[3]<<"________"<<showground[4]<<"________"<<showground[5]<<"   |"<<endl
    <<"|   | \\      |      / |   |"<<endl
    <<"|   |   "<<showground[6]<<"____"<<showground[7]<<"____"<<showground[8]<<"   |   |"<<endl
    <<"|   |   |         |   |   |"<<endl
    <<"|   |   |         |   |   |"<<endl
    <<showground[9]<<"___"<<setw(2)<<showground[10]<<"__"<<setw(2)<<showground[11]<<"       "<<showground[12]<<"___"<<showground[13]<<"___"<<showground[14]<<endl
    <<"|   |   |         |   |   |"<<endl
    <<"|   |   |         |   |   |"<<endl
    <<"|   |   "<<showground[15]<<"___"<<showground[16]<<"___"<<showground[17]<<"  |   |"<<endl
    <<"|   |  /     |      \\ |   |"<<endl
    <<"|   "<<showground[18]<<"_______"<<showground[19]<<"_______"<<showground[20]<<"  |"<<endl
    <<"|  /         |         \\  |"<<endl
    <<setw(2)<<showground[21]<<"___________"<<showground[22]<<"___________"<<showground[23]<<endl;




}