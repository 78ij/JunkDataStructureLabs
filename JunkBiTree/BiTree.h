/*
* AUTHOR: Jiamu Sun
* EMAIL: x739566858@outlook.com
* GITHUB: 78ij
*/

#include "common.h"


typedef struct BiTreeNode {
	ElemType data;
	int index; // used to mark the node
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
status      CreateBiTree(BiTree &T, int length, int *preorder, int *inorder, ElemType * data);
status		ClearBiTree(BiTree &T);
bool		BiTreeEmpty(const BiTree &T);
int			BiTreeDepth(const BiTree &T);
BiTreeNode *Root(const BiTree &T);
status		Value(const BiTree &T, int index, ElemType &value);
status		Assign(BiTree &T, int index,ElemType &value);
BiTreeNode *Parent(const BiTree &T, int index);
BiTreeNode *LeftChild(const BiTree &T, int index);
BiTreeNode *RightChild(const BiTree &T, int index);
BiTreeNode *LeftSibling(const BiTree &T, int index);
BiTreeNode *RightSibling(const BiTree &T, int index);
status      InsertChild(BiTree &T, int index, int LR, BiTree &c);
status      DeleteChild(BiTree &T, int index, int LR);
status      PreOrderTraverse(const BiTree &T);
status      InOrderTraverse(const BiTree &T);
status      PostOrderTraverse(const BiTree &T);
status		LevelOrderTraverse(const BiTree &T);