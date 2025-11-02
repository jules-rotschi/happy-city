#include "SetOfCards.h"

SetOfCards::SetOfCards(const std::vector<Card>& cards)
	: m_cards(cards) { }

size_t SetOfCards::Size() const
{
	return m_cards.size();
}

bool SetOfCards::Empty() const
{
	return m_cards.empty();
}

const std::vector<Card>& SetOfCards::GetCards() const
{
	return m_cards;
}

void SetOfCards::Add(const Card& card)
{
	m_cards.push_back(card);
}

void SetOfCards::RemoveAt(int index)
{
	for (int i = index; i < Size() - 1; i++)
	{
		m_cards[i] = m_cards[static_cast<size_t>(i) + 1];
	}
	m_cards.pop_back();
}