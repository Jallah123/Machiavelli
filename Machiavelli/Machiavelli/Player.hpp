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
#include <vector>
#include <memory>
#include "Card.h"

class Player {
public:
	Player() {}
	Player(const std::string& name, const int& day, const int& month, const int& year) : name{ name } { age.tm_mday = day; age.tm_mon = month; age.tm_year = year; }

	std::string getName() const { return name; }
	void setName(const std::string& new_name) { name = new_name; }

	tm getAge() { return age; };
private:
	std::string name;
	tm age;
	std::vector<std::unique_ptr<Card>> characterCards;
	std::vector<std::unique_ptr<Card>> playedCards;
	std::vector<std::unique_ptr<Card>> handCards;
};

#endif /* Player_hpp */
