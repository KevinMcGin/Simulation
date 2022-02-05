#include  "gtest/gtest.h"
#include "InputJSON.h"

#include <iostream>
#include <fstream>

TEST(InputJsonTest, JsonRead) {
    string fileName = "test_file_name.json";
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

	InputJSON inputJSON(fileName.c_str());

    auto input = inputJSON.input(0);
    auto particles = input->GetArray();
	EXPECT_FLOAT_EQ(0.030432f, particles[0]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-15.061090, particles[0]["pos"][0].GetFloat());
	EXPECT_FLOAT_EQ(0.032683f, particles[1]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-7.088444, particles[1]["pos"][1].GetFloat());

    auto input2 = inputJSON.input(1);
    auto particles2 = input2->GetArray();
	EXPECT_FLOAT_EQ(1.030432f, particles2[0]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-1.061090, particles2[0]["pos"][0].GetFloat());
	EXPECT_FLOAT_EQ(1.032683f, particles2[1]["r"].GetFloat());
	EXPECT_FLOAT_EQ(17.088444, particles2[1]["pos"][1].GetFloat());
    
    auto input3 = inputJSON.input(10);
    auto particles3 = input3->GetArray();
	EXPECT_FLOAT_EQ(1.030432f, particles3[0]["r"].GetFloat());
	EXPECT_FLOAT_EQ(-1.061090, particles3[0]["pos"][0].GetFloat());
	EXPECT_FLOAT_EQ(1.032683f, particles3[1]["r"].GetFloat());
	EXPECT_FLOAT_EQ(17.088444, particles3[1]["pos"][1].GetFloat());
}