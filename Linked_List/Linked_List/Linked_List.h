#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define NULL 0

/*********************************************************
Class: Node
Description: A Node to act as the individual pieces of the
	Linked_List
*********************************************************/
class Node {
public:
	Node();
	Node(void * pData, int size);
	Node * mpcNext;
	void * mpData;
	int size;
};

/*********************************************************
Class: Linked_List
Description: A linked list Data Structure with recurisvely
	implemented methods.
*********************************************************/
class Linked_List {
public:
	Linked_List();
	void Insert_Last(void * pData, int size);
	void Insert_After(void * pData, void * pReference, int size);
	void Insert_Start(void * pData, int size);
	void Insert_Sorted_Ascending(void * pData, int size);
	void Print_List();
	bool Is_Sorted_Ascending();
	void Sort_Ascending();
	void Delete();
	Node * mpcHead;
	Node * mpcCurrent;
	int size;
};

void ASSERT(std::string sFunction_Name, bool bIsExecuted);
void MemCpy(void * pSource, void * pDestination, int size);