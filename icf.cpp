#include "icf.h"

namespace icf
{
	void icf::clearScreen()
	{
		for (int i = 0; i < 256; i++)
		{
			std::cout << "\n";
		}
	}

	int icf::stringToInt(std::string str)
	{
		int returnVal = 0;
		for (int i = 0; i < str.length(); i++)
		{
			returnVal = returnVal * 10 + str[i] - 48;
		}
		return returnVal;
	}

	void icf::toLowerCase(std::string& input)
	{
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] < 91)
			{
				input[i] = input[i] + 32;
			}
		}
	}

	bool icf::isAlpha(std::string var)
	{
		for (int i = 0; i < var.length(); i++)
		{
			if (var.at(i) < 65)
			{
				return false;
			}
		}
		return true;
	}

	int icf::length(int val)
	{
		int length = 0;
		while (val >= 1)
		{
			val /= 10;
			length++;
		}
		return length;
	}

	int icf::length(std::string val)
	{
		int length = 0;
		while (val[length] != '\0')
		{
			length++;
		}
		return length;
	}

	std::string substr(std::string val, int startIndex, int length)
	{
		std::string returnVal = "";
		for (int i = startIndex; i < (startIndex + length); i++)
		{
			if (val[i] == '\0')
			{
				break;
			}
			returnVal += val[i];
		}
		return returnVal;
	}


	bool icf::yorn(std::string prompt)
	{
		std::string temp;
		bool running = true;
		std::cout << prompt;
		while (running)
		{
			if (std::cin >> temp)
			{
				toLowerCase(temp);
				running = false;
			}
			else
			{
				std::cout << "Enter a valid input.\n";
			}
		}
		if (temp == "y")
		{
			return true;
		}
		return false;
	}
}