#include "AIController.h"

#include <assert.h>

#include "Game.h"

const Card* AIController::ChooseCardToDiscard(Game& game, const Player& player, int& cardIndex) const
{
	bool needsMoney = false;
	bool needsHappiness = false;
	bool needsPeople = false;

	DetermineNeeds(player, needsMoney, needsHappiness, needsPeople);

	if (game.m_visibleBuildingCards.Size() == 1)
	{
		const Card& card = game.m_visibleBuildingCards.GetCards()[0];

		bool discard = false;
		discard |= card.GetPrice() > player.GetCityMoney();
		discard |= needsMoney && card.GetIncome() == 0;
		discard |= card.GetHappiness() < 0 || card.GetPeople() < 0;

		if (discard)
		{
			cardIndex = 0;
			return &card;
		}
		else return nullptr;
	}
	
	const Card* worstCard = nullptr;
	int worstIncome = 2;
	int worstHappiness = 3;
	int worstPeople = 3;
	int worstCardIndex = 0;

	if (needsMoney)
	{
		int i = 0;
		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			if (card.GetIncome() < worstIncome)
			{
				worstCard = &card;
				worstIncome = card.GetIncome();
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}

			bool cardIsAsBadAsWorst = card.GetIncome() == worstIncome;

			if (cardIsAsBadAsWorst && needsHappiness && card.GetHappiness() < worstHappiness)
			{
				worstCard = &card;
				worstIncome = card.GetIncome();
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}
			if (cardIsAsBadAsWorst && needsPeople && card.GetHappiness() < worstHappiness)
			{
				worstCard = &card;
				worstIncome = card.GetIncome();
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}

			int cardScore = card.GetHappiness() * card.GetPeople();
			int worstScore = worstHappiness * worstPeople;

			if (cardIsAsBadAsWorst && (!needsHappiness && !needsPeople) && cardScore < worstScore)
			{
				worstCard = &card;
				worstIncome = card.GetIncome();
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}
			i++;
		}
	}
	else
	{
		int i = 0;
		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			if (needsHappiness && card.GetHappiness() < worstHappiness)
			{
				worstCard = &card;
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}
			if (needsPeople && card.GetHappiness() < worstHappiness)
			{
				worstCard = &card;
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}

			int cardScore = card.GetHappiness() * card.GetPeople();
			int worstScore = worstHappiness * worstPeople;

			if ((!needsHappiness && !needsPeople) && cardScore < worstScore)
			{
				worstCard = &card;
				worstHappiness = card.GetHappiness();
				worstPeople = card.GetPeople();
				worstCardIndex = i;
			}
			i++;
		}
	}

	cardIndex = worstCardIndex;
	return worstCard;
}

DeckOfCards& AIController::ChooseDeckToDraw(Game& game, const Player& player) const
{
	if (player.GetCityMoney() <= 3)
	{
		return game.m_buildingCards1;
	}

	if (player.GetCityMoney() <= 5)
	{
		return game.m_buildingCards2;
	}

	return game.m_buildingCards3;
}

