#pragma once

#include <vector>

class Card;
class Game;
class DeckOfCards;
class Player;

class PlayerController
{
public:
	PlayerController() = default;
	virtual ~PlayerController() = default;

	virtual const Card* ChooseCardToDiscard(Game& game, const Player& player, int& cardIndex) const = 0;
	virtual DeckOfCards& ChooseDeckToDraw(Game& game, const Player& player) const = 0;
	virtual int ChooseWhatToDo(Game& game, const Player& player) const = 0;
	virtual const Card& ChooseResidenceBuildingToBuy(Game& game, const Player& player, std::vector<Card>*& cardsWhereTaken) const = 0;
	virtual const Card& ChooseBuildingToBuy(Game& game, const Player& player, int& cardIndex) const = 0;
	virtual const Card* ChooseSpecialBuildingToBuy(Game& game, const Player& player, int& cardIndex) const = 0;
};

