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
#include "rapidjson/filereadstream.h"

InputJSON::InputJSON(string fileName): 
	time(0)
{
	FILE* fp;
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		char* mode = "rb";
	#else
		char* mode = "r";
	#endif
	fopen_s(&fp, fileName.c_str(), mode);
 
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	// if ( !is.() )
    // {
    //     std::cerr << "Could not open file for reading!\n";
    // }

	std::cout << "parsing" << std::endl;
    doc.ParseStream( is );
	std::cout << "parsed" << std::endl;
	
}

InputJSON::~InputJSON() { }

Value* InputJSON::input() {
	char timeString[11]; 
	sprintf_s(timeString,"%ld", time++);
	if(doc.HasMember(timeString)) {
		return &doc[timeString];
	} else  {
		char timeString2[11]; 
		time = time - 2;
		sprintf_s(timeString2,"%ld", time);
		return &doc[timeString2];
	}
}