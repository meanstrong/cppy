#include "cppy/cppy.h"
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

#ifndef CPPY_CREATE_SHARED_LIBRARY

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

#endif // CPPY_CREATE_SHARED_LIBRARY



TEST(TEST_CPPY_STR, lower) {
	{
		std::string s = "AaBbCcDd";
		std::string result;
		EXPECT_EQ(CPPY_STR_lower(s, &result), PyException::Ok);
		EXPECT_EQ(result, "aabbccdd");
	}
	{
		std::string s = "123Aa456";
		std::string result;
		EXPECT_EQ(CPPY_STR_lower(s, &result), PyException::Ok);
		EXPECT_EQ(result, "123aa456");
	}
}

TEST(TEST_CPPY_STR, at) {
	std::string s = "123";
	char result;
	EXPECT_EQ(CPPY_STR_at(s, 0, &result), PyException::Ok);
	EXPECT_EQ(result, '1');
	EXPECT_EQ(CPPY_STR_at(s, 2, &result), PyException::Ok);
	EXPECT_EQ(result, '3');
	EXPECT_EQ(CPPY_STR_at(s, -2, &result), PyException::Ok);
	EXPECT_EQ(result, '2');
	EXPECT_EQ(CPPY_STR_at(s, 3, &result), PyException::IndexError);
	EXPECT_EQ(CPPY_STR_at(s, -4, &result), PyException::IndexError);
}

TEST(TEST_CPPY_INT, init) {
	{
		std::string s = "123";
		int result;
		EXPECT_EQ(CPPY_INT_init(s, &result), PyException::Ok);
		EXPECT_EQ(result, 123);
	}
	{
		std::string s = "99999999999999999999999999999999";
		int result;
		EXPECT_EQ(CPPY_INT_init(s, &result), PyException::OverflowError);
	}
	{
		std::string s = "XXX";
		int result;
		EXPECT_EQ(CPPY_INT_init(s, &result), PyException::ValueError);
	}
}

TEST(TEST_CPPY_INT, bit_length) {
	{
		int x = 37;
		int result;
		EXPECT_EQ(CPPY_INT_bit_length(x, &result), PyException::Ok);
		EXPECT_EQ(result, 6);
	}
	{
		int x = 30665;
		int result;
		EXPECT_EQ(CPPY_INT_bit_length(x, &result), PyException::Ok);
		EXPECT_EQ(result, 15);
	}
}

TEST(TEST_CPPY_INT, bit_count) {
	{
		int x = 13;
		int result;
		EXPECT_EQ(CPPY_INT_bit_count(x, &result), PyException::Ok);
		EXPECT_EQ(result, 3);
	}
	{
		int x = 37;
		int result;
		EXPECT_EQ(CPPY_INT_bit_count(x, &result), PyException::Ok);
		EXPECT_EQ(result, 3);
	}
	{
		int x = -30665;
		int result;
		EXPECT_EQ(CPPY_INT_bit_count(x, &result), PyException::Ok);
		EXPECT_EQ(result, 10);
	}
}

TEST(TEST_CPPY_SET, init) {
	{
		int elements[10]{ 0,1,2,3,4,5,4,3,2,1 };
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_init(10, elements, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 6);
	}
	{
		double elements[10]{ 0.,1.,2.,3.,4.,5.,4.,3.,2.,1. };
		std::set<double> result;
		EXPECT_EQ(CPPY_SET_init(10, elements, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 6);
	}
}

TEST(TEST_CPPY_SET, add) {
	{
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_add(&result, 10), PyException::Ok);
		EXPECT_EQ(result.size(), 1);
	}
	{
		std::set<int> result{1, 2};
		EXPECT_EQ(CPPY_SET_add(&result, 10), PyException::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> result{1, 2};
		EXPECT_EQ(CPPY_SET_add(&result, 1), PyException::Ok);
		EXPECT_EQ(result.size(), 2);
	}
}

TEST(TEST_CPPY_SET, clear) {
	std::set<int> result{1, 2, 3};
	EXPECT_EQ(CPPY_SET_clear(&result), PyException::Ok);
	EXPECT_EQ(result.size(), 0);
}

TEST(TEST_CPPY_SET, copy) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_copy(a, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_copy(a, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 10);
	}
}

