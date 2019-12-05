#include <pch.h>
#include "../include/CARD.h"
#include "../include/COMMUNITY.h"

const char* COMMUNITY::m_classname = "COMMUNITY";

extern std::vector<CARD> DECK;

/// <summary>
/// COMMUNITY constructor
/// </summary>
/// <param name="count">Amount of COMMUNITY cards to generate</param>
COMMUNITY::COMMUNITY(int& count)
{
	for (int i = 0; i < 3; i++)
	{
		count++;                                        // Burn one card first pass
		this->CARD_POOL.push_back(DECK[count]);
	}

	for (int i = 0; i < 2; i++)
	{
		count = count + 2;                              // Burn one each pass
		this->CARD_POOL.push_back(DECK[count]);
	}
};

/// <summary>
/// Returns the name of this class
/// </summary>
/// <returns>char*</returns>
const char* COMMUNITY::get_classname()
{
	return this->m_classname;
}

/// <summary>
/// Returns a CARD from the avaliable card pool of this COMMUNITY
/// </summary>
/// <param name="card_number">Numeric value of the CARD to return</param>
/// <returns>CARD object</returns>
CARD COMMUNITY::get_card(const int& card_number)
{
	return this->CARD_POOL[card_number];
}

/// <summary>
/// Returns the actual pool of CARDs for this COMMUNITY
/// </summary>
/// <returns>vector of CARD</returns>
std::vector<CARD> COMMUNITY::get_card_pool()
{
	return this->CARD_POOL;
}

/// <summary>
/// Return the amount of available CARDs within this COMMUNITY
/// </summary>
/// <returns>INT</returns>
int COMMUNITY::card_pool_max()
{
	return CARD_POOL.size();
}
