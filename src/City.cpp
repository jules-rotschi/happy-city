#include "City.h"

#include "Print.h"

City::City()
{
	m_cards.reserve(10);
}

int City::GetHappiness() const
{
	int happiness = 0;

	for (const Card& card : m_cards)
	{
		happiness += card.GetHappiness();
	}

	return happiness;
}

int City::GetPeople() const
{
	int people = 0;

	for (const Card& card : m_cards)
	{
		people += card.GetPeople();
	}

	return people;
}

int City::GetMoney() const
{
	return m_money;
}

bool City::IsFull() const
{
	return m_cards.size() == 10;
}

bool City::Contains(const Card& card) const
{
	for (const Card& ownCard : m_cards)
	{
		if (card == ownCard)
		{
			return true;
		}
	}

	return false;
}

const std::vector<Card>& City::GetCards() const
{
	return m_cards;
}

void City::BuyCard(const Card& card)
{
	m_cards.push_back(card);
	m_money -= card.GetPrice();
}

void City::Income()
{
	for (const Card& card : m_cards)
	{
		m_money += card.GetIncome();
	}
}

void City::GiveMoney(int money)
{
	m_money += money;
}

void City::PrintState() const
{
	Print(std::format(L"Pièces : {}\n", m_money));
	Print(L"Cartes :\n");

	for (const Card& card : m_cards)
	{
		Print(std::format(L"  - {}\n", card.ToString()));
	}
}