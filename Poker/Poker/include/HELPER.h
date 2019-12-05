#ifndef _HELPER_H
#define _HELPER_H

std::string convert_2_currency(int value);

template <class T>
int number_of_digits(T number)
{
	int digits = 0;

	if (number < 0) digits = 1; // remove this line if '-' counts as a digit

	while (number)
	{
		number /= 10;
		digits++;
	}

	return digits;
}

#endif // !_HELPER_H