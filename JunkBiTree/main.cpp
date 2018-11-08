#include "BiTree.h"

int main() {
	int in[6] = {4,2,1,5,3,6};
	int pre[6] = { 1,2,4,3,5,6 };
	ElemType data[6] = {6,7,8,9,10,11};
	BiTree tree;
	InitBiTree(tree);
	CreateBiTree(tree, 6, pre, in,data);
	LevelOrderTraverse(tree);
	system("pause");
}