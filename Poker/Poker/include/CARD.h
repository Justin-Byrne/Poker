#ifndef _CARD_H
#define _CARD_H

class CARD
{
private:
	int m_card_number;
	int m_rank_value;
	int m_suite_value;
	const wchar_t* m_suite;
	const wchar_t* m_rank;
	bool m_dealt;
	bool m_shuffled;

public:
	CARD(const int& number, const int& rank, const int& suite);
	CARD();
	~CARD();

	void shuffled();
	void dealt();

	bool is_dealt();
	bool is_shuffled();

	int get_rank_value();
	const wchar_t* get_rank();
	const wchar_t* get_suite();
};

#endif // !_CARD_H