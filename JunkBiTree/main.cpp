#include "BiTree.h"

void PrintMenu(void) {
	/*
	* Function Name: PrintMenu
	* Parameter: None
	* Return: None
	* Use: Print the main menu
	*/

	printf("\n+---------------------------------------------------+\n");
	printf("|                *THE* BINARY TREE DEMO               |\n");
	printf("|                                                     |\n");
	printf("|                     Functions                       |\n");
	printf("|                                                     |\n");
	printf("|      1.InitBiTree             2.DestroyBiTree       |\n");
	printf("|      3.CreateBiTree           4.ClearBiTree         |\n");
	printf("|      5.BiTreeEmpty            6.BiTreeDepth         |\n");
	printf("|      7.Root                   8.Value               |\n");
	printf("|      9.Assign                 10.Parent             |\n");
	printf("|     11.LeftChild              12.RightChild         |\n");
	printf("|     13.LeftSibling            14.RightSibling       |\n");
	printf("|     15.InsertChild            16.DeleteChild        |\n");
	printf("|     17.PreOrderTraverse       18.InOrderTraverse    |\n");
	printf("|     19.PostOrderTraverse      20.LevelOrderTraverse |\n");
	printf("|                                                     |\n");
	printf("|                                                     |\n");
	printf("|                      78ij@8102                      |\n");
	printf("|                                                     |\n");
	printf("+-----------------------------------------------------+\n");
	printf("\n");

}

status LoadData(BiTree **head) {
	/*
	* Function Name: LoadData
	* Parameter: none
	* Return Status(int)
	* Use: load data from file
	*/
	FILE *fp = fopen("SLDB", "rb");
	if (fp == NULL)
		return ERROR;

	int size = 0;
	int count = 0;
	BiTree *tmp = (BiTree *)malloc(sizeof(BiTree));
	size = fread(tmp, sizeof(BiTree), 1, fp);
	if (size == 0) {
		free(tmp);
		return OK;
	}
	count++;
	size = tmp->length;
	int *preorder = (int *)malloc(size * sizeof(int));
    int *inorder = (int *)malloc(size * sizeof(int));
	ElemType *data = (ElemType *)malloc(size * sizeof(ElemType));
	fread(preorder, sizeof(int), size, fp);
	fread(inorder, sizeof(int), size, fp);
	fread(data, sizeof(ElemType), size, fp);
	CreateBiTree(*tmp, size, preorder, inorder, data);
    *head = tmp;

	while (1) {
		BiTree *tmp = (BiTree *)malloc(sizeof(BiTree));
		size = fread(tmp, sizeof(BiTree), 1, fp);
		if (size == 0) {
			free(tmp);
			break;
		}
		count++;
		size = tmp->length;
		fread(preorder, sizeof(int), size, fp);
		fread(inorder, sizeof(int), size, fp);
		fread(data, sizeof(ElemType), size, fp);
		CreateBiTree(*tmp, size, preorder, inorder, data);
		(*head)->next = tmp;
		*head = (*head)->next;
	}
	(*head)->next = NULL;
	*head = tmp;
	fclose(fp);
	return OK;
}

status SaveData(BiTree *head) {
	/*
	* Function Name: SaveData
	* Parameter: BiTree *heAD
	* Return: Status(int)
	* Use: save data to file
	*/

	FILE *fp = fopen("SLDB", "wb");
	if (fp == NULL)
		return ERROR;
	BiTree *L = head, *p = head;
	while (L != NULL) {
		fwrite(L, sizeof(BiTree), 1, fp);
		write(L->root, PRE, true, fp);
		write(L->root, IN, true, fp);
		write(L->root, IN, false, fp);
		p = L->next;
		DestroyBiTree(*L);
		//free(L);
		L = p;
	}

	fclose(fp);
	return OK;
}

