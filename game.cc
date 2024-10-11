#include "game.h"

#include <iostream>


Game::Game()
{
	std::cout << "What your name player one : ";
	std::cin >> player1_.name_;
	std::cout << "Your name is : " << player1_.name_ << std::endl << std::endl;

	system("pause");

	system("cls");

	std::cout << "What your name player Tow : ";
	std::cin >> player2_.name_;
	std::cout << "Your name is : " << player2_.name_ << std::endl << std::endl;

	system("pause");

	system("cls");
}

void Game::WhoWinner()
{
	if (player1_.rankings_.RankToInt() > player2_.rankings_.RankToInt())
	{
		std::cout << player1_.name_ << " wins round!" << std::endl;
	}
	else if (player1_.rankings_.RankToInt() < player2_.rankings_.RankToInt())
	{
		std::cout << player2_.name_ << " wins round!" << std::endl;
	}
	else if (player1_.rankings_.RankToInt() == player2_.rankings_.RankToInt())
	{
		if (player1_.rankings_.HighestCard() > player2_.rankings_.HighestCard())
		{
			if (player2_.rankings_.HighestCard().ValueToInt() == 1)
			{
				std::cout << player2_.name_ << " wins round!" << std::endl;
			}
			else
			{
				std::cout << player1_.name_ << " wins round!" << std::endl;
			}
		}
		else if (player1_.rankings_.HighestCard() < player2_.rankings_.HighestCard())
		{
			if (player1_.rankings_.HighestCard().ValueToInt() == 1)
			{
				std::cout << player1_.name_ << " wins round!" << std::endl;
			}
			else
			{
				std::cout << player2_.name_ << " wins round!" << std::endl;
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
	std::cout << player1_.name_ << " rank: " << std::endl;
	player1_.rankings_.RankToString();
	std::cout << player2_.name_ << " rank: " << std::endl;
	player2_.rankings_.RankToString();
}

void Game::CheckHand()
{
	player1_.rankings_.CheckRank(player1_.Hand(), dealer_.Board());
	std::cout << std::endl;
	player2_.rankings_.CheckRank(player2_.Hand(), dealer_.Board());
}

void Game::CheckBankEmpty(bool& game_end)
{
	if (player1_.bank_ <= 0 || player2_.bank_ <= 0)
	{
		if (player2_.bank_ <= 0)
		{
			std::cout << player1_.name_ << " Wins All!" << std::endl;
		}
		else
		{
			std::cout << player2_.name_ << " Wins All!" << std::endl;
		}
		game_end = true;
	}
}

void Game::GameLoop()
{
	bool game_end = false;

	do
	{
		bool flag_fold = false;
		bool flag_all_in = false;
		bool flag_fold_player_one = false;
		bool flag_fold_player_tow = false;

		NewGame();

		CardDeal();

		BetTurn(flag_fold_player_one, flag_fold_player_tow, flag_fold, flag_all_in);

		if (!flag_fold)
		{
			Flop();
			if (!flag_all_in)
			{
				system("cls");
				DisplayTable();
				system("pause");
				system("cls");

				BetTurn(flag_fold_player_one, flag_fold_player_tow, flag_fold, flag_all_in);
			}

			if (!flag_fold)
			{
				Turn();
				if (!flag_all_in)
				{
					system("cls");
					DisplayTable();
					system("pause");
					system("cls");

					BetTurn(flag_fold_player_one, flag_fold_player_tow, flag_fold, flag_all_in);
				}

				if (!flag_fold)
				{
					River();
					if (!flag_all_in)
					{
						system("cls");
						DisplayTable();
						system("pause");
						system("cls");

						BetTurn(flag_fold_player_one, flag_fold_player_tow, flag_fold, flag_all_in);
					}


					if (!flag_fold)
					{

						CheckHand();

						system("cls");

						DisplayPlayer1();
						DisplayPlayer2();
						DisplayTable();

						DisplayRankPlayer();

						std::cout << std::endl;

						WhoWinner();
					}
				}
			}
		}

		std::cout << std::endl;


		if (flag_fold_player_one)
		{
			system("cls");
			std::cout << player1_.name_ << " folds!" << std::endl;
			std::cout << player2_.name_ << " win!" << std::endl;
			player2_.bank_ += pot_;
		}

		if (flag_fold_player_tow)
		{
			system("cls");
			std::cout << player2_.name_ << " folds!" << std::endl;
			std::cout << player1_.name_ << " win!" << std::endl;
			player1_.bank_ += pot_;
		}

		CheckBankEmpty(game_end);

		system("pause");
	} while (!game_end);
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

void Game::DisplayPlayer1()
{
	std::cout << player1_.name_ << " : " << std::endl;
	std::cout << "Bank : " << player1_.bank_ << std::endl << std::endl;
	std::cout << "Hand :" << std::endl;
	player1_.ShowHand();
	std::cout << std::endl;
}

void Game::DisplayPlayer2()
{
	std::cout << player2_.name_ << " : " << std::endl;
	std::cout << "Bank : " << player2_.bank_ << std::endl << std::endl;
	std::cout << "Hand :" << std::endl;
	player2_.ShowHand();
	std::cout << std::endl;
}

void Game::DisplayTable()
{
	std::cout << "Pot : "  << pot_ << std::endl << std::endl;

	std::cout << "Board :" << std::endl;
	dealer_.ShowBoard();
	std::cout << std::endl;
}

void Game::BetTurn(bool& flag_fold_player_one, bool& flag_fold_player_tow, bool& flag_fold, bool& flag_all_in)
{
	do
	{
		system("cls");
		std::cout << "Turn " << player1_.name_ << std::endl;
		system("pause");
		system("cls");

		DisplayPlayer1();

		std::string choice_player_one;
		std::string choice_player_tow;
		std::string bet_player_one;
		std::string bet_player_tow;

		if (player2_.bet_ <= 0)
		{
			std::cout << player1_.name_ << " what do you want to do : " << std::endl << "(1) Check" << std::endl << "(2) Bet" << std::endl << "(3) All in" << std::endl << "(4) Fold" << std::endl;
		}
		else
		{
			std::cout << player1_.name_ << " what do you want to do : " << std::endl << "(1) Call" << std::endl << "(2) All in" << std::endl << "(3) Fold" << std::endl;
		}

		std::cin >> choice_player_one;

		if (choice_player_one == "1")
		{
			if (player2_.bank_ < player1_.bet_)
			{
				player1_.bet_ = player1_.bank_;
				player1_.bank_ -= player1_.bet_;
			}
			else if (player2_.bet_ > 0)
			{
				player1_.bet_ = player2_.bet_;
				player1_.bank_ -= player1_.bet_;
				continue;
			}


		}
		else if (choice_player_one == "2")
		{
			if (player2_.bet_ > 0)
			{
				player1_.bet_ = player1_.bank_;
				player1_.bank_ -= player1_.bet_;
				flag_all_in = true;
			}
			else
			{
				system("cls");
				while (true)
				{
					std::cout << "What your bet : " << std::endl << "(1) " << kBetOne << std::endl << "(2) " << kBetTow << std::endl << "(3) " << kBetThree << std::endl << "(4) " << kBetFour << std::endl;
					std::cin >> bet_player_one;
					if (bet_player_one == "1")
					{
						player1_.bet_ = kBetOne;
						player1_.bank_ -= player1_.bet_;
						break;
					}
					if (bet_player_one == "2")
					{
						player1_.bet_ = kBetTow;
						player1_.bank_ -= player1_.bet_;
						break;
					}
					if (bet_player_one == "3")
					{
						player1_.bet_ = kBetThree;
						player1_.bank_ -= player1_.bet_;
						break;
					}
					if (bet_player_one == "4")
					{
						player1_.bet_ = kBetFour;
						player1_.bank_ -= player1_.bet_;
						break;
					}
					system("cls");
					std::cout << "Invalid input" << std::endl;
				}
			}
		}
		else if (choice_player_one == "3")
		{
			if (player2_.bet_ > 0)
			{
				flag_fold_player_one = true;
				flag_fold = true;
				break;
			}
			player1_.bet_ = player1_.bank_;
			player1_.bank_ -= player1_.bet_;
			flag_all_in = true;
		}
		else if (choice_player_one == "4")
		{
			if (player2_.bet_ > 0)
			{
				system("cls");
				std::cout << "Invalid input" << std::endl;
				continue;
			}
			flag_fold_player_one = true;
			flag_fold = true;
			break;
		}
		else
		{
			system("cls");
			std::cout << "Invalid input" << std::endl;
			continue;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////// Player 2 Turn //////////////////////////////////////////////////////////////////////////////////////
		system("cls");
		std::cout << "Turn " << player2_.name_ << std::endl;
		system("pause");
		system("cls");

		DisplayPlayer2();

		if (player1_.bet_ <= 0)
		{
			std::cout << player2_.name_ << " what do you want to do : " << std::endl << "(1) Check" << std::endl << "(2) Bet" << std::endl << "(3) All in" << std::endl << "(4) Fold" << std::endl;
		}
		else
		{
			std::cout << player2_.name_ << " what do you want to do : " << std::endl << "(1) Call" << std::endl << "(2) All in" << std::endl << "(3) Fold" << std::endl;
		}

		std::cin >> choice_player_tow;

		if (choice_player_tow == "1")
		{
			if (player1_.bet_ > 0)
			{
				if (player1_.bank_ < player2_.bet_)
				{
					player2_.bet_ = player2_.bank_;
					player2_.bank_ -= player2_.bet_;
				}
				else
				{
					player2_.bet_ = player1_.bet_;
					player2_.bank_ -= player2_.bet_;
				}
			}
		}
		else if (choice_player_tow == "2")
		{
			if (player1_.bet_ > 0)
			{
				player2_.bet_ = player2_.bank_;
				player2_.bank_ -= player2_.bet_;
				flag_all_in = true;
			}
			else 
			{
				system("cls");
				while (true)
				{
					std::cout << "What your bet : " << std::endl << "(1) " << kBetOne << std::endl << "(2) " << kBetTow << std::endl << "(3) " << kBetThree << std::endl << "(4) " << kBetFour << std::endl;
					std::cin >> bet_player_tow;
					if (bet_player_tow == "1")
					{
						player2_.bet_ = kBetOne;
						player2_.bank_ -= player2_.bet_;
						break;
					}
					if (bet_player_tow == "2")
					{
						player2_.bet_ = kBetTow;
						player2_.bank_ -= player2_.bet_;
						break;
					}
					if (bet_player_tow == "3")
					{
						player2_.bet_ = kBetThree;
						player2_.bank_ -= player2_.bet_;
						break;
					}
					if (bet_player_tow == "4")
					{
						player2_.bet_ = kBetFour;
						player2_.bank_ -= player2_.bet_;
						break;
					}
					system("cls");
					std::cout << "Invalid input" << std::endl;
				}
			}
		}
		else if (choice_player_tow == "3")
		{
			if (player1_.bet_ > 0)
			{
				flag_fold_player_tow = true;
				flag_fold = true;
				break;
			}
			player2_.bet_ = player2_.bank_;
			player2_.bank_ -= player2_.bet_;
			flag_all_in = true;
		}
		else if (choice_player_tow == "4")
		{
			if (player1_.bet_ > 0)
			{
				system("cls");
				std::cout << "Invalid input" << std::endl;
				continue;
			}
			flag_fold_player_one = true;
			flag_fold = true;
			break;
		}
		else
		{
			system("cls");
			std::cout << "Invalid input" << std::endl;
			continue;
		}

		if (player1_.bank_ == 0)
		{
			break;
		}
	} while (player1_.bet_ != player2_.bet_);
	pot_ += player1_.bet_ + player2_.bet_;
	player1_.bet_ = 0;
	player2_.bet_ = 0;
}
