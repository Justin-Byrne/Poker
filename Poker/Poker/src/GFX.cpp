#include <pch.h>
#include "../include/GFX.h"

extern int cards_per_player;
extern int number_of_opponents;

/// <summary>
/// Vector containing literal string values for the back of each card
/// </summary>
std::vector<const wchar_t*> GFX::tmpl_card_back =
{
	L"┌─────────┐",     // 0
	L"│░░░░░░░░░│",     // 1
	L"│░░░░░░░░░│",     // 2
	L"│░░░░░░░░░│",     // 3
	L"│░░░░░░░░░│",     // 4
	L"│░░░░░░░░░│",     // 5
	L"│░░░░░░░░░│",     // 6
	L"│░░░░░░░░░│",     // 7
	L"└─────────┘"      // 8
};

/// <summary>
/// Vector containing literal string values for the face of each card
/// </summary>
std::vector<const wchar_t*> GFX::tmpl_card_face =
{
	L"┌─────────┐",     // 0
	L"│r        │",     // 1
	L"│         │",     // 2
	L"│         │",     // 3
	L"│    s    │",     // 4
	L"│         │",     // 5
	L"│         │",     // 6
	L"│        r│",     // 7
	L"└─────────┘"      // 8
};

/// <summary>
/// Vector containing each line for the title screen
/// </summary>
std::vector<std::string> GFX::poker_fun =
{
	"    _/_/_/              _/                         ",
	"   _/    _/    _/_/    _/  _/      _/_/    _/  _/_/",
	"  _/_/_/    _/    _/  _/_/      _/_/_/_/  _/_/     ",
	" _/        _/    _/  _/  _/    _/        _/        ",
	"_/          _/_/    _/    _/    _/_/_/  _/         ",
	"    _/_/_/_/                                       ",
	"   _/        _/    _/  _/_/_/                      ",
	"  _/_/_/    _/    _/  _/    _/                     ",
	" _/        _/    _/  _/    _/                      ",
	"_/          _/_/_/  _/    _/                       "
};

/// <summary>
/// Vector containing each line for the game over screen
/// </summary>
std::vector<std::string> GFX::game_over =
{
	"    _/_/_/",
	"  _/          _/_/_/  _/_/_/  _/_/      _/_/       ",
	" _/  _/_/  _/    _/  _/    _/    _/  _/_/_/_/      ",
	"_/    _/  _/    _/  _/    _/    _/  _/             ",
	" _/_/_/    _/_/_/  _/    _/    _/    _/_/_/        ",
	"     _/_/                                          ",
	"  _/    _/  _/      _/    _/_/    _/  _/_/         ",
	" _/    _/  _/      _/  _/_/_/_/  _/_/              ",
	"_/    _/    _/  _/    _/        _/                 ",
	" _/_/        _/        _/_/_/  _/                  "
};

/// <summary>
/// Vector containing literal string values for poker chips
/// </summary>
std::vector<std::wstring> GFX::chip =
{
	L"┌─────────┐\t",     // 0
	L"└─────────┘\t"      // 1
};

/// <summary>
/// Vector continaing literal strings for community area
/// </summary>
std::vector<std::wstring> GFX::community_area =
{
	L"┌─────────────────────────────────────────────────────┐",
	L"│                                                     │",
	L"│                                                     │",
	L"│                                                     │",
	L"│                                                     │",
	L"│                                                     │",
	L"│                                                     │",
	L"│                                                     │",
	L"└─────────────────────────────────────────────────────┘"
};

/// <summary>
/// Prints out a string of characters
/// </summary>
/// <param name="string"></param>
void GFX::print(const char* string)
{
	std::cout << string;
}

/// <summary>
/// Prints a string of wide characters
/// </summary>
/// <param name="wstring"></param>
void GFX::print(const wchar_t* wstring)
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	std::wcout << wstring;

	_setmode(_fileno(stdout), _O_TEXT);
}

/// <summary>
/// Prints vector with character strings
/// </summary>
/// <param name="wstring">Vector with character strings</param>
void GFX::display(std::vector<std::string> string)
{
	for (int i = 0; i < string.size(); i++)
		std::cout << string[i] << std::endl;
}

/// <summary>
/// Prints vector with wide character strings
/// </summary>
/// <param name="wstring">Vector with wide character strings</param>
void GFX::display(std::vector<std::wstring> wstring)
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < wstring.size(); i++)
		std::wcout << wstring[i] << std::endl;

	_setmode(_fileno(stdout), _O_TEXT);
}

/// <summary>
/// Display graphics in center of screen
/// </summary>
/// <param name="string">Vector of strings</param>
void GFX::display_centered(std::vector<std::string> string)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int num_cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//int num_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	virtual_border(string, num_cols);

	// OUTPUT
	for (int i = 0; i < string.size(); ++i)
	{
		center_output(string[i], num_cols);
		std::cout << std::endl;
	}

	virtual_border(string, num_cols);
}

/// <summary>
/// Display graphics in center of screen
/// </summary>
/// <param name="string">String message</param>
void GFX::display_centered(std::string string)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int num_cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//int num_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	virtual_border(string, num_cols);

	// OUTPUT
	center_output(string, num_cols);

	virtual_border(string, num_cols);
}

