// StringAlgo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
	result_type test(str.begin(), str.end());

	auto s1 = string_algo::trim_copy(str);
	string_algo::trim(str);
	assert(s1 == str);

	auto s2 = string_algo::to_lower_copy(str);
	string_algo::to_lower(str);
	assert(str == s2);
	s2 = string_algo::to_upper_copy(str);
	string_algo::to_upper(str);
	assert(str == s2);

	bool b = false;
	b = string_algo::starts_with(str, str);
	b = string_algo::starts_with(str, "123");
	b = string_algo::starts_with("123456789", "123");
	assert(b);
	b = string_algo::ends_with("123456789", "789", [](char ch1, char ch2)
		{
			return ch1 == ch2;
		});
	assert(b);
	b = string_algo::contains(str, "456");
	b = string_algo::contains(str, str);
	b = string_algo::contains("1234567", "456");
	assert(b);
	b = string_algo::icontains("abcdef", "CDe");
	assert(b);
	b = string_algo::contains("1234567", "9");
	assert(!b);
	b = boost::contains("1234567", "456");
	assert(b);
	b = string_algo::iequals(str, str);
	b = string_algo::iequals("abc", "Abc");
	assert(b);
	b = string_algo::iequals("abc", "AbC");
	assert(b);

	auto span_1 = string_algo::find_first(str, "word");
	auto span_2 = string_algo::find_first(str, str);
	auto span = string_algo::find_first("hello word", "word");

	auto span2 = string_algo::ifind_last("hello word", "wOrD");

	auto span3_2 = string_algo::ifind_nth("hello", str, 1);
	auto span3_1 = string_algo::ifind_nth(str, "worD", 1);
	auto span3 = string_algo::ifind_nth("hello world Word", "worD", 1);

	//auto r=boost::find_first("hello", "ll");

	auto span4 = string_algo::find_head("hello", 2);
	auto span5 = string_algo::find_head(str, -2);

	auto span6 = string_algo::find_tail("hello", 2);
	auto span7 = string_algo::find_tail(str, -2);

	auto span8 = string_algo::find_token("hahhaha333333",
		[](char ch) { return ch == '3'; });

	std::string test_str = " i am a student , you are a  teacher! ";
	std::vector<std::string> vec,vec1,vec2,vec3;
	boost::split(vec, test_str, boost::is_any_of(", "), boost::token_compress_off);
	string_algo::split(vec1, test_str, string_algo::is_any_of(", "), string_algo::token_compress_off);
	assert(vec==vec1);

	boost::split(vec2, test_str, boost::is_any_of(", "), boost::token_compress_on);
	string_algo::split(vec3, " i am a student , you are a  teacher! ", string_algo::is_any_of(", "), string_algo::token_compress_on);
	assert(vec2 == vec3);

	std::list<std::string> list,list1,list2,list3;
	boost::ifind_all(list, test_str, "a");
	string_algo::ifind_all(list1," i am a student , you are a  teacher! ","a");
	assert(list == list1);

	auto l1=boost::find_all(list2,test_str,"a");
	auto l2=string_algo::find_all(list3, test_str, "a");
	assert(list2==list3);

	auto v=boost::join(vec, " , ");
	auto v2=string_algo::join(vec," , ");
	assert(v == v2);

	v = boost::join_if(vec, " , ",
		[](auto& value) { return value.size() > 2; });
	v2 = string_algo::join_if(vec, " , ", 
		[](auto& value) { return value.size() > 2; });
	assert(v == v2);

	test_str = "hello world";
	string_algo::replace_all(test_str, "l", "LL");
	
	std::cout << "Hello World!\n";
}
