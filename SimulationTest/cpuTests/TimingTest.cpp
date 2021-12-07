#include  "gtest/gtest.h"
#include "Timing.h"

TEST(TimingTest, TimeInSeconds) {
	Timing::setTime();
    string time = Timing::getTime();
	EXPECT_EQ('s', time.back());
}

// TEST(TimingTest, TimeInMins) {
// 	Timing::setTime();
//     string time = Timing::getTime();
// 	EXPECT_EQ("mins", time.substr(time.size() - 4));
// }

// TEST(TimingTest, TimeInMins) {
// 	Timing::setTime();
//     string time = Timing::getTime();
// 	EXPECT_EQ("hrs", time.substr(time.size() - 3));
// }