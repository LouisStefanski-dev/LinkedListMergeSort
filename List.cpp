#include "List.h"

List::List()
{
	first = nullptr;
	last = nullptr;
	curr = nullptr;
}

void List::sort(List &list)
{
	if (list.oneOrLess())
	{
		return;
	}
	List list1, list2;
	list.goToFirst();
	while (!list.empty())
	{
		list1.add(*list.getCurrent());
		list.deleteCurrent();
		list.goToFirst();
		
		if (!list.atEnd())
		{
			list2.add(*list.getCurrent());
			list.deleteCurrent();
			list.goToFirst();
		}
	}
	sort(list1);
	sort(list2);
	merge(list, list1, list2);
}

void List::merge(List& list, List& list1, List& list2)
{
	while ((!list1.empty()) && (!list2.empty()))
	{
		list1.goToFirst();
		list2.goToFirst();
		Person element1;
		Person	element2;
		element1 = *list1.getCurrent();
		element2 = *list2.getCurrent();
		std::string name1 = element1.getName().lastName + element1.getName().firstName;
		std::string name2 = element2.getName().lastName + element2.getName().firstName;
		icf::toLowerCase(name1);
		icf::toLowerCase(name2);
		if (name1 < name2)
		{
			list1.deleteCurrent();
			list1.goToFirst();
			list.add(element1);
		}
		else 
		{
			list2.deleteCurrent();
			list2.goToFirst();
			list.add(element2);
		}
	}
	while (!list1.empty())
	{
		Person element;
		element = *list1.getCurrent();
		list1.deleteCurrent();
		list1.goToFirst();
		list.add(element);
	}
	while (!list2.empty())
	{
		Person element;
		element = *list2.getCurrent();
		list2.deleteCurrent();
		list2.goToFirst();
		list.add(element);
	}
}

bool List::oneOrLess()
{
	if (first == nullptr)
	{
		return true;
	}
	if (first->next == nullptr)
	{
		return true;
	}
	return false;
}

void List::add(Person element)
{
	ListNode* newNode = new ListNode();
	newNode->element = element;
	if (last != nullptr)
	{
		last->next = newNode;
	}
	else
	{
		first = newNode;
	}
	last = newNode;
	sorted = false;
}

void List::sort()
{
	if (!sorted) {
		List list;
		goToFirst();

		while (!empty())
		{
			list.add(*getCurrent());
			deleteCurrent();
			goToFirst();
		}


		sort(list);

		list.goToFirst();
		while (!list.empty())
		{
			add(*list.getCurrent());
			list.deleteCurrent();
			list.goToFirst();
		}
		sorted = true;
	}
}

/// <summary>
/// Call atEnd() to ensure list is not at end. In the event this getCurrent() function is called
/// and the list is in fact at the end it will return an empty string.
/// </summary>
/// <returns>current element of type string</returns>
Person* List::getCurrent()
{
	if (curr == nullptr) //no elements, should never reach if checked with atEnd
	{
		return NULL;
	}
	Person* per = &curr->element;
	return per;
}

/// <summary>
/// After calling the deleteCurrent ensure that goToFirst() is called as curr is set to NULL in this funct
/// </summary>
void List::deleteCurrent()
{
	if (curr == nullptr) //empty
	{
		return;
	}
	curr->element = first->element; //replaces current with first
	ListNode* deleteNode = first; //first will be deleted, which now has currents element
	first = first->next;
	if (first == nullptr) //if firsts next is at the end 
	{
		last = nullptr;
	}
	delete deleteNode;
	curr = nullptr;
	sorted = false;
}
