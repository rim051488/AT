#pragma once
#include <string>
using namespace std;
class Convert
{
public:
	wstring ConvertToWstring(const std::string& str);			// SJIS(マルチバイト文字)で得た文字をワイド文字(Unicode)に変換

};

