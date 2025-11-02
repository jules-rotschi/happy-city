#include "RealController.h"

#include "Input.h"
#include "Game.h"

const Card* RealController::ChooseCardToDiscard(Game& game, const Player& player, int& cardIndex) const
{
	int input = -1;

	Input<int>(
		L"Pour défausser une carte, entre le numéro associé. Pour ne défausser aucune carte, entre \'0\'.",
		input,
		[game](int var) {return var >= 0 && var <= game.m_visibleBuildingCards.Size(); },
		std::format(L"Tu dois entrer un nombre compris entre 1 et {}.", game.m_visibleBuildingCards.Size())
	);

	Print('\n');

	if (input == 0) return nullptr;

	cardIndex = input - 1;

	return &game.m_visibleBuildingCards.GetCards()[cardIndex];
}

DeckOfCards& RealController::ChooseDeckToDraw(Game& game, const Player& player) const
{
	Print(L"Choisis une pioche pour retourner une carte :\n");
	Print(L"[1] 1, 2 ou 3 pièces\n");
	Print(L"[2] 4 ou 5 pièces\n");
	Print(L"[3] 6, 7, 8 ou 9 pièces\n");

	int input = 0;

	Input<int>(
		L"",
		input,
		[](int var) {return var >= 1 && var <= 3; },
		L"Tu dois entrer un nombre compris entre 1 et 3."
	);

	Print('\n');

	switch (input)
	{
	case 1:
		return game.m_buildingCards1;
	case 2:
		return game.m_buildingCards2;
	case 3:
		return game.m_buildingCards3;
	default:
		return game.m_buildingCards1;
	}
}

int RealController::ChooseWhatToDo(Game& game, const Player& player) const
{
	Print(L"Tu peux maintenant :\n");
	Print(L"[1] Acheter un bâtiment parmi les cartes \"logements\"\n");
	Print(L"[2] Acheter un bâtiment parmi les cartes \"bâtiments\" visibles\n");
	Print(L"[3] Ne rien acheter et récupérer une pièce.\n");

	int input = 0;

	Input<int>(
		L"",
		input,
		[](int var) {return var >= 1 && var <= 3; },
		L"Tu dois entrer un nombre compris entre 1 et 3."
	);

	Print('\n');

	return input;
}

const Card& RealController::ChooseResidenceBuildingToBuy(Game& game, const Player& player, std::vector<Card>*& cardsWhereTaken) const
{
	Print(L"Choisis une carte \"logement\" :\n");
	int i = game.PrintResidencesAndGetCount(true);

	int input = 0;

	Input<int>(
		L"",
		input,
		[i](int var) {return var >= 1 && var <= i; },
		std::format(L"Tu dois entrer un nombre compris entre 1 et {}.", i)
	);

	Print('\n');

	int cardIndex = input - 1;

	const Card* cardToBuy = nullptr;

	if (cardIndex < game.m_houseCards.size())
	{
		cardToBuy = &game.m_houseCards[cardIndex];
	}
	else if (cardIndex < game.m_residenceCards.size())
	{
		cardToBuy = &game.m_residenceCards[cardIndex - game.m_houseCards.size()];
	}
	else
	{
		cardToBuy = &game.m_luxuryResidenceCards[cardIndex - game.m_houseCards.size() - game.m_residenceCards.size()];
	}

	if (input <= game.m_houseCards.size())
	{
		cardsWhereTaken = &game.m_houseCards;
	}
	else if (input <= game.m_residenceCards.size())
	{
		cardsWhereTaken = &game.m_residenceCards;
	}
	else if (input <= game.m_luxuryResidenceCards.size())
	{
		cardsWhereTaken = &game.m_luxuryResidenceCards;
	}

	return *cardToBuy;
}

const Card& RealController::ChooseBuildingToBuy(Game& game, const Player& player, int& cardIndex) const
{
	Print(L"Choisis une carte \"bâtiment\" :\n");
	game.PrintVisibleBuildings(true);

	int input = 0;

	Input<int>(
		L"",
		input,
		[game](int var) {return var >= 1 && var <= game.m_visibleBuildingCards.Size(); },
		std::format(L"Tu dois entrer un nombre compris entre 1 et {}.", game.m_visibleBuildingCards.Size())
	);

	Print('\n');

	cardIndex = input - 1;

	return game.m_visibleBuildingCards.GetCards()[cardIndex];
}

const Card* RealController::ChooseSpecialBuildingToBuy(Game& game, const Player& player, int& cardIndex) const
{
	int input = -1;

	Input<int>(
		L"Pour en obtenir une, entre le numéro associé. Sinon, entre \'0\'.",
		input,
		[game](int var) {return var >= 0 && var <= game.m_specialBuildingCards.Size(); },
		std::format(L"Tu dois entrer un nombre compris entre 0 et {}.", game.m_specialBuildingCards.Size())
	);

	Print('\n');

	if (input == 0) return nullptr;

	cardIndex = input - 1;

	return &game.m_specialBuildingCards.GetCards()[cardIndex];
}