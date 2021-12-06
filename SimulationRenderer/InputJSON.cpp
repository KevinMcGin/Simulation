#include "InputJSON.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

InputJSON::InputJSON(string fileName): 
	time(0)
{
	ifstream ifs(fileName);
	if ( !ifs.is_open() )
    {
        std::cerr << "Could not open file for reading!\n";
    }

    IStreamWrapper isw { ifs };

	doc = {};
    doc.ParseStream( isw );
	
}

InputJSON::~InputJSON()
{
}

Value* InputJSON::input()
{
	char s[11]; 
	sprintf(s,"%ld", time);
	Value* particles = &doc[s];
	time++;
	return particles;
}
