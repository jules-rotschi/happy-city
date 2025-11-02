#include "Player.h"

#include "AIController.h"
#include "RealController.h"
#include "Print.h"

Player::Player(const std::wstring& name, bool isAI)
	: m_name(name)
{
	if (isAI)
	{
		m_controller = std::make_unique<AIController>();
	}
	else
	{
		m_controller = std::make_unique<RealController>();
	}
}

std::wstring Player::GetName() const
{
	return m_name;
}

int Player::GetCityMoney() const
{
	return m_city.GetMoney();
}

int Player::GetCardsCount(CardType cardType) const
{
	int count = 0;

	for (const Card& card : GetCityCards())
		if (card.GetType() == cardType)
			count++;

	return count;
}

int Player::GetScore() const
{
	return m_city.GetHappiness() * m_city.GetPeople();
}

PlayerController& Player::GetController() const
{
	return *m_controller;
}

City& Player::GetCity()
{
	return m_city;
}

const std::vector<Card>& Player::GetCityCards() const
{
	return m_city.GetCards();
}

bool Player::CityContains(const Card& card) const
{
	return m_city.Contains(card);
}

bool Player::CityContains(const std::wstring& cardName) const
{
	return m_city.Contains(Card(CardType::PUBLIC, cardName, 0, 0, 0, 0));
}

void Player::PrintCityState() const
{
	m_city.PrintState();
	Print(std::format(L"Score : {}\n", GetScore()));
}