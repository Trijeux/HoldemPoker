#include "rankings.h"

#include <iostream>
#include <map>

void Rankings::StraightFlush(std::vector<Card> hand_player, std::vector<Card> board)
{
	std::vector<Card> all_hand = hand_player;

	for (auto b : board)
	{
		all_hand.emplace_back(b);
	}

	std::map<int, Card::EnumSuit> map_for_straight_flush = Flush(all_hand);

	if (flush_)
	{
		Straight(map_for_straight_flush);
	}
	else
	{
		for (auto a : all_hand)
		{
			map_for_straight_flush.emplace(a.ValueToInt(), a.Suit());
		}
		Straight(map_for_straight_flush);
	}

	if (flush_ && straight_)
	{
		straight_flush_ = true;
		rank_ = EnumRank::kStraightFlush;
	}
}

std::map<int, Card::EnumSuit> Rankings::Flush(std::vector<Card> all_hand)
{
	std::map<int, Card::EnumSuit> square;
	std::map<int, Card::EnumSuit> heart;
	std::map<int, Card::EnumSuit> club;
	std::map<int, Card::EnumSuit> diamond;

	auto suit_to_return = Card::EnumSuit::kNoSuit;

	bool is_flush = false;

	for (auto a : all_hand)
	{
		switch (a.Suit())
		{
		case Card::EnumSuit::kSquare:
			square.emplace(a.ValueToInt(), a.Suit());
			if (!is_flush && square.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kSquare;
				is_flush = true;
			}
			break;
		case Card::EnumSuit::kHeart:
			heart.emplace(a.ValueToInt(), a.Suit());
			if (!is_flush && heart.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kHeart;
				is_flush = true;
			}
			break;
		case Card::EnumSuit::kClub:
			club.emplace(a.ValueToInt(), a.Suit());
			if (!is_flush && club.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kClub;
				is_flush = true;
			}
			break;
		case Card::EnumSuit::kDiamond:
			diamond.emplace(a.ValueToInt(), a.Suit());
			if (!is_flush && diamond.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kDiamond;
				is_flush = true;
			}
			break;
		}
	}

	if (is_flush)
	{
		flush_ = true;
		rank_ = EnumRank::kFlush;
	}

	switch (suit_to_return)
	{
	case Card::EnumSuit::kSquare: return square;
	case Card::EnumSuit::kHeart: return heart;
	case Card::EnumSuit::kClub: return club;
	case Card::EnumSuit::kDiamond: return diamond;
	case Card::EnumSuit::kNoSuit: break;
	}
	return {};
}

void Rankings::Straight(std::map<int, Card::EnumSuit> map_for_straight)
{
	straight_ = false;

	if (map_for_straight.size() >= 5)
	{
		int old_value = 0;
		int straight_count = 0;
		bool have_ace = false;

		for (auto m : map_for_straight)
		{
			if (m.first == 1)
			{
				have_ace = true;
				continue;
			}

			if (m.first == old_value + 1)
			{
				straight_count++;
				old_value = m.first;
			}
			else
			{
				old_value = m.first;
				straight_count = 1;
			}
		}

		if (straight_count == 4 && have_ace && (old_value == 13 || old_value == 5))
		{
			straight_count++;
		}

		if (straight_count >= 5)
		{
			straight_ = true;
			rank_ = EnumRank::kStraight;
		}
	}
}

void Rankings::CheckRank()
{
	switch (rank_)
	{
	case EnumRank::kRoyalFlush: std::cout << "Royal Flush" << std::endl; break;
	case EnumRank::kStraightFlush: std::cout << "Straight Flush" << std::endl; break;
	case EnumRank::kFourOfAKind: std::cout << "Four of a Kind" << std::endl; break;
	case EnumRank::kFullHouse: std::cout << "Full House" << std::endl; break;
	case EnumRank::kFlush: std::cout << "Flush" << std::endl; break;
	case EnumRank::kStraight: std::cout << "Straight" << std::endl; break;
	case EnumRank::kThreeOfAKind: std::cout << "Three of a Kind" << std::endl; break;
	case EnumRank::kTwoPair: std::cout << "Two Pair" << std::endl; break;
	case EnumRank::kOnePair: std::cout << "One Pair" << std::endl; break;
	default: std::cout << "High Card" << std::endl; break;
	}
}

void Rankings::NewGame()
{
	rank_ = EnumRank::kHighCard;
	royal_flush_ = false;
	straight_flush_ = false;
	four_of_a_kind_ = false;
	full_house_ = false;
	flush_ = false;
	straight_ = false;
	three_of_a_kind_ = false;
	two_pair_ = false;
	one_pair_ = false;
	high_card_ = false;
}
