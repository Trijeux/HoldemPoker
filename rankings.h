#ifndef RANKINGS_H
#define RANKINGS_H
#include <map>
#include <vector>

#include "card.h"

class Rankings
{
public:
	Rankings();

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

	void RankToString();

	int RankToInt();

	void NewGame();
	void CheckRank(std::vector<Card>,std::vector<Card>);
	EnumRank Rank() const { return rank_; }
	Card HighestCard() const { return highest_card_; }

private:

	void RoyalFlush(std::vector<Card> vector_straight_flush); // Quinte Flush Royale
	void StraightFlush(std::vector<Card>, std::vector<Card>); // Quinte Flush
	void SameValue(std::vector<Card>, std::vector<Card>); // Carte Identique
	void HighCard(std::vector<Card>);// Carte Haute
	std::vector<Card> Flush(std::vector<Card>, std::vector<Card>); // Couleur
	void Straight(std::vector<Card>, std::vector<Card>); // Suite

	bool straight_ = false;
	bool flush_ = false;

	Card highest_card_;
	EnumRank rank_ = EnumRank::kHighCard;
};

#endif // RANKINGS_H