int main() {
	int selection = -1;
	BiTree *head = NULL;
	while (selection != 0) {
		PrintMenu();
		scanf("%d", &selection);
		LoadData(&head);
		BiTree *L = head;
		BiTree *tmp = head;
		int tree_index;
		switch (selection) {
		case -1:
			while (head != NULL) {
				printf("TreeID:%d\tListlength:%d\t", head->TreeID, head->length);
				cout << "Preorder Traverse: ";
				PreOrderTraverse(*head);
				cout << endl;
				head = head->next;
			}
			head = L;
			break;
		case 1:
			printf("* Function Name: InitBiTree\n");
			printf("* Parameter: BiTree &T\n");
			printf("* Return: Status(int)\n");
			printf("* Use: initialize the binary tree\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head != NULL) {
				printf("Error, the tree %d already exist.\n", tree_index);
			}
			else {
				BiTree *new_tree = (BiTree *)malloc(sizeof(BiTree));
				if (InitBiTree(*new_tree) == OK) {
					printf("Inital the tree %d succeed.\n", tree_index);
					new_tree->TreeID = tree_index;
					new_tree->next = L;
					head = new_tree;
				}
				else {
					printf("ERROR, something wrong with the RAM\n");
				}
			}
			printf("\n");
			break;
		case 2:
			printf("* Function Name: DestroyBiTree\n");
			printf("* Parameter: BiTree &T\n");
			printf("* Return: Status(int)\n");
			printf("* Use: destroy the binary tree\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", tree_index);
				break;
			}
			if (head->TreeID == tree_index) {
				head = head->next;
				DestroyBiTree(*L);
				printf("List %d has been removed\n", tree_index);
				break;
			}
			while (head->next != NULL) {
				if (head->next->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head->next == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				L = head->next;
				head->next = head->next->next;
				DestroyBiTree(*L);
				printf("List %d has been removed\n", tree_index);
				head = tmp;
			}
			printf("\n");
			break;
		case 3:
			printf("* Function Name: CreateBiTree\n");
			printf("* Parameter: BiTree &T, int length, int *preorder, int *inorder, ElemType * data\n");
			printf("* Return: Status(int)\n");
			printf("* Use: create the tree using the defination data\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				int length = 0;
				cout << "please insert the length" << endl;
				cin >> length;
				int *pre = (int *)malloc(sizeof(int) * length);
				int *in = (int *)malloc(sizeof(int) * length);
				ElemType *data = (ElemType *)malloc(sizeof(ElemType) * length);
				cout << "please insert the preorder index" << endl;
				for (int i = 0; i < length; i++) cin >> pre[i];
				cout << "please insert the inorder index" << endl;
				for (int i = 0; i < length; i++) cin >> in[i];
				cout << "please insert the inorder data" << endl;
				for (int i = 0; i < length; i++) cin >> data[i];
				ClearBiTree(*head);
				CreateBiTree(*head, length, pre, in, data);
				free(pre);
				free(in);
				free(data);
				head = L;
			}

			printf("\n");
			break;
		case 4:
			printf("* Function Name: ClearBiTree\n");
			printf("* Parameter: BiTree &T\n");
			printf("* Return: Status(int)\n");
			printf("* Use: clear the BiTree\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				ClearBiTree(*head);
				head = L;
				printf("The Tree %d has been cleared.\n", tree_index);
			}
			break;
		case 5:
			printf("* Function Name: BiTreeEmpty\n");
			printf("* Parameter: const BiTree &T\n");
			printf("* Return: bool\n");
			printf("* Use: check whether the tree is empty\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				bool empty = BiTreeEmpty(*head);
				head = L;
				if (empty) {
					printf("The tree %d is empty!", tree_index);
				}
				else {
					printf("The tree %d is not empty", tree_index);
				}
			}
			break;
		case 6:
			printf("* Function Name: BiTreeDepth\n");
			printf("* Parameter: const BiTree &T\n");
			printf("* Return: int\n");
			printf("* Use: calculate the depth of the tree.\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				printf("The depth of tree %d is %d", tree_index, BiTreeDepth(*head));
				head = L;
			}
			break;
		case 7:
			printf("* Function Name: Root\n");
			printf("* Parameter: const BiTree &T\n");
			printf("* Return: BiTreeNode *\n");
			printf("* Use: return the root node of the tree.\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				BiTreeNode * root = Root(*head);
				head = L;
				if (root != NULL)
					printf("The index of the root is %d,the data is %d\n", root->index, root->data);
				else
					printf("The root is empty!");
			}
			break;
		case 8:
			printf("* Function Name: Value\n");
			printf("* Parameter: const BiTree &T, int index,ElemType &value\n");
			printf("* Return: status\n");
			printf("* Use: return the value of the node\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				ElemType value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				if (Value(*head, index, value) == OK) {
					cout << "The value is " << value << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 9:
			printf("* Function Name: Assign\n");
			printf("* Parameter: BiTree &T, int index, ElemType &value\n");
			printf("* Return: status\n");
			printf("* Use: assign given value to given node\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				ElemType value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				cout << "Please insert the desired value!" << endl;
				cin >> value;
				if (Assign(*head, index, value) == OK) {
					cout << "The value " << value << "is successfully inserted into the node "<< index << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 10:
			printf("* Function Name: Parent\n");
			printf("* Parameter: const BiTree &T, int index\n");
			printf("* Return: BiTreeNode *\n");
			printf("* Use: return the parent of the given node \n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				BiTreeNode *value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				value = Parent(*head, index);
				if (value != NULL){
					cout << "The parent data is " << value->data << " and the index is" << value->index << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 11:
			printf("* Function Name: LeftChild\n");
			printf("* Parameter: const BiTree &T, int index\n");
			printf("* Return: BiTreeNode *\n");
			printf("* Use: return the LeftChild of the given node\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				BiTreeNode *value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				value = LeftChild(*head, index);
				if (value != NULL) {
					cout << "The left child data is " << value->data << " and the index is" << value->index << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 12:
			printf("* Function Name: RightChild\n");
			printf("* Parameter: const BiTree &T, int index\n");
			printf("* Return: BiTreeNode *\n");
			printf("* Use: return the RightChild of the given node\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				BiTreeNode *value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				value = RightChild(*head, index);
				if (value != NULL) {
					cout << "The right child data is " << value->data << " and the index is" << value->index << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 13:
			printf("* Function Name: LeftSibling\n");
			printf("* Parameter: const BiTree &T, int index\n");
			printf("* Return: BiTreeNode *\n");
			printf("* Use: return the LeftSibling of the given node\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				BiTreeNode *value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				value = LeftSibling(*head, index);
				if (value != NULL) {
					cout << "The left sibling data is " << value->data << " and the index is" << value->index << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 14:
			printf("* Function Name: RightSibling\n");
			printf("* Parameter: const BiTree &T, int index\n");
			printf("* Return: BiTreeNode *\n");
			printf("* Use: return the RightSibling of the given node\n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				BiTreeNode *value;
				int index = 0;
				cout << "Please insert the desired index!" << endl;
				cin >> index;
				value = RightSibling(*head, index);
				if (value != NULL) {
					cout << "The right sibling data is " << value->data << " and the index is" << value->index << endl;
				}
				else
					cout << "Sorry, we encounter an error." << endl;
			}
			break;
		case 15:
			printf("* Function Name: InsertChild\n");
			printf("* Parameter: BiTree &T, int index, int LR, BiTree &c\n");
			printf("* Return: status\n");
			printf("* Use: Insert the BiTree to the given node \n");
			printf("please enter the id of the tree:");
			scanf("%d", &tree_index);
			while (head != NULL) {
				if (head->TreeID == tree_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the tree %d does not exist.\n", tree_index);
				head = L;
			}
			else {
				int instree_index = 0;
				cout << "please enter the id of the inserted tree" << endl;
				cin >> instree_index;
				BiTree * head2 = L;
				while (head2 != NULL) {
					if (head2->TreeID == instree_index)
						break;
					head2 = head2->next;
				}
				if (head2 == NULL) {
					printf("Error, the tree %d does not exist.\n", tree_index);
					break;
				}
				else {
					int index = 0, LR = 0;
					cout << "please insert the node index" << endl;
					cin >> index;
					cout << "L or R? (L = 0 R = 1)" << endl;
					cin >> LR;
					if (LR != 0 && LR != 1)
					{
						cout << "invalid input." << endl;
						break;
					}
					if (InsertChild(*head, index, LR, *head2) != OK)
						cout << "Sorry, we encounter an error." << endl ;
					else {
						cout << "insert complete." << endl;
					}
				}
			}
			break;
		case 0:
			cout << "Thanks for using.";
			break;
		default:
			cout << "No such selection.";
			break;
		}
		SaveData(head);
	}
}