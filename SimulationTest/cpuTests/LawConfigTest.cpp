#include <gtest/gtest.h>
#include "cpp/law/LawConfig.h"

TEST(LawConfigTest, DefaultsToEveryLawAndNewtonianMomentum) {
	LawConfig lawConfig;
	EXPECT_TRUE(lawConfig.isCollisionCoalesceEnabled);
	EXPECT_TRUE(lawConfig.isNewtonGravityEnabled);
	EXPECT_TRUE(lawConfig.isNewtonFirstLawEnabled);
	EXPECT_EQ(MOMENTUM_NEWTON, lawConfig.momentum);
	EXPECT_FLOAT_EQ((float)PhysicalConstants::GRAVITATIONAL_CONSTANT, lawConfig.gravitationalConstant);
}

TEST(LawConfigTest, SetLawsEnablesOnlyTheLawsNamed) {
	LawConfig lawConfig;
	EXPECT_EQ("", lawConfig.setLaws("newtonGravity,newtonFirstLaw"));
	EXPECT_FALSE(lawConfig.isCollisionCoalesceEnabled);
	EXPECT_TRUE(lawConfig.isNewtonGravityEnabled);
	EXPECT_TRUE(lawConfig.isNewtonFirstLawEnabled);
}

TEST(LawConfigTest, SetLawsAcceptsEveryAdvertisedName) {
	LawConfig lawConfig;
	for (const auto& name : LawConfig::lawNames()) {
		EXPECT_EQ("", lawConfig.setLaws(name)) << "law name " << name;
	}
}

TEST(LawConfigTest, SetLawsIgnoresSurroundingWhitespaceAndEmptyEntries) {
	LawConfig lawConfig;
	EXPECT_EQ("", lawConfig.setLaws(" collisionCoalesce , , newtonGravity "));
	EXPECT_TRUE(lawConfig.isCollisionCoalesceEnabled);
	EXPECT_TRUE(lawConfig.isNewtonGravityEnabled);
	EXPECT_FALSE(lawConfig.isNewtonFirstLawEnabled);
}

// An empty list is a universe with no laws, which is a legitimate thing to
// ask for — and specifically not the same as sending no list at all, which
// leaves every law on.
TEST(LawConfigTest, SetLawsWithAnEmptyListDisablesEverything) {
	LawConfig lawConfig;
	EXPECT_EQ("", lawConfig.setLaws(""));
	EXPECT_FALSE(lawConfig.isCollisionCoalesceEnabled);
	EXPECT_FALSE(lawConfig.isNewtonGravityEnabled);
	EXPECT_FALSE(lawConfig.isNewtonFirstLawEnabled);
}

TEST(LawConfigTest, SetLawsRejectsAnUnknownName) {
	LawConfig lawConfig;
	const auto error = lawConfig.setLaws("newtonGravity,relativity");
	EXPECT_NE("", error);
	// The name the caller got wrong has to appear in the message, since it
	// is shown as-is next to the control they need to fix.
	EXPECT_NE(std::string::npos, error.find("relativity"));
}

// A name that fails to parse must leave the whole config untouched, rather
// than applying the part of the list that happened to come first.
TEST(LawConfigTest, SetLawsAppliesNothingWhenOneNameIsUnknown) {
	LawConfig lawConfig;
	ASSERT_EQ("", lawConfig.setLaws("collisionCoalesce"));
	EXPECT_NE("", lawConfig.setLaws("newtonGravity,nonsense"));
	EXPECT_TRUE(lawConfig.isCollisionCoalesceEnabled);
	EXPECT_FALSE(lawConfig.isNewtonGravityEnabled);
}

TEST(LawConfigTest, SetMomentumAcceptsEveryAdvertisedName) {
	LawConfig lawConfig;
	for (const auto& name : LawConfig::momentumNames()) {
		EXPECT_EQ("", lawConfig.setMomentum(name)) << "momentum name " << name;
	}
}

TEST(LawConfigTest, SetMomentumSelectsTheModel) {
	LawConfig lawConfig;
	EXPECT_EQ("", lawConfig.setMomentum("einstein"));
	EXPECT_EQ(MOMENTUM_EINSTEIN, lawConfig.momentum);
	EXPECT_EQ("", lawConfig.setMomentum("newton"));
	EXPECT_EQ(MOMENTUM_NEWTON, lawConfig.momentum);
}

TEST(LawConfigTest, SetMomentumRejectsAnythingElse) {
	LawConfig lawConfig;
	EXPECT_NE("", lawConfig.setMomentum("relativistic"));
	EXPECT_NE("", lawConfig.setMomentum(""));
	// Left on the default rather than quietly changed by a rejected value.
	EXPECT_EQ(MOMENTUM_NEWTON, lawConfig.momentum);
}

TEST(LawConfigTest, SetGravitationalConstantTakesAPositiveNumber) {
	LawConfig lawConfig;
	EXPECT_EQ("", lawConfig.setGravitationalConstant("1.5e-10"));
	EXPECT_FLOAT_EQ(1.5e-10f, lawConfig.gravitationalConstant);
}

TEST(LawConfigTest, SetGravitationalConstantRejectsZeroAndNegatives) {
	LawConfig lawConfig;
	EXPECT_NE("", lawConfig.setGravitationalConstant("0"));
	EXPECT_NE("", lawConfig.setGravitationalConstant("-1"));
	EXPECT_FLOAT_EQ((float)PhysicalConstants::GRAVITATIONAL_CONSTANT, lawConfig.gravitationalConstant);
}

// Text that is not a number at all must be reported as such, not silently
// read as the 0 that atof would have produced.
TEST(LawConfigTest, SetGravitationalConstantRejectsTextAsNotANumber) {
	LawConfig lawConfig;
	EXPECT_EQ("gravitationalConstant must be a number", lawConfig.setGravitationalConstant("abc"));
	EXPECT_EQ("gravitationalConstant must be a number", lawConfig.setGravitationalConstant("1.0e-10nonsense"));
	EXPECT_EQ("gravitationalConstant must be a number", lawConfig.setGravitationalConstant(""));
}

TEST(LawConfigTest, SetGravitationalConstantRejectsNotANumberValue) {
	LawConfig lawConfig;
	EXPECT_EQ("gravitationalConstant must be greater than 0", lawConfig.setGravitationalConstant("nan"));
}
