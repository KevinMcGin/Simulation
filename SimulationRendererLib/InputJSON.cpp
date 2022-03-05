#include "InputJSON.h"
#include "constant/OperatingSystemConstants.h"

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
	time(0),
	originalTime(0)
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
		throw std::runtime_error("Could not open file for reading!");
    }
 
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    doc.ParseStream( is );
	std::cout << "Parsing done" << std::endl;
	
}

InputJSON::~InputJSON() { }

Value* InputJSON::input(int elapsedFrames) {
	originalTime = time;
	time += elapsedFrames;
	return getFrame();
}

Value* InputJSON::getFrame() {
	const size_t bufferSize = 11;
	const auto bufferSizeInt = (int)bufferSize;
	char timeString[bufferSizeInt];
	#if defined(WINDOWS)
		sprintf_s(timeString, "%ld", time);
	#else
		snprintf(timeString, bufferSize, "%ld", time);
	#endif
	if(doc.HasMember(timeString)) {
		return &doc[timeString];
	} else {
		time = originalTime;
		return getLastFrame();
	}
}

Value* InputJSON::getLastFrame() {
	const size_t bufferSize = 11;
	const auto bufferSizeInt = (int)bufferSize;
	char timeString[bufferSizeInt];
	#if defined(WINDOWS)
		sprintf_s(timeString, "%ld", time);
	#else
		snprintf(timeString, bufferSize, "%ld", time);
	#endif
	if(!doc.HasMember(timeString)) {
		time--;
		return getFrame();
	} else {
		time++;
		return getLastFrame();
	}
}