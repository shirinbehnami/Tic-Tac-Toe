
#include "player_ground.h"

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

	//graphics
	void show_logo();
	void show_cow();
	void calc(int i, int j);

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