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

InputJSON::~InputJSON() { }

Value* InputJSON::input() {
	char timeString[11]; 
	sprintf(timeString,"%ld", time++);
	if(doc.HasMember(timeString)) {
		return &doc[timeString];
	} else  {
		char timeString2[11]; 
		time = time - 2;
		sprintf(timeString2,"%ld", time);
		return &doc[timeString2];
	}
}