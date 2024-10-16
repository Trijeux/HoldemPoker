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

	std::string name_;
	
	int bank_ = 1000;

	int bet_ = 0;

private:

	std::vector<Card> hand_;
};

#endif // PLAYER_H
