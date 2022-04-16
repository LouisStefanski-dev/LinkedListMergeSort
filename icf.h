#pragma once
#include <string>
#include <iostream>

namespace icf //in-class functions
{
	void clearScreen();
	int stringToInt(std::string str);
	void toLowerCase(std::string& input);
	bool isAlpha(std::string var);

	template<typename K>
	bool checkType(K original, std::string comp);
	template<typename K>
	bool checkType(K original, int comp);
	template<typename K>
	void getInput(K& returnVal, std::string prompt);


	bool yorn(std::string prompt);
	int length(int val);
	int length(std::string val);

	std::string substr(std::string val, int startIndex, int length);
}


template<typename K>
inline bool icf::checkType(K original, std::string comp)
{
	for (int i = 0; i < original.length(); i++)
	{
		if (original.at(i) < 65) { return false; };
	}
	return true;
}

template<typename K>
inline bool icf::checkType(K original, int comp)
{
	for (int i = 0; i < original.length(); i++)
	{
		if (original.at(i) >= 48 && original.at(i) <= 57) { return true; };
	}
	return false;
}

template<typename K>
inline void icf::getInput(K& returnVal, std::string prompt)
{
	K tempVal;
	while (true)
	{
		std::cout << prompt;
		if (std::cin >> tempVal)
		{
			returnVal = tempVal;
			break;
		}
		else
		{
			std::cout << "Enter a valid entry relating to prompt.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			icf::clearScreen();
		}
	}
}

