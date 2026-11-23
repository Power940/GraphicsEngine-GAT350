#pragma once
#include <string>
#include <iostream>

template<typename T, typename... Args>
inline void MultiPrint(std::string d, T f, Args... rest)
{
	constexpr std::size_t restSize = sizeof...(rest);

	if constexpr (restSize > 0)
	{
		std::cout << f << d;
		MultiPrintln(d, std::forward<Args>(rest)...);
	}
	else if constexpr (restSize == 0)
	{
		std::cout << f;
	}
}

template<typename T, typename... Args>
inline void MultiPrintln(std::string d, T f, Args... rest)
{
	constexpr std::size_t restSize = sizeof...(rest);

	if constexpr (restSize > 0)
	{
		std::cout << f << d;
		MultiPrintln(d, std::forward<Args>(rest)...);
	}
	else if constexpr (restSize == 0)
	{
		std::cout << f << std::endl;
	}
}