int AIController::ChooseWhatToDo(Game& game, const Player& player) const
{
	bool needsMoney = false;
	bool needsHappiness = false;
	bool needsPeople = false;

	DetermineNeeds(player, needsMoney, needsHappiness, needsPeople);

	if (needsMoney)
	{
		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			bool isPriceAccessible = card.GetPrice() <= player.GetCityMoney();
			bool hasBeenBought = player.CityContains(card);
			bool hasIncome = card.GetIncome() > 0;
			bool doesNotKillHappiness = card.GetHappiness() >= 0;
			bool doesNotKillPeople = card.GetPeople() >= 0;

			if (isPriceAccessible && !hasBeenBought && hasIncome && doesNotKillHappiness && doesNotKillPeople)
				return 2;
		}
		return 3;
	}

	if (needsHappiness)
	{
		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			if (player.GetCityMoney() >= card.GetPrice() && !player.CityContains(card) && card.GetHappiness() > 0)
				return 2;
		}
		needsPeople = true;
	}

	if (needsPeople)
	{
		if (player.GetCityMoney() >= 1 && player.GetCityMoney() < 3 && !player.CityContains(L"Maison") && !game.m_houseCards.empty())
		{
			return 1;
		}
		if (player.GetCityMoney() >= 3 && player.GetCityMoney() < 6 && !player.CityContains(L"Immeuble") && !game.m_residenceCards.empty())
		{
			return 1;
		}
		if (player.GetCityMoney() >= 6 && !player.CityContains(L"Résidence de luxe") && !game.m_luxuryResidenceCards.empty())
		{
			return 1;
		}

		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			if (player.GetCityMoney() >= card.GetPrice() && !player.CityContains(card) && card.GetPeople() > 0)
				return 2;
		}

		needsHappiness = true;
	}

	if (needsHappiness == needsPeople)
	{
		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			if (player.GetCityMoney() >= card.GetPrice() && !player.CityContains(card) && card.GetHappiness() >= 0 && card.GetPeople() >= 0)
				return 2;
		}

		if (player.GetCityMoney() >= 6 && !player.CityContains(L"Résidence de luxe") && !game.m_luxuryResidenceCards.empty())
		{
			return 1;
		}
		if (player.GetCityMoney() >= 3 && !player.CityContains(L"Immeuble") && !game.m_residenceCards.empty())
		{
			return 1;
		}
		if (player.GetCityMoney() >= 1 && !player.CityContains(L"Maison") && !game.m_houseCards.empty())
		{
			return 1;
		}
	}

	return 3;
}

const Card& AIController::ChooseResidenceBuildingToBuy(Game& game, const Player& player, std::vector<Card>*& cardsWhereTaken) const
{
	if (player.GetCityMoney() >= 6 && !game.m_luxuryResidenceCards.empty() && !player.CityContains(L"Résidence de luxe"))
	{
		cardsWhereTaken = &game.m_luxuryResidenceCards;
		return game.m_luxuryResidenceCards[0];
	}
	if (player.GetCityMoney() >= 3 && !game.m_residenceCards.empty() && !player.CityContains(L"Immeuble"))
	{
		cardsWhereTaken = &game.m_residenceCards;
		return game.m_residenceCards[0];
	}
	cardsWhereTaken = &game.m_houseCards;
	return game.m_houseCards[0];
}

