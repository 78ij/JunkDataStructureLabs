/*
* AUTHOR: Jiamu Sun
* EMAIL: x739566858@outlook.com
* GITHUB: 78ij
*/

#include "common.h"

//��ͷ��������.
typedef struct LinkedListNode {
	ElemType data;
	LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList{
	int length;
	LinkedListNode *head;
	LinkedList *next;
	int ListID = -1;
} LinkedList;

status IntiaList(LinkedList &L);
status DestroyList(LinkedList &L);
status ClearList(LinkedList &L);
bool   ListEmpty(const LinkedList &L);
int    ListLength(const LinkedList &L);
status GetElem(const LinkedList &L, int i, ElemType &e);
int    LocateElem(const LinkedList &L, const ElemType &e); //�򻯹�
status PriorElem(const LinkedList &L, const ElemType &cur_e, ElemType &pre_e);
status NextElem(const LinkedList &L, const ElemType &cur_e, ElemType &next_e);
status ListInsert(LinkedList &L, int i, ElemType &e);
status ListDelete(LinkedList &L, int i, ElemType &e);
status ListTraverse(const LinkedList &L);  //�򻯹