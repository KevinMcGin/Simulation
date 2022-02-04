#include  "gtest/gtest.h"
#include "util/Timing.h"

TEST(TimingTest, TimeInSeconds) {
	Timing timing= Timing();
	timing.setTime();
    string time = timing.getTimeWithUnit();
	EXPECT_EQ('s', time.back());
}

TEST(TimingTest, TimeInMins) {
    string time = Timing::getTimeWithUnit(3599.f);
	EXPECT_EQ("mins", time.substr(time.size() - 4));
}

TEST(TimingTest, TimeInHrs) {
    string time = Timing::getTimeWithUnit(3600.f);
	EXPECT_EQ("hrs", time.substr(time.size() - 3));
}