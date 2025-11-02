#pragma once

#include <iostream>
#include <string>
#include <format>

inline void Print(const std::wstring& s)
{
    std::wcout << s;
}

inline void Print(wchar_t c)
{
    std::wcout << c;
}