#pragma region TODO
#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <map>
#include <random>

#include "game.h"
#include "player.h"

void test_verif_suite()
{
	bool is_suite = false;

	int suite_count = 0;

	int verificateur = 0;

	int value = 0;

	std::array<int, 7> test{ 1, 2, 3, 4, 5, 12, 13 };

	srand(time(NULL));

	std::shuffle(test.begin(), test.end(), std::default_random_engine(rand()));

	std::multimap<int, int> test2;

	for (int idx = 0; idx < test.size(); idx++)
	{
		test2.emplace(test.at(idx), idx);
	}

	for (auto t : test2)
	{
		if (!is_suite)
		{
			verificateur = t.first;

			is_suite = true;
		}

		if (t.first == verificateur)
		{
			verificateur++;
			suite_count++;
		}
		else if (suite_count < 5)
		{
			verificateur = t.first;
			verificateur++;
			suite_count = 1;
			is_suite = false;
		}

		std::cout << t.first << " : " << "idx = " << t.second << std::endl;
	}

	if (verificateur >= 13 && suite_count >= 4)
	{
		for (auto t : test2)
		{
			if (t.first == 1)
			{
				suite_count++;
			}
		}
	}

	if (suite_count >= 5)
	{
		std::cout << "Is Suite" << std::endl;
	}
	else
	{
		std::cout << "No Suite" << std::endl;
	}
}
#pragma endregion

#include "deck.h"

int main()
{
	Game game;

	game.GameLoop();
}
