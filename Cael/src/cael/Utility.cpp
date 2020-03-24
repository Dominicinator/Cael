#include "Utility.h"

Cael::Utility::RandomFloat::RandomFloat(const float & a, const float & b) :
	lower(a), upper(b)
{
	std::random_device randomDevice;
	generator = std::mt19937(randomDevice());
	distribution = std::uniform_real_distribution<float>(lower, upper);
}

Cael::Utility::RandomFloat::~RandomFloat() {}

float Cael::Utility::RandomFloat::next()
{
	return distribution(generator);
}

Cael::Utility::RandomDouble::RandomDouble(const double & a, const double & b) :
	lower(a), upper(b)
{
	std::random_device randomDevice;
	generator = std::mt19937(randomDevice());
	distribution = std::uniform_real_distribution<double>(lower, upper);
}

Cael::Utility::RandomDouble::~RandomDouble() {}

double Cael::Utility::RandomDouble::next()
{
	return distribution(generator);
}