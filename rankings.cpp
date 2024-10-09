#include "rankings.h"

#include <algorithm>
#include <iostream>
#include <map>

Rankings::Rankings() : highest_card_(Card(0,0))
{

}

void Rankings::RoyalFlush(std::vector<Card> vector_straight_flush)
{
	int royal_flush = 0;
	for (auto card : vector_straight_flush)
	{
		switch (card.Value())  // NOLINT(clang-diagnostic-switch-enum)
		{
		case Card::EnumValue::kAce:  // NOLINT(bugprone-branch-clone)
			royal_flush++;
			break;
		case Card::EnumValue::kKing:
			royal_flush++;
			break;
		case Card::EnumValue::kQueen:
			royal_flush++;
			break;
		case Card::EnumValue::kJack:
			royal_flush++;
			break;
		case Card::EnumValue::kTen:
			royal_flush++;
			break;
		default:
			royal_flush = 0;
			break;
		}
	}
	if (royal_flush >= 5)
	{
		rank_ = EnumRank::kRoyalFlush;
	}
}

void Rankings::StraightFlush(std::vector<Card> hand_player, std::vector<Card> board)
{
	std::vector<Card> all_hand = hand_player;

	for (auto b : board)
	{
		all_hand.emplace_back(b);
	}

	std::vector<Card> vector_for_straight_flush = Flush(all_hand, hand_player);

	if (flush_)
	{
		Straight(vector_for_straight_flush, hand_player);
	}
	else
	{
		Straight(all_hand, hand_player);
	}

	if (flush_ && straight_)
	{
		rank_ = EnumRank::kStraightFlush;
		RoyalFlush(vector_for_straight_flush);
	}
}

std::vector<Card> Rankings::Flush(std::vector<Card> all_hand, std::vector<Card> hand)
{
	std::vector<Card> vec_square;
	std::vector<Card> vec_heart;
	std::vector<Card> vec_club;
	std::vector<Card> vec_diamond;

	auto suit_to_return = Card::EnumSuit::kNoSuit;

	bool is_flush = false;

	for (auto a : all_hand)
	{
		switch (a.Suit())
		{
		case Card::EnumSuit::kSquare:
			vec_square.emplace_back(a);
			if (!is_flush && vec_square.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kSquare;
				is_flush = true;
			}
			break;
		case Card::EnumSuit::kHeart:
			vec_heart.emplace_back(a);
			if (!is_flush && vec_heart.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kHeart;
				is_flush = true;
			}
			break;
		case Card::EnumSuit::kClub:
			vec_club.emplace_back(a);
			if (!is_flush && vec_club.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kClub;
				is_flush = true;
			}
			break;
		case Card::EnumSuit::kDiamond:
			vec_diamond.emplace_back(a);
			if (!is_flush && vec_diamond.size() >= 5)
			{
				suit_to_return = Card::EnumSuit::kDiamond;
				is_flush = true;
			}
			break;
		}
	}

	bool have_hand = false;
	switch (suit_to_return)
	{
	case Card::EnumSuit::kSquare:
		for (auto h : hand)
		{
			for (auto v : vec_square)
			{
				if (h == v && !have_hand)
				{
					is_flush = true;
					have_hand = true;
				}
				else if (!have_hand)
				{

					is_flush = false;
				}
			}
		}
		break;
	case Card::EnumSuit::kHeart:
		for (auto h : hand)
		{
			for (auto v : vec_heart)
			{
				if (h == v && !have_hand)
				{
					is_flush = true;
					have_hand = true;
				}
				else if (!have_hand)
				{
					is_flush = false;
				}
			}
		}
		break;
	case Card::EnumSuit::kClub:
		for (auto h : hand)
		{
			for (auto v : vec_club)
			{
				if (h == v && !have_hand)
				{
					is_flush = true;
					have_hand = true;
				}
				else if (!have_hand)
				{
					is_flush = false;
				}
			}
		}
		break;
	case Card::EnumSuit::kDiamond:
		for (auto h : hand)
		{
			for (auto v : vec_diamond)
			{
				if (h == v && !have_hand)
				{
					is_flush = true;
					have_hand = true;
				}
				else if (!have_hand)
				{
					is_flush = false;
				}
			}
		}
		break;
	case Card::EnumSuit::kNoSuit: break;
	}

	if (is_flush)
	{
		flush_ = true;
		rank_ = EnumRank::kFlush;
	}

	switch (suit_to_return)
	{
	case Card::EnumSuit::kSquare: return vec_square;
	case Card::EnumSuit::kHeart: return vec_heart;
	case Card::EnumSuit::kClub: return vec_club;
	case Card::EnumSuit::kDiamond: return vec_diamond;
	case Card::EnumSuit::kNoSuit: break;
	}
	return {};
}

