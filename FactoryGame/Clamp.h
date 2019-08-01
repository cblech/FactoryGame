#pragma once
#include <SFML/System.hpp>
//template <typename T>
//inline T clamp(T value, T min, T max);


template<typename T>
inline sf::Vector2<T> clamp(sf::Vector2<T> value, sf::Vector2<T> min, sf::Vector2<T> max)
{
	sf::Vector2<T> retVal;

	if (value.x < min.x)
		retVal.x= min.x;
	else if (value.x > max.x)
		retVal.x = max.x;
	else
		retVal.x = value.x;
	if (value.y < min.y)
		retVal.y= min.y;
	else if (value.y > max.y)
		retVal.y = max.y;
	else
		retVal.y = value.y;

	return retVal;
}

template<typename T>
inline T clamp(T value, T min, T max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}
