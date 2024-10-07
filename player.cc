#include "player.h"

#include <iostream>

void Player::AddCardInHand(const Card card)
{
	hand_.push_back(card);
}

void Player::ShowHand() const
{
	for (const auto& h : hand_)
	{
		std::cout << h.ValueToString() << " of " << h.SuitToString() << std::endl;
	}
}

void Player::ClearHand()
{
	hand_.clear();
	hand_.shrink_to_fit();
}
