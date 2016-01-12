#include <map>
#include <string>

enum ColorEnum
{
	YELLOW,
	GREEN,
	BLUE,
	RED,
	LILA,
	NONE
};

static std::map<std::string, ColorEnum> ColorMap = { { "geel", YELLOW }, { "groen", GREEN }, { "rood", RED }, { "lila", LILA },{ "blauw", BLUE },{ " ", NONE } };