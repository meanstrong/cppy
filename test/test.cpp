#include <iostream>
#include <fstream>

#include "cppy/cppy.h"
#include <gtest/gtest.h>

TEST(TEST_CPPY_STR, count) {
	std::string s = "AAAAA";
	int count;
	EXPECT_EQ(CPPY_STR_count(s, "A", &count), CPPY_ERROR_t::Ok);
	EXPECT_EQ(count, 5);
	EXPECT_EQ(CPPY_STR_count(s, "AA", &count), CPPY_ERROR_t::Ok);
	EXPECT_EQ(count, 2);
	EXPECT_EQ(CPPY_STR_count(s, "AAA", &count), CPPY_ERROR_t::Ok);
	EXPECT_EQ(count, 1);
	EXPECT_EQ(CPPY_STR_count(s, "AA", &count, 4), CPPY_ERROR_t::Ok);
	EXPECT_EQ(count, 0);
}

TEST(TEST_CPPY_STR, strip) {
	{
		std::string s = "AAAAA";
		std::string result;
		EXPECT_EQ(CPPY_STR_strip(s, &result, "A"), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 0);
	}
	{
		std::string s = " \t \tAAAAA\r\n";
		std::string result;
		EXPECT_EQ(CPPY_STR_strip(s, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 5);
	}
	{
		std::string s = "ABCDBA";
		std::string result;
		EXPECT_EQ(CPPY_STR_strip(s, &result, "AB"), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 2);
	}
}

TEST(TEST_CPPY_STR, split) {
	std::string s = "A B\tC\nD E   F";
	{
		std::vector<std::string> result;
		EXPECT_EQ(CPPY_STR_split(s, &result), CPPY_ERROR_t::Ok);
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
		EXPECT_EQ(CPPY_STR_split(s, &result, " "), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 6);
		EXPECT_EQ(result[0], "A");
		EXPECT_EQ(result[1], "B\tC\nD");
		EXPECT_EQ(result[2], "E");
		EXPECT_EQ(result[3], "");
		EXPECT_EQ(result[4], "");
		EXPECT_EQ(result[5], "F");
	}
}

TEST(TEST_CPPY_STR, rsplit) {
	std::string s = "A B\tC\nD E   F";
	{
		std::vector<std::string> result;
		EXPECT_EQ(CPPY_STR_rsplit(s, &result, 2), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
		EXPECT_EQ(result[0], "A B\tC\nD");
		EXPECT_EQ(result[1], "E");
		EXPECT_EQ(result[2], "F");
	}
	{
		std::vector<std::string> result;
		EXPECT_EQ(CPPY_STR_rsplit(s, &result, " ", 2), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
		EXPECT_EQ(result[0], "A B\tC\nD E ");
		EXPECT_EQ(result[1], "");
		EXPECT_EQ(result[2], "F");
	}
}

TEST(TEST_CPPY_STR, find) {
	std::string s = "ABCD";
	{
		int result;
		EXPECT_EQ(CPPY_STR_find(s, "CD", &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 2);
	}
	{
		int result;
		EXPECT_EQ(CPPY_STR_find(s, "E", &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, -1);
	}
}

TEST(TEST_CPPY_STR, index) {
	std::string s = "ABCD";
	{
		int result;
		EXPECT_EQ(CPPY_STR_index(s, "CD", &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 2);
	}
	{
		int result;
		EXPECT_EQ(CPPY_STR_index(s, "E", &result), CPPY_ERROR_t::ValueError);
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
		EXPECT_EQ(CPPY_STR_lower(s, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, "aabbccdd");
	}
	{
		std::string s = "123Aa456";
		std::string result;
		EXPECT_EQ(CPPY_STR_lower(s, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, "123aa456");
	}
}

TEST(TEST_CPPY_STR, at) {
	std::string s = "123";
	char result;
	EXPECT_EQ(CPPY_STR_at(s, 0, &result), CPPY_ERROR_t::Ok);
	EXPECT_EQ(result, '1');
	EXPECT_EQ(CPPY_STR_at(s, 2, &result), CPPY_ERROR_t::Ok);
	EXPECT_EQ(result, '3');
	EXPECT_EQ(CPPY_STR_at(s, -2, &result), CPPY_ERROR_t::Ok);
	EXPECT_EQ(result, '2');
	EXPECT_EQ(CPPY_STR_at(s, 3, &result), CPPY_ERROR_t::IndexError);
	EXPECT_EQ(CPPY_STR_at(s, -4, &result), CPPY_ERROR_t::IndexError);
}

TEST(TEST_CPPY_STR, encode) {
	std::string result;
	EXPECT_EQ(CPPY_STR_encode(L"ÖÐÎÄ", &result), CPPY_ERROR_t::Ok);
	char c;
	char expect[6]{ 0xe4, 0xb8, 0xad, 0xe6, 0x96, 0x87 };
	for (int i = 0; i < 6; i++)
	{
		EXPECT_EQ(CPPY_STR_at(result, i, &c), CPPY_ERROR_t::Ok);
		EXPECT_EQ(c, expect[i]);
	}
}

TEST(TEST_CPPY_INT, init) {
	{
		std::string s = "+123";
		int result;
		EXPECT_EQ(CPPY_INT_init(&result, s), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 123);
	}
	{
		std::string s = "-123";
		int result;
		EXPECT_EQ(CPPY_INT_init(&result, s), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, -123);
	}
	{
		std::string s = "99999999999999999999999999999999";
		int result;
		EXPECT_EQ(CPPY_INT_init(&result, s), CPPY_ERROR_t::OverflowError);
	}
	{
		std::string s = "XXX";
		int result;
		EXPECT_EQ(CPPY_INT_init(&result, s), CPPY_ERROR_t::ValueError);
	}
}

TEST(TEST_CPPY_INT, bit_length) {
	{
		int x = 37;
		int result;
		EXPECT_EQ(CPPY_INT_bit_length(x, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 6);
	}
	{
		int x = 30665;
		int result;
		EXPECT_EQ(CPPY_INT_bit_length(x, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 15);
	}
}

TEST(TEST_CPPY_INT, bit_count) {
	{
		int x = 13;
		int result;
		EXPECT_EQ(CPPY_INT_bit_count(x, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 3);
	}
	{
		int x = 37;
		int result;
		EXPECT_EQ(CPPY_INT_bit_count(x, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 3);
	}
	{
		int x = -30665;
		int result;
		EXPECT_EQ(CPPY_INT_bit_count(x, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result, 10);
	}
}

TEST(TEST_CPPY_SET, init) {
	{
		int elements[10]{ 0,1,2,3,4,5,4,3,2,1 };
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_init(&result, 10, elements), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 6);
	}
	{
		double elements[10]{ 0.,1.,2.,3.,4.,5.,4.,3.,2.,1. };
		std::set<double> result;
		EXPECT_EQ(CPPY_SET_init(&result, 10, elements), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 6);
	}
	{
		std::vector<int> input{1, 2, 3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_init(&result, input.begin(), input.end()), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 5);
	}
}

TEST(TEST_CPPY_SET, add) {
	{
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_add(&result, 10), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 1);
	}
	{
		std::set<int> result{1, 2};
		EXPECT_EQ(CPPY_SET_add(&result, 10), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> result{1, 2};
		EXPECT_EQ(CPPY_SET_add(&result, 1), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 2);
	}
}

TEST(TEST_CPPY_SET, clear) {
	std::set<int> result{1, 2, 3};
	EXPECT_EQ(CPPY_SET_clear(&result), CPPY_ERROR_t::Ok);
	EXPECT_EQ(result.size(), 0);
}

TEST(TEST_CPPY_SET, copy) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_copy(a, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_copy(a, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 10);
	}
}

TEST(TEST_CPPY_SET, difference) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 0);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 2);
		bool is_contain;
		EXPECT_EQ(CPPY_SET_iscontain(result, 1, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(is_contain);
		EXPECT_EQ(CPPY_SET_iscontain(result, 2, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(is_contain);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
	}
}

TEST(TEST_CPPY_SET, difference_update) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		EXPECT_EQ(CPPY_SET_difference_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 0);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_difference_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 2);
		bool is_contain;
		EXPECT_EQ(CPPY_SET_iscontain(a, 1, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(is_contain);
		EXPECT_EQ(CPPY_SET_iscontain(a, 2, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(is_contain);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		EXPECT_EQ(CPPY_SET_difference_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 3);
	}
}

TEST(TEST_CPPY_SET, intersection) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_intersection(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_intersection(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 1);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_intersection(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 0);
	}
}

TEST(TEST_CPPY_SET, intersection_update) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		EXPECT_EQ(CPPY_SET_intersection_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		EXPECT_EQ(CPPY_SET_intersection_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 1);
		bool is_contain;
		EXPECT_EQ(CPPY_SET_iscontain(a, 3, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(is_contain);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		EXPECT_EQ(CPPY_SET_intersection_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 0);
	}
}

TEST(TEST_CPPY_SET, _union) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_union(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_union(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 5);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_union(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 6);
	}
}

TEST(TEST_CPPY_SET, update) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3};
		EXPECT_EQ(CPPY_SET_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 3);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		EXPECT_EQ(CPPY_SET_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 5);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		EXPECT_EQ(CPPY_SET_update(&a, b), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 6);
	}
}

TEST(TEST_CPPY_SET, pop) {
	{
		std::set<int> a{1, 2, 3};
		int result;
		EXPECT_EQ(CPPY_SET_pop(&a, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 2);
	}
	{
		std::set<int> a;
		int result;
		EXPECT_EQ(CPPY_SET_pop(&a, &result), CPPY_ERROR_t::KeyError);
	}
}

TEST(TEST_CPPY_SET, remove) {
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_remove(&a, 1), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 2);
	}
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_remove(&a, 0), CPPY_ERROR_t::KeyError);
		EXPECT_EQ(a.size(), 3);
	}
}

TEST(TEST_CPPY_SET, discard) {
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_discard(&a, 1), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 2);
	}
	{
		std::set<int> a{1, 2, 3};
		EXPECT_EQ(CPPY_SET_discard(&a, 0), CPPY_ERROR_t::Ok);
		EXPECT_EQ(a.size(), 3);
	}
}

TEST(TEST_CPPY_SET, isdisjoint) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{4, 5, 6};
		bool result;
		EXPECT_EQ(CPPY_SET_isdisjoint(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_isdisjoint(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
}

TEST(TEST_CPPY_SET, issubset) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		bool result;
		EXPECT_EQ(CPPY_SET_issubset(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issubset(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issubset(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(result);
	}
}

TEST(TEST_CPPY_SET, issuperset) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		bool result;
		EXPECT_EQ(CPPY_SET_issuperset(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issuperset(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_issuperset(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
}

TEST(TEST_CPPY_SET, symmetric_difference) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_symmetric_difference(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 1);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_symmetric_difference(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 4);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2, 3, 4, 5};
		std::set<int> result;
		EXPECT_EQ(CPPY_SET_symmetric_difference(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 2);
	}
}

TEST(TEST_CPPY_SET, equal) {
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{1, 2};
		bool result;
		EXPECT_EQ(CPPY_SET_eq(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 4, 5};
		bool result;
		EXPECT_EQ(CPPY_SET_eq(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(result);
	}
	{
		std::set<int> a{1, 2, 3};
		std::set<int> b{3, 2, 1};
		bool result;
		EXPECT_EQ(CPPY_SET_eq(a, b, &result), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(result);
	}
}


TEST(TEST_CPPY_SET, iterator) {
	{
		std::set<int> a{};
		int* result{ nullptr };
		EXPECT_EQ(CPPY_SET_iter(a, result), CPPY_ERROR_t::Ok);
	}
	{
		std::set<int> a{1, 2, 3};
		int result[3];
		EXPECT_EQ(CPPY_SET_iter(a, result), CPPY_ERROR_t::Ok);
	}
}

TEST(TEST_CPPY_VECTOR, init) {
	{
		std::vector<int> this_vector;
		int data[3]{ 1, 2, 3 };
		EXPECT_EQ(CPPY_VECTOR_init(&this_vector, 3, data), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 3);
		EXPECT_EQ(this_vector[0], 1);
		EXPECT_EQ(this_vector[1], 2);
		EXPECT_EQ(this_vector[2], 3);
	}
	{
		std::vector<int> this_vector;
		std::vector<int> data{ 1, 2, 3 };
		EXPECT_EQ(CPPY_VECTOR_init(&this_vector, data.begin(), data.end()), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 3);
		EXPECT_EQ(this_vector[0], 1);
		EXPECT_EQ(this_vector[1], 2);
		EXPECT_EQ(this_vector[2], 3);
	}
}

TEST(TEST_CPPY_LIST, init) {
	{
		std::list<int> this_vector;
		int data[3]{ 1, 2, 3 };
		EXPECT_EQ(CPPY_LIST_init<int>(&this_vector, 3, data), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 3);
		int i = 0;
		for (auto it = this_vector.begin(); it != this_vector.end(); it++)
		{
			EXPECT_EQ(*it, data[i++]);
		}
	}
	{
		std::list<int> this_vector;
		std::vector<int> data{ 1, 2, 3 };
		EXPECT_EQ(CPPY_LIST_init(&this_vector, data.begin(), data.end()), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 3);
		int i = 0;
		for (auto it = this_vector.begin(); it != this_vector.end(); it++)
		{
			EXPECT_EQ(*it, data[i++]);
		}
	}
}

TEST(TEST_CPPY_VECTOR, copy) {
	std::vector<int> this_vector;
	std::vector<int> data{ 1, 2, 3 };
	EXPECT_EQ(CPPY_VECTOR_copy(data, &this_vector), CPPY_ERROR_t::Ok);
	EXPECT_EQ(this_vector.size(), 3);
	EXPECT_EQ(this_vector[0], 1);
	EXPECT_EQ(this_vector[1], 2);
	EXPECT_EQ(this_vector[2], 3);
}

TEST(TEST_CPPY_VECTOR, clear) {
	std::vector<int> this_vector{1, 2, 3};
	EXPECT_EQ(CPPY_VECTOR_clear(&this_vector), CPPY_ERROR_t::Ok);
	EXPECT_EQ(this_vector.size(), 0);
}

TEST(TEST_CPPY_VECTOR, append) {
	std::vector<int> this_vector{1, 2, 3};
	EXPECT_EQ(CPPY_VECTOR_append(&this_vector, 4), CPPY_ERROR_t::Ok);
	EXPECT_EQ(this_vector.size(), 4);
	EXPECT_EQ(this_vector[3], 4);
}

TEST(TEST_CPPY_VECTOR, iscontain) {
	{
		std::vector<int> this_vector{1, 2, 3};
		bool is_contain;
		EXPECT_EQ(CPPY_VECTOR_contains(this_vector, 0, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(is_contain);
	}
	{
		std::vector<int> this_vector{1, 2, 3};
		bool is_contain;
		EXPECT_EQ(CPPY_VECTOR_contains(this_vector, 2, &is_contain), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(is_contain);
	}
}

TEST(TEST_CPPY_VECTOR, count) {
	std::vector<int> this_vector{1, 2, 3};
	int count;
	EXPECT_EQ(CPPY_VECTOR_count(this_vector, 1, &count), CPPY_ERROR_t::Ok);
	EXPECT_EQ(count, 1);
}

TEST(TEST_CPPY_VECTOR, extend) {
	std::vector<int> this_vector{1, 2, 3};
	std::vector<int> data{ 4, 5, 6 };
	EXPECT_EQ(CPPY_VECTOR_extend(&this_vector, data.begin(), data.end()), CPPY_ERROR_t::Ok);
	EXPECT_EQ(this_vector.size(), 6);
	EXPECT_EQ(this_vector[0], 1);
	EXPECT_EQ(this_vector[1], 2);
	EXPECT_EQ(this_vector[2], 3);
	EXPECT_EQ(this_vector[3], 4);
	EXPECT_EQ(this_vector[4], 5);
	EXPECT_EQ(this_vector[5], 6);
}

TEST(TEST_CPPY_VECTOR, index) {
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		int index = -1;
		EXPECT_EQ(CPPY_VECTOR_index(this_vector, 3, &index), CPPY_ERROR_t::Ok);
		EXPECT_EQ(index, 2);
	}
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		int index = -1;
		EXPECT_EQ(CPPY_VECTOR_index(this_vector, 9, &index), CPPY_ERROR_t::ValueError);
	}
}

TEST(TEST_CPPY_VECTOR, insert) {
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		EXPECT_EQ(CPPY_VECTOR_insert(&this_vector, 0, 10), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 7);
		EXPECT_EQ(this_vector[0], 10);
	}
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		EXPECT_EQ(CPPY_VECTOR_insert(&this_vector, 10, 10), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 7);
		EXPECT_EQ(this_vector[6], 10);
	}
}

TEST(TEST_CPPY_VECTOR, pop) {
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		int data;
		EXPECT_EQ(CPPY_VECTOR_pop(&this_vector, &data, 10), CPPY_ERROR_t::IndexError);
		EXPECT_EQ(this_vector.size(), 6);
	}
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		int data;
		EXPECT_EQ(CPPY_VECTOR_pop(&this_vector, &data), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 5);
		EXPECT_EQ(data, 6);
	}
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		int data;
		EXPECT_EQ(CPPY_VECTOR_pop(&this_vector, &data, -2), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 5);
		EXPECT_EQ(data, 5);
	}
}

TEST(TEST_CPPY_VECTOR, remove) {
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		EXPECT_EQ(CPPY_VECTOR_remove(&this_vector, 10), CPPY_ERROR_t::ValueError);
		EXPECT_EQ(this_vector.size(), 6);
	}
	{
		std::vector<int> this_vector{1, 2, 3, 4, 5, 6};
		EXPECT_EQ(CPPY_VECTOR_remove(&this_vector, 3), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector.size(), 5);
	}
}

TEST(TEST_CPPY_VECTOR, mul) {
	{
		std::vector<int> this_vector{ 1, 2, 3};
		std::vector<int> result;
		EXPECT_EQ(CPPY_VECTOR_mul(this_vector, 3, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 9);
	}
	{
		std::vector<int> this_vector{ 1, 2, 3};
		std::vector<int> result;
		EXPECT_EQ(CPPY_VECTOR_mul(this_vector, 0, &result), CPPY_ERROR_t::Ok);
		EXPECT_EQ(result.size(), 0);
	}
}

TEST(TEST_CPPY_VECTOR, isequal) {
	{
		std::vector<int> this_vector{ 1, 2, 3};
		std::vector<int> other_vector{ 1, 2, 3};
		bool isequal;
		EXPECT_EQ(CPPY_VECTOR_eq(this_vector, other_vector, &isequal), CPPY_ERROR_t::Ok);
		EXPECT_TRUE(isequal);
	}
	{
		std::vector<int> this_vector{ 1, 2, 3};
		std::vector<int> other_vector{ 1, 2, 4};
		bool isequal;
		EXPECT_EQ(CPPY_VECTOR_eq(this_vector, other_vector, &isequal), CPPY_ERROR_t::Ok);
		EXPECT_FALSE(isequal);
	}
}

TEST(TEST_CPPY_VECTOR, iterator) {
	{
		std::vector<int> this_vector{ 1, 2, 3};
		int data[3];
		EXPECT_EQ(CPPY_VECTOR_iter(this_vector, data), CPPY_ERROR_t::Ok);
		EXPECT_EQ(data[0], 1);
		EXPECT_EQ(data[1], 2);
		EXPECT_EQ(data[2], 3);
	}
}

TEST(TEST_CPPY_VECTOR, reverse) {
	{
		std::vector<int> this_vector{ 1, 2, 3};
		EXPECT_EQ(CPPY_VECTOR_reverse(&this_vector), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector[0], 3);
		EXPECT_EQ(this_vector[1], 2);
		EXPECT_EQ(this_vector[2], 1);
	}
}

TEST(TEST_CPPY_VECTOR, sort) {
	{
		std::vector<int> this_vector{ 1, 2, 3, 2, 1};
		EXPECT_EQ(CPPY_VECTOR_sort(&this_vector), CPPY_ERROR_t::Ok);
		EXPECT_EQ(this_vector[0], 1);
		EXPECT_EQ(this_vector[1], 1);
		EXPECT_EQ(this_vector[2], 2);
		EXPECT_EQ(this_vector[3], 2);
		EXPECT_EQ(this_vector[4], 3);
	}
}

TEST(TEST_CPPY_PLATFORM, memory) {
	DWORDLONG total, available;
	CPPY_PLATFORM_memory(&total, &available);
}

TEST(TEST_CPPY_PLATFORM, cpu_percent) {
	double percent = 0.;
	CPPY_PLATFORM_cpu_percent(&percent, 1);
}

TEST(TEST_CPPY_IO, text_file) {
	{
		std::ofstream stream;
		CPPY_IO_open("D:\\1.txt", &stream, "w");
		CPPY_IO_write(stream, "12345\n67890\n\n0000");
		CPPY_IO_close(stream);
	}
	{
		std::ifstream stream;
		CPPY_IO_open("D:\\1.txt", &stream);
		std::string content;
		while (CPPY_IO_readline(stream, &content) == CPPY_ERROR_t::Ok)
			std::cout << content << std::endl;
		CPPY_IO_close(stream);
	}

}

TEST(TEST_CPPY_BUILTINS, linspace) {
	{
		double result[5];
		CPPY_BUILTINS_linspace(0.0, 1.0, 5, result);
		EXPECT_NEAR(result[0], 0.0, 1.0e-16);
		EXPECT_NEAR(result[4], 1.0, 1.0e-16);
	}
	{
		double result[5];
		CPPY_BUILTINS_linspace(0.0, 1.0, 5, result, false);
		EXPECT_NEAR(result[0], 0.0, 1.0e-16);
		EXPECT_NEAR(result[4], 0.8, 1.0e-16);
	}
}

TEST(TEST_CPPY_BUILTINS, _max) {
	{
		double data[5]{ 0., 2., 5., 3., 4. };
		double result;
		CPPY_BUILTINS_max(data, data + 5, &result);
		EXPECT_NEAR(result, 5., 1.0e-16);
	}
	{
		double result;
		CPPY_BUILTINS_max(std::initializer_list{ 0., 2., 5., 3., 4. }, & result);
		EXPECT_NEAR(result, 5., 1.0e-16);
	}
}

TEST(TEST_CPPY_BUILTINS, _min) {
	{
		double data[5]{ 0., 2., 5., 3., 4. };
		double result;
		CPPY_BUILTINS_min(data, data + 5, &result);
		EXPECT_NEAR(result, 0., 1.0e-16);
	}
	{
		double result;
		CPPY_BUILTINS_min(std::initializer_list{ 0., 2., 5., 3., 4. }, & result);
		EXPECT_NEAR(result, 0., 1.0e-16);
	}
}

TEST(TEST_CPPY_BUILTINS, all) {
	{
		std::vector<int> data{ 2, 1, 3, 4 };
		bool result;
		CPPY_BUILTINS_all(data.begin(), data.end(), [](int x) { return x > 0; }, &result);
		EXPECT_TRUE(result);
	}
	{
		std::vector<int> data{ 2, 1, 3, 4 };
		bool result;
		CPPY_BUILTINS_all(data.begin(), data.end(), [](int x) { return x > 1; }, &result);
		EXPECT_FALSE(result);
	}
	{
		std::vector<int> data;
		bool result;
		CPPY_BUILTINS_all(data.begin(), data.end(), [](int x) { return x > 0; }, &result);
		EXPECT_TRUE(result);
	}
}

TEST(TEST_CPPY_BUILTINS, any) {
	{
		std::vector<int> data{ 2, 1, 3, 4 };
		bool result;
		CPPY_BUILTINS_any(data.begin(), data.end(), [](int x) { return x > 0; }, &result);
		EXPECT_TRUE(result);
	}
	{
		std::vector<int> data{ 2, 1, 3, 4 };
		bool result;
		CPPY_BUILTINS_any(data.begin(), data.end(), [](int x) { return x > 4; }, &result);
		EXPECT_FALSE(result);
	}
	{
		std::vector<int> data;
		bool result;
		CPPY_BUILTINS_any(data.begin(), data.end(), [](int x) { return x > 0; }, &result);
		EXPECT_FALSE(result);
	}
}

TEST(TEST_CPPY_DATETIME, duration) {
	std::chrono::steady_clock::time_point start, end;
	CPPY_DATETIME_now(&start);
	int i = 100;
	while (i-- > 0);
	CPPY_DATETIME_now(&end);

	std::chrono::nanoseconds::rep duration;
	CPPY_DATETIME_duration<std::chrono::nanoseconds>(start, end, &duration);
	EXPECT_GT(duration, 0);
}

TEST(TEST_CPPY_EXPECT, expect) {
	CPPY_EXPECT(true) << "this is true";
	CPPY_EXPECT(false) << "this is false";
}

TEST(TEST_CPPY_ASSERT, assert) {
	CPPY_ASSERT(true) << "this is true";
	try { CPPY_ASSERT(false) << "this is false"; }
	catch (const CPPY_Assertion_message& result) {
		std::cout << result.message() << std::endl;
	}

}

TEST(TEST_CPPY_RANDOM, random) {
	{
		double x;
		CPPY_RANDOM_random(1.0, 10.0, &x);
		EXPECT_GE(x, 1.0);
		EXPECT_LT(x, 10.0);
	}
}

TEST(TEST_CPPY_RANDOM, randint) {
	{
		int x;
		CPPY_RANDOM_randint(1, 10, &x);
		EXPECT_GE(x, 1);
		EXPECT_LE(x, 10);
	}
}

TEST(TEST_CPPY_thread, thread_pool) {
	ThreadPoolExecutor pool(static_cast<size_t>(4));
	std::vector<int> args{ 1, 2, 3, 4 };
	std::vector<std::future<int>> futures;

	for (const int& x : args) {
		futures.push_back(pool.submit([](const int x) { return x * 2; }, x));
	}

	for (size_t i = 0; i < args.size(); i++)
	{
		EXPECT_EQ(futures[i].get(), args[i] * 2);
	}
}