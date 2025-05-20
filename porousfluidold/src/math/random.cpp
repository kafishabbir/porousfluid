#include "mathrandom.h"

void math::Random::seed()
{
	srand(std::time(nullptr));
}

int math::Random::integer()
{
	return rand();
}

int math::Random::integer(const int max)
{
	return integer() % max;
}

int math::Random::integer(const int min, const int max)
{
	return integer(max - min) + min;
}

double math::Random::fraction(const double decimal_shift)
{
	double ans = 0;
	double divider = 1;
	for(int i = 0; i < 3; ++ i)
	{
		ans += integer(1, 10) / divider;
		divider *= 10;
	}

	if(integer(2))
	{
		ans *= -1;
	}

	return ans / decimal_shift;
}
