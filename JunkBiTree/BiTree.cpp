#include "BiTree.h"

//------------------------------------
//    Auxiliary functions
//------------------------------------

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

BiTreeNode *FindNode(BiTreeNode *root, int index) {
	if (root == NULL) return NULL;
	if (root->index == index) return root;
	else {
		BiTreeNode *left = FindNode(root->left,index);
		BiTreeNode *right = FindNode(root->right,index);
		if (left != NULL) return left;
		if (right != NULL) return right;
		return NULL;
	}
}

//----------------------------
//            APIs
//----------------------------


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
* Function Name: Root
* Parameter: const BiTree &T
* Return: BiTreeNode *
* Use: return the root node of the tree.
*/
BiTreeNode *Root(const BiTree &T) {
	return T.root;
}

/*
* Function Name: Value
* Parameter: const BiTree &T, int index,ElemType &value
* Return: status
* Use: return the value of the node
*/
status Value(const BiTree &T, int index,ElemType &value) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	else
		value = node->data;
	return OK;
}

/*
* Function Name: Assign
* Parameter: BiTree &T, int index, ElemType &value
* Return: status
* Use: assign given value to given node
*/
status Assign(BiTree &T, int index, ElemType &value) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	else
		node->data = value;
	return OK;
}

/*
* Function Name: Parent
* Parameter: const BiTree &T, int index
* Return: BiTreeNode *
* Use: return the parent of the given node 
*/
BiTreeNode *Parent(const BiTree &T, int index) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	else
		return node->parent;
}

/*
* Function Name: LeftChild
* Parameter: const BiTree &T, int index
* Return: BiTreeNode *
* Use: return the LeftChild of the given node
*/
BiTreeNode *LeftChild(const BiTree &T, int index) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	else
		return node->left;
}

/*
* Function Name: RightChild
* Parameter: const BiTree &T, int index
* Return: BiTreeNode *
* Use: return the RightChild of the given node
*/
BiTreeNode *RightChild(const BiTree &T, int index) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	else
		return node->right;
}

/*
* Function Name: LeftSibling
* Parameter: const BiTree &T, int index
* Return: BiTreeNode *
* Use: return the LeftSibling of the given node
*/
BiTreeNode *LeftSibling(const BiTree &T, int index) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	if (node->parent == NULL) return NULL;
	else {
		if (node->parent->left == node)
			return NULL;
		if (node->parent->right == node)
			return node->parent->left;
	}
}

/*
* Function Name: RightSibling
* Parameter: const BiTree &T, int index
* Return: BiTreeNode *
* Use: return the RightSibling of the given node
*/
BiTreeNode *RightSibling(const BiTree &T, int index) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	if (node->parent == NULL) return NULL;
	else {
		if (node->parent->right == node)
			return NULL;
		if (node->parent->left == node)
			return node->parent->right;
	}
}

/*
* Function Name: InsertChild
* Parameter: BiTree &T, int index, int LR, BiTree &c
* Return: status
* Use: Insert the BiTree to the given node 
*/
status  InsertChild(BiTree &T, int index, int LR, BiTree &c) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL || c.root == NULL || c.root->right == NULL) return ERROR;
	if (LR == 0) { // left
		BiTreeNode *tmp = node->left;
		c.root->parent = node;
		node->left = c.root;
		c.root->right = tmp;
		return OK;
	}
	if (LR == 1) {
		BiTreeNode *tmp = node->right;
		c.root->parent = node;
		node->right = c.root;
		c.root->right = tmp;
		return OK;
	}
	else return ERROR;
}

/*
* Function Name: DeleteChild
* Parameter: BiTree &T, int index, int LR
* Return: status
* Use: delete the child tree of the given node
*/
status  DeleteChild(BiTree &T, int index, int LR) {
	BiTreeNode *node = FindNode(T.root, index);
	if (node == NULL) return ERROR;
	if (LR == 0) {
		if (node->left == NULL) return ERROR;
		FreeNodes(node->left);
		node->left = NULL;
		return OK;
	}
	if (LR == 1) {
		if (node->right == NULL) return ERROR;
		FreeNodes(node->right);
		node->right = NULL;
		return OK;
	}
	else return ERROR;
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