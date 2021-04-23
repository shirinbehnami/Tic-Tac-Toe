
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