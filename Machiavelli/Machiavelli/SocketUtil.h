#pragma once
#include <memory>

using namespace std;

class Player;
class SocketUtil
{
public:
	static int GetNumber(shared_ptr<Player> player, int max, int min = 0);
private:
	SocketUtil();
	~SocketUtil();
};

