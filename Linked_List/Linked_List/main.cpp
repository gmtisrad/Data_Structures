#include "Linked_List.h"
#include <iostream>

int main(int argc, char * argv[]) {
	int * destination = NULL;
	Linked_List * pLinkedList;

	/*Test for MemCpy
	std::cout << "Begin MemCpy Test:\n\nOriginal: 10 \nPerforming MemCpy... ";
	destination = new int();
	MemCpy(&original, destination, sizeof(int));
	std::cout << "MemCpy complete. \nCopied Value: " << original << "\n";
	*/

	/*  Test for Linked_List::Insert Last
	pLinkedList = new Linked_List();

	for (int i = 0; i < 5; i++) {
		pLinkedList->Insert_Last(&i, sizeof(int));
		ASSERT("Insert_Last Test", pLinkedList->mpcHead != NULL);
		std::cout << *(int *)pLinkedList->mpcCurrent->mpData << '\n';
	}
	delete pLinkedList*/

	/*Test for Linked_List::Insert_Start()
	pLinkedList = new Linked_List();

	for (int i = 0; i < 5; i++) {
		pLinkedList->Insert_Start(&i, sizeof(int));
		ASSERT("Insert_Start Test, NULL != pLinkedList->mpcHead:", NULL != pLinkedList->mpcHead);
		std::cout << *(int *)pLinkedList->mpcHead->mpData << "\n";
	}
	delete pLinkedList;*/

	/*Test for Linked_List::Sort_Ascending()
	pLinkedList = new Linked_List();
	
	for (int i = 0; i < 5; i++) {
		pLinkedList->Insert_Start(&i, sizeof(int));
	}
	ASSERT("Linked_List::Is_Sorted_Ascending, true == Linked_List::Is_Sorted_Ascending", pLinkedList->Is_Sorted_Ascending());
	pLinkedList->mpcCurrent = pLinkedList->mpcHead;
	pLinkedList->Sort_Ascending();
	ASSERT("Linked_List::Sort_Ascending(), true == Linked_List::Is_Sorted_Ascending", pLinkedList->Is_Sorted_Ascending());
	delete pLinkedList;
	*/

	pLinkedList = new Linked_List();

	for (int i = 0; i < 8; i++) {
		pLinkedList->Insert_Next(&i, sizeof(int));
	}
	pLinkedList->mpcCurrent = pLinkedList->mpcHead;
	pLinkedList->Print_List();
	pLinkedList->Sort_Ascending();
	pLinkedList->Print_List();

	delete pLinkedList;

	return EXIT_SUCCESS;
}