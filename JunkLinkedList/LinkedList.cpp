/*
* AUTHOR: Jiamu Sun
* EMAIL: x739566858@outlook.com
* GITHUB: 78ij
*/

#include "LinkedList.h"

/*
* Function Name: InitaList
* Parameter: LinkedList &L
* Return: Status(int)
* Use: initialize the linear list
*/
status IntiaList(LinkedList &L) {
	L.head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	if (L.head == NULL) return ERROR;
	L.head->next = NULL;
	L.length = 0;
	/*L.length = 1;
	LinkedListNode *tmp = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	tmp->data = 1;
	L.head->next = tmp;
	tmp->next = NULL;*/
	return OK;
}

/*
* Function Name: DestroyList
* Parameter: LinkedList &L
* Return: Status(int)
* Use: destroy the linear list
*/
status DestroyList(LinkedList &L) {
	LinkedListNode *tmp = L.head->next;
	LinkedListNode *tmp2 = tmp;
	while (tmp != NULL) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	free(L.head);
	L.head = NULL;
	L.length = 0;
	return OK;
}

/*
* Function Name: ClearList
* Parameter: LinkedList &L
* Return: Status(int)
* Use: make the list empty
*/

status ClearList(LinkedList &L) {
	LinkedListNode *tmp = L.head->next;
	LinkedListNode *tmp2 = tmp;
	while (tmp != NULL) {
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	L.head->next = NULL;
	L.length = 0;
	return OK;
}

/*
* Function Name: ListEmpty
* Parameter: const LinkedList &L
* Return: bool
* Use: check if the list is empty.
*/

bool ListEmpty(const LinkedList &L) {
	if (L.length == 0) return true;
	else return false;
}

/*
* Function Name: ListLength
* Parameter: LinkedList &L
* Return: int
* Use: returns the length of the list.
*/

int ListLength(const LinkedList &L) {
	return L.length;
}

/*
* Function Name: GetElem
* Parameter: const LinkedList &L, int i ElemType &e
* Return: Status(int)
* Use: get the i-th element of the list(i starts from 1)
*/
status GetElem(const LinkedList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) {
		return ERROR; //∑√Œ ‘ΩΩÁ
	}
	LinkedListNode *ele = L.head;
	for (int j = 0; j < i; j++) {
		ele = ele->next;
	}
	e = ele->data;
	return OK;
}

/*
* Function Name: LocateElem
* Parameter: const LinkedList &L, const ElemType &e
* Return: int
* Use: return the number of the element that equals the parameter(number starts from 1)
*/
int LocateElem(const LinkedList &L, const ElemType &e) {
	LinkedListNode *ele = L.head;
	for (int i = 0; i < L.length; i++) {
		ele = ele->next;
		if (ele->data == e) return i + 1;
	}
	return 0;
}

/*
* Function Name: PriorElem
* Parameter: const LinkedList &L, ElemType &cur_e, ElemType &pre_e
* Return: Status(int)
* Use: get the the prior element of the specified element, pass it using parameter.
*/
status PriorElem(const LinkedList &L, const ElemType &cur_e, ElemType &pre_e) {
	int loc = LocateElem(L, cur_e);
	if (loc == 0 || loc == 1) return ERROR;
	else {
		loc--;
		GetElem(L, loc, pre_e);
		return OK;
	}
}

/*
* Function Name: NextElem
* Parameter: const LinkedList &L, ElemType &cur_e, ElemType &next_e
* Return: Status(int)
* Use: get the the next element of the specified element, pass it using parameter.
*/
status NextElem(const LinkedList &L, const ElemType &cur_e, ElemType &next_e) {
	int loc = LocateElem(L, cur_e);
	if (loc == L.length || loc == 0) return ERROR;
	else {
		loc++;
		GetElem(L, loc, next_e);
		return OK;
	}
}

/*
* Function Name: ListInsert
* Parameter: LinkedList &L, int i, ElemType &e
* Return: Status(int)
* Use: insert an element after the specifyed number(the list must be non-empty)
*/
status ListInsert(LinkedList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) return ERROR;
	LinkedListNode *ele = L.head;
	for (int j = 0; j < i; j++) {
		ele = ele->next;
	}
	LinkedListNode *tmp = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	tmp->data = e;
	tmp->next = ele->next;
	ele->next = tmp;
	L.length++;
	return OK;
}

/*
* Function Name: ListDelete
* Parameter: LinkedList &L, int i, ElemType &e
* Return: Status(int)
* Use: Delete the specified element.
*/
status ListDelete(LinkedList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) return ERROR;
	L.length--;
	GetElem(L, i, e);
	LinkedListNode *ele = L.head;
	for (int j = 0; j < i - 1; j++) {
		ele = ele->next;
	}
	LinkedListNode *tmp = ele->next;
	ele->next = tmp->next;
	free(tmp);
	return OK;
}

/*
* Function Name: ListTraverse
* Parameter: const LinkedList &L
* Return: Status(int)
* Use: Traverse the list and output its elements.
*/
status ListTraverse(const LinkedList &L) {
	LinkedListNode *ele = L.head->next;
	while (ele != NULL) {
		cout << ele->data << " ";
		ele = ele->next;
	}
	cout << endl;
	return OK;
}