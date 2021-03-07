#include "pch.h"

int main(int argc) {
	char** argv2 = new char* [1];

	for (unsigned int i = 0; i < 1; i++) {
		// str is likely to be an array of characters
		argv2[i] = "str";
	}

	::testing::InitGoogleTest(&argc, argv2);
	return RUN_ALL_TESTS();
}