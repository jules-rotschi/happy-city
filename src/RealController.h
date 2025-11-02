#pragma once

#include "PlayerController.h"

class RealController : public PlayerController
{
public:
	const Card* ChooseCardToDiscard(Game& game, const Player& player, int& cardIndex) const override;
	DeckOfCards& ChooseDeckToDraw(Game& game, const Player& player) const override;
	int ChooseWhatToDo(Game& game, const Player& player) const override;
	const Card& ChooseResidenceBuildingToBuy(Game& game, const Player& player, std::vector<Card>*& cardsWhereTaken) const override;
	const Card& ChooseBuildingToBuy(Game& game, const Player& player, int& cardIndex) const override;
	const Card* ChooseSpecialBuildingToBuy(Game& game, const Player& player, int& cardIndex) const override;
};

