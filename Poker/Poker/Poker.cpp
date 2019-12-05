/**
 * @package:   Poker
 * @version:   0.3.0 12/05/2019
 * @file:      Poker.cpp
 * @brief:     Basic Poker Game in C++
 * @author:    Justin D. Byrne <justin@byrne-systems.com>
 * @license:   MIT License
 */

#pragma region INCLUDES

#include "PCH.h"
#include "include/CARD.h"				/* CARD */
#include "include/GFX.h"				/* GFX */
#include "include/PLAYER.h"				/* PLAYER */
#include "include/COMMUNITY.h"			/* COMMUNITY */
#include "include/HELPER.h"

#pragma endregion

#pragma region PREPROCESSOR_DIRECTIVES

 /* NOTE: Text is the default even if the given _O_TEXT bit is not on. */
#define	_O_TEXT		0x4000	/* CR-LF in file becomes LF in memory. */
#define _O_U16TEXT	0x20000

#define LOG(x)   std::cout << x << std::endl;
#define WLOG(x)  std::wcout << x << std::endl;
#define ERROR(x) std::cout << "[error] " << x << std::endl;

#pragma endregion

#pragma region GLOBAL_VARIABLE_DECLARATIONS

int cards_per_player = 2;
int number_of_opponents = NULL;
const int big_blind_amount = 50;
const unsigned int chip_base_amount = 200000;
int main_pot;
int side_pot;
int player_bet;
bool game_loop;

/// <summary>
/// Blind structure to set a specific pace for the mini tournament
/// Col 1         Col 2         Col 3
/// Small blind  |Big blind    |Time (in minutes)
/// </summary>
std::vector<std::vector<int>> blind_levels =
{
	{10, 20, 15},       // Level 1
	{20, 40, 30},       // Level 2
	{30, 60, 45},       // Level 3
	{50, 100, 60},      // Level 4
	{100, 200, 75},     // Level 5
	{150, 300, 90},     // Level 6
	{200, 400, 105},    // Level 7
	{400, 800, 120},    // Level 8
	{800, 1600, 145},   // Level 9
};

/// <summary>
/// Chip distribution percentages for chip totals with a 20,000 base amount
/// </summary>
std::vector<double> chip_distribution
{
	0.0375,             // $5
	0.05,               // $10
	0.0625,             // $25
	0.35,               // $100
	0.5                 // $500
};

/// <summary>
/// Individual denominations of chips
/// </summary>
int chip_denoms[5] =
{
	5,                  // White
	10,                 // Red
	25,                 // Green
	100,                // Blue
	500                 // Black
};

extern std::vector<CARD> DECK;
extern std::vector<PLAYER> PLAYERS;

bool UNIT_TESTING = true;

#pragma endregion

#pragma region FORWARD_DECLARATIONS

int const gen_random_number(const int& min, const int& max);
bool intro();
bool set_player_amount();
bool generate_cards();
bool shuffle();
bool deal();
bool show_table();
bool show_chips();
void bet();
void sleep(int sec);
void UNIT_TESTS(bool TEST[]);
bool exit();

#pragma endregion

/// <summary>
/// The main function of this program
/// </summary>
/// <param name="argc">Command line argument count</param>
/// <param name="argv">Command line argument vector</param>
/// <returns>Exit code</returns>
int main(int argc, const char* argv[])
{
	if (!intro())
	{
		if (!generate_cards())
		{
			if (!shuffle())
			{
				if (!deal())
				{
					do
					{
						system("CLS");                  //<! Clear screen prior to displaying cards and table

						if (!show_table())
						{
							if (!show_chips())
							{
								int mod;

								do
								{
									bet();

									mod = player_bet % 5;

									if (mod == 0)
									{
										//<! Subtract anti from chip total      -
										//<! Subtract bet chips from chip total  |
										//<! Show pot total                     -
										//<! Adjust each player's card percentages
										//<!
										//<!
										//<!
									}
									else
									{
										game_loop = false;
									}
								} while (player_bet == 0);
							}
							else
							{
								ERROR("Failed to show chips!");
							}
						}
						else
						{
							ERROR("Failed to show table!");
						}

					} while (!game_loop);
				}
				else
				{
					ERROR("Failed to deal cards!");
				}
			}
			else
			{
				ERROR("DECK failed to shuffle!");
			}
		}
		else
		{
			ERROR("DECK failed to generate!");
		}
	}
	else
	{
		ERROR("intro() did not successfully execute!");
	}

	return exit();
}

/// <summary>
/// Displays the graphical intro, and requests to set the amount of opponent players
/// </summary>
/// <returns>Will return 0 if number_of_opponents > 0</returns>
bool intro()
{
	if (!GFX::set_window_size())
		GFX::display_centered(GFX::poker_fun);
	else
		ERROR("Failed to set window size!");

	//sleep(3);

	return set_player_amount();							//<! Request (and set) numeric value for number_of_opponents
}

