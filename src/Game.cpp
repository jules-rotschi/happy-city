#include "Game.h"

#include <array>
#include <algorithm>
#include <random>

#include "Player.h"
#include "Card.h"
#include "Input.h"
#include "PlayerController.h"
#include "Print.h"

void Game::Init()
{
	int playersCount = 0;

	Input<int>(
		L"Combien de joueurs pour cette partie ?",
		playersCount,
		[](int count) {return count >= 2 && count <= 5; },
		L"Le jeu se joue entre 2 et 5 joueurs."
	);

	m_players.reserve(playersCount);

	Print('\n');

	for (int i = 0; i < playersCount; i++)
	{
		std::wstring name;
		bool isAi = false;

		Input(
			std::format(L"Quel est le nom du joueur {} ?", i + 1),
			name,
			[](const std::wstring& _) {return true; },
			L""
		);

		Print('\n');

		std::wstring aiInput;

		Input(
			std::format(L"{} est-il un réel humain (h) ou une intelligence artificielle (ia) ?", name),
			aiInput,
			[](const std::wstring& input) {return input == L"h" || input == L"H" || input == L"ia" || input == L"IA"; },
			LR"(Entrée invalide : entre 'h' pour "humain" ou 'ia' pour "intelligence artificelle".)"
		);

		Print('\n');

		if (aiInput == L"ia" || aiInput == L"IA")
			isAi = true;

		m_players.push_back(new Player(name, isAi));
	}

	for (Player* player : m_players)
	{
		player->GetCity().BuyCard({ CardType::HAPPY_MARKET, L"Happy market", 0, 1, 0, 0 });
	}

	m_buildingCards1.Reserve(22);
	m_buildingCards2.Reserve(22);
	m_buildingCards3.Reserve(22);

	m_buildingCards1 = DeckOfCards({
		{ CardType::INDUSTRY, L"Usine", 1, 1, -1, 0 },
		{ CardType::INDUSTRY, L"Aciérie", 1, 1, -1, 0 },
		{ CardType::INDUSTRY, L"Maison hantée", 1, 1, 0, -1 },
		{ CardType::INDUSTRY, L"Maison hantée", 1, 1, 0, -1 },
		{ CardType::PUBLIC, L"Commissariat", 2, 0, 0, 1 },
		{ CardType::PUBLIC, L"École", 2, 0, 0, 1 },
		{ CardType::BUSINESS, L"Magasin de chaussures", 2, 1, 0, 0 },
		{ CardType::BUSINESS, L"Magasin de chaussures", 2, 1, 0, 0 },
		{ CardType::PUBLIC, L"Parc", 2, 0, 1, 0 },
		{ CardType::PUBLIC, L"Parc", 2, 0, 1, 0 },
		{ CardType::BUSINESS, L"Marché", 2, 1, 0, 0 },
		{ CardType::BUSINESS, L"Marché", 2, 1, 0, 0 },
		{ CardType::ACCOMODATION, L"Igloo", 3, 1, 0, 1 },
		{ CardType::ACCOMODATION, L"Igloo", 3, 1, 0, 1 },
		{ CardType::BUSINESS, L"Bibliothèque", 3, 1, 0, 1 },
		{ CardType::BUSINESS, L"Bibliothèque", 3, 1, 0, 1 },
		{ CardType::BUSINESS, L"Pâtisserie", 3, 1, 1, 0 },
		{ CardType::BUSINESS, L"Pâtisserie", 3, 1, 1, 0 },
		{ CardType::BUSINESS, L"Banque", 3, 1, 0, 1 },
		{ CardType::BUSINESS, L"Banque", 3, 1, 0, 1 },
		{ CardType::BUSINESS, L"Fleuriste", 3, 1, 1, 0 },
		{ CardType::BUSINESS, L"Fleuriste", 3, 1, 1, 0 }
	});

	m_buildingCards2 = DeckOfCards({
		{ CardType::PUBLIC, L"Musée", 4, 0, 2, 0 },
		{ CardType::PUBLIC, L"Musée", 4, 0, 2, 0 },
		{ CardType::BUSINESS, L"Parfumerie", 4, 2, 0, 0 },
		{ CardType::BUSINESS, L"Parfumerie", 4, 2, 0, 0 },
		{ CardType::PUBLIC, L"Observatoire", 4, 0, 2, 0 },
		{ CardType::PUBLIC, L"Observatoire", 4, 0, 2, 0 },
		{ CardType::BUSINESS, L"Magasin de bricolage", 4, 2, 0, 0 },
		{ CardType::BUSINESS, L"Magasin de bricolage", 4, 2, 0, 0 },
		{ CardType::PUBLIC, L"Hôpital", 4, 0, 0, 2 },
		{ CardType::PUBLIC, L"Hôpital", 4, 0, 0, 2 },
		{ CardType::BUSINESS, L"Centre commercial", 5, 1, 2, 0 },
		{ CardType::BUSINESS, L"Centre commercial", 5, 1, 2, 0 },
		{ CardType::HOBBY, L"Palace", 5, 2, 1, 0 },
		{ CardType::HOBBY, L"Palace", 5, 2, 1, 0 },
		{ CardType::INDUSTRY, L"Garage", 5, 2, 0, 1 },
		{ CardType::INDUSTRY, L"Garage", 5, 2, 0, 1 },
		{ CardType::INDUSTRY, L"Bureaux", 5, 2, 0, 1 },
		{ CardType::INDUSTRY, L"Bureaux", 5, 2, 0, 1 },
		{ CardType::HOBBY, L"Restaurant", 5, 2, 1, 0 },
		{ CardType::HOBBY, L"Restaurant", 5, 2, 1, 0 },
		{ CardType::PUBLIC, L"Mystère 1", 5, 1, 1, 1 },
		{ CardType::PUBLIC, L"Mystère 1", 5, 1, 1, 1 }
	});

	m_buildingCards3 = DeckOfCards({
		{ CardType::PUBLIC, L"Laboratoire", 6, 1, 0, 2 },
		{ CardType::PUBLIC, L"Laboratoire", 6, 1, 0, 2 },
		{ CardType::PUBLIC, L"Université", 6, 1, 0, 2 },
		{ CardType::PUBLIC, L"Université", 6, 1, 0, 2 },
		{ CardType::HOBBY, L"Casino", 7, 2, 2, 0 },
		{ CardType::HOBBY, L"Casino", 7, 2, 2, 0 },
		{ CardType::HOBBY, L"SPA", 7, 2, 2, 0 },
		{ CardType::HOBBY, L"SPA", 7, 2, 2, 0 },
		{ CardType::ACCOMODATION, L"Cabane", 8, 0, 0, 3 },
		{ CardType::ACCOMODATION, L"Cabane", 8, 0, 0, 3 },
		{ CardType::HOBBY, L"Station de ski", 8, 0, 3, 0 },
		{ CardType::HOBBY, L"Station de ski", 8, 0, 3, 0 },
		{ CardType::HOBBY, L"Zoo", 8, 0, 3, 0 },
		{ CardType::HOBBY, L"Zoo", 8, 0, 3, 0 },
		{ CardType::HOBBY, L"Parc d'attraction", 9, 1, 3, 0 },
		{ CardType::HOBBY, L"Parc d'attraction", 9, 1, 3, 0 },
		{ CardType::HOBBY, L"Stade", 9, 1, 3, 0 },
		{ CardType::HOBBY, L"Stade", 9, 1, 3, 0 },
		{ CardType::PUBLIC, L"Mystère 2", 9, 1, 0, 3 },
		{ CardType::PUBLIC, L"Mystère 2", 9, 1, 0, 3 },
		{ CardType::PUBLIC, L"Mystère 3", 9, 1, 0, 3 },
		{ CardType::PUBLIC, L"Mystère 3", 9, 1, 0, 3 }
	});

	m_buildingCards1.Shuffle();
	m_buildingCards2.Shuffle();
	m_buildingCards3.Shuffle();

	Card houseCard(CardType::ACCOMODATION, L"Maison", 1, 0, 0, 1);
	Card residenceCard(CardType::ACCOMODATION, L"Immeuble", 3, 0, 0, 2);
	Card luxuryResidenceCard(CardType::ACCOMODATION, L"Résidence de luxe", 6, 0, 0, 3);

	m_houseCards.reserve(m_players.size() - 1);
	m_residenceCards.reserve(m_players.size() - 1);
	m_luxuryResidenceCards.reserve(m_players.size() - 1);

	for (int i = 0; i < m_players.size() - 1; i++)
	{
		m_houseCards.push_back(houseCard);
		m_residenceCards.push_back(residenceCard);
		m_luxuryResidenceCards.push_back(luxuryResidenceCard);
	}

	std::array<Card, 18> specialBuildingCards = {
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0),
		Card(CardType::SPECIAL, L"Ranch de licornes", { {CardType::PUBLIC, 2}, {CardType::ACCOMODATION, 1}, {CardType::INDUSTRY, 1} }, 1, 3, 0)
	};

	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::shuffle(specialBuildingCards.begin(), specialBuildingCards.end(), random_engine);

	for (int i = 0; i < m_players.size() + 2; i++)
	{
		m_specialBuildingCards.Add(specialBuildingCards[i]);
	}
}

