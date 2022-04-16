#pragma once
#include "List.h"
#include "icf.h"

#include<typeinfo>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

class PeopleManager
{
private:
	List PeopleList;
	unsigned int counter = 0;
	const unsigned short int divider = 20;
	bool search(Person& person, unsigned int id);
	bool search(Person& person, std::string name, unsigned int mode); //0 first name, 1 last name

public:
	PeopleManager() {};
	~PeopleManager() { while (!PeopleList.empty()) { PeopleList.goToFirst(); PeopleList.deleteCurrent(); } };
	bool readInRecords(std::string file);
	void parseRecord(std::string record);
	bool writeRecordsToFile(std::string file);
	void addPerson(namePack name, unsigned int id, recordTypes recordType = P);
	bool handleInput();
	void displayPerson(Person person);

	void displayOutputInterface(int divider);
	void deletePerson(int id);

};

