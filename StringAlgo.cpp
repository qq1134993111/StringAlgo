﻿// StringAlgo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <span>
#include <cassert>
#include <iostream>
#include<vector>
#include<string>

#include "string_algo/string.hpp"
#include "boost/algorithm/string.hpp"
int main()
{
	std::string str = "  Hello   ";

	if (1)
	{
		
		const std::vector<char> v(str.begin(), str.end());
		std::span<const char> sp(v);

		auto span1 = string_algo::as_literal(str);
		auto span2 = string_algo::as_literal(v);
		auto span3 = string_algo::as_literal(sp);
		auto span4 = string_algo::as_literal(" hello world ");
		char sz[] = { "hello" };
		auto span5 = string_algo::as_literal(sz);
		////v[3] = 'G';
		//
		std::cout << typeid(span1).name() << "\n";
		std::cout << typeid(span2).name() << "\n";
		std::cout << typeid(span3).name() << "\n";
		std::cout << typeid(span4).name() << "\n";
		std::cout << typeid(span5).name() << "\n";
		assert(span3[3] == v[3]);
	}

	

	typedef std::span<typename  std::string::value_type> result_type;
	result_type test(str.begin(),str.end());
	
	auto s1 = string_algo::trim_copy(str);
	string_algo::trim(str);
	assert(s1==str);

	auto s2 = string_algo::to_lower_copy(str);
	string_algo::to_lower(str);
	assert(str==s2);
	s2 = string_algo::to_upper_copy(str);
	string_algo::to_upper(str);
	assert(str == s2);

	bool b = false;
	b=string_algo::starts_with("123456789", "123");
	assert(b);
	b = string_algo::ends_with("123456789", "789", [](char ch1, char ch2)
	{
		return ch1 == ch2;
	});
	assert(b);
	b=string_algo::contains("1234567", "456");
	assert(b);
	b = string_algo::icontains("abcdef", "CDe");
	assert(b);
	b = string_algo::contains("1234567", "9");
	assert(!b);
	b=boost::contains("1234567", "456");
	assert(b);
	b = string_algo::iequals("abc", "Abc");
	assert(b);
	b = string_algo::iequals("abc", "AbC");
	assert(b);
	
    std::cout << "Hello World!\n";
}
