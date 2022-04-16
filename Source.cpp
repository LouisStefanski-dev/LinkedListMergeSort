#include "PeopleManager.h"
#include <iostream>

int main()
{
	PeopleManager manager;

	manager.readInRecords("people.txt");
	while (manager.handleInput())
	{
	}
	manager.writeRecordsToFile("people.txt");

	return 0;
}  