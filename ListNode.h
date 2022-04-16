#pragma once
#include "Person.h"
#include <string>

class ListNode
{
public:
	Person element;
	ListNode* next = nullptr;

	ListNode() { next = nullptr; };
};

