#pragma once
#include "ListNode.h"
#include "icf.h"
#include "Person.h"
#include <string>
#include <iostream>

class List
{
private:
	ListNode* first = nullptr;
	ListNode* last = nullptr;
	ListNode* curr = nullptr;
	void sort(List& list);
	void merge(List& list, List& list1, List& list2);
	bool oneOrLess();
	bool sorted = false; //used to check if list is already sorted. Set to false by add and deleteCurrent
							//set to true after sort has run
public:
	List();
	void add(Person element);
	void sort();
	bool empty() { return (first == NULL); };
	void goToFirst() { curr = first; };
	void goToNext() { curr = curr->next; };
	bool atEnd() { return (curr == NULL); };
	Person* getCurrent();
	void deleteCurrent();
};

