#include "InputJSON.h"
#include "OperatingSystemConstants.h"

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

InputJSON::InputJSON(const char* fileName): 
	time(0)
{
	std::cout << "Parsing simulation: " << fileName << std::endl;
	FILE* fp;
	#if defined(WINDOWS)
		char* mode = "rb";
		fopen_s(&fp, fileName, mode);
	#else
		char* mode = "r";
		fp = fopen64(fileName, mode);
	#endif
	if (!fp) {
        std::cerr << "Could not open file for reading!\n";
    }
 
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    doc.ParseStream( is );
	std::cout << "Parsing done" << std::endl;
	
}

InputJSON::~InputJSON() { }

Value* InputJSON::input() {
	char timeString[11]; 
	#if defined(WINDOWS)
		sprintf_s(timeString,"%ld", time++);
	#else
		sprintf(timeString,"%ld", time++);
	#endif
	if(doc.HasMember(timeString)) {
		return &doc[timeString];
	} else  {
		char timeString2[11]; 
		time = time - 2;
		#if defined(WINDOWS)
			sprintf_s(timeString2,"%ld", time);
		#else
			sprintf(timeString2,"%ld", time);
		#endif
		return &doc[timeString2];
	}
}