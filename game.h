#ifndef GAME_H
#define GAME_H
#include "dealer.h"
#include "deck.h"
#include "player.h"
#include "rankings.h"

class Game
{
public:
	Game();
	void GameLoop();
private:
	Player player1_;
	Player player2_;

	Dealer dealer_;

	Deck deck_;

	void CardDeal();
	void Flop();
	void Turn();
	void River();
	void DrawGame();
};

#endif // GAME_H
