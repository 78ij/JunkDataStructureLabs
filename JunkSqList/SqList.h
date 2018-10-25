#ifndef SqList_H
#define SqList_H

#include "common.h"

//page 22 on textbook
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define LIST_MAX 500


typedef struct SqList {
	ElemType *head;
	int length;
	int listsize;
	int ListID = -1;
	SqList *next; //Initially I didn't want to add this........
}SqList;


//page 19 on textbook
status IntiaList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
bool   ListEmpty(const SqList &L);
int    ListLength(const SqList &L);
status GetElem(const SqList &L,int i, ElemType &e);
int    LocateElem(const SqList &L,const ElemType &e); //简化过
status PriorElem(const SqList &L,const ElemType &cur_e,ElemType &pre_e);
status NextElem(const SqList &L,const ElemType &cur_e,ElemType &next_e);
status ListInsert(SqList &L,int i,ElemType &e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(const SqList &L);  //简化过



#endif //SqList_H