void Game::Run()
{
	while (!m_isOver)
	{
		Income();
		Actions();
		Print(L"Fin du tour de table.\n\n");
	}

	Print(L"La partie est terminée !\n\n");

	PrintState();
	Print('\n');

	Print(L"Scores :\n");

	for (const Player* player : m_players)
	{
		Print(std::format(L"- {} -> {}\n", player->GetName(), player->GetScore()));
	}

	Print('\n');

	const Player* winner = GetWinner();

	if (!winner)
	{
		Print(L"Aucun gagnant...\n");
	}
	else
	{
		Print(std::format(L"{} a gagné !\n", winner->GetName()));
	}
}

void Game::ShutDown()
{
	for (Player* player : m_players)
	{
		delete player;
	}
}

void Game::Income() const
{
	for (Player* player : m_players)
	{
		player->GetCity().Income();
	}
	Print(L"Les salaires ont été versés !\n\n");
}

void Game::Actions()
{
	for (Player* player : m_players)
	{
		LetPlay(*player);
	}
}

void Game::PrintState() const
{
	for (const Player* player : m_players)
	{
		Print(std::format(L"--- Ville de {} ---\n", player->GetName()));
		player->PrintCityState();
		Print('\n');
	}

	Print(L"Cartes \"bâtiments spéciaux\" disponibles :\n");
	PrintSpecialBuildings(false);
}

