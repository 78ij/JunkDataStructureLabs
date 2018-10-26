/*
* AUTHOR: Jiamu Sun
* EMAIL: x739566858@outlook.com
* GITHUB: 78ij
*/


#include "SqList.h"

/*
* Function Name: InitaList
* Parameter: SqList &L
* Return: Status(int)
* Use: initialize the linear list
*/
status IntiaList(SqList &L) {
	L.listsize = LIST_INIT_SIZE;
	L.head = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
	if (L.head == NULL) //分配失败
		return ERROR;
	else return OK;
}

/*
* Function Name: DestroyList
* Parameter: SqList &L
* Return: Status(int)
* Use: destroy the linear list
*/
status DestroyList(SqList &L) {
	L.length = 0;
	L.listsize = 0;
	free(L.head);
	L.head = NULL; //防止野指针
	return OK;
}

/*
* Function Name: ClearList
* Parameter: SqList &L
* Return: Status(int)
* Use: make the list empty
*/
status ClearList(SqList &L) {
	ElemType *head = (ElemType *)memset(L.head, 0, sizeof(ElemType) * L.length);
	L.length = 0;
	return OK;
}

/*
* Function Name: ListEmpty
* Parameter: const SqList &L
* Return: bool
* Use: check if the list is empty.
*/
bool ListEmpty(const SqList &L) {
	if (L.length != 0) return false;
	else return true;
}

/*
* Function Name: ListLength
* Parameter: SqList &L
* Return: int
* Use: returns the length of the list.
*/
int ListLength(const SqList &L) {
	return L.length;
}

/*
* Function Name: GetElem
* Parameter: const SqList &L, int i ElemType &e
* Return: Status(int)
* Use: get the i-th element of the list(i starts from 1)
*/
status GetElem(const SqList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) {
		return ERROR; //访问越界
	}
	int j = --i;
	ElemType *elementloc = (ElemType *)L.head + j;
	e = *elementloc;
	return OK;
}

/*
* Function Name: LocateElem
* Parameter: const SqList &L, const ElemType &e
* Return: int
* Use: return the number of the element that equals the parameter(number starts from 1)
*/
int LocateElem(const SqList &L, const ElemType &e) {
	for (int i = 1; i <= L.length; i++) {
		ElemType ele;
		GetElem(L, i, ele);
		if (ele == e) return i;
	}
	return 0;
}

/*
* Function Name: PriorElem
* Parameter: const SqList &L, ElemType &cur_e, ElemType &pre_e
* Return: Status(int)
* Use: get the the prior element of the specified element, pass it using parameter.
*/
status PriorElem(const SqList &L, const ElemType &cur_e, ElemType &pre_e) {
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
* Parameter: const SqList &L, ElemType &cur_e, ElemType &next_e
* Return: Status(int)
* Use: get the the next element of the specified element, pass it using parameter.
*/
status NextElem(const SqList &L, const ElemType &cur_e, ElemType &next_e) {
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
* Parameter: SqList &L, int i, ElemType &e
* Return: Status(int)
* Use: insert an element after the specifyed number(the list must be non-empty)
*/
status ListInsert(SqList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) return ERROR;
	if (L.length + 1 > L.listsize) { //扩大存储空间并复制元素
		if (L.listsize + LISTINCREMENT > LIST_MAX) return OVERFLOW;
		L.listsize += LISTINCREMENT;
		ElemType *temp = L.head;
		L.head = (ElemType *)realloc(L.head,sizeof(ElemType) * L.listsize);

	}
	for (int j = L.length - 1; j >= i - 1; j--) {
		*(L.head + j + 1) = *(L.head + j);
	}
	*(L.head + i - 1) = e;
	L.length++;
	return OK;
}

/*
* Function Name: ListDelete
* Parameter: SqList &L, int i, ElemType &e
* Return: Status(int)
* Use: Delete the specified element.
*/
status ListDelete(SqList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) return ERROR;
	L.length--;
	GetElem(L, i, e);
	for (int j = i; j < L.length - 1; j++) {
		*(L.head + j - 1) = *(L.head + j);
	}
	return OK;
}

/*
* Function Name: ListTraverse
* Parameter: const SqList &L
* Return: Status(int)
* Use: Traverse the list and output its elements.
*/
status ListTraverse(const SqList &L) {
	ElemType e;
	for (int i = 1; i <= L.length; i++) {
		GetElem(L, i, e);
		cout << e << " ";
	}
	cout << endl;
	return OK;
}