void Rankings::Straight(std::vector<Card> all_hand, std::vector<Card> hand)
{
	straight_ = false;

	std::vector<Card> cards_straight;

	std::sort(all_hand.begin(), all_hand.end(), Card::CompareCards);

	if (all_hand.size() >= 5)
	{
		int old_value = 0;
		int straight_count = 0;
		bool is_straight = false;
		bool have_ace = false;

		for (auto a : all_hand)
		{
			if (a.ValueToInt() == 1)
			{
				have_ace = true;
				continue;
			}

			if (a.ValueToInt() == old_value + 1)
			{
				straight_count++;
				old_value = a.ValueToInt();
				cards_straight.emplace_back(a);
				is_straight = true;
			}
			else if (a.ValueToInt() == old_value)
			{
				cards_straight.emplace_back(a);
			}
			else if(!(straight_count == 5))
			{
				old_value = a.ValueToInt();
				straight_count = 1;
				cards_straight.clear();
				cards_straight.emplace_back(a);
				is_straight = false;
			}
		}

		if (is_straight && cards_straight.size() >= 5)
		{
			bool flag_have_hand = false;
			for (auto a : hand)
			{
				for (auto c : cards_straight)
				{
					if (a == c)
					{
						is_straight = true;
						flag_have_hand = true;
						break;
					}
					else
					{
						is_straight = false;
					}
				}
				if (flag_have_hand)
				{
					break;
				}
			}
		}

		if (straight_count == 4 && have_ace && (old_value == 13 || old_value == 5))
		{
			straight_count++;
		}

		if (straight_count >= 5 && is_straight)
		{
			straight_ = true;
			rank_ = EnumRank::kStraight;
		}
	}
}

void Rankings::CheckRank(std::vector<Card> hand, std::vector<Card> board)
{
	HighCard(hand);
	StraightFlush(hand, board);
	if (rank_ != EnumRank::kStraightFlush && rank_ != EnumRank::kRoyalFlush)
	{
		SameValue(hand, board);
	}
	if (rank_ == EnumRank::kHighCard)
	{
		SameValue(hand, board);
	}
}