void Game::PrintResidences(bool isOrdered) const
{
	int i = 1;
	for (const Card& card : m_houseCards)
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
			i++;
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
	}

	for (const Card& card : m_residenceCards)
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
			i++;
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
	}

	for (const Card& card : m_luxuryResidenceCards)
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
			i++;
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
	}
}

int Game::PrintResidencesAndGetCount(bool isOrdered) const
{
	int i = 1;
	for (const Card& card : m_houseCards)
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
		i++;
	}

	for (const Card& card : m_residenceCards)
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
		i++;
	}

	for (const Card& card : m_luxuryResidenceCards)
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
		i++;
	}

	return i - 1;
}

void Game::PrintVisibleBuildings(bool isOrdered) const
{
	int i = 1;
	for (const Card& card : m_visibleBuildingCards.GetCards())
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
			i++;
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
	}
}

void Game::PrintSpecialBuildings(bool isOrdered) const
{
	int i = 1;
	for (const Card& card : m_specialBuildingCards.GetCards())
	{
		if (isOrdered)
		{
			Print(std::format(L"[{}] {}\n", i, card.ToString()));
			i++;
		}
		else
		{
			Print(std::format(L"  - {}\n", card.ToString()));
		}
	}
}

void Game::LetPlay(Player& player)
{
	PrintState();
	Print(std::format(L"\n{}, à ton tour !\n\n", player.GetName()));

	LetDiscardVisibleCard(player);
	LetDrawNewCards(player);

	Print(L"Cartes \"logements\" disponibles :\n");
	PrintResidences(false);
	Print(L"\n");

	Print(L"Cartes \"bâtiments\" disponibles :\n");
	PrintVisibleBuildings(false);
	Print(L"\n");

	bool hasPlayed = false;

	while (!hasPlayed)
	{
		int input = player.GetController().ChooseWhatToDo(*this, player);

		switch (input)
		{
		case 1:
			hasPlayed = LetBuyResidenceBuilding(player);
			break;
		case 2:
			hasPlayed = LetBuyBuilding(player);
			break;
		case 3:
		default:
			player.GetCity().GiveMoney(1);
			hasPlayed = true;
		}
	}

	if (!player.GetCity().IsFull())
	{
		bool hasGotOrLeave = false;
		
		while (!hasGotOrLeave)
		{
			hasGotOrLeave = LetGetSpecialCard(player);
		}
	}

	if (player.GetCity().IsFull())
	{
		Print(std::format(L"La ville de {} est pleine (10 bâtiments). La partie est terminée dès la fin du tour.\n\n", player.GetName()));
		m_isOver = true;
	}

	Print(std::format(L"---------- FIN DU TOUR DE {} ----------\n\n", player.GetName()));
}

void Game::LetDiscardVisibleCard(const Player& player)
{
	if (!m_visibleBuildingCards.Empty())
	{
		Print(L"Voici les cartes \"bâtiment\" visibles :\n");
		PrintVisibleBuildings(true);
		Print(L"\n");

		int cardIndex = 0;

		const Card* cardToDiscard = player.GetController().ChooseCardToDiscard(*this, player, cardIndex);

		if (!cardToDiscard) return;

		Print(std::format(L"{} défausse la carte {}.\n\n", player.GetName(), cardToDiscard->GetName()));

		if (cardToDiscard->GetPrice() <= 3)
		{
			m_buildingCardsDiscard1.push_back(*cardToDiscard);
		}
		else if (cardToDiscard->GetPrice() <= 5)
		{
			m_buildingCardsDiscard2.push_back(*cardToDiscard);
		}
		else
		{
			m_buildingCardsDiscard3.push_back(*cardToDiscard);
		}

		m_visibleBuildingCards.RemoveAt(cardIndex);
	}
}

