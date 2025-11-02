#pragma once

#include <set>
#include <vector>

#include "Card.h"

class SetOfCards
{
public:
	SetOfCards() = default;
	SetOfCards(const std::vector<Card>& cards);

	size_t Size() const;
	bool Empty() const;

	const std::vector<Card>& GetCards() const;

	void Add(const Card& card);
	void RemoveAt(int index);

private:
	std::vector<Card> m_cards;
};

