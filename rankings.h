#ifndef RANKINGS_H
#define RANKINGS_H
#include <map>
#include <vector>

#include "card.h"

class Rankings
{
public:
	enum class EnumRank
	{
		kHighCard,
		kOnePair,
		kTwoPair,
		kThreeOfAKind,
		kStraight,
		kFlush,
		kFullHouse,
		kFourOfAKind,
		kStraightFlush,
		kRoyalFlush
	};

	void RoyalFlush(); // Quinte Flush Royale
	void StraightFlush(std::vector<Card>, std::vector<Card>); // Quinte Flush
	void FourOfAKind(); // Carre
	void FullHouse(); // Full
	void ThreeOfAKind(); // Brelan
	void TwoPair(); // Double Paire
	void OnePair(); // Paire
	void HighCard(); // Carte Haute
	void CheckRank();
	void NewGame();
	EnumRank Rank() const { return rank_; }

private:
	std::map<int, Card::EnumSuit> Flush(std::vector<Card> all_hand); // Couleur
	void Straight(std::map<int, Card::EnumSuit> map_for_straight); // Suite

	bool royal_flush_ = false;
	bool straight_flush_ = false;
	bool four_of_a_kind_ = false;
	bool full_house_ = false;
	bool flush_ = false;
	bool straight_ = false;
	bool three_of_a_kind_ = false;
	bool two_pair_ = false;
	bool one_pair_ = false;
	bool high_card_ = false;
	EnumRank rank_;
};

#endif // RANKINGS_H
