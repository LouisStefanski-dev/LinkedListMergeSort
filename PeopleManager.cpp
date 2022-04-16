#include "PeopleManager.h"

//reads records using standard ' ' delimination
bool PeopleManager::readInRecords(std::string file) //uses " " as a delimiter 
{
	std::ifstream dataFile(file);
	if (!dataFile)
	{
		std::cout << "Could not open file" << std::endl;
		return false;
	}
	std::string record;
	while (std::getline(dataFile, record))
	{
		parseRecord(record);
	}
	dataFile.close();
	PeopleList.sort();
	return true;
}

//writes records from to indicated file
bool PeopleManager::writeRecordsToFile(std::string file)
{
	std::fstream dataFile;
	dataFile.open(file, std::ios::out | std::ios::trunc);
	if (!dataFile)
	{
		std::cout << "Could not open file" << std::endl;
		return false;
	}
	Person record;
	PeopleList.goToFirst();
	while(!PeopleList.atEnd())
	{
		record = *PeopleList.getCurrent();
		dataFile << record.id << " " << record.firstName << " " << record.lastName << "\n";
		PeopleList.goToNext();
	}
	dataFile.close();
	return true;
} 

void PeopleManager::parseRecord(std::string record)
{
	int posInArray = 0;
	int pos = 0;
	//length of array is the number of expected return values 
	std::string dataReadIn[3];
	while (true)
	{
		if (record.find(" ") == std::string::npos)
		{
			dataReadIn[posInArray] = record.substr(0);
			break;
		};
		pos = record.find(" ");
		dataReadIn[posInArray++] = record.substr(0, pos);
		record = record.substr(record.find(" ") + 1);
		//id is covered by std::string::npos case above
	}
	//last name comes first then first name, so firstNames pos is 1 
	namePack newPack;
	newPack.firstName = dataReadIn[1];
	newPack.lastName = dataReadIn[2];
	addPerson(newPack, icf::stringToInt(dataReadIn[0]));
}

bool PeopleManager::search(Person& person, unsigned int id)
{
	PeopleList.goToFirst();
	while(!PeopleList.atEnd())
	{
		if ((*PeopleList.getCurrent()).getId() == id)
		{
			person = *PeopleList.getCurrent();
			return true;
		}
		PeopleList.goToNext();
	}
	return false;
}

//Also prints out entries
bool PeopleManager::search(Person& person, std::string name, unsigned int mode)
{
	bool found = false;
	PeopleList.goToFirst();
	icf::toLowerCase(name);
	std::string checkName;
	icf::clearScreen();
	displayOutputInterface(divider);
	while(!PeopleList.atEnd())
	{
		checkName = ((mode == 0) ? (*PeopleList.getCurrent()).getName().firstName : (*PeopleList.getCurrent()).getName().lastName);
		icf::toLowerCase(checkName);
		if (name == icf::substr(checkName, 0, icf::length(name)))
		{
			found = true;
			displayPerson(*PeopleList.getCurrent());
		}
		PeopleList.goToNext();
	}
	return found;
}

void PeopleManager::addPerson(namePack name, unsigned int id, recordTypes recordType)
{
	Person* newPerson = new Person();
	newPerson->firstName = name.firstName;
	newPerson->lastName = name.lastName;
	newPerson->id = id;
	newPerson->recordType = recordType;
	counter++;
	PeopleList.add(*newPerson);
}

