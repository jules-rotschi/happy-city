#pragma once

#include <vector>

#include "Card.h"
#include "DeckOfCards.h"
#include "SetOfCards.h"
#include "Player.h"

class Game
{
public:
	Game() = default;

	void Init();
	void Run();
	void ShutDown();

private:
	void Income() const;
	void Actions();

	void PrintState() const;
	void PrintResidences(bool isOrdered) const;
	int PrintResidencesAndGetCount(bool isOrdered) const;
	void PrintVisibleBuildings(bool isOrdered) const;
	void PrintSpecialBuildings(bool isOrdered) const;

	void LetPlay(Player& player);
	void LetDiscardVisibleCard(const Player& player);
	void LetDrawNewCards(const Player& player);
	bool LetBuyResidenceBuilding(Player& player);
	bool LetBuyBuilding(Player& player);
	bool LetGetSpecialCard(Player& player);

	const Player* GetWinner() const;

	friend class RealController;
	friend class AIController;

private:
	bool m_isOver = false;

	std::vector<Player*> m_players;

	std::vector<Card> m_houseCards;
	std::vector<Card> m_residenceCards;
	std::vector<Card> m_luxuryResidenceCards;

	DeckOfCards m_buildingCards1;
	DeckOfCards m_buildingCards2;
	DeckOfCards m_buildingCards3;
	SetOfCards m_visibleBuildingCards;

	std::vector<Card> m_buildingCardsDiscard1;
	std::vector<Card> m_buildingCardsDiscard2;
	std::vector<Card> m_buildingCardsDiscard3;

	SetOfCards m_specialBuildingCards;
};

