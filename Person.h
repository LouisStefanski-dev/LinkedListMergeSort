#pragma once
#include <string>


enum recordTypes { P };
struct namePack 
{
	std::string firstName;
	std::string lastName;
};

class Person
{
public:
	Person();

	//variables
	std::string firstName, lastName;
	recordTypes recordType;
	unsigned int id;

	//functions
	unsigned int getId() { return id; };

	//returns a struct, returnedName, containing first and last name
	namePack getName();
	recordTypes getRecordType() { return recordType; };
};

