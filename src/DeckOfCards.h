#pragma once

#include <vector>

#include "Card.h"

class DeckOfCards
{
public:
	DeckOfCards() = default;
	DeckOfCards(const std::vector<Card>& cards);

	size_t Size() const;
	bool Empty() const;

	const std::vector<Card>& GetCards() const;
	
	void Reserve(size_t maxSize);

	void Shuffle();
	Card Draw();
	void FillByDiscardIfEmpty(std::vector<Card>& discard);

private:
	std::vector<Card> m_cards;
};

