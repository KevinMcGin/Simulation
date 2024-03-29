#include  "gtest/gtest.h"
#include "InputJson.h"

#include <iostream>
#include <fstream>

void testJsonReadPosition0(Value* input) {
    auto particles = input->GetArray();
	EXPECT_FLOAT_EQ(0.030432f, particles[0]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-15.061090, particles[0]["pos"][0].GetFloat());
	EXPECT_FLOAT_EQ(0.032683f, particles[1]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-7.088444, particles[1]["pos"][1].GetFloat());
}

void testJsonReadPosition1(Value* input) {
    auto particles = input->GetArray();
	EXPECT_FLOAT_EQ(1.030432f, particles[0]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-1.061090, particles[0]["pos"][0].GetFloat());
	EXPECT_FLOAT_EQ(1.032683f, particles[1]["r"].GetFloat());
	EXPECT_FLOAT_EQ(17.088444, particles[1]["pos"][1].GetFloat());
}

TEST(InputJsonTest, JsonRead) {
    std::string fileName = "test_file_name.json";
    std::ofstream file;
    file.open(fileName);
    file << "{"
        "\"0\": ["
            "{ \"r\": 0.030432,"
            "\"pos\": [-15.061090,-6.764659,0.000000]},"
            "{ \"r\": 0.032683,"
            "\"pos\": [-8.086112,-7.088444,0.000000]}"
        "],"
        "\"1\": ["
            "{ \"r\": 1.030432,"
            "\"pos\": [-1.061090,-6.764659,0.000000]},"
            "{ \"r\": 1.032683,"
            "\"pos\": [-18.086112,17.088444,0.000000]}"
        "]"
    "}";
    file.close();

	InputJson inputJson(fileName.c_str());

    testJsonReadPosition0(inputJson.input(0));
    testJsonReadPosition1(inputJson.input(1));
    testJsonReadPosition1(inputJson.input(10));
    testJsonReadPosition0(inputJson.input(-1));
    testJsonReadPosition1(inputJson.input(10));
}

TEST(InputJsonTest, FileNoFound) {
	 try {
        InputJson inputJson("file_not_exist");
        FAIL() << "No error thrown: Could not open file for reading!";
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Could not open file for reading!"));
    } catch(...) {
        FAIL() << "Wrong error thrown: expected Could not open file for reading!";
    }
}