TEST(TEST_CPPY_SET, difference) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 0);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 2);
		bool is_contain;
		EXPECT_EQ(CPPY_SET_contains(result, 1, &is_contain), PyException::Ok);
		EXPECT_TRUE(is_contain);
		EXPECT_EQ(CPPY_SET_contains(result, 2, &is_contain), PyException::Ok);
		EXPECT_TRUE(is_contain);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 3);
	}
}

TEST(TEST_CPPY_SET, difference_update) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		EXPECT_EQ(CPPY_SET_difference_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 0);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 2);
		bool is_contain;
		EXPECT_EQ(CPPY_SET_contains(a, 1, &is_contain), PyException::Ok);
		EXPECT_TRUE(is_contain);
		EXPECT_EQ(CPPY_SET_contains(a, 2, &is_contain), PyException::Ok);
		EXPECT_TRUE(is_contain);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		EXPECT_EQ(CPPY_SET_difference_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 3);
	}
}

TEST(TEST_CPPY_SET, intersection) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_intersection(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_intersection(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 1);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_intersection(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 0);
	}
}

TEST(TEST_CPPY_SET, intersection_update) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		EXPECT_EQ(CPPY_SET_intersection_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		EXPECT_EQ(CPPY_SET_intersection_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 1);
		bool is_contain;
		EXPECT_EQ(CPPY_SET_contains(a, 3, &is_contain), PyException::Ok);
		EXPECT_TRUE(is_contain);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		EXPECT_EQ(CPPY_SET_intersection_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 0);
	}
}

TEST(TEST_CPPY_SET, _union) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_union(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_union(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 5);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_union(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 6);
	}
}

TEST(TEST_CPPY_SET, update) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		EXPECT_EQ(CPPY_SET_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		EXPECT_EQ(CPPY_SET_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 5);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		EXPECT_EQ(CPPY_SET_update(&a, b), PyException::Ok);
		EXPECT_EQ(a.size(), 6);
	}
}

TEST(TEST_CPPY_SET, pop) {
	{
		std::set<int> a{1, 2, 3};
		int result;
		EXPECT_EQ(CPPY_SET_pop(&a, &result), PyException::Ok);
		EXPECT_EQ(a.size(), 2);
	}
	{
		std::set<int> a;
		int result;
		EXPECT_EQ(CPPY_SET_pop(&a, &result), PyException::KeyError);
	}
}

TEST(TEST_CPPY_SET, remove) {
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_remove(&a, 1), PyException::Ok);
		EXPECT_EQ(a.size(), 2);
	}
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_remove(&a, 0), PyException::KeyError);
		EXPECT_EQ(a.size(), 3);
	}
}

TEST(TEST_CPPY_SET, discard) {
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_discard(&a, 1), PyException::Ok);
		EXPECT_EQ(a.size(), 2);
	}
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_discard(&a, 0), PyException::Ok);
		EXPECT_EQ(a.size(), 3);
	}
}

TEST(TEST_CPPY_SET, isdisjoint) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		bool result;
		EXPECT_EQ(CPPY_SET_isdisjoint(a, b, &result), PyException::Ok);
		EXPECT_TRUE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_isdisjoint(a, b, &result), PyException::Ok);
		EXPECT_FALSE(result);
	}
}

TEST(TEST_CPPY_SET, issubset) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		bool result;
		EXPECT_EQ(CPPY_SET_issubset(a, b, &result), PyException::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issubset(a, b, &result), PyException::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issubset(a, b, &result), PyException::Ok);
		EXPECT_TRUE(result);
	}
}

TEST(TEST_CPPY_SET, issuperset) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		bool result;
		EXPECT_EQ(CPPY_SET_issuperset(a, b, &result), PyException::Ok);
		EXPECT_TRUE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issuperset(a, b, &result), PyException::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issuperset(a, b, &result), PyException::Ok);
		EXPECT_FALSE(result);
	}
}

TEST(TEST_CPPY_SET, symmetric_difference) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_symmetric_difference(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 1);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_symmetric_difference(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 4);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_symmetric_difference(a, b, &result), PyException::Ok);
		EXPECT_EQ(result.size(), 2);
	}
}