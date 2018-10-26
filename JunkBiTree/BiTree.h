/*
* AUTHOR: Jiamu Sun
* EMAIL: x739566858@outlook.com
* GITHUB: 78ij
*/

#include "common.h"

typedef struct BiTreeNode {
	ElemType data;
	BiTreeNode *parent;
	BiTreeNode *left;
	BiTreeNode *right;
}BiTreeNode;

typedef struct BiTree {
	int TreeID = -1;
	BiTreeNode *root;
	BiTree *next;
}BiTree;