#include "deck.h"

#include <iostream>
#include <random>

void Deck::MakeDeck()
{
	for (int suit = 0; suit <= kNbSuitMax-1; suit++)
	{
		for (int value = 1; value <= kNbCardForOneSuitMax; value++)
		{
			cards_.emplace_back(value, suit);
		}
	}
}

void Deck::DrawDeck() const
{
	for (auto c : cards_)
	{
		std::cout << c.ValueToString() << " of " << c.SuitToString() << std::endl;
	}
}

Card Deck::PickCardAndRemove()
{
	Card card = cards_.front();
	cards_.erase(cards_.begin());
	return card;
}

void Deck::ShuffleDeck()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards_.begin(), cards_.end(), g);
}

void Deck::ClearDeck()
{
	cards_.clear();
	cards_.shrink_to_fit();
}

void Deck::BurnCard()
{
	cards_.erase(cards_.begin());
}
