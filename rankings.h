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

	void RoyalFlush(std::vector<Card> vector_straight_flush); // Quinte Flush Royale
	void StraightFlush(std::vector<Card>, std::vector<Card>); // Quinte Flush
	void SameValue(std::vector<Card>, std::vector<Card>); // Carte Identique
	void HighCard(std::vector<Card>);// Carte Haute
	void CheckRank();
	void NewGame();
	EnumRank Rank() const { return rank_; }

private:
	std::vector<Card> Flush(std::vector<Card>, std::vector<Card>); // Couleur
	void Straight(std::vector<Card>, std::vector<Card>); // Suite

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
