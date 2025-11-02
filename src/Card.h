#pragma once

#include <string>
#include <map>

#include "CardType.h"

class Player;

class Card
{
public:
	Card() = delete;
	Card(CardType type, std::wstring_view name, int price, int income, int happiness, int people);
	Card(CardType type, std::wstring_view name, const std::map<CardType, int>& accessibility, int income, int happiness, int people);

	CardType GetType() const;
	std::wstring GetName() const;
	int GetPrice() const;
	int GetIncome() const;
	int GetHappiness() const;
	int GetPeople() const;

	bool IsAccessibleTo(const Player& player) const;

	std::wstring ToString() const;

	friend bool operator==(const Card& lhs, const Card& rhs);

private:
	CardType m_type;
	std::wstring m_name;
	
	int m_price = 1;

	std::map<CardType, int> m_accessibility;

	int m_income = 0;
	int m_happiness = 0;
	int m_people = 0;
};