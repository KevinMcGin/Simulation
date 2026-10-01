#include  <gtest/gtest.h>
#include "cpp/util/Json.h"

TEST(JsonTest, QuotesAPlainString) {
	EXPECT_EQ("\"abc\"", Json::quote("abc"));
}

// The reason this exists: the values being wrapped are CSV documents, which
// are nothing but lines. A raw newline inside a JSON string is invalid, and
// a parser rejects the entire response rather than the line it sat on.
TEST(JsonTest, EscapesNewlinesSoACsvCanBeAValue) {
	EXPECT_EQ("\"a,b\\n1,2\\n\"", Json::quote("a,b\n1,2\n"));
}

TEST(JsonTest, EscapesQuotesAndBackslashes) {
	EXPECT_EQ("\"a\\\"b\\\\c\"", Json::quote("a\"b\\c"));
}

TEST(JsonTest, EscapesOtherControlCharactersAsUnicode) {
	EXPECT_EQ("\"a\\u0001b\"", Json::quote(std::string("a\x01" "b")));
}

TEST(JsonTest, LeavesOrdinaryPunctuationAlone) {
	EXPECT_EQ("\"1.5e+30,-2\"", Json::quote("1.5e+30,-2"));
}

TEST(JsonTest, BuildsAnObject) {
	const std::string fields = "\"a\":" + Json::quote("1") + ",\"b\":" + Json::quote("2");
	EXPECT_EQ("{\"a\":\"1\",\"b\":\"2\"}", Json::object(fields));
}
