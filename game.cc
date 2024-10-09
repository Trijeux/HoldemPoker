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
	bool game_end = false;

	do
	{
		deck_.MakeDeck();
		deck_.ShuffleDeck();
		
		CardDeal();


		//DrawGame();
		/*system("pause");
	system("cls");*/
		Flop();

		//DrawGame();
		/*system("pause");
	system("cls");*/
		Turn();

		//DrawGame();
		/*system("pause");
	system("cls");*/
		River();


		DrawGame();
		std::cout << std::endl << std::endl << std::endl;
		player1_.rankings_.CheckRank(player1_.Hand(), dealer_.Board());
		player2_.rankings_.CheckRank(player2_.Hand(), dealer_.Board());

		std::cout << "Player 1's rank: " << std::endl;
		player1_.rankings_.RankToString();
		std::cout << "Player 2's rank: " << std::endl;
		player2_.rankings_.RankToString();

		std::cout << std::endl;

		if (player1_.rankings_.RankToInt() > player2_.rankings_.RankToInt())
		{
			std::cout << "Player 1 wins!" << std::endl;
		}
		else if (player1_.rankings_.RankToInt() < player2_.rankings_.RankToInt())
		{
			std::cout << "Player 2 wins!" << std::endl;
		}
		else if (player1_.rankings_.RankToInt() == player2_.rankings_.RankToInt())
		{
			if (player1_.rankings_.HighestCard() > player2_.rankings_.HighestCard())
			{
				if (player2_.rankings_.HighestCard().ValueToInt() == 1)
				{
					std::cout << "Player 2 wins!" << std::endl;
				}
				else
				{
					std::cout << "Player 1 wins!" << std::endl;
				}
			}
			else if (player1_.rankings_.HighestCard() < player2_.rankings_.HighestCard())
			{
				if (player1_.rankings_.HighestCard().ValueToInt() == 1)
				{
					std::cout << "Player 1 wins!" << std::endl;
				}
				else
				{
					std::cout << "Player 2 wins!" << std::endl;
				}
			}
			else if (player1_.rankings_.HighestCard() == player2_.rankings_.HighestCard())
			{
				std::cout << "It's a tie!" << std::endl;
			}
		}

		deck_.ClearDeck();
		player1_.ClearHand();
		player1_.rankings_.NewGame();
		player2_.ClearHand();
		player2_.rankings_.NewGame();
		dealer_.ClearBoard();

		std::cout << std::endl;

		game_end = true;
	}
	while (!game_end);
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
