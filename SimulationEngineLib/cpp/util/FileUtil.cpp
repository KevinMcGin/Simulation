#include "cpp/util/FileUtil.h"
#include <fstream>

std::string FileUtil::fileToString(const char* outputFile) {
	std::ifstream file(outputFile);
	std::string outputJson(
		(std::istreambuf_iterator<char>(file)), 
		std::istreambuf_iterator<char>()
	);
	file.close();
	return outputJson;
}