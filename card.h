#ifndef CARD_H
#define CARD_H

class Card
{
	enum class Suit
	{
		kSwords,
		kCups,
		kClubs,
		kCoins
	};

	enum class Value
	{
		kAce,
		kOne,
		kTow,
		kThree,
		kFour,
		kFive,
		kSix,
		kSeven,
		kEight,
		kNine,
		kTen,
		kInfantryman,
		kHorseRider,
		kKing,
	};
};

#endif // CARD_H
