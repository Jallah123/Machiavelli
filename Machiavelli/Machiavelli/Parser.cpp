#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

vector<string> &Parser::split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<vector<string>> Parser::Parse(string textfile)
{
	vector<vector<string>> result{};
	ifstream input_file{ textfile };

	string line;
	while (getline(input_file, line)) {
		if (line.at(0) == '/') {
			continue;
		}
		vector<string> elements{};
		split(line, ';', elements);
		result.push_back(elements);
	}
	return result;
}