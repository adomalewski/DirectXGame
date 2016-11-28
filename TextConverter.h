#pragma once

#include <string>

namespace
{
	void makeWChar(LPCWSTR& textOut, std::string in)
	{
		std::wstring* stemp = new std::wstring(in.begin(), in.end());
		textOut = (*stemp).c_str();
	}
}
