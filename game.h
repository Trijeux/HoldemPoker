#ifndef GAME_H
#define GAME_H
#include "dealer.h"
#include "deck.h"
#include "player.h"
#include "rankings.h"


constexpr int kBetOne = 10;
constexpr int kBetTow = 50;
constexpr int kBetThree = 100;
constexpr int kBetFour = 500;

class Game
{
public:
	Game();
	void WhoWinner();
	void NewGame();
	void DisplayRankPlayer();
	void CheckHand();
	void CheckBankEmpty(bool& game_end);
	void GameLoop();
private:
	Player player1_;
	Player player2_;

	Dealer dealer_;

	Deck deck_;

	int pot_ = 0;

	void CardDeal();
	void Flop();
	void Turn();
	void River();
	void DisplayPlayer1();
	void DisplayPlayer2();
	void DisplayTable();

	void BetTurn(bool& flag_fold_player_one, bool& flag_fold_player_tow, bool& flag_fold, bool& flag_all_in);
};

#endif // GAME_H
