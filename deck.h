#ifndef DECK_H
#define DECK_H
#include <vector>

#include "card.h"

constexpr int kNbCardForOneSuitMax = 13;
constexpr int kNbSuitMax = 4;

class Deck
{
public:
	void MakeDeck();

	void DrawDeck() const;

	Card PickCardAndRemove();

	void ShuffleDeck();

	void ClearDeck();

	void BurnCard();
private:
	std::vector<Card> cards_;

};

#endif // DECK_H
