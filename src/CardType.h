#pragma once

enum class CardType
{
	HAPPY_MARKET,
	ACCOMODATION,
	BUSINESS,
	INDUSTRY,
	PUBLIC,
	HOBBY,
	SPECIAL
};

inline std::wstring CardTypeToString(CardType cardType)
{
	switch (cardType)
	{
	case CardType::HAPPY_MARKET:
		return L"Happy Market";

	case CardType::ACCOMODATION:
		return L"Habitation";

	case CardType::BUSINESS:
		return L"Commerce";

	case CardType::INDUSTRY:
		return L"Bâtiment industriel";

	case CardType::PUBLIC:
		return L"Bâtiment public";

	case CardType::HOBBY:
		return L"Lieu de loisir";

	case CardType::SPECIAL:
		return L"Bâtiment spécial";

	default:
		return L"Inconnu";
	}
}