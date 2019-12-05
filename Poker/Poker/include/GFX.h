#include "../pch.h"
#include "PLAYER.h"
#include "COMMUNITY.h"

#ifndef _GFX_H
#define _GFX_H

namespace GFX
{
	extern std::vector<std::string> poker_fun;
	extern std::vector<std::string> game_over;
	extern std::vector<std::wstring> community_area;
	extern std::vector<std::wstring> chip;
	extern std::vector<const wchar_t*> tmpl_card_back;
	extern std::vector<const wchar_t*> tmpl_card_face;

	void print(const char* string);
	void print(const wchar_t* wstring);
	void display(std::vector<std::string> string);
	void display(std::vector<std::wstring> wstring);
	void display_centered(std::vector<std::string> string);
	void display_centered(std::string string);

	std::vector<std::vector<std::wstring>> get_card_vector(CARD card[], const int& amount);

	void display_card_face_up(std::vector<PLAYER>& players, bool player = false);
	void display_card_face_down();
	void display_chips();

	bool set_window_size(const int& width = 800, const int& height = 600);

	/// <summary>
	/// Centers output within the console
	/// </summary>
	/// <param name="string">String</param>
	/// <param name="num_cols">Number of columns to pad</param>
	template<typename T>
	void center_output(T string, int& num_cols)
	{
		// Calculate left padding
		int padding_left = (num_cols / 2) - (string.size() / 2);

		// Put padding spaces
		for (int i = 0; i < padding_left; ++i)
			std::cout << ' ';

		// Print string
		std::cout << string;
	}

	/// <summary>
	/// Virtual border to wrap around centered graphics
	/// </summary>
	/// <param name="string">vector^string^</param>
	/// <param name="num_cols">number of columns to space apart</param>
	template<typename T>
	void virtual_border(T string, int& num_cols)
	{
		// VIRTUAL BORDER
		std::cout << std::endl;
		for (int i = 0; i < num_cols; ++i) std::cout << ' ';
		//std::cout << ' ' << std::endl;
	}
};

#endif // !_GFX_H
