#ifndef DEALER_H
#define DEALER_H
#include <vector>

#include "card.h"

class Dealer
{
public:
	Dealer() = default;

	void AddCardInBoard(const Card card);

	void ShowBoard() const;

	void ClearBoard();

	std::vector<Card> Board() const { return board_; }

private:
	std::vector<Card> board_;


};

#endif // DEALER_H
