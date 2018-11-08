/*
* AUTHOR: Jiamu Sun
* EMAIL: x739566858@outlook.com
* GITHUB: 78ij
*/

#include "common.h"


typedef struct BiTreeNode {
	ElemType data;
	int index; // used to retrieve the tree
	BiTreeNode *parent;
	BiTreeNode *left;
	BiTreeNode *right;
}BiTreeNode;

typedef struct BiTree {
	int TreeID = -1;
	BiTreeNode *root;
	BiTree *next;
}BiTree;

//APIs

status		InitBiTree(BiTree &T);
status		DestroyBiTree(BiTree &T);
status CreateBiTree(BiTree &T, int length, int *preorder, int *inorder, ElemType * data);
status		ClearBiTree(BiTree &T);
bool		BiTreeEmpty(const BiTree &T);
//int			BiTreeDepth(const BiTree &T);
//BiTreeNode *Root(const BiTree &T);
//status		Value(const BiTree &T, BiTreeNode &e);
//status		Assign(BiTree &T, BiTreeNode &e,ElemType &value);
//BiTreeNode *Parent(const BiTree &T, BiTreeNode &e);
//BiTreeNode *LeftChild(const BiTree &T, BiTreeNode &e);
//BiTreeNode *RightChild(const BiTree &T, BiTreeNode &e);
//BiTreeNode *LeftSibling(const BiTree &T, BiTreeNode &e);
//BiTreeNode *RightSibling(const BiTree &T, BiTreeNode &e);
//status      InsertChild(BiTree &T, BiTreeNode &p, int LR, BiTree &c);
//status      DeleteChild(BiTree &T, BiTreeNode &p, int LR);
status      PreOrderTraverse(const BiTree &T);
status      InOrderTraverse(const BiTree &T);
status      PostOrderTraverse(const BiTree &T);
status		LevelOrderTraverse(const BiTree &T);