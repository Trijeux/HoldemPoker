#include "card.h"

#include <iostream>

Card::Card(const int value, const int suit)
{
	value_ = static_cast<EnumValue>(value);
	suit_ = static_cast<EnumSuit>(suit);
}

bool Card::CompareCards(const Card& a, const Card& b)
{
	return static_cast<int>(a.value_) < static_cast<int>(b.value_);
}
std::string Card::SuitToString() const
{
	switch (suit_)
	{
	case EnumSuit::kHeart: return "Hearts";
	case EnumSuit::kDiamond: return "Diamonds";
	case EnumSuit::kClub: return "Clubs";
	case EnumSuit::kSquare: return "Spades";
	}
	return {};
}

std::string Card::ValueToString() const
{
	switch (value_)
	{
	case EnumValue::kAce: return "Ace";
	case EnumValue::kTwo: return "Two";
	case EnumValue::kThree: return "Three";
	case EnumValue::kFour: return "Four";
	case EnumValue::kFive: return "Five";
	case EnumValue::kSix: return "Six";
	case EnumValue::kSeven: return "Seven";
	case EnumValue::kEight: return "Eight";
	case EnumValue::kNine: return "Nine";
	case EnumValue::kTen: return "Ten";
	case EnumValue::kJack: return "Jack";
	case EnumValue::kQueen: return "Queen";
	case EnumValue::kKing: return "King";
	}
	return {};
}