void Game::LetDrawNewCards(const Player& player)
{
	while (m_visibleBuildingCards.Size() < 3)
	{
		if (m_visibleBuildingCards.Empty())
		{
			Print(L"Aucune carte \"bâtiment\" visible.\n\n");
		}
		else
		{
			Print(L"Voici les cartes \"bâtiments\" visibles :\n");
			PrintVisibleBuildings(false);
			Print(L"\n");
		}

		DeckOfCards& deckForDrawing = player.GetController().ChooseDeckToDraw(*this, player);

		Print(std::format(L"{} pioche.\n\n", player.GetName()));

		m_visibleBuildingCards.Add(deckForDrawing.Draw());

		m_buildingCards1.FillByDiscardIfEmpty(m_buildingCardsDiscard1);
		m_buildingCards2.FillByDiscardIfEmpty(m_buildingCardsDiscard2);
		m_buildingCards3.FillByDiscardIfEmpty(m_buildingCardsDiscard3);
	}
}

bool Game::LetBuyResidenceBuilding(Player& player)
{
	if (m_houseCards.empty() && m_residenceCards.empty() && m_luxuryResidenceCards.empty())
	{
		Print(L"Il n'y a plus de cartes \"logement\" disponible...\n");
		return false;
	}

	std::vector<Card>* cardsWhereTaken = nullptr;

	const Card& cardToBuy = player.GetController().ChooseResidenceBuildingToBuy(*this, player, cardsWhereTaken);

	if (cardToBuy.GetPrice() > player.GetCityMoney())
	{
		Print(L"Tu n'as pas assez d'argent pour acheter cette carte.\n");
		return false;
	}

	if (player.CityContains(cardToBuy))
	{
		Print(L"Tu ne peux pas acheter une carte que tu as déjà.\n");
		return false;
	}

	Print(std::format(L"{} achète la carte {}.\n\n", player.GetName(), cardToBuy.GetName()));
	
	player.GetCity().BuyCard(cardToBuy);

	cardsWhereTaken->pop_back();

	return true;
}

bool Game::LetBuyBuilding(Player& player)
{
	int cardIndex = 0;

	const Card& cardToBuy = player.GetController().ChooseBuildingToBuy(*this, player, cardIndex);

	if (cardToBuy.GetPrice() > player.GetCityMoney())
	{
		Print(L"Tu n'as pas assez d'argent pour acheter cette carte.\n");
		return false;
	}

	if (player.CityContains(cardToBuy))
	{
		Print(L"Tu ne peux pas acheter une carte que tu as déjà.\n");
		return false;
	}

	Print(std::format(L"{} achète la carte {}.\n\n", player.GetName(), cardToBuy.GetName()));

	player.GetCity().BuyCard(cardToBuy);
	m_visibleBuildingCards.RemoveAt(cardIndex);

	return true;
}

bool Game::LetGetSpecialCard(Player& player)
{
	Print(L"Voici ta ville :\n");
	player.PrintCityState();
	Print('\n');

	Print(L"Voici les cartes \"bâtiments spéciaux\" disponibles :\n");
	PrintSpecialBuildings(true);
	Print('\n');

	int cardIndex = 0;

	const Card* cardToBuy = player.GetController().ChooseSpecialBuildingToBuy(*this, player, cardIndex);

	if (!cardToBuy) return true;

	if (!cardToBuy->IsAccessibleTo(player))
	{
		Print(L"Ta ville ne remplit pas les conditions nécessaires pour prendre cette carte spéciale.\n");
		return false;
	}
	
	player.GetCity().BuyCard(*cardToBuy);
	m_specialBuildingCards.RemoveAt(cardIndex);

	return true;
}

const Player* Game::GetWinner() const
{
	int maxScore = 0;
	const Player* winner = nullptr;
	int winnerMoney = 0;

	for (const Player* player : m_players)
	{
		int score = player->GetScore();

		if (score > maxScore)
		{
			maxScore = score;
			winner = player;
			winnerMoney = player->GetCityMoney();
		}

		else if (score == maxScore)
		{
			int money = player->GetCityMoney();
			if (money > winnerMoney)
			{
				winner = player;
				winnerMoney = money;
			}
			if (money == winnerMoney)
			{
				winner = nullptr;
			}
		}
	}

	return winner;
}