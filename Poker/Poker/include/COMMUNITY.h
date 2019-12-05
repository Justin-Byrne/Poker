#ifndef _COMMUNITY_H
#define _COMMUNITY_H

struct COMMUNITY
{
	static const char* m_classname;
	std::vector<CARD> CARD_POOL;

	COMMUNITY(int& count);

	const char* get_classname();
	CARD get_card(const int& card_number);
	std::vector<CARD> get_card_pool();
	int card_pool_max();

	void print_card_pool();
};

#endif // !_COMMUNITY_H
