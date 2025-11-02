#pragma once

#include <functional>

#include "Print.h"

class StreamError : public std::runtime_error
{
public:
	inline StreamError(const std::string& message) : std::runtime_error(message) {};
};

inline void Input(const std::wstring& questionString, std::wstring& outVar, const std::function<bool(std::wstring)>& validate, const std::wstring& predicateString)
{
	if (!questionString.empty())
	{
		Print(questionString);
		Print('\n');
	}

	getline(std::wcin, outVar);

	while (!validate(outVar))
	{
		if (std::wcin.eof())
		{
			throw StreamError("Erreur de flux. Recommence.");
		}
		else if (std::wcin.fail())
		{
			Print(L"Entrée invalide. Recommence.\n");
			std::wcin.clear();
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			Print(predicateString);
			Print('\n');
		}

		getline(std::wcin, outVar);
	}
}

template <typename T>
void Input(const std::wstring& questionString, T& outVar, const std::function<bool(T)>& validate, const std::wstring& predicateString)
{
	if (!questionString.empty())
	{
		Print(questionString);
		Print('\n');
	}

	while (!(std::cin >> outVar) || !validate(outVar))
	{
		if (std::cin.eof())
		{
			throw StreamError("Erreur de flux. Recommence.");
		}
		else if (std::cin.fail())
		{
			Print(L"Entrée invalide. Recommence.\n");
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			Print(predicateString);
			Print('\n');
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}