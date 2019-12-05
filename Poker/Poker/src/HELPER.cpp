#include <pch.h>
#include "../include/HELPER.h"

std::string convert_2_currency(int value)
{
	std::string currency_string = std::to_string(value);

	int length = currency_string.length();

	if (length > 3)
	{
		int cycle_amount = length / 3;
		int pos = length - 3;
		int offset = 0;
		int count = 0;

		while (count < cycle_amount)
		{
			currency_string.insert(pos + offset, ",");

			if (length % 3 == 0) count++;

			offset -= 3;
			count++;
		}
	}

	currency_string.insert(0, "$");

	return currency_string;
}
