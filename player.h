#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "card.h"
#include "rankings.h"

class Player
{
public:
	Player() = default;
	void AddCardInHand(Card card);
	void ShowHand() const;

	void ClearHand();
	std::vector<Card> Hand() const { return hand_; }

	Rankings rankings_;

	int Bank() const { return bank_; }

	int bank_ = 1000;

private:

	std::vector<Card> hand_;
};

#endif // PLAYER_H
