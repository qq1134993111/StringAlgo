// StringAlgo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
#include<string>

#include "string_algo/string.hpp"

int main()
{
	std::string str = "  Hello   ";
	
	auto s1 = string_algo::trim_copy(str);
	string_algo::trim(str);

	auto s2 = string_algo::to_upper_copy(str);
	string_algo::to_lower(str);

	
    std::cout << "Hello World!\n";
}