void Rankings::SameValue(std::vector<Card> hand, std::vector<Card> board)
{
	std::vector<Card> all_hand = board;
	int old_value = 0;

	for (auto a : hand)
	{
		all_hand.emplace_back(a);
	}

	std::sort(all_hand.begin(), all_hand.end(), Card::CompareCards);

	int value_count = 0;
	bool is_same_value = false;

	std::vector<Card> same_value_hand;
	std::vector<Card> same_value_hand_end;

	for (auto a : all_hand)
	{
		if (a.ValueToInt() == old_value)
		{
			value_count++;
			same_value_hand.emplace_back(a);
		}
		else
		{
			old_value = a.ValueToInt();
			value_count = 1;
			if (rank_ == EnumRank::kHighCard)
			{
				is_same_value = false;
			}
			same_value_hand.clear();
			same_value_hand.emplace_back(a);

		}

		if (value_count == 2 && rank_ == EnumRank::kHighCard)
		{
			for (auto s : same_value_hand)
			{
				same_value_hand_end.emplace_back(s);
			}
			same_value_hand.clear();
			is_same_value = true;
			rank_ = EnumRank::kOnePair;
		}
		else if(value_count == 2 && rank_ == EnumRank::kOnePair)
		{
			for (auto s : same_value_hand)
			{
				same_value_hand_end.emplace_back(s);
			}
			same_value_hand.clear();
			is_same_value = true;
			rank_ = EnumRank::kTwoPair;
		}
		else if (value_count == 3 && rank_ == EnumRank::kOnePair)
		{
			for (auto s : same_value_hand)
			{
				same_value_hand_end.emplace_back(s);
			}
			same_value_hand.clear();
			is_same_value = true;
			rank_ = EnumRank::kThreeOfAKind;
		}
		else if (value_count == 3 && (rank_ == EnumRank::kTwoPair || rank_ == EnumRank::kStraight || rank_ == EnumRank::kFlush))
		{
			for (auto s : same_value_hand)
			{
				same_value_hand_end.emplace_back(s);
			}
			same_value_hand.clear();
			is_same_value = true;
			rank_ = EnumRank::kFullHouse;
		}
		else if (value_count == 4 && (rank_ == EnumRank::kThreeOfAKind || rank_ == EnumRank::kStraight || rank_ == EnumRank::kFlush))
		{
			for (auto s : same_value_hand)
			{
				same_value_hand_end.emplace_back(s);
			}
			same_value_hand.clear();
			is_same_value = true;
			rank_ = EnumRank::kFourOfAKind;
		}

	}

	if (is_same_value && same_value_hand_end.size() >= 2)
	{
		bool flag_have_hand = false;
		for (auto a : hand)
		{
			for (auto c : same_value_hand_end)
			{
				if (a == c)
				{
					is_same_value = true;
					flag_have_hand = true;
					break;
				}
				else
				{
					is_same_value = false;
				}
			}
			if (flag_have_hand)
			{
				break;
			}
		}

		if (!is_same_value)
		{
			rank_ = EnumRank::kHighCard;
		}
	}
}

void Rankings::HighCard(std::vector<Card> hand)
{
	if (hand.front() > hand.back())
	{
		highest_card_ = hand.front();
	}
	else
	{
		highest_card_ = hand.back();
	}


	if (hand.front().ValueToInt() == 1)
	{
		highest_card_ = hand.front();
	}
	else if (hand.back().ValueToInt() == 1)
	{
		highest_card_ = hand.back();
	}
	
}

void Rankings::RankToString()
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
	default: std::cout << "High Card : " << highest_card_.ValueToString() << " of " << highest_card_.SuitToString() << std::endl; break;
	}
}

int Rankings::RankToInt()
{
	switch (rank_)
	{
	case EnumRank::kRoyalFlush: return static_cast<int>(EnumRank::kRoyalFlush);
	case EnumRank::kStraightFlush: return static_cast<int>(EnumRank::kStraightFlush);
	case EnumRank::kFourOfAKind: return static_cast<int>(EnumRank::kFourOfAKind);
	case EnumRank::kFullHouse: return static_cast<int>(EnumRank::kFullHouse);
	case EnumRank::kFlush: return static_cast<int>(EnumRank::kFlush);
	case EnumRank::kStraight: return static_cast<int>(EnumRank::kStraight);
	case EnumRank::kThreeOfAKind: return static_cast<int>(EnumRank::kThreeOfAKind);
	case EnumRank::kTwoPair: return static_cast<int>(EnumRank::kTwoPair);
	case EnumRank::kOnePair: return static_cast<int>(EnumRank::kOnePair);
	case EnumRank::kHighCard: return static_cast<int>(EnumRank::kHighCard);
	}
}

void Rankings::NewGame()
{
	rank_ = EnumRank::kHighCard;
	flush_ = false;
	straight_ = false;
}
