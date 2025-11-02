#pragma once

#include <string>
#include <memory>

#include "City.h"
#include "PlayerController.h"

class Player
{
public:
	Player() = default;
	Player(const std::wstring& name, bool isAI = false);

	std::wstring GetName() const;
	int GetCityMoney() const;
	int GetCardsCount(CardType cardType) const;
	int GetScore() const;

	PlayerController& GetController() const;

	City& GetCity();
	const std::vector<Card>& GetCityCards() const;
	bool CityContains(const Card& card) const;
	bool CityContains(const std::wstring& cardName) const;

	void PrintCityState() const;

private:
	std::wstring m_name = L"Player";
	City m_city;
	std::unique_ptr<PlayerController> m_controller;
};

