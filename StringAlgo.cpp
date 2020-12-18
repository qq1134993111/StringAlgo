// StringAlgo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
#include<string>

#include "string_algo/string.hpp"

int main()
{
	std::string str = "Hello   ";
	string_algo::trim(str);
	auto s2 = string_algo::trim_copy(str);
	
    std::cout << "Hello World!\n";
}