const Card& AIController::ChooseBuildingToBuy(Game& game, const Player& player, int& cardIndex) const
{
	bool needsMoney = false;
	bool needsHappiness = false;
	bool needsPeople = false;

	DetermineNeeds(player, needsMoney, needsHappiness, needsPeople);

	if (needsMoney)
	{
		const Card* bestCard = nullptr;
		int bestCardIncome = 0;
		int bestCardSum = 0;
		int bestCardIndex = 0;

		int i = 0;

		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			bool isPriceAccessible = card.GetPrice() <= player.GetCityMoney();
			bool doesNotKillHappiness = card.GetHappiness() < 0;
			bool doesNotKillPeople = card.GetPeople() < 0;

			if (isPriceAccessible && doesNotKillHappiness && doesNotKillPeople && !player.CityContains(card))
			{
				int cardSum = card.GetHappiness() + card.GetPeople();
				if (card.GetIncome() > bestCardIncome)
				{
					bestCard = &card;
					bestCardIncome = card.GetIncome();
					bestCardSum = cardSum;
					bestCardIndex = i;
				}
				if (card.GetIncome() == bestCardIncome && cardSum > bestCardSum)
				{
					bestCard = &card;
					bestCardIncome = card.GetIncome();
					bestCardSum = cardSum;
					bestCardIndex = i;
				}
			}
			i++;
		}
		if (bestCard)
		{
			cardIndex = bestCardIndex;
			return *bestCard;
		}
	}

	if (needsHappiness)
	{
		const Card* bestCard = nullptr;
		int bestCardHappiness = 0;
		int bestCardSum = 0;
		int bestCardIndex = 0;

		int i = 0;

		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			int cardSum = card.GetHappiness() + card.GetPeople();

			if (player.GetCityMoney() >= card.GetPrice() && !player.CityContains(card))
			{
				if (card.GetHappiness() > bestCardHappiness)
				{
					bestCard = &card;
					bestCardHappiness = card.GetHappiness();
					bestCardSum = cardSum;
					bestCardIndex = i;
				}
				if (card.GetHappiness() == bestCardHappiness && cardSum > bestCardSum)
				{
					bestCard = &card;
					bestCardHappiness = card.GetHappiness();
					bestCardSum = cardSum;
					bestCardIndex = i;
				}
			}
			i++;
		}
		
		if (bestCard)
		{
			cardIndex = bestCardIndex;
			return *bestCard;
		}
		else
			needsPeople = true;
	}

	if (needsPeople)
	{
		const Card* bestCard = nullptr;
		int bestCardPeople = 0;
		int bestCardSum = 0;
		int bestCardIndex = 0;

		int i = 0;

		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			int cardSum = card.GetHappiness() + card.GetPeople();

			if (player.GetCityMoney() >= card.GetPrice() && !player.CityContains(card))
			{
				if (card.GetPeople() > bestCardPeople)
				{
					bestCard = &card;
					bestCardPeople = card.GetPeople();
					bestCardSum = cardSum;
					bestCardIndex = i;
				}
				if (card.GetPeople() == bestCardPeople && cardSum > bestCardSum)
				{
					bestCard = &card;
					bestCardPeople = card.GetPeople();
					bestCardSum = cardSum;
					bestCardIndex = i;
				}
			}
			i++;
		}

		if (bestCard)
		{
			cardIndex = bestCardIndex;
			return *bestCard;
		}
		else
			needsHappiness = true;
	}

	if (needsHappiness == needsPeople)
	{
		const Card* bestCard = nullptr;
		int bestCardSum = 0;
		int bestCardDifference = 3;
		int bestCardIndex = 0;

		int i = 0;

		for (const Card& card : game.m_visibleBuildingCards.GetCards())
		{
			int cardSum = card.GetHappiness() + card.GetPeople();
			int cardDifference = std::abs(card.GetHappiness() - card.GetPeople());

			if (player.GetCityMoney() >= card.GetPrice() && !player.CityContains(card))
			{
				if (cardSum > bestCardSum)
				{
					bestCard = &card;
					bestCardSum = cardSum;
					bestCardDifference = cardDifference;
					bestCardIndex = i;
				}
				if (cardSum == bestCardSum && cardDifference < bestCardDifference)
				{
					bestCard = &card;
					bestCardSum = cardSum;
					bestCardDifference = cardDifference;
					bestCardIndex = i;
				}
			}
			i++;
		}

		if (bestCard)
		{
			cardIndex = bestCardIndex;
			return *bestCard;
		}
	}

	assert(false);
	cardIndex = 0;
	return game.m_visibleBuildingCards.GetCards()[0];
}

const Card* AIController::ChooseSpecialBuildingToBuy(Game& game, const Player& player, int& cardIndex) const
{
	bool needsMoney = false;
	bool needsHappiness = false;
	bool needsPeople = false;

	DetermineNeeds(player, needsMoney, needsHappiness, needsPeople);

	const Card* bestCard = nullptr;
	int bestCardScore = 0;
	int bestCardIndex = 0;

	int i = 0;

	for (const Card& card : game.m_specialBuildingCards.GetCards())
	{
		int cardScore = static_cast<int>(needsMoney) * card.GetIncome() + card.GetHappiness() * (1 + static_cast<int>(needsHappiness)) + card.GetPeople() * (1 + static_cast<int>(needsHappiness));
		
		if (card.IsAccessibleTo(player) && cardScore > bestCardScore)
		{
			bestCard = &card;
			bestCardScore = cardScore;
			bestCardIndex = i;
		}
		i++;
	}

	cardIndex = bestCardIndex;
	return bestCard;
}

void AIController::DetermineNeeds(const Player& player, bool& money, bool& happiness, bool& people) const
{
	int playerMoney = player.GetCityMoney();
	int playerIncome = 0;
	int playerHappiness = 0;
	int playerPeople = 0;

	for (const Card& card : player.GetCityCards())
	{
		playerIncome += card.GetIncome();
		playerHappiness += card.GetHappiness();
		playerPeople += card.GetPeople();
	}

	money = playerMoney + playerIncome < 9;
	happiness = playerPeople > playerHappiness;
	people = playerHappiness > playerPeople;
}