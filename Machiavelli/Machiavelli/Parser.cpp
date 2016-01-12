#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Utility.h"

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
		Utility::split(line, ';', elements);
		result.push_back(elements);
	}
	return result;
}