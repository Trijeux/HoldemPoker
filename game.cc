#include "game.h"

#include <iostream>


void Game::WhoWinner()
{
	if (player1_.rankings_.RankToInt() > player2_.rankings_.RankToInt())
	{
		std::cout << "Player 1 wins round!" << std::endl;
		player1_.bank_ += 50;
		player2_.bank_ -= 50;
	}
	else if (player1_.rankings_.RankToInt() < player2_.rankings_.RankToInt())
	{
		std::cout << "Player 2 wins round!" << std::endl;
		player1_.bank_ -= 50;
		player2_.bank_ += 50;
	}
	else if (player1_.rankings_.RankToInt() == player2_.rankings_.RankToInt())
	{
		if (player1_.rankings_.HighestCard() > player2_.rankings_.HighestCard())
		{
			if (player2_.rankings_.HighestCard().ValueToInt() == 1)
			{
				std::cout << "Player 2 wins round!" << std::endl;
				player1_.bank_ -= 50;
				player2_.bank_ += 50;
			}
			else
			{
				std::cout << "Player 1 wins round!" << std::endl;
				player1_.bank_ += 50;
				player2_.bank_ -= 50;
			}
		}
		else if (player1_.rankings_.HighestCard() < player2_.rankings_.HighestCard())
		{
			if (player1_.rankings_.HighestCard().ValueToInt() == 1)
			{
				std::cout << "Player 1 wins round!" << std::endl;
				player1_.bank_ += 50;
				player2_.bank_ -= 50;
			}
			else
			{
				std::cout << "Player 2 wins round!" << std::endl;
				player1_.bank_ -= 50;
				player2_.bank_ += 50;
			}
		}
		else if (player1_.rankings_.HighestCard() == player2_.rankings_.HighestCard())
		{
			std::cout << "It's a tie!" << std::endl;
		}
	}
}

void Game::NewGame()
{
	deck_.ClearDeck();
	player1_.ClearHand();
	player1_.rankings_.NewGame();
	player2_.ClearHand();
	player2_.rankings_.NewGame();
	dealer_.ClearBoard();
	deck_.MakeDeck();
	deck_.ShuffleDeck();
}

void Game::DisplayRankPlayer()
{
	std::cout << "Player 1's rank: " << std::endl;
	player1_.rankings_.RankToString();
	std::cout << "Player 2's rank: " << std::endl;
	player2_.rankings_.RankToString();
}

void Game::CheckHand()
{
	player1_.rankings_.CheckRank(player1_.Hand(), dealer_.Board());
	player2_.rankings_.CheckRank(player2_.Hand(), dealer_.Board());
}

void Game::CheckBankEmpty(bool& game_end)
{
	if (player1_.Bank() <= 0 || player2_.Bank() <= 0)
	{
		if (player2_.Bank() <= 0)
		{
			std::cout  << "Player 1 Wins All!" << std::endl;
		}
		else
		{
			std::cout  << "Player 2 Wins All!" << std::endl;
		}
		game_end = true;
	}
}

void Game::GameLoop()
{
	bool game_end = false;

	do
	{
		NewGame();

		CardDeal();

		DrawGame();
		Flop();

		DrawGame();
		Turn();

		DrawGame();
		River();

		DrawGame();
		
		std::cout << std::endl << std::endl << std::endl;

		CheckHand();

		DisplayRankPlayer();

		std::cout << std::endl;

		WhoWinner();

		std::cout << std::endl;

		CheckBankEmpty(game_end);
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
	std::cout << "Player 1 : " << std::endl;
	std::cout << "Bank : " << player1_.Bank() << std::endl << std::endl;
	std::cout << "Hand :" << std::endl;
	player1_.ShowHand();
	std::cout << std::endl;
	std::cout << "Player 2 : " << std::endl;
	std::cout << "Bank : " << player2_.Bank() << std::endl << std::endl;
	std::cout << "Hand :" << std::endl;
	player2_.ShowHand();
	std::cout << std::endl << "Board :" << std::endl;
	dealer_.ShowBoard();
	std::cout << std::endl;
}