bool PeopleManager::handleInput()
{
	std::string check;
	while (true)
	{
		icf::clearScreen();
		std::cout << "1. Add Person\n2.Display all People\n3.Search by ID\n4.Search by first name\n5.Search by last name\n6.Edit Person\n7.Delete Person\n0.Exit\n";
		if (!(std::cin >> check))
		{
			std::cout << "Please enter a valid input.\n";
		}
		else
		{
			if (icf::isAlpha(check))
			{
				std::cout << "Please enter a valid input.\n";
			}
			else
			{
				break;
			}
		}
	}
	bool inputLoop = true;
	switch (icf::stringToInt(check))
	{
	case 1: //adds a person
	{
		icf::clearScreen();
		std::string fName, lName, check;
		while (inputLoop)
		{
			while (true) //firstName
			{
				icf::getInput(fName, "Please enter first name: \n");
				if (icf::checkType(fName, "CheckString"))
				{
					break;
				}
				std::cout << "Enter proper input.\n";
			}
			while (true) //lastName
			{
				icf::getInput(lName, "Please enter last name: \n");
				if (icf::checkType(fName, "CheckString"))
				{
					break;
				}
				std::cout << "Enter proper input.\n";
			}
			icf::clearScreen();
			std::cout << "Is this information correct?(Y o N)\n";
			std::cout << "First name: " << fName << "\nLast name: " << lName << std::endl;
			while (true)
			{
				if (std::cin >> check)
				{
					icf::toLowerCase(check);
					if (check == "y")
					{
						if (icf::yorn("Would you like to add this person?(Y o N)\n"))
						{
							namePack newName;
							newName.firstName = fName;
							newName.lastName = lName;
							addPerson(newName, counter + 1000, P);
							PeopleList.goToFirst();
							PeopleList.sort();
							inputLoop = false;
							break;
						}
						inputLoop = false;
						break;
					}
					break;
				}
				else
				{
					std::cout << "Please enter a valid input.\n";
				}
			}
		}
		icf::clearScreen();
		break;
	}
	case 2:
	{
		PeopleList.goToFirst();
		icf::clearScreen();
		displayOutputInterface(divider);

		while(!PeopleList.atEnd())
		{
			displayPerson(*PeopleList.getCurrent());
			PeopleList.goToNext();
		}
		std::string check;
		while (true)
		{
			if (icf::yorn("Would you like to stop viewing this screen? (Y o N)")) { break; };
		}
		break;
	}
	case 3:
		//search by id
	{
		icf::clearScreen();
		int id;
		Person tempPerson;
		while (true)
		{
			icf::getInput(id, "Please enter the ID of the person you'd like to search for:\n");
			if (!((id - 1000) > counter))
			{
				if (search(tempPerson, id))
				{
					icf::clearScreen();
					displayOutputInterface(divider);
					displayPerson(tempPerson);
					while (icf::yorn("Would you like to continue viewing this page? Y o N\n")) {};
					break;
				}
				std::cout << "Nobody by that ID was found.\n";
				while (icf::yorn("Would you like to continue viewing this page? Y o N\n")) {};
				break;
			}
			std::cout << "Please enter a proper id\n";
		}
		break;
	}
	case 4:
		//first name search
	{
		icf::clearScreen();
		std::string name;
		Person tempPerson;
		while (true)
		{
			icf::getInput(name, "Please enter the first name of the person you'd like to search for:\n");
			if (icf::checkType(name, "TestString"))
			{
				if (!search(tempPerson, name, 0))
				{
					std::cout << "Nobody by that first name was found.\n";
					while (icf::yorn("Would you like to continue viewing this page? Y o N\n")) {};
					break;
				}
				while (icf::yorn("Would you like to continue viewing this page? Y o N\n")) {};
				break;
			}
			std::cout << "Please enter a proper first name.\n";
		}
		break;
	}
	case 5:
		//last name search
	{
		icf::clearScreen();
		std::string name;
		Person tempPerson;
		while (true)
		{
			icf::getInput(name, "Please enter the last name of the person you'd like to search for:\n");
			if (icf::checkType(name, "TestString"))
			{
				if (!search(tempPerson, name, 1))
				{
					std::cout << "Nobody by that last name was found.\n";
					while (icf::yorn("Would you like to continue viewing this page? Y o N\n")) {};
					break;
				}
				while (icf::yorn("Would you like to continue viewing this page? Y o N\n")) {};
				break;
			}
			std::cout << "Please enter a proper last name.\n";
		}
		break;
	}
	case 6: 
	{
		int id;
		std::string name;
		Person newPerson;

		//finds person to edit
		icf::clearScreen();
		icf::getInput(id, "Please enter the ID of the person you'd like to edit\n");
		search(newPerson, id);
		displayOutputInterface(divider);
		displayPerson(newPerson);
		if (!icf::yorn("Would you like to edit this person?\n")) { break; }

		//gets new name
		icf::clearScreen();
		namePack newName;
		icf::getInput(name, "What would you like the first name to be?\n");
		newName.firstName = name;
		icf::getInput(name, "What would you like the last name to be?\n");
		newName.lastName = name;

		//swaps entries
		icf::clearScreen();
		std::cout << "First name: " << newName.firstName << "\nLast name: " << newName.lastName << std::endl;
		if (!icf::yorn("Add this edited information?\n")) { break; };
		deletePerson(id);
		addPerson(newName, id);
		break;
	}
	case 7:
		//delete
	{
		int id;
		Person newPerson;
		icf::clearScreen();
		icf::getInput(id, "What record would you like to delete? (Record ID)\n");
		if (search(newPerson, id))
		{
			icf::clearScreen();
			displayOutputInterface(divider);
			displayPerson(newPerson);
			if (icf::yorn("Are you sure you want to delete this person?\n"))
			{
				PeopleList.goToFirst();
				deletePerson(id);
				PeopleList.sort();
				break;
			}
		}

		break;
	}
	case 0:
	{
		return false;
		break;
	}
	default:
	{
		std::cout << "Invalid entry\n";
		break;
	}
	}
	return true;
}


void PeopleManager::deletePerson(int id)
{
	PeopleList.goToFirst();
	while (!PeopleList.atEnd())
	{
		if ((*PeopleList.getCurrent()).id == id)
		{
			PeopleList.deleteCurrent();
			PeopleList.goToFirst();
			PeopleList.sort();
			break;
		};
		PeopleList.goToNext();
	}
}

void PeopleManager::displayOutputInterface(int divider)
{
	std::cout << "ID" << std::setw(divider + icf::length("ID")) << "First Name" << std::setw(divider + icf::length("ID")) << "Last Name\n";
}


void PeopleManager::displayPerson(Person person)
{
	std::cout << person.getId() << std::setw(divider) <<  person.getName().firstName << std::setw(divider) << person.getName().lastName << std::endl;
}


