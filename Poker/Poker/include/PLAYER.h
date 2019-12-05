#include "CARD.h"

#ifndef _PLAYER_H
#define _PLAYER_H

class PLAYER
{
private:
	static const char* m_classname;
	static int m_class_iterator;
	int m_player_number;
	bool m_playable = false;                            /*<! Player = true, Opponent = false */
	int chip_stack;

	std::vector<CARD> CARD_POOL;

public:
	PLAYER(const int& no_of_opponents);
	~PLAYER();

	void set_playable();
	void take_card(const CARD& card);

	const char* get_classname();
	int player_number();
	bool is_playable();
	int get_chip_stack();

	CARD get_card(const int& card_number);
	std::vector<CARD> get_card_pool();

	int card_pool_amount();
};

#endif // !_PLAYER_H
