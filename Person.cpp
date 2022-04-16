
#include "Person.h"

Person::Person()
{
	id = 0; //default value
	firstName = "";
	lastName = "";
	recordType = P;
}

namePack Person::getName()
{
	namePack returnVal;
	returnVal.firstName = firstName;
	returnVal.lastName = lastName;
	return returnVal;
}