/// <summary>
/// Get and set a numeric value for the amount of poker players
/// </summary>
bool set_player_amount()
{
	bool result;

	do
	{
		system("CLS");

		GFX::display_centered("How many opponent players? [1-3]: ");

		int keypress = _getch();

		switch (keypress)
		{
		case 49: number_of_opponents = 1; break;
		case 50: number_of_opponents = 2; break;
		case 51: number_of_opponents = 3; break;
		default: number_of_opponents = 0; break;
		}
	} while (number_of_opponents > 3 || number_of_opponents <= 0);

	system("CLS");

	return (!number_of_opponents) ? 1 : 0;
}

/// <summary>
/// Generates all 52 cards for the entire DECK
/// </summary>
/// <returns>Exit code</returns>
bool generate_cards()
{
	int card_number = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 14; j++)
		{
			card_number++;

			DECK.push_back(CARD(card_number, j, i));    // Generate each card
		}
	}

	return (DECK.size() == 52) ? 0 : 1;
}

/// <summary>
/// Shuffles all CARDs throughout the entire DECK
/// </summary>
/// <returns>Exit code</returns>
bool shuffle()
{
	int j;

	std::srand(unsigned(time(0)));

	for (int i = DECK.size() - 1; i > 0; i--)
	{
		do {
			j = std::rand() % i;
		} while (j >= i);

		std::swap(DECK[i], DECK[j]);
		DECK[i].shuffled();
	}

	return 0;
}

/// <summary>
/// Deals all PLAYER and COMMUNITY CARDs
/// </summary>
/// <returns>True|False</returns>
bool deal()
{
	for (int i = 0; i < number_of_opponents + 1; i++)   // Create opponent(s) and player
		PLAYERS.push_back(PLAYER(number_of_opponents));

	int count = 0;      // <! Card count

	do                  // Deal cards out to opponent(s) and player
	{
		for (int i = 0; i < PLAYERS.size(); i++)
		{
			PLAYERS[i].take_card(DECK[count]);
			count++;
		}
	} while (count < cards_per_player * PLAYERS.size());

	COMMUNITY community(count);                         // Create community cards

	return 0;
}

bool show_table()
{
	GFX::display_card_face_down();
	GFX::display(GFX::community_area);
	GFX::display_card_face_up(PLAYERS, true);

	return 0;
}

/// <summary>
/// Display players avaliable chips
/// </summary>
/// <returns></returns>
bool show_chips()
{
	int chip_amounts[5];

	for (int i = 0; i < 5; i++)
		chip_amounts[i] = (chip_base_amount * chip_distribution[i]) / chip_denoms[i] / 10;

	std::cout << std::endl;

	GFX::display_chips();

	for (int i = 0; i < 5; i++)
	{
		std::cout << " " << chip_denoms[i] << "x" << chip_amounts[i] << "\t\t";
	}

	std::cout << "\n" << std::endl;

	return 0;
}

/// <summary>
/// Request the amount to be bet, and subtracts that amount from player
/// </summary>
void bet()
{
	int bet;
	double chip_total = chip_base_amount * 1.00;

	std::cout << "Your current chip total is: " << convert_2_currency(chip_total) << std::endl;

	std::cout << "Please enter in denominations of $5\n" << std::endl;

	std::cout << "How much would you like to bet? ";

	std::cin >> player_bet;
}

/// <summary>
/// Sleep delay that delays program for the amount of second passed via param
/// </summary>
/// <param name="sec">Amount of seconds to sleep for</param>
void sleep(int sec)
{
	std::this_thread::sleep_for(std::chrono::seconds(sec));
}

/// <summary>
/// Generates a random numeric value
/// </summary>
/// <param name="min">Lower bounds numeric value</param>
/// <param name="max">Upper bounds numeric value</param>
/// <returns>INT</returns>
int const gen_random_number(const int& min, const int& max)
{
	return (rand() % max) + min;
}

/// <summary>
/// Performs a series of unit tests
/// </summary>
/// <param name="TEST">Array of boolean arguments for each test case</param>
void UNIT_TESTS(bool TEST[])
{
	srand(time(NULL));  /*!< @note: Initialize random seed */

#pragma region TEST1
	if (TEST[0])
	{
		LOG("#> Testing gen_rand()");

		int i = 0;

		// srand(time(NULL));      /*!< @note: Initialize random seed */

		do
		{
			LOG("[" << i << "] " << "Random value: " << gen_random_number(1, 14));
			i++;
		} while (i < 10);

		LOG("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << "\n");
	}
#pragma endregion

#pragma region TEST2
	if (TEST[1])
	{
		LOG("#> Size of types");
		LOG("Size of char is " << sizeof(char) << " byte(s)");
		LOG("Size of int is " << sizeof(int) << " byte(s)");
		LOG("Size of float is " << sizeof(float) << " byte(s)");
		LOG("Size of short int is " << sizeof(short int) << " byte(s)");
		LOG("Size of long int is " << sizeof(long int) << " byte(s)");
		LOG("Size of double is " << sizeof(double) << " byte(s)");
		LOG("Size of wchar_t is " << sizeof(wchar_t) << " byte(s)");
	}
#pragma endregion
}

/// <summary>
/// Exiting sequence
/// </summary>
/// <returns>Exit code</returns>
bool exit()
{
	LOG("Press any key to escape!");
	std::cin.get();	                                    // pause

	return EXIT_SUCCESS;
}
