#include "cppy/str.h"
#include <gtest/gtest.h>

TEST(TEST_CPPY_STR, count) {
	std::string s = "AAAAA";
	int count;
	EXPECT_EQ(CPPY_STR_count(s, "A", &count), PyException::Ok);
	EXPECT_EQ(count, 5);
	EXPECT_EQ(CPPY_STR_count(s, "AA", &count), PyException::Ok);
	EXPECT_EQ(count, 2);
	EXPECT_EQ(CPPY_STR_count(s, "AAA", &count), PyException::Ok);
	EXPECT_EQ(count, 1);
	EXPECT_EQ(CPPY_STR_count(s, "AA", 4, &count), PyException::Ok);
	EXPECT_EQ(count, 0);
}

TEST(TEST_CPPY_STR, split) {
	std::string s = "A B\tC\nD E   F";
	{
		std::vector<std::string> result;
		EXPECT_EQ(CPPY_STR_split(s, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 6);
		EXPECT_EQ(result[0], "A");
		EXPECT_EQ(result[1], "B");
		EXPECT_EQ(result[2], "C");
		EXPECT_EQ(result[3], "D");
		EXPECT_EQ(result[4], "E");
		EXPECT_EQ(result[5], "F");
	}
	{
		std::vector<std::string> result;
		EXPECT_EQ(CPPY_STR_split(s, " ", &result), PyException::Ok);
		EXPECT_EQ(result.size(), 6);
		EXPECT_EQ(result[0], "A");
		EXPECT_EQ(result[1], "B\tC\nD");
		EXPECT_EQ(result[2], "E");
		EXPECT_EQ(result[3], "");
		EXPECT_EQ(result[4], "");
		EXPECT_EQ(result[5], "F");
	}
}

TEST(TEST_CPPY_STR, find) {
	std::string s = "ABCD";
	{
		int result;
		EXPECT_EQ(CPPY_STR_find(s, "CD", &result), PyException::Ok);
		EXPECT_EQ(result, 2);
	}
	{
		int result;
		EXPECT_EQ(CPPY_STR_find(s, "E", &result), PyException::Ok);
		EXPECT_EQ(result, -1);
	}
}

TEST(TEST_CPPY_STR, index) {
	std::string s = "ABCD";
	{
		int result;
		EXPECT_EQ(CPPY_STR_index(s, "CD", &result), PyException::Ok);
		EXPECT_EQ(result, 2);
	}
	{
		int result;
		EXPECT_EQ(CPPY_STR_index(s, "E", &result), PyException::ValueError);
	}
}

TEST(TEST_CPPY_STR, format) {
	std::string s = "A{}B{}C{}D";
	{
		std::string result;
		EXPECT_EQ(CPPY_STR_format(s, &result, 1, 2, 3), PyException::Ok);
		EXPECT_EQ(result, "A1B2C3D");
	}
	{
		std::string result;
		EXPECT_EQ(CPPY_STR_format(s, &result, "123", "456", "789"), PyException::Ok);
		EXPECT_EQ(result, "A123B456C789D");
	}
}