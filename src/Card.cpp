#include "Card.h"

#include <format>

#include "Player.h"

Card::Card(CardType type, std::wstring_view name, int price, int income, int happiness, int people)
	: m_type(type), m_name(name), m_price(price), m_income(income), m_happiness(happiness), m_people(people) {}

Card::Card(CardType type, std::wstring_view name, const std::map<CardType, int>& accessibility, int income, int happiness, int people)
	: m_type(type), m_name(name), m_accessibility(accessibility), m_income(income), m_happiness(happiness), m_people(people) {}

CardType Card::GetType() const
{
	return m_type;
}

std::wstring Card::GetName() const
{
	return m_name;
}

int Card::GetPrice() const
{
	return m_price;
}

int Card::GetIncome() const
{
	return m_income;
}

int Card::GetHappiness() const
{
	return m_happiness;
}

int Card::GetPeople() const
{
	return m_people;
}

bool Card::IsAccessibleTo(const Player& player) const
{
	for (const auto& [cardType, condition] : m_accessibility)
	{
		if (player.GetCardsCount(cardType) < condition)
			return false;
	}

	return true;
}

bool operator==(const Card& lhs, const Card& rhs)
{
	return lhs.m_name == rhs.m_name;
}

std::wstring Card::ToString() const
{
	std::wstring string;

	std::wstring identifier = std::format(L"{} ({})", m_name, CardTypeToString(m_type));

	while (identifier.size() < 50)
	{
		identifier += '.';
	}

	string += identifier;

	if (m_type == CardType::SPECIAL)
		string += L"[Prix : 0$]";
	else
		string += std::format(L"[Prix : {}$]", GetPrice());

	string += std::format(L" -> {}$ | ", GetIncome());

	std::wstring happinessString;

	if (GetHappiness() < 0)
	{
		happinessString = std::format(L"{} <3", GetHappiness());
	}

	if (GetHappiness() == 0)
	{
		happinessString = L"Aucun <3";
	}

	for (int i = 0; i < GetHappiness(); i++)
	{
		happinessString += L"<3 ";
	}

	while (happinessString.size() < 8)
	{
		happinessString += '.';
	}

	if (happinessString.size() == 8)
	{
		happinessString += ' ';
	}

	string += happinessString;
	
	string += std::format(L"| {} habitants", GetPeople());

	if (m_type == CardType::SPECIAL)
	{
		string += L" [Accessibilité : ";

		bool isFirst = true;

		for (const auto& [cardType, condition] : m_accessibility)
		{
			if (!isFirst)
				string += L", ";
			else
				isFirst = false;

			string += std::format(L"{} {}", condition, CardTypeToString(cardType));
		}

		string += L"]";
	}

	return string;
}