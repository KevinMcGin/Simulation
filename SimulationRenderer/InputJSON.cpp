#include "InputJSON.h"


InputJSON::InputJSON(string fileName): 
	time(0)
{
	ifstream file(fileName);
	string stream;
	file >> stream;
	
}

InputJSON::~InputJSON()
{
}

Json::Value InputJSON::input()
{
	auto particles = root[to_string(time)];
	time++;
	return particles;
}
