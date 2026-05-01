#include <fstream>
#include <iostream>

#ifdef _WIN32
#    include <windows.h>
#endif

#include <gtest/gtest.h>
#include "cppy/cppy.h"

TEST(TEST_CPPY_STR, count)
{
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

TEST(TEST_CPPY_STR, strip)
{
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

TEST(TEST_CPPY_STR, split)
{
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

TEST(TEST_CPPY_STR, rsplit)
{
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

TEST(TEST_CPPY_STR, find)
{
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

TEST(TEST_CPPY_STR, index)
{
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

TEST(TEST_CPPY_STR, format)
{
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

TEST(TEST_CPPY_STR, lower)
{
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

TEST(TEST_CPPY_STR, join)
{
    {
        std::string s[]{"123", "456", "789"};
        std::string result;
        EXPECT_EQ(CPPY_STR_join("", s, s + 3, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, "123456789");
    }
    {
        std::vector<std::string> s{"123", "456", "789"};
        std::string result;
        EXPECT_EQ(CPPY_STR_join(",", s.begin(), s.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, "123,456,789");
    }
}

TEST(TEST_CPPY_STR, at)
{
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

TEST(TEST_CPPY_STR, encode)
{
    std::string result;
#ifdef _WIN32
    EXPECT_EQ(CPPY_STR_encode(L"\u4E2D\u6587", &result, CP_UTF8), CPPY_ERROR_t::Ok);
#else
    EXPECT_EQ(CPPY_STR_encode(L"\u4E2D\u6587", &result, "UTF-8"), CPPY_ERROR_t::Ok);
#endif
    char c;
    char expect[6];
    expect[0] = static_cast<char>(0xe4);
    expect[1] = static_cast<char>(0xb8);
    expect[2] = static_cast<char>(0xad);
    expect[3] = static_cast<char>(0xe6);
    expect[4] = static_cast<char>(0x96);
    expect[5] = static_cast<char>(0x87);
    for (int i = 0; i < 6; i++)
    {
        EXPECT_EQ(CPPY_STR_at(result, i, &c), CPPY_ERROR_t::Ok);
        EXPECT_EQ(c, expect[i]);
    }
}

TEST(TEST_CPPY_STR, startswith)
{
    {
        std::string s = "hello world";
        bool result;
        EXPECT_EQ(CPPY_STR_startswith(s, "hello", &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, true);
    }
    {
        std::string s = "hello world";
        bool result;
        EXPECT_EQ(CPPY_STR_startswith(s, "world", &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, false);
    }
}

TEST(TEST_CPPY_STR, endswith)
{
    {
        std::string s = "hello world";
        bool result;
        EXPECT_EQ(CPPY_STR_endswith(s, "world", &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, true);
    }
    {
        std::string s = "hello world";
        bool result;
        EXPECT_EQ(CPPY_STR_endswith(s, "hello", &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, false);
    }
}

TEST(TEST_CPPY_STR, partition)
{
    std::string result[3];
    EXPECT_EQ(CPPY_STR_partition("hello:world", ":", result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], ":");
    EXPECT_EQ(result[2], "world");
}

TEST(TEST_CPPY_STR, rpartition)
{
    std::string result[3];
    EXPECT_EQ(CPPY_STR_rpartition("hello:world:test", ":", result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result[0], "hello:world");
    EXPECT_EQ(result[1], ":");
    EXPECT_EQ(result[2], "test");
}

TEST(TEST_CPPY_STR, slice)
{
    {
        std::string s = "hello world";
        std::string result;
        EXPECT_EQ(CPPY_STR_slice(s, &result, 0, 5), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, "hello");
    }
    {
        std::string s = "hello world";
        std::string result;
        EXPECT_EQ(CPPY_STR_slice(s, &result, 6, 11), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, "world");
    }
    {
        std::string s = "hello world";
        std::string result;
        EXPECT_EQ(CPPY_STR_slice(s, &result, 0, 11, 2), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, "hlowrd");
    }
}

TEST(TEST_CPPY_STR, replace)
{
    std::string s = "hello hello world";
    std::string result;
    EXPECT_EQ(CPPY_STR_replace(s, "hello", "hi", &result, -1), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "hi hi world");
}

TEST(TEST_CPPY_STR, upper)
{
    std::string s = "Hello World";
    std::string result;
    EXPECT_EQ(CPPY_STR_upper(s, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "HELLO WORLD");
}

TEST(TEST_CPPY_STR, rfind)
{
    std::string s = "hello hello world";
    int result;
    EXPECT_EQ(CPPY_STR_rfind(s, "hello", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, 6);
}

TEST(TEST_CPPY_STR, rindex)
{
    std::string s = "hello hello world";
    int result;
    EXPECT_EQ(CPPY_STR_rindex(s, "hello", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, 6);
}

TEST(TEST_CPPY_STR, isspace)
{
    {
        std::string s = "   \t\n";
        bool result;
        EXPECT_EQ(CPPY_STR_isspace(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, true);
    }
    {
        std::string s = "hello";
        bool result;
        EXPECT_EQ(CPPY_STR_isspace(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, false);
    }
}

TEST(TEST_CPPY_STR, isalpha)
{
    {
        std::string s = "HelloWorld";
        bool result;
        EXPECT_EQ(CPPY_STR_isalpha(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, true);
    }
    {
        std::string s = "Hello123";
        bool result;
        EXPECT_EQ(CPPY_STR_isalpha(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, false);
    }
}

TEST(TEST_CPPY_STR, isdigit)
{
    {
        std::string s = "12345";
        bool result;
        EXPECT_EQ(CPPY_STR_isdigit(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, true);
    }
    {
        std::string s = "123a";
        bool result;
        EXPECT_EQ(CPPY_STR_isdigit(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, false);
    }
}

TEST(TEST_CPPY_STR, isalnum)
{
    {
        std::string s = "Hello123";
        bool result;
        EXPECT_EQ(CPPY_STR_isalnum(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, true);
    }
    {
        std::string s = "Hello@World";
        bool result;
        EXPECT_EQ(CPPY_STR_isalnum(s, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result, false);
    }
}

TEST(TEST_CPPY_STR, islower)
{
    bool result;
    EXPECT_EQ(CPPY_STR_islower("hello world", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_islower("Hello World", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_islower("", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_islower("123!@#", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_islower("   ", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_islower("a", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_islower("hello123", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
}

TEST(TEST_CPPY_STR, isupper)
{
    bool result;
    EXPECT_EQ(CPPY_STR_isupper("HELLO WORLD", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_isupper("Hello World", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_isupper("", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_isupper("123!@#", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_isupper("   ", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_isupper("A", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_isupper("HELLO123", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
}

TEST(TEST_CPPY_STR, istitle)
{
    bool result;
    EXPECT_EQ(CPPY_STR_istitle("Hello World", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_istitle("hello world", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_istitle("", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_istitle("   ", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_istitle("123!@#", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_istitle("A", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_istitle("a", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ(CPPY_STR_istitle("Hello   World   123", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ(CPPY_STR_istitle("Hello WOrld", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
}

TEST(TEST_CPPY_STR, mul)
{
    std::string s = "abc";
    std::string result;
    EXPECT_EQ(CPPY_STR_mul(s, 3, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "abcabcabc");
}

TEST(TEST_CPPY_STR, capitalize)
{
    std::string s = "hello world";
    std::string result;
    EXPECT_EQ(CPPY_STR_capitalize(s, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "Hello world");
}

TEST(TEST_CPPY_STR, swapcase)
{
    std::string s = "Hello World";
    std::string result;
    EXPECT_EQ(CPPY_STR_swapcase(s, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "hELLO wORLD");
}

TEST(TEST_CPPY_STR, title)
{
    std::string s = "hello world";
    std::string result;
    EXPECT_EQ(CPPY_STR_title(s, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "Hello World");
}

TEST(TEST_CPPY_STR, removeprefix)
{
    std::string s = "TestHello";
    std::string result;
    EXPECT_EQ(CPPY_STR_removeprefix(s, "Test", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "Hello");
}

TEST(TEST_CPPY_STR, removesuffix)
{
    std::string s = "HelloTest";
    std::string result;
    EXPECT_EQ(CPPY_STR_removesuffix(s, "Test", &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "Hello");
}

TEST(TEST_CPPY_STR, zfill)
{
    std::string s = "42";
    std::string result;
    EXPECT_EQ(CPPY_STR_zfill(s, 5, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "00042");
}

TEST(TEST_CPPY_STR, ljust)
{
    std::string s = "hello";
    std::string result;
    EXPECT_EQ(CPPY_STR_ljust(s, 10, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "hello     ");
}

TEST(TEST_CPPY_STR, rjust)
{
    std::string s = "hello";
    std::string result;
    EXPECT_EQ(CPPY_STR_rjust(s, 10, &result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "     hello");
}

TEST(TEST_CPPY_STR, center)
{
    std::string s = "hello";
    std::string result;
    EXPECT_EQ(CPPY_STR_center(s, 11, &result, ' '), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "   hello   ");
}

TEST(TEST_CPPY_STR, expandtabs)
{
    std::string s = "hello\tworld";
    std::string result;
    EXPECT_EQ(CPPY_STR_expandtabs(s, &result, 8), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, "hello   world");
}

TEST(TEST_CPPY_STR, splitlines)
{
    std::string s = "hello\nworld\r\ntest";
    std::vector<std::string> result;
    EXPECT_EQ(CPPY_STR_splitlines(s, &result, false), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
    EXPECT_EQ(result[2], "test");
}

TEST(TEST_CPPY_INT, init)
{
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

TEST(TEST_CPPY_INT, bit_length)
{
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

TEST(TEST_CPPY_INT, bit_count)
{
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

TEST(TEST_CPPY_SET, init)
{
    {
        int elements[10]{0, 1, 2, 3, 4, 5, 4, 3, 2, 1};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_init(&result, elements, elements + 10), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 6);
    }
    {
        double elements[10]{0., 1., 2., 3., 4., 5., 4., 3., 2., 1.};
        std::set<double> result;
        EXPECT_EQ(CPPY_SET_init(&result, elements, elements + 10), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 6);
    }
    {
        std::vector<int> input{1, 2, 3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_init(&result, input.begin(), input.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 5);
    }
}

TEST(TEST_CPPY_SET, add)
{
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

TEST(TEST_CPPY_SET, clear)
{
    std::set<int> result{1, 2, 3};
    EXPECT_EQ(CPPY_SET_clear(&result), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result.size(), 0);
}

TEST(TEST_CPPY_SET, copy)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_copy(a.begin(), a.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 3);
    }
    {
        std::set<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_copy(a.begin(), a.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 10);
    }
}

TEST(TEST_CPPY_SET, difference)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_difference(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 0);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_difference(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
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
        EXPECT_EQ(CPPY_SET_difference(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 3);
    }
}

TEST(TEST_CPPY_SET, difference_update)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3};
        EXPECT_EQ(CPPY_SET_difference_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 0);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_difference_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
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
        EXPECT_EQ(CPPY_SET_difference_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 3);
    }
}

TEST(TEST_CPPY_SET, intersection)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_intersection(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 3);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_intersection(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 1);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{4, 5, 6};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_intersection(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 0);
    }
}

TEST(TEST_CPPY_SET, intersection_update)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3};
        EXPECT_EQ(CPPY_SET_intersection_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 3);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        EXPECT_EQ(CPPY_SET_intersection_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 1);
        bool is_contain;
        EXPECT_EQ(CPPY_SET_iscontain(a, 3, &is_contain), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(is_contain);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{4, 5, 6};
        EXPECT_EQ(CPPY_SET_intersection_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 0);
    }
}

TEST(TEST_CPPY_SET, _union)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_union(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 3);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_union(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 5);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{4, 5, 6};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_union(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 6);
    }
}

TEST(TEST_CPPY_SET, update)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3};
        EXPECT_EQ(CPPY_SET_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 3);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        EXPECT_EQ(CPPY_SET_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 5);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{4, 5, 6};
        EXPECT_EQ(CPPY_SET_update(&a, b.begin(), b.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(a.size(), 6);
    }
}

TEST(TEST_CPPY_SET, pop)
{
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

TEST(TEST_CPPY_SET, remove)
{
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

TEST(TEST_CPPY_SET, discard)
{
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

TEST(TEST_CPPY_SET, isdisjoint)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{4, 5, 6};
        bool result;
        EXPECT_EQ(CPPY_SET_isdisjoint(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        bool result;
        EXPECT_EQ(CPPY_SET_isdisjoint(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
}

TEST(TEST_CPPY_SET, issubset)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2};
        bool result;
        EXPECT_EQ(CPPY_SET_issubset(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        bool result;
        EXPECT_EQ(CPPY_SET_issubset(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3, 4, 5};
        bool result;
        EXPECT_EQ(CPPY_SET_issubset(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(result);
    }
}

TEST(TEST_CPPY_SET, issuperset)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2};
        bool result;
        EXPECT_EQ(CPPY_SET_issuperset(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        bool result;
        EXPECT_EQ(CPPY_SET_issuperset(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3, 4, 5};
        bool result;
        EXPECT_EQ(CPPY_SET_issuperset(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
}

TEST(TEST_CPPY_SET, symmetric_difference)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 1);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 4);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2, 3, 4, 5};
        std::set<int> result;
        EXPECT_EQ(CPPY_SET_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 2);
    }
}

TEST(TEST_CPPY_SET, isequal)
{
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{1, 2};
        bool result;
        EXPECT_EQ(CPPY_SET_isequal(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 4, 5};
        bool result;
        EXPECT_EQ(CPPY_SET_isequal(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(result);
    }
    {
        std::set<int> a{1, 2, 3};
        std::set<int> b{3, 2, 1};
        bool result;
        EXPECT_EQ(CPPY_SET_isequal(a.begin(), a.end(), b.begin(), b.end(), &result), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(result);
    }
}

TEST(TEST_CPPY_SET, iterator)
{
    {
        std::set<int> a{1, 2, 3};
        EXPECT_EQ(CPPY_Iterable_iter(a.begin(), a.end(), [](int x) { std::cout << x; }), CPPY_ERROR_t::Ok);
    }
    {
        std::set<int> a{1, 2, 3};
        int result[3];
        EXPECT_EQ(CPPY_Iterable_iter(a.begin(), a.end(), result, [](int x) { return x * x; }), CPPY_ERROR_t::Ok);
    }
}

TEST(TEST_CPPY_VECTOR, init)
{
    {
        std::vector<int> this_vector;
        int data[3]{1, 2, 3};
        EXPECT_EQ(CPPY_VECTOR_init(&this_vector, data, data + 3), CPPY_ERROR_t::Ok);
        EXPECT_EQ(this_vector.size(), 3);
        EXPECT_EQ(this_vector[0], 1);
        EXPECT_EQ(this_vector[1], 2);
        EXPECT_EQ(this_vector[2], 3);
    }
    {
        std::vector<int> this_vector;
        std::vector<int> data{1, 2, 3};
        EXPECT_EQ(CPPY_VECTOR_init(&this_vector, data.begin(), data.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(this_vector.size(), 3);
        EXPECT_EQ(this_vector[0], 1);
        EXPECT_EQ(this_vector[1], 2);
        EXPECT_EQ(this_vector[2], 3);
    }
}

TEST(TEST_CPPY_LIST, init)
{
    {
        std::list<int> this_vector;
        int data[3]{1, 2, 3};
        EXPECT_EQ(CPPY_LIST_init<int>(&this_vector, data, data + 3), CPPY_ERROR_t::Ok);
        EXPECT_EQ(this_vector.size(), 3);
        int i = 0;
        for (auto it = this_vector.begin(); it != this_vector.end(); it++)
        {
            EXPECT_EQ(*it, data[i++]);
        }
    }
    {
        std::list<int> this_vector;
        std::vector<int> data{1, 2, 3};
        EXPECT_EQ(CPPY_LIST_init(&this_vector, data.begin(), data.end()), CPPY_ERROR_t::Ok);
        EXPECT_EQ(this_vector.size(), 3);
        int i = 0;
        for (auto it = this_vector.begin(); it != this_vector.end(); it++)
        {
            EXPECT_EQ(*it, data[i++]);
        }
    }
}

TEST(TEST_CPPY_VECTOR, copy)
{
    std::vector<int> this_vector;
    std::vector<int> data{1, 2, 3};
    EXPECT_EQ(CPPY_VECTOR_copy(data, &this_vector), CPPY_ERROR_t::Ok);
    EXPECT_EQ(this_vector.size(), 3);
    EXPECT_EQ(this_vector[0], 1);
    EXPECT_EQ(this_vector[1], 2);
    EXPECT_EQ(this_vector[2], 3);
}

TEST(TEST_CPPY_VECTOR, clear)
{
    std::vector<int> this_vector{1, 2, 3};
    EXPECT_EQ(CPPY_VECTOR_clear(&this_vector), CPPY_ERROR_t::Ok);
    EXPECT_EQ(this_vector.size(), 0);
}

TEST(TEST_CPPY_VECTOR, append)
{
    std::vector<int> this_vector{1, 2, 3};
    EXPECT_EQ(CPPY_VECTOR_append(&this_vector, 4), CPPY_ERROR_t::Ok);
    EXPECT_EQ(this_vector.size(), 4);
    EXPECT_EQ(this_vector[3], 4);
}

TEST(TEST_CPPY_VECTOR, iscontain)
{
    {
        std::vector<int> this_vector{1, 2, 3};
        bool is_contain;
        EXPECT_EQ(CPPY_VECTOR_iscontain(this_vector, 0, &is_contain), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(is_contain);
    }
    {
        std::vector<int> this_vector{1, 2, 3};
        bool is_contain;
        EXPECT_EQ(CPPY_VECTOR_iscontain(this_vector, 2, &is_contain), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(is_contain);
    }
}

TEST(TEST_CPPY_VECTOR, count)
{
    std::vector<int> this_vector{1, 2, 3};
    int count;
    EXPECT_EQ(CPPY_VECTOR_count(this_vector, 1, &count), CPPY_ERROR_t::Ok);
    EXPECT_EQ(count, 1);
}

TEST(TEST_CPPY_VECTOR, extend)
{
    std::vector<int> this_vector{1, 2, 3};
    std::vector<int> data{4, 5, 6};
    EXPECT_EQ(CPPY_VECTOR_extend(&this_vector, data.begin(), data.end()), CPPY_ERROR_t::Ok);
    EXPECT_EQ(this_vector.size(), 6);
    EXPECT_EQ(this_vector[0], 1);
    EXPECT_EQ(this_vector[1], 2);
    EXPECT_EQ(this_vector[2], 3);
    EXPECT_EQ(this_vector[3], 4);
    EXPECT_EQ(this_vector[4], 5);
    EXPECT_EQ(this_vector[5], 6);
}

TEST(TEST_CPPY_VECTOR, index)
{
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

TEST(TEST_CPPY_VECTOR, insert)
{
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

TEST(TEST_CPPY_VECTOR, pop)
{
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

TEST(TEST_CPPY_VECTOR, remove)
{
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

TEST(TEST_CPPY_VECTOR, mul)
{
    {
        std::vector<int> this_vector{1, 2, 3};
        std::vector<int> result;
        EXPECT_EQ(CPPY_VECTOR_mul(this_vector, 3, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 9);
    }
    {
        std::vector<int> this_vector{1, 2, 3};
        std::vector<int> result;
        EXPECT_EQ(CPPY_VECTOR_mul(this_vector, 0, &result), CPPY_ERROR_t::Ok);
        EXPECT_EQ(result.size(), 0);
    }
}

TEST(TEST_CPPY_VECTOR, isequal)
{
    {
        std::vector<int> this_vector{1, 2, 3};
        std::vector<int> other_vector{1, 2, 3};
        bool isequal;
        EXPECT_EQ(CPPY_VECTOR_isequal(this_vector, other_vector, &isequal), CPPY_ERROR_t::Ok);
        EXPECT_TRUE(isequal);
    }
    {
        std::vector<int> this_vector{1, 2, 3};
        std::vector<int> other_vector{1, 2, 4};
        bool isequal;
        EXPECT_EQ(CPPY_VECTOR_isequal(this_vector, other_vector, &isequal), CPPY_ERROR_t::Ok);
        EXPECT_FALSE(isequal);
    }
}

TEST(TEST_CPPY_VECTOR, iterator)
{
    {
        std::vector<int> this_vector{1, 2, 3};
        int data[3];
        EXPECT_EQ(CPPY_Iterable_iter(this_vector.begin(), this_vector.end(), data, [](int x) { return x * x; }),
                  CPPY_ERROR_t::Ok);
        EXPECT_EQ(data[0], 1);
        EXPECT_EQ(data[1], 4);
        EXPECT_EQ(data[2], 9);
    }
}

TEST(TEST_CPPY_VECTOR, reverse)
{
    {
        std::vector<int> this_vector{1, 2, 3};
        EXPECT_EQ(CPPY_VECTOR_reverse(&this_vector), CPPY_ERROR_t::Ok);
        EXPECT_EQ(this_vector[0], 3);
        EXPECT_EQ(this_vector[1], 2);
        EXPECT_EQ(this_vector[2], 1);
    }
}

TEST(TEST_CPPY_VECTOR, sort)
{
    {
        std::vector<int> this_vector{1, 2, 3, 2, 1};
        EXPECT_EQ(CPPY_VECTOR_sort(&this_vector), CPPY_ERROR_t::Ok);
        EXPECT_EQ(this_vector[0], 1);
        EXPECT_EQ(this_vector[1], 1);
        EXPECT_EQ(this_vector[2], 2);
        EXPECT_EQ(this_vector[3], 2);
        EXPECT_EQ(this_vector[4], 3);
    }
}

TEST(TEST_CPPY_PLATFORM, memory)
{
    uint64_t total, available;
    EXPECT_EQ(CPPY_PLATFORM_memory(&total, &available), CPPY_ERROR_t::Ok);
    EXPECT_GT(total, 0);
    EXPECT_GT(available, 0);
}

TEST(TEST_CPPY_PLATFORM, cpu_percent)
{
    double percent = 0.;
    EXPECT_EQ(CPPY_PLATFORM_cpu_percent(&percent, 1), CPPY_ERROR_t::Ok);
    EXPECT_GE(percent, 0.0);
    EXPECT_LE(percent, 100.0);
}

TEST(TEST_CPPY_PLATFORM, os_info)
{
    std::string result;
    EXPECT_EQ(CPPY_PLATFORM_os_info(&result), CPPY_ERROR_t::Ok);
    EXPECT_FALSE(result.empty());
}

TEST(TEST_CPPY_DATETIME, now)
{
    {
        std::chrono::steady_clock::time_point result;
        EXPECT_EQ(CPPY_DATETIME_now(&result), CPPY_ERROR_t::Ok);
    }
    {
        std::time_t result;
        EXPECT_EQ(CPPY_DATETIME_now(&result), CPPY_ERROR_t::Ok);
        EXPECT_GT(result, 0);
    }
}

TEST(TEST_CPPY_BUILTINS, divmod)
{
    int div, mod;
    EXPECT_EQ(CPPY_BUILTINS_divmod(13, 5, &div, &mod), CPPY_ERROR_t::Ok);
    EXPECT_EQ(div, 2);
    EXPECT_EQ(mod, 3);
}

TEST(TEST_CPPY_BUILTINS, sorted)
{
    std::vector<int> data{3, 1, 4, 1, 5};
    EXPECT_EQ(CPPY_BUILTINS_sorted(data.begin(), data.end()), CPPY_ERROR_t::Ok);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 1);
    EXPECT_EQ(data[2], 3);
    EXPECT_EQ(data[3], 4);
    EXPECT_EQ(data[4], 5);
}

TEST(TEST_CPPY_BUILTINS, callable)
{
    bool result;
    struct Helper
    {
        static void plain_function(int)
        {
        }
    };
    struct NoCall
    {
    };
    struct WithCall
    {
        void operator()()
        {
        }
    };
    struct WithCallArgs
    {
        void operator()(int)
        {
        }
    };
    EXPECT_EQ((CPPY_BUILTINS_callable<WithCall>(&result)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ((CPPY_BUILTINS_callable<NoCall>(&result)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, false);
    EXPECT_EQ((CPPY_BUILTINS_callable<WithCallArgs>(&result)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    auto lambda_noargs = []() { return 42; };
    EXPECT_EQ((CPPY_BUILTINS_callable<decltype(lambda_noargs)>(&result)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    auto lambda_withargs = [](int x) { return x + 1; };
    EXPECT_EQ((CPPY_BUILTINS_callable<decltype(lambda_withargs)>(&result)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
    EXPECT_EQ((CPPY_BUILTINS_callable<decltype(&Helper::plain_function)>(&result)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(result, true);
}

TEST(TEST_CPPY_BUILTINS, chr)
{
    std::string s;
    EXPECT_EQ(CPPY_BUILTINS_chr(0x41, &s), CPPY_ERROR_t::Ok);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ((uint8_t)s[0], 0x41);
    EXPECT_EQ(CPPY_BUILTINS_chr(0x4E2D, &s), CPPY_ERROR_t::Ok);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ((uint8_t)s[0], 0xE4);
    EXPECT_EQ((uint8_t)s[1], 0xB8);
    EXPECT_EQ((uint8_t)s[2], 0xAD);
    EXPECT_EQ(CPPY_BUILTINS_chr(0x1F600, &s), CPPY_ERROR_t::Ok);
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ((uint8_t)s[0], 0xF0);
    EXPECT_EQ((uint8_t)s[1], 0x9F);
    EXPECT_EQ((uint8_t)s[2], 0x98);
    EXPECT_EQ((uint8_t)s[3], 0x80);
    EXPECT_EQ(CPPY_BUILTINS_chr(0x110000, &s), CPPY_ERROR_t::ValueError);
}

TEST(TEST_CPPY_BUILTINS, filter)
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto is_even = [](int x) { return x % 2 == 0; };
    std::vector<int> vec_out;
    EXPECT_EQ((CPPY_BUILTINS_filter(data.begin(), data.end(), is_even, std::back_inserter(vec_out))), CPPY_ERROR_t::Ok);
    EXPECT_EQ(vec_out.size(), 5);
    EXPECT_EQ(vec_out[0], 2);
    EXPECT_EQ(vec_out[4], 10);
    std::list<int> list_out;
    EXPECT_EQ((CPPY_BUILTINS_filter(data.begin(), data.end(), is_even, std::back_inserter(list_out))),
              CPPY_ERROR_t::Ok);
    EXPECT_EQ(list_out.size(), 5);
    EXPECT_EQ(list_out.front(), 2);
    EXPECT_EQ(list_out.back(), 10);
    std::deque<int> deque_out;
    EXPECT_EQ((CPPY_BUILTINS_filter(data.begin(), data.end(), is_even, std::front_inserter(deque_out))),
              CPPY_ERROR_t::Ok);
    EXPECT_EQ(deque_out.size(), 5);
    std::list<int> list_data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> from_list;
    EXPECT_EQ((CPPY_BUILTINS_filter(list_data.begin(), list_data.end(), is_even, std::back_inserter(from_list))),
              CPPY_ERROR_t::Ok);
    EXPECT_EQ(from_list.size(), 5);
    int raw_array[5]{0};
    EXPECT_EQ((CPPY_BUILTINS_filter(data.begin(), data.end(), is_even, raw_array)), CPPY_ERROR_t::Ok);
    EXPECT_EQ(raw_array[0], 2);
    EXPECT_EQ(raw_array[1], 4);
    EXPECT_EQ(raw_array[2], 6);
    EXPECT_EQ(raw_array[3], 8);
    EXPECT_EQ(raw_array[4], 10);
    std::vector<int> empty;
    std::vector<int> empty_out;
    EXPECT_EQ((CPPY_BUILTINS_filter(empty.begin(), empty.end(), is_even, std::back_inserter(empty_out))),
              CPPY_ERROR_t::Ok);
    EXPECT_EQ(empty_out.size(), 0);
}

TEST(TEST_CPPY_BUILTINS, reversed)
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    EXPECT_EQ((CPPY_BUILTINS_reversed(vec.begin(), vec.end())), CPPY_ERROR_t::Ok);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 1);
    std::vector<int> single{42};
    EXPECT_EQ((CPPY_BUILTINS_reversed(single.begin(), single.end())), CPPY_ERROR_t::Ok);
    EXPECT_EQ(single[0], 42);
    std::vector<int> empty;
    EXPECT_EQ((CPPY_BUILTINS_reversed(empty.begin(), empty.end())), CPPY_ERROR_t::Ok);
    EXPECT_EQ(empty.size(), 0);
    std::list<int> lst{10, 20, 30, 40};
    EXPECT_EQ((CPPY_BUILTINS_reversed(lst.begin(), lst.end())), CPPY_ERROR_t::Ok);
    EXPECT_EQ(lst.size(), 4);
    EXPECT_EQ(lst.front(), 40);
    EXPECT_EQ(lst.back(), 10);
    std::string str = "hello";
    EXPECT_EQ((CPPY_BUILTINS_reversed(str.begin(), str.end())), CPPY_ERROR_t::Ok);
    EXPECT_EQ(str, "olleh");
}

TEST(TEST_CPPY_RANDOM, shuffle)
{
    std::vector<int> original{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> data = original;
    CPPY_RANDOM_Random rng;
    rng.shuffle(data.begin(), data.end());

    bool is_order_changed = false;
    for (size_t i = 0; i < original.size(); i++)
    {
        if (data[i] != original[i])
        {
            is_order_changed = true;
            break;
        }
    }
    EXPECT_TRUE(is_order_changed);

    std::sort(data.begin(), data.end());
    std::sort(original.begin(), original.end());
    EXPECT_EQ(data, original);
}

TEST(TEST_CPPY_IO, StringIO)
{
    CPPY_IO_StringIO sio;
    sio.write("hello world");
    std::string result = sio.getvalue();
    EXPECT_EQ(result, "hello world");
}

TEST(TEST_CPPY_IO, BytesIO)
{
    CPPY_IO_BytesIO bio;
    std::vector<char> data = {'h', 'e', 'l', 'l', 'o'};
    bio.write(data);
    std::vector<char> result = bio.getvalue();
    EXPECT_EQ(result.size(), 5);
}

TEST(TEST_CPPY_IO, text_file)
{
    const char* temp_file = "test_temp.txt";
    {
        constexpr std::ios_base::openmode mode = CPPY_IO_FileIO::mode('w');
        CPPY_IO_FileIO file = CPPY_IO_FileIO(temp_file, mode);
        file.write("12345\n67890\n\n0000");
        file.flush();
    }
    {
        CPPY_IO_FileIO file = CPPY_IO_FileIO(temp_file);
        std::string line1, line2, line3, line4;
        EXPECT_EQ(file.readline(&line1), CPPY_ERROR_t::Ok);
        EXPECT_EQ(file.readline(&line2), CPPY_ERROR_t::Ok);
        EXPECT_EQ(file.readline(&line3), CPPY_ERROR_t::Ok);
        EXPECT_EQ(file.readline(&line4), CPPY_ERROR_t::Ok);
        EXPECT_EQ(line1, "12345");
        EXPECT_EQ(line2, "67890");
        EXPECT_EQ(line3, "");
        EXPECT_EQ(line4, "0000");
    }
}

TEST(TEST_CPPY_BUILTINS, linspace)
{
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

TEST(TEST_CPPY_BUILTINS, _max)
{
    {
        double data[5]{0., 2., 5., 3., 4.};
        double* result{nullptr};
        CPPY_BUILTINS_max(data, data + 5, &result);
        EXPECT_NEAR(*result, 5., 1.0e-16);
    }
    {
        auto data = std::initializer_list<double>{0., 2., 5., 3., 4.};
        const double* result{nullptr};
        CPPY_BUILTINS_max(data.begin(), data.end(), &result);
        EXPECT_NEAR(*result, 5., 1.0e-16);
    }
}

TEST(TEST_CPPY_BUILTINS, _min)
{
    {
        double data[5]{0., 2., 5., 3., 4.};
        double* result{nullptr};
        CPPY_BUILTINS_min(data, data + 5, &result);
        EXPECT_NEAR(*result, 0., 1.0e-16);
    }
    {
        auto data = std::initializer_list<double>{0., 2., 5., 3., 4.};
        const double* result{nullptr};
        CPPY_BUILTINS_min(data.begin(), data.end(), &result);
        EXPECT_NEAR(*result, 0., 1.0e-16);
    }
}

TEST(TEST_CPPY_BUILTINS, all)
{
    {
        std::vector<int> data{2, 1, 3, 4};
        bool result;
        CPPY_BUILTINS_all(data.begin(), data.end(), [](int x) { return x > 0; }, &result);
        EXPECT_TRUE(result);
    }
    {
        std::vector<int> data{2, 1, 3, 4};
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
    {
        std::vector<int> data{1, 2, 3, 4};
        bool result;
        CPPY_BUILTINS_all(data.begin(), data.end(), &result);
        EXPECT_TRUE(result);
    }
    {
        std::vector<int> data{1, 2, 3, 0};
        bool result;
        CPPY_BUILTINS_all(data.begin(), data.end(), &result);
        EXPECT_FALSE(result);
    }
}

TEST(TEST_CPPY_BUILTINS, any)
{
    {
        std::vector<int> data{2, 1, 3, 4};
        bool result;
        CPPY_BUILTINS_any(data.begin(), data.end(), [](int x) { return x > 0; }, &result);
        EXPECT_TRUE(result);
    }
    {
        std::vector<int> data{2, 1, 3, 4};
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
    {
        std::vector<int> data{0, 0, 1, 0, 0};
        bool result;
        CPPY_BUILTINS_any(data.begin(), data.end(), &result);
        EXPECT_TRUE(result);
    }
    {
        std::vector<int> data{0, 0, 0, 0, 0};
        bool result;
        CPPY_BUILTINS_any(data.begin(), data.end(), &result);
        EXPECT_FALSE(result);
    }
}

TEST(TEST_CPPY_BUILTINS, sum)
{
    {
        double data[5]{0., 2., 5., 3., 4.};
        double result;
        CPPY_BUILTINS_sum(data, data + 5, 0.0, &result);
        EXPECT_NEAR(result, 14., 1.0e-16);
    }
    {
        auto data = std::initializer_list<double>{0., 2., 5., 3., 4.};
        double result;
        CPPY_BUILTINS_sum(data.begin(), data.end(), 0.0, &result);
        EXPECT_NEAR(result, 14., 1.0e-16);
    }
}

TEST(TEST_CPPY_DATETIME, duration)
{
    std::chrono::steady_clock::time_point start, end;
    CPPY_DATETIME_now(&start);
    int i = 100;
    while (i-- > 0)
        ;
    CPPY_DATETIME_now(&end);

    std::chrono::nanoseconds::rep duration;
    CPPY_DATETIME_duration<std::chrono::nanoseconds>(start, end, &duration);
    EXPECT_GE(duration, 0);
}

TEST(TEST_CPPY_DATETIME, strftime)
{
    {
        std::string strftime;
        CPPY_DATETIME_strftime(std::time(nullptr), &strftime);
        EXPECT_EQ(strftime.size(), 19);
    }
    {
        std::string strftime;
        CPPY_DATETIME_strftime(std::time(nullptr), &strftime, "%Y");
        EXPECT_EQ(strftime.size(), 4);
    }
}

TEST(TEST_CPPY_EXPECT, expect)
{
    CPPY_EXPECT(true) << "this is true";
    CPPY_EXPECT(false) << "this is false";
}

TEST(TEST_CPPY_ASSERT, assert)
{
    CPPY_ASSERT(true) << "this is true";
    try
    {
        CPPY_ASSERT(false) << "this is false";
    }
    catch (const CPPY_Assertion_message& result)
    {
        (void)result;
    }
}

TEST(TEST_CPPY_RANDOM, random)
{
    CPPY_RANDOM_Random random;
    {
        double x;
        EXPECT_EQ(random.uniform(1.0, 10.0, &x), CPPY_ERROR_t::Ok);
        EXPECT_GE(x, 1.0);
        EXPECT_LT(x, 10.0);
    }
    {
        double x;
        EXPECT_EQ(random.random(&x), CPPY_ERROR_t::Ok);
        EXPECT_GE(x, 0.0);
        EXPECT_LT(x, 1.0);
    }
}

TEST(TEST_CPPY_RANDOM, randint)
{
    CPPY_RANDOM_Random random;
    {
        int a{1}, b{10}, x;
        random.randint(1, 10, &x);
        EXPECT_GE(x, a);
        EXPECT_LE(x, b);
    }
    {
        size_t a{1}, b{10}, x;
        random.randint(a, b, &x);
        EXPECT_GE(x, a);
        EXPECT_LE(x, b);
    }
}

TEST(TEST_CPPY_RANDOM, uniform)
{
    CPPY_RANDOM_Random random;
    {
        float a{1.}, b{10.}, x;
        random.uniform(a, b, &x);
        EXPECT_GE(x, a);
        EXPECT_LE(x, b);
    }
    {
        double a{1.}, b{10.}, x;
        random.uniform(a, b, &x);
        EXPECT_GE(x, a);
        EXPECT_LE(x, b);
    }
}

TEST(TEST_CPPY_RANDOM, choice)
{
    CPPY_RANDOM_Random random;
    {
        std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int x;
        random.choice(a.begin(), a.end(), &x);
        bool is_contain{false};
        CPPY_VECTOR_iscontain(a, x, &is_contain);
        EXPECT_TRUE(is_contain);
    }
    {
        std::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int x;
        random.choice(a.begin(), a.end(), &x);
        bool is_contain{false};
        CPPY_LIST_iscontain(a, x, &is_contain);
        EXPECT_TRUE(is_contain);
    }
}

TEST(TEST_CPPY_thread, thread_pool)
{
    CPPY_CONCURRENT_ThreadPoolExecutor pool(static_cast<size_t>(4));
    std::vector<int> args{1, 2, 3, 4};
    std::vector<std::future<int>> futures;

    for (const int& x : args)
    {
        futures.push_back(pool.submit([](const int x) { return x * 2; }, x));
    }

    for (size_t i = 0; i < args.size(); i++)
    {
        EXPECT_EQ(futures[i].get(), args[i] * 2);
    }
}

TEST(TEST_CPPY_MEMORY_handler, _int)
{
    {
        CPPY_MEMORY_handler<int> number;
        EXPECT_EQ(number.alloc(5), CPPY_ERROR_t::Ok);
        number[0] = 1;
        number[1] = 2;
        number.free();
        EXPECT_EQ(number.get_size(), 0);
        EXPECT_EQ(number.get_pointer(), nullptr);
    }
    {
        CPPY_MEMORY_handler<int> number;
        const std::size_t n = 5;
        auto p_size = number.address_of_size();
        auto p_pointer = number.address_of_pointer();
        *p_size = n;
        *p_pointer = static_cast<int*>(std::malloc(n * sizeof(int)));
        number[0] = 1;
        number[1] = 2;
        number.free();
        EXPECT_EQ(number.get_size(), 0);
        EXPECT_EQ(number.get_pointer(), nullptr);
    }
}

TEST(TEST_CPPY_MEMORY_array_handler, _int_double)
{
    {
        CPPY_MEMORY_array_handler<int, double> number;
        EXPECT_EQ(number.alloc(5), CPPY_ERROR_t::Ok);
        number.get_pointer<0>()[0] = 1;
        number.get_pointer<1>()[0] = 2.;
        number.free();
        EXPECT_EQ(number.get_size(), 0);
        EXPECT_EQ(number.get_pointer<0>(), nullptr);
        EXPECT_EQ(number.get_pointer<1>(), nullptr);
    }
    {
        CPPY_MEMORY_array_handler<int, double> number;
        const int n = 5;
        auto p_size = number.address_of_size();
        auto p_pointer_0 = number.address_of_pointer<0>();
        auto p_pointer_1 = number.address_of_pointer<1>();
        *p_size = n;
        *p_pointer_0 = static_cast<int*>(std::malloc(n * sizeof(int)));
        *p_pointer_1 = static_cast<double*>(std::malloc(n * sizeof(double)));
        number.get_pointer<0>()[0] = 1;
        number.get_pointer<1>()[1] = 2.;
        number.free();
        EXPECT_EQ(number.get_size(), 0);
        EXPECT_EQ(number.get_pointer<0>(), nullptr);
        EXPECT_EQ(number.get_pointer<1>(), nullptr);
    }
}