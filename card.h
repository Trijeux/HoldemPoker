#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

class Card
{
public:
	enum class EnumSuit
	{
		kSquare,
		kHeart,
		kClub,
		kDiamond,
		kNoSuit
	};

	enum class EnumValue
	{
		kAce = 1,
		kTwo,
		kThree,
		kFour,
		kFive,
		kSix,
		kSeven,
		kEight,
		kNine,
		kTen,
		kJack,
		kQueen,
		kKing
	};

	Card(int value, int suit);
	static bool CompareCards(const Card& a, const Card& b);

	std::string SuitToString() const;
	std::string ValueToString() const;

	int ValueToInt() const { return static_cast<int>(value_); }

	EnumValue Value() const { return value_; }
	EnumSuit Suit() const { return suit_; }

	bool operator==(const Card& other) const { return value_ == other.value_ && suit_ == other.suit_; }

	bool operator>(const Card& other) const { return value_ > other.value_; }

private:
	EnumValue value_;
	EnumSuit suit_;
};

#endif // CARD_H
