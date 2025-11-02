#include "DeckOfCards.h"

#include <algorithm>
#include <random>

DeckOfCards::DeckOfCards(const std::vector<Card>& cards)
	: m_cards(cards) { }

size_t DeckOfCards::Size() const
{
	return m_cards.size();
}

bool DeckOfCards::Empty() const
{
	return m_cards.empty();
}

const std::vector<Card>& DeckOfCards::GetCards() const
{
	return m_cards;
}

void DeckOfCards::Reserve(size_t maxSize)
{
	m_cards.reserve(maxSize);
}

void DeckOfCards::Shuffle()
{
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::shuffle(m_cards.begin(), m_cards.end(), random_engine);
}

Card DeckOfCards::Draw()
{
	Card card = m_cards[Size() - 1];
	m_cards.pop_back();
	return card;
}

void DeckOfCards::FillByDiscardIfEmpty(std::vector<Card>& discard)
{
	if (Empty())
	{
		*this = discard;
		Shuffle();

		discard.clear();
	}
}