#include "game.h"

#include <iostream>

Game::Game()
{
	//deck_.MakeDeck();
	////deck_.ShuffleDeck();

	//deck_.DrawDeck();
	//std::cout << std::endl;
}

void Game::GameLoop()
{
	Rankings::EnumRank rank;
	int round = 1;

	do
	{
		deck_.MakeDeck();
		deck_.ShuffleDeck();
		
		CardDeal();


		DrawGame();
		/*system("pause");
	system("cls");*/
		Flop();

		DrawGame();
		/*system("pause");
	system("cls");*/
		Turn();

		DrawGame();
		/*system("pause");
	system("cls");*/
		River();


		DrawGame();
		std::cout << std::endl << std::endl << std::endl;
		player1_.rankings_.SameValue(player1_.Hand(), dealer_.Board());
		player2_.rankings_.SameValue(player2_.Hand(), dealer_.Board());

		std::cout << "Player 1's rank: " << std::endl;
		player1_.rankings_.CheckRank();
		std::cout << "Player 2's rank: " << std::endl;
		player2_.rankings_.CheckRank();

		rank = player1_.rankings_.Rank();

		deck_.ClearDeck();
		player1_.ClearHand();
		player1_.rankings_.NewGame();
		player2_.ClearHand();
		player2_.rankings_.NewGame();
		dealer_.ClearBoard();

		std::cout << std::endl;

		round++;
	}
	while (!(rank == Rankings::EnumRank::kThreeOfAKind));
	std::cout << std::endl << "Nombre de Round : " << round << std::endl;
}

void Game::CardDeal()
{
	for (int i = 0; i < 2; ++i)
	{
		player1_.AddCardInHand(deck_.PickCardAndRemove());
		player2_.AddCardInHand(deck_.PickCardAndRemove());
	}
}

void Game::Flop()
{
	deck_.BurnCard();
	for (int i = 0; i < 3; ++i)
	{
		dealer_.AddCardInBoard(deck_.PickCardAndRemove());
	}
}

void Game::Turn()
{
	deck_.BurnCard();
	dealer_.AddCardInBoard(deck_.PickCardAndRemove());
}

void Game::River()
{
	deck_.BurnCard();
	dealer_.AddCardInBoard(deck_.PickCardAndRemove());
}

void Game::DrawGame()
{
	std::cout << "Player 1's hand:" << std::endl;
	player1_.ShowHand();
	std::cout << std::endl << "Player 2's hand:" << std::endl;
	player2_.ShowHand();
	std::cout << std::endl << "Board :" << std::endl;
	dealer_.ShowBoard();
	std::cout << std::endl;
}
