#include "dealer.h"

#include <iostream>
#include <ostream>

void Dealer::AddCardInBoard(const Card card)
{
	board_.push_back(card);
}

void Dealer::ShowBoard() const
{
	for (const auto& b : board_)
	{
		std::cout << b.ValueToString() << " of " << b.SuitToString() << std::endl;
	}
}

void Dealer::ClearBoard()
{
	board_.clear();
	board_.shrink_to_fit();
}
