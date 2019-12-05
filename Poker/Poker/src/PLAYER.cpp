#include <pch.h>
#include "../include/PLAYER.h"

int PLAYER::m_class_iterator = 0;
const char* PLAYER::m_classname = "PLAYER";

extern int cards_per_player;

/// <summary>
/// Player constructor
/// </summary>
/// <param name="no_of_opponents">Numeric value of opponents</param>
PLAYER::PLAYER(const int& no_of_opponents)
{
	this->m_player_number = ++this->m_class_iterator;   // <! Set player number

	if (this->m_player_number > no_of_opponents)        // <! If player number maxes out, assign final player as non-opponent live player
		this->set_playable();

	// <! TODO: Add code copy community cards from COMMUNITY::CARD_POOL to PLAYER::CARD_POOL
};

/// <summary>
/// Player de-constructor
/// </summary>
PLAYER::~PLAYER()
{
	this->m_player_number--;
};

/// <summary>
/// Sets whether the current PLAYER is representative of a playable character
/// </summary>
void PLAYER::set_playable()
{
	this->m_playable = true;
}

/// <summary>
/// Return the name of this class
/// </summary>
/// <returns>char*</returns>
const char* PLAYER::get_classname()
{
	return this->m_classname;
}

/// <summary>
/// Injects a CARD into this PLAYER's card pool
/// </summary>
/// <param name="card"></param>
void PLAYER::take_card(const CARD& card)
{
	this->CARD_POOL.push_back(card);
}

/// <summary>
/// Returns the numeric value identifiying each PLAYER
/// </summary>
/// <returns>INT</returns>
int PLAYER::player_number()
{
	return this->m_player_number;
}

/// <summary>
/// Returns whether this PLAYER is a playable character
/// </summary>
/// <returns>True|False</returns>
bool PLAYER::is_playable()
{
	return this->m_playable;
}

/// <summary>
/// Returns a single CARD for this PLAYER
/// </summary>
/// <param name="card_number">Numeric value for the CARD to return</param>
/// <returns>CARD</returns>
CARD PLAYER::get_card(const int& card_number)
{
	return this->CARD_POOL[card_number];
}

/// <summary>
/// Returns the entire card pool of this PLAYER
/// </summary>
/// <returns>vector of PLAYER</returns>
std::vector<CARD> PLAYER::get_card_pool()
{
	return this->CARD_POOL;
}

/// <summary>
/// Returns the amount of CARDs within this PLAYER's card pool
/// </summary>
/// <returns></returns>
int PLAYER::card_pool_amount()
{
	return this->CARD_POOL.size();
}

std::vector<PLAYER> PLAYERS;