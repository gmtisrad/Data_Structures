#include "./Linked_List.h"

/******************************************************************************
Method:      Node::Node
Parameters:  None
Returns:     An instance of the Node object

Description: Instantiates a Node object.
******************************************************************************/
Node::Node() {
	mpData = NULL;
	mpcNext = NULL;
}

/******************************************************************************
Method:      Node::Node
Parameters:  void * - The Data to be stored in the node
						 int    - The size in bites of the data
Returns:     An instance of the Node object
Description: Instantiates a Node object and stores the passed data inside.
******************************************************************************/
Node::Node(void * pData, int size) {
	this->mpData = malloc(sizeof(int));
	MemCpy(pData, mpData, size);
	mpcNext = NULL;
}

/******************************************************************************
 Method:     ASSERT
 Parameters: std::string - The Name of the function
									  bool - Success or failure of tested expression
Returns:     None.
Description: Tests and prints the truth of an expression and prints the name
						 of the method.
******************************************************************************/
void ASSERT(std::string sFunction_Name, bool bIsTrue) {
	if (bIsTrue) {
		std::cout << "Assert: " << sFunction_Name << " Success\n";
	}
	else {
		std::cout << "Assert: " << sFunction_Name << " Failure\n";
	}
}

/******************************************************************************
Method:      MemCpy
Parameters:  void * - The source of data to be copied
					   void * - The Destination for the copied data
						 int    - The size in bites for the copied data
Returns:		 None.
Description: Copies a contiguous portion of memory of size length in bits from
						 pSource to pDestination.
******************************************************************************/
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

/******************************************************************************
Method:      Linked_Lists::Linked_List
Parameters:  None.
Returns:		 An instance of the Linked_List object.
Description: Instantiates the Linked_List object.
******************************************************************************/
Linked_List::Linked_List(){
	mpcCurrent = NULL;
	mpcHead = NULL;
	size = 0;
}

/******************************************************************************
Method:      Linked_List::Linked_List
Parameters:  void * - The data to be added to the list
						 int    - The size in bits of the data
Returns:     None.
Description: Inserts pData into the end of the list.
						 Note: 
******************************************************************************/
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

/******************************************************************************
Method:      Linked_List::Insert_After
Parameters:  void * - The Data to be inserted into the list
						 void * - The data stored in the Node to be inserted after
						 int    - The size of the data to be copied
Returns:     None.
Description: This function inserts data after the Node that contains the 
						 reference data.
******************************************************************************/
void Linked_List::Insert_After(void * pData, void * pReference, int size){
	if (NULL == pData) {
		std::cout << "Error: No data to insert.\n";
		return;
	}

	Node * pTempNode = new Node();
	pTempNode->mpData = malloc(size);
	MemCpy(pData, pTempNode->mpData, size);


	if (NULL == this->mpcHead) {
		this->mpcCurrent = pTempNode;
		this->mpcHead = pTempNode;
	}
	else if (*(int *)this->mpcCurrent->mpData == *(int *)pReference) {
		this->Insert_Next(pData, size);
		this->mpcCurrent = this->mpcHead;
	}
	else {
		this->Insert_After(pData, pReference, size);
	}
}

/******************************************************************************
Method:      Linked_List::Insert_Next
Parameters:  void * - The data to be inserted into the list
						 int    - The size in bites of the data to be copied
Returns:		 None.
Description: Inserts a Node containing the data after this->mpcCurrent
******************************************************************************/
void Linked_List::Insert_Next(void * pData, int size) {
	if (NULL == pData) {
		std::cout << "Error: No data to insert.\n";
		return;
	}

	Node * pNewNode = new Node();
	pNewNode->mpData = malloc(size);
	MemCpy(pData, pNewNode->mpData, size);

	if (NULL == this->mpcHead) {
		this->mpcHead = pNewNode;
		this->mpcCurrent = pNewNode;
		return;
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		this->mpcCurrent->mpcNext = pNewNode;
		this->mpcCurrent = pNewNode;
		return;
	}
	else {
		pNewNode->mpcNext = this->mpcCurrent->mpcNext;
		this->mpcCurrent->mpcNext = pNewNode;
		return;
	}
}

/******************************************************************************
Method:      Linked_List::Insert_Start
Parameters:  void * - The data to be inserted into the list
						 int    - The size in bites of the data to be copied
Returns:     None.
Description: Inserts the data into the start of he list.
******************************************************************************/
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

/******************************************************************************
Method:      Linked_List::Insert_Sorted_Ascending
Parameters:  void * - The data to be inserted into the list
						 int    - The size in bites of the data to be copied
Returns:     None.
Description: Inserts the data into the list in ascending order.
******************************************************************************/
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
		this->Insert_Next(pData, size);
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		this->Insert_Next(pData, size);
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
		std::cout << "Error: List is empty.\n";
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

/******************************************************************************
Method:      Linked_List::Is_Sorted_Ascending
Parameters:  None.
Returns:		 bool - True if list is sorted; Else false.
Description: Recursively checks if the list is sorted in ascending order.
******************************************************************************/
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

/******************************************************************************
Method:			 Linked_List:Sort_Ascending
Parameters:  None.
Returns:		 None.
Description: Recursively sorts the list in ascending order.
******************************************************************************/
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

/******************************************************************************
Method:			 Linked_List::Delete
Parameters:	 None.
Returns:		 None.
Description: Recursively deletes the list and frees any allocated memory
******************************************************************************/
void Linked_List::Delete(){
	Node * pTempNode;
	ASSERT("Delete, NULL != this->mpcHead", NULL != this->mpcHead);
	
	if (NULL == this->mpcHead) {
		std::cout << "Error: Cannot delete empty function";
		return;
	}
	else if (NULL == this->mpcCurrent->mpcNext) {
		free (this->mpcCurrent->mpData);
		delete (this->mpcCurrent);
	}
	else {
		pTempNode = this->mpcCurrent->mpcNext;
		free (this->mpcCurrent->mpData);
		delete (this->mpcCurrent);
		this->mpcCurrent = pTempNode;
		this->Delete();
	}
}
