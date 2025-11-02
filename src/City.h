#pragma once

#include <vector>

#include "Card.h"

class City
{
public:
	City();

	int GetHappiness() const;
	int GetPeople() const;
	int GetMoney() const;
	bool IsFull() const;
	bool Contains(const Card& card) const;

	const std::vector<Card>& GetCards() const;

	void BuyCard(const Card& card);
	
	void Income();
	void GiveMoney(int money);

	void PrintState() const;

private:
	std::vector<Card> m_cards;
	int m_money = 2;
};