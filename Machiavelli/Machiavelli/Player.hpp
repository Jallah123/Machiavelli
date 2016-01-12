//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>

class Player {
public:
	Player() {}
	Player(const std::string& name, const int& day, const int& month, const int& year) : name{ name } { age.tm_mday = day; age.tm_mon = month; age.tm_year = year; }

	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
private:
	std::string name;
	tm age;
	std::vector<unique_ptr<Card>> characterCards;
	std::vector<unique_ptr<Card>> playedCards;
	std::vector<unique_ptr<Card>> handCards;
};

#endif /* Player_hpp */
