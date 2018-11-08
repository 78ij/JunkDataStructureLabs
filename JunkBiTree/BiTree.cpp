#include "BiTree.h"

// Auxiliary functions

enum TraverseMethod {
	PRE,IN,POST,LEVEL
};

void FreeNodes(BiTreeNode *root) {
	if (root == NULL) return;
	if (root->left != NULL)
		FreeNodes(root->left);
	if (root->right != NULL)
		FreeNodes(root->right);
	free(root);

}

int search(int value, int *string, int length) {
	if (length <= 0) return -1;
	for (int i = 0; i < length; i++) {
		if (string[i] == value) return i;
	}
	return -1;
}

//data:in order
BiTreeNode *Create(int *pre, int *in, int length,ElemType *data) {
	int rootindex = search(pre[0], in, length);
	BiTreeNode *root = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	if (rootindex == -1) return NULL;
	root->data = data[rootindex];
	root->index = in[rootindex];
	root->left = Create(pre + 1, in, rootindex + 1,data);
	if (root->left != NULL) root->left->parent = root;
	root->right = Create(pre + rootindex + 1, in + rootindex + 1, length - rootindex - 1, data + rootindex + 1);
	if (root->right != NULL) root->right->parent = root;
	return root;
}

void Traverse(BiTreeNode *root, TraverseMethod method, void(* fun)(BiTreeNode * a)) {
	if (root == NULL) return;
	switch (method) {
	case PRE:
		cout << root->data << " ";
		if(fun != NULL)
			fun(root);
		Traverse(root->left, PRE, fun);
		Traverse(root->right, PRE, fun);
		break;
	case IN:
		Traverse(root->left, IN, fun);
		cout << root->data << " ";
		if (fun != NULL)
			fun(root);
		Traverse(root->right, IN, fun);
		break;
	case POST:
		Traverse(root->left, POST, fun);
		Traverse(root->right, POST, fun);
		cout << root->data << " ";
		if (fun != NULL)
			fun(root);
		break;
	case LEVEL:
		queue<BiTreeNode *> q;
		q.push(root);
		while (q.size() != 0) {
			BiTreeNode * n = q.front();
			q.pop();
			cout << n->data << " ";
			if (fun != NULL)
				fun(n);
			if (n->left != NULL) q.push(n->left);
			if (n->right != NULL) q.push(n->right);
		}
		break;
	}
}

int Depth(BiTreeNode * root) {
	if (root == NULL) return 0;
	int depthleft = Depth(root->left);
	int depthright = Depth(root->right);
	int depth = depthleft > depthright ? depthleft : depthright;
	return depth + 1;
}

/*
* Function Name: InitBiTree
* Parameter: BiTree &T
* Return: Status(int)
* Use: initialize the binary tree
*/
status InitBiTree(BiTree &T) {
	T.next = NULL;
	T.root = NULL;
	return OK;
}

/*
* Function Name: DestroyBiTree
* Parameter: BiTree &T
* Return: Status(int)
* Use: destroy the binary tree
*/
status DestroyBiTree(BiTree &T) {
	FreeNodes(T.root);
	T.root = NULL;
	return OK;
}

/*
* Function Name: CreateBiTree
* Parameter: BiTree &T, int length, int *preorder, int *inorder, ElemType * data
* Return: Status(int)
* Use: create the tree using the defination data
*/
status CreateBiTree(BiTree &T, int length, int *preorder, int *inorder, ElemType * data) {
	T.root = Create(preorder, inorder, length, data);
	return OK;
}

/*
* Function Name: ClearBiTree
* Parameter: BiTree &T
* Return: Status(int)
* Use: clear the BiTree
*/
status ClearBiTree(BiTree &T) {
	if (T.root == NULL) return OK;
	FreeNodes(T.root->left);
	FreeNodes(T.root->right);
	return OK;
}

/*
* Function Name: BiTreeEmpty
* Parameter: const BiTree &T
* Return: bool
* Use: check whether the tree is empty
*/
bool BiTreeEmpty(const BiTree &T) {
	if (T.root == NULL) return true;
	else return false;
}

/*
* Function Name: BiTreeDepth
* Parameter: const BiTree &T
* Return: int
* Use: calculate the depth of the tree.
*/
int	BiTreeDepth(const BiTree &T) {
	return Depth(T.root);
}


/*
* Function Name: PreOrderTraverse
* Parameter:const BiTree &T
* Return: Status(int)
* Use: pre order traverse the tree.
*/
status PreOrderTraverse(const BiTree &T) {
	Traverse(T.root, PRE, NULL);
	return OK;
}

/*
* Function Name: InOrderTraverse
* Parameter:const BiTree &T
* Return: Status(int)
* Use: in order traverse the tree.
*/
status InOrderTraverse(const BiTree &T) {
	Traverse(T.root, IN, NULL);
	return OK;
}

/*
* Function Name: PostOrderTraverse
* Parameter:const BiTree &T
* Return: Status(int)
* Use: post order traverse the tree.
*/
status PostOrderTraverse(const BiTree &T) {
	Traverse(T.root, POST, NULL);
	return OK;
}

/*
* Function Name: LevelOrderTraverse
* Parameter:const BiTree &T
* Return: Status(int)
* Use: level order traverse the tree.
*/
status LevelOrderTraverse(const BiTree &T) {
	Traverse(T.root, LEVEL, NULL);
	return OK;
}