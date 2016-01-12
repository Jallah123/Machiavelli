#pragma once
#include <vector>

using namespace std;

class Utility
{
public:
	static Utility* GetInstance();
	int RandomNumber(int min, int max);
	static vector<string>& split(const string &s, char delim, vector<string> &elems);
private:
	Utility();
	~Utility();
	static Utility* instance;
};