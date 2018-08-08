#include "./Linked_List.h"

Node::Node() {
	mpData = NULL;
	mpcNext = NULL;
}
Node::Node(void * pData, int size) {
	MemCpy(pData, mpData, size);
	mpcNext = NULL;
}

void ASSERT(std::string sFunction_Name, bool bIsTrue) {
	if (bIsTrue) {
		std::cout << "Assert: " << sFunction_Name << " Success\n";
	}
	else {
		std::cout << "Assert: " << sFunction_Name << " Failure\n";
	}
}

void MemCpy(void *pSource, void *pDestination, int size) {
	char *pcDestination = (char *)pDestination;
	char *pcSource = (char *)pSource;

	ASSERT("MemCpy", pSource != NULL && pDestination != NULL);

	if (NULL != pcDestination) {
		for (int i = 0; i < size; i++) {
			pcDestination[i] = pcSource[i];
		}
	}
}

Linked_List::Linked_List(){
	mpcCurrent = NULL;
	mpcHead = NULL;
	size = 0;
}

/*To call this function outside of the scope of itself, psCurrentNode should be Linked_List->mpcHead*/
void Linked_List::Insert_Last(void * pData, int size) {
	ASSERT("Insert_Last, pData != NULL:", pData != NULL);
	Node * pNewNode = new Node();
	pNewNode->mpData = malloc(size);
	MemCpy(pData, pNewNode->mpData, size);

	if (NULL == this->mpcHead) {
		this->mpcHead = pNewNode;
		this->mpcCurrent = this->mpcHead;
		++this->size;
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		this->mpcCurrent->mpcNext = pNewNode;
		++this->size;
		this->mpcCurrent = mpcCurrent->mpcNext;
	}
	else {
		this->Insert_Last(pData, size);
	}
}

void Linked_List::Insert_After(void * pData, void * pReference, int size){
	Node * pTempNode = new Node();
	pTempNode->mpData = malloc(sizeof(int));
	MemCpy(pData, pTempNode->mpData, size);

	if (NULL == this->mpcCurrent) {
		this->mpcCurrent = pTempNode;
		this->mpcHead = pTempNode;
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		this->mpcCurrent->mpcNext = pTempNode;
	}
	else {
		pTempNode->mpcNext = this->mpcCurrent->mpcNext;
		this->mpcCurrent->mpcNext = pTempNode;
	}
}

void Linked_List::Insert_Start(void * pData, int size) {
	ASSERT("Insert_Start, pData != NULL:", pData != NULL);
	Node * pNewNode = new Node();
	pNewNode->mpData = malloc(size);
	MemCpy(pData, pNewNode->mpData, size);

	if (NULL == this->mpcHead) {
		this->mpcHead = pNewNode;
		this->mpcCurrent = mpcHead;
		++this->size;
	}
	else {
		pNewNode->mpcNext = this->mpcHead;
		this->mpcHead = pNewNode;
		this->mpcCurrent = mpcHead;
	}
	ASSERT("Insert_Start, this->mpcHead != NULL:", this->mpcHead != NULL);
}


void Linked_List::Insert_Sorted_Ascending(void * pData, int size){
	Node * pTempNode = new Node();
	MemCpy(pData, pTempNode->mpData, size);

	if (NULL == this->mpcHead) {
		if (!this->Is_Sorted_Ascending()) {
			std::cout << "List is not sorted.\n";
		}
		this->Insert_Start(pData, size);
		return;
	}
	else if (*(int *)pData < *(int *)this->mpcCurrent->mpcNext->mpData) {
		this->Insert_After(pData, size);
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		this->Insert_After(pData, size);
	}
	else {
		this->Insert_Sorted_Ascending(pData, size);
	}
}

/****************************************************
Method: Print_List
Parameters: None
Returns: None
Description: Recursively traverses the list printing 
	the values located at each Node
	**NOTE** mpcCurrent must == mpcHead upon fist call
****************************************************/
void Linked_List::Print_List(){
	if (NULL == this->mpcHead) {
		ASSERT("Print_List, NULL == this->mpcHead", NULL == this->mpcHead);
		std::cout << "List is empty.\n";
		return;
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		ASSERT("Print_List, NULL == this->mpcCurrent->mpcNext", NULL == this->mpcCurrent->mpcNext);
		std::cout << *(int *)mpcCurrent->mpData << "\n";
		this->mpcCurrent = this->mpcHead;
	}
	else {
		ASSERT("Print_List, NULL != this->mpcCurrent->mpcNext", NULL != this->mpcCurrent->mpcNext);
		std::cout << *(int *)mpcCurrent->mpData << "\n";
		this->mpcCurrent = this->mpcCurrent->mpcNext;
		this->Print_List();
	}
}

bool Linked_List::Is_Sorted_Ascending() {
	bool bIsSorted = true;
	this->mpcCurrent = this->mpcHead;
	while (NULL != this->mpcCurrent->mpcNext) {
		if (*(int *) this->mpcCurrent->mpData > *(int *) this->mpcCurrent->mpcNext->mpData) {
			bIsSorted = false;
			break;
		}
		else {
			this->mpcCurrent = this->mpcCurrent->mpcNext;
		}
	}
	return bIsSorted;
}

void Linked_List::Sort_Ascending(){
	Node * pTempNode;

	ASSERT("Sort_Ascending, NULL != this->mpcHead", NULL != this->mpcHead);
	
	if (!this->Is_Sorted_Ascending()) {
		if (NULL == this->mpcHead) {
			std::cout << "Empty List\n";
			return;
		}
		else if (NULL == this->mpcHead->mpcNext) {
			std::cout << "One Item In List\n";
			return;
		}
		else if (*(int *)this->mpcCurrent->mpData > *(int *)this->mpcCurrent->mpcNext->mpData) {
			if (NULL != this->mpcCurrent->mpcNext->mpcNext) {
				pTempNode = this->mpcCurrent->mpcNext;
				this->mpcCurrent->mpcNext = pTempNode->mpcNext;
				pTempNode->mpcNext = this->mpcCurrent;
			}
			else {
				pTempNode = this->mpcCurrent->mpcNext;
				this->mpcCurrent->mpcNext = pTempNode->mpcNext;
				pTempNode->mpcNext = this->mpcCurrent;
			}
			if (this->mpcHead == this->mpcCurrent) {
				this->mpcHead = pTempNode;
			}
		}
		this->Sort_Ascending();
	}
}

void Linked_List::Delete(){
	Node * pTempNode;
	ASSERT("Delete, NULL != this->mpcHead", NULL != this->mpcHead);
	if (NULL == this->mpcCurrent->mpcNext) {
		delete (this->mpcCurrent->mpData);
		delete (this->mpcCurrent);
	}
	else {
		pTempNode = this->mpcCurrent->mpcNext;
		delete (this->mpcCurrent->mpData);
		delete (this->mpcCurrent);
		this->mpcCurrent = pTempNode;
		this->Delete();
	}
}
