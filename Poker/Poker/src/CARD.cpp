#include <pch.h>
#include "../include/CARD.h"

/// <summary>
/// An array of literals for each CARD's suite
/// </summary>
const wchar_t* suites[] =
{
	L"\x2666",          // Diamond
	L"\x2665",          // Heart
	L"\x2660",          // Spade
	L"\x2663"           // Club
};

/// <summary>
/// An array of character literals for each CARD's rank
/// </summary>
const wchar_t* ranks[] = {
	L"\x2500", L"A", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K", L"A"
};

/// <summary>
/// CARD constructor
/// </summary>
/// <param name="number">The unique numeric iterative value of each new CARD</param>
/// <param name="rank">The ranking numeric value of the CARD; 2 - 14</param>
/// <param name="suite">The numeric value of the suite; 0 - Diamond, 1 - Heart, 2 - Spade, 3 - Club</param>
CARD::CARD(const int& number, const int& rank, const int& suite) :
	m_card_number(number), m_rank_value(rank), m_suite_value(suite), m_suite(suites[suite]), m_rank(ranks[rank]), m_dealt(false), m_shuffled(false)
{ }

/// <summary>
/// Default CARD Constructor
/// </summary>
CARD::CARD() {};

/// <summary>
/// CARD de-constructor
/// </summary>
CARD::~CARD() { };

/// <summary>
/// Sets associated CARD as shuffled
/// </summary>
void CARD::shuffled()
{
	this->m_shuffled = true;                            /*!< @note: Set CARD shuffled as TRUE */
}

/// <summary>
/// Sets associated CARD as dealt
/// </summary>
void CARD::dealt()
{
	this->m_dealt = true;                               /*!< @note: Set CARD dealt as TRUE */
}

/// <summary>
/// Returns whether this CARD is dealt
/// </summary>
/// <returns>True|False</returns>
bool CARD::is_dealt()
{
	return this->m_dealt;                               /*!< @note: Determine whether this card is dealt */
}

/// <summary>
///	Returns whether CARD is shuffled
/// </summary>
/// <returns>True|False</returns>
bool CARD::is_shuffled()
{
	return this->m_shuffled;                            /*!< @note: Determine whether this card is shuffled */
}

/// <summary>
/// Returns this CARD's character value for its rank
/// </summary>
/// <returns>Char literal</returns>
const wchar_t* CARD::get_rank()
{
	return this->m_rank;
}

/// <summary>
/// Returns this CARD's rank as a value
/// </summary>
/// <returns>INT</returns>
int CARD::get_rank_value()
{
	return this->m_rank_value;
}

/// <summary>
/// Returns this CARD's character value for its suite
/// </summary>
/// <returns>Char literal</returns>
const wchar_t* CARD::get_suite()
{
	return this->m_suite;                               /*!< @note: Returning cards suite's symbol */
}

std::vector<CARD> DECK;