/// <summary>
/// Retrieves card vector containing each player/opponent card passed through
/// </summary>
/// <param name="player_cards">Array of player/opponent cards</param>
/// <param name="amount">Total amount of cards</param>
/// <returns>vector^string^</returns>
std::vector<std::vector<std::wstring>> GFX::get_card_vector(CARD player_cards[], const int& amount)
{
	// Create vector to hold CARD(s) for display; only
	std::vector<std::vector<std::wstring>> cards(amount);

	for (int i = 0; i < amount; i++)
		for (int j = 0; j < tmpl_card_face.size(); j++)
			cards[i].push_back(tmpl_card_face[j]);

	// Set ranking symbol
	for (int i = 0; i < amount; i++)
	{
		switch (player_cards[i].get_rank_value())
		{
		case 10:
			cards[i][1].replace(1, 2, player_cards[i].get_rank());
			cards[i][7].replace(8, 2, player_cards[i].get_rank());
			break;
		default:
			cards[i][1].replace(1, 1, player_cards[i].get_rank());
			cards[i][7].replace(9, 1, player_cards[i].get_rank());
			break;
		}
	}

	// Set suite
	for (int i = 0; i < amount; i++)
		cards[i][4].replace(5, 1, player_cards[i].get_suite());

	return cards;
}

/// <summary>
/// Print card face up
/// </summary>
/// <param name="players">PLAYER object</param>
/// <param name="player">True|False</param>
void GFX::display_card_face_up(std::vector<PLAYER>& players, bool player)
{
	if (!player)        // Opponent(s)
	{
		// Locally store opponent's cards to better fetch data
		CARD* card = new CARD[number_of_opponents * cards_per_player];

		int card_no = 0;

		// Set card with each opponent's CARD
		for (int i = 0; i < number_of_opponents; i++)
		{
			for (int j = 0; j < cards_per_player; j++)
			{
				card[card_no] = players[i].get_card(j);
				card_no++;
			}
		}

		// Get card vector containing all opponent's CARDs
		std::vector<std::vector<std::wstring>> cards = get_card_vector(card, number_of_opponents * cards_per_player);

		// Display cards
		_setmode(_fileno(stdout), _O_U16TEXT);

		for (int i = 0; i < tmpl_card_face.size(); i++)
		{
			for (int j = 0; j < number_of_opponents * cards_per_player; j++)
			{
				std::wcout << cards[j][i];

				if (j == cards.size() - 1)
					std::wcout << std::endl;

				if ((j + 1) % cards_per_player == 0 && j != cards.size() - 1)
					std::wcout << L'\t';
			}
		}

		_setmode(_fileno(stdout), _O_TEXT);

		// Cleanup
		delete[] card;
	}
	else                // Player
	{
		// Locally store player's cards to better fetch data
		CARD* card = new CARD[cards_per_player];

		// Set card with each player's CARD
		for (int i = 0; i < cards_per_player; i++)
			card[i] = players[players.size() - 1].get_card(i);

		// Get card vector containing all player's CARDs
		std::vector<std::vector<std::wstring>> cards = get_card_vector(card, cards_per_player);

		// Display cards
		_setmode(_fileno(stdout), _O_U16TEXT);

		for (int i = 0; i < tmpl_card_face.size(); i++)
		{
			for (int j = 0; j < cards_per_player; j++)
			{
				std::wcout << cards[j][i];

				if (j == cards.size() - 1)
					std::wcout << std::endl;
			}
		}

		_setmode(_fileno(stdout), _O_TEXT);

		// Cleanup
		delete[] card;
	}
}

/// <summary>
/// Prints opponents cards face down
/// </summary>
void GFX::display_card_face_down()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < number_of_opponents; i++)       // CARD TOP
	{
		for (int j = 0; j < cards_per_player; j++)
			print(tmpl_card_back[0]);

		(i == number_of_opponents - 1) ? print(L"\n") : print(L"\t");
	}

	for (int i = 1; i < 8; i++)                         // CARD PADDING
	{
		for (int j = 0; j < number_of_opponents; j++)
		{
			for (int k = 0; k < cards_per_player; k++)
				print(tmpl_card_back[i]);

			(j == number_of_opponents - 1) ? print(L"\n") : print(L"\t");
		}
	}

	for (int i = 0; i < number_of_opponents; i++)       // CARD BOTTOM
	{
		for (int j = 0; j < cards_per_player; j++)
			print(tmpl_card_back[tmpl_card_back.size() - 1]);

		(i == number_of_opponents - 1) ? print(L"\n") : print(L"\t");
	}

	_setmode(_fileno(stdout), _O_TEXT);
}

/// <summary>
/// Display the avaliable chips and amounts onto the screen.
/// </summary>
/// <param name="amount"></param>
void GFX::display_chips()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < chip.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::wcout << chip[i];
		}

		std::wcout << std::endl;
	}

	_setmode(_fileno(stdout), _O_TEXT);
}

/// <summary>
/// Sets the console window size while centering within the primary screen
/// </summary>
/// <param name="width">Width of the console window</param>
/// <param name="height">Height of the console window</param>
/// <returns>True|False</returns>
bool GFX::set_window_size(const int& width, const int& height)
{
	RECT screen;
	COORD pos;

	const HWND h_desktop = GetDesktopWindow();
	const HWND h_console = GetConsoleWindow();

	GetWindowRect(h_desktop, &screen);

	pos.X = (screen.right - width) / 2;
	pos.Y = (screen.bottom - height) / 2;

	if (h_console != NULL)
		MoveWindow(h_console, pos.X, pos.Y, width, height, true);

	SetForegroundWindow(h_console);

	return 0;
}
