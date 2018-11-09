#include "LinkedList.h"

void PrintMenu(void) {
	/*
	* Function Name: PrintMenu
	* Parameter: None
	* Return: None
	* Use: Print the main menu
	*/

	printf("\n+---------------------------------------------------+\n");
	printf("|                *THE* LINEAR LIST DEMO               |\n");
	printf("|                                                     |\n");
	printf("|                     Functions                       |\n");
	printf("|                                                     |\n");
	printf("|      1.InitalList             2.DestroyList         |\n");
	printf("|      3.ClearList              4.IsListEmpty         |\n");
	printf("|      5.ListLength             6.GetElem             |\n");
	printf("|      7.LocateElem             8.PriorElem           |\n");
	printf("|      9.NextElem              10.ListInsert          |\n");
	printf("|     11.ListDelete            12.ListTraverse        |\n");
	printf("|                                                     |\n");
	printf("|                      0.Exit                         |\n");
	printf("|                                                     |\n");
	printf("|                      78ij@8102                      |\n");
	printf("|                                                     |\n");
	printf("+-----------------------------------------------------+\n");
	printf("\n");

}

status LoadData(LinkedList **head) {
	/*
	* Function Name: LoadData
	* Parameter: std::vector<LinkedList> lists
	* Return Status(int)
	* Use: load data from file
	*/
	FILE *fp = fopen("SLDB", "rb");
	if (fp == NULL)
		return ERROR;

	int size = 0;
	int count = 0;
	LinkedList *tmp = (LinkedList *)malloc(sizeof(LinkedList));
	size = fread(tmp, sizeof(LinkedList), 1, fp);
	tmp->head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	tmp->head->next = NULL;
	if (size == 0)
		return OK;
	count++;
	LinkedListNode *ele = tmp->head;
	LinkedListNode *ele2;
	for (int i = 0; i < tmp->length; i++) {
		ele2 = (LinkedListNode *)malloc(sizeof(LinkedListNode));
		fread(ele2, sizeof(LinkedListNode), 1, fp);
		ele->next = ele2;
		ele = ele->next;
	}
	ele->next = NULL;
	*head = tmp;


	while (1) {
		LinkedList *tmp = (LinkedList *)malloc(sizeof(LinkedList));
		size = fread(tmp, sizeof(LinkedList), 1, fp);
		if (size == 0)
			break;
		count++;
		tmp->head = (LinkedListNode *)malloc(sizeof(LinkedListNode));
		tmp->head->next = NULL;
		LinkedListNode *ele3 = tmp->head;
		LinkedListNode *ele4;
		for (int i = 0; i < tmp->length; i++) {
			ele4 = (LinkedListNode *)malloc(sizeof(LinkedListNode));
			fread(ele4, sizeof(LinkedListNode), 1, fp);
			ele3->next = ele4;
			ele3 = ele3->next;
		}
		ele3->next = NULL;
		(*head)->next = tmp;
		*head = (*head)->next;
	}
	(*head)->next = NULL;
	*head = tmp;
	fclose(fp);
	return OK;
}

status SaveData(LinkedList *head) {
	/*
	* Function Name: SaveData
	* Parameter: vector<LinkedList> lists
	* Return: Status(int)
	* Use: save data to file
	*/

	FILE *fp = fopen("SLDB", "wb");
	if (fp == NULL)
		return ERROR;

	LinkedList *L = head, *p = head;
	while (L != NULL) {
		fwrite(L, sizeof(LinkedList), 1, fp);
		LinkedListNode *ele = L->head->next;
		while (ele != NULL) {
			fwrite(ele,sizeof(LinkedListNode), 1, fp);
			ele = ele->next;
		}
		p = L->next;
		DestroyList(*L);
		L = p;
	}

	fclose(fp);
	return OK;
}


int main() {
	int selection = -1;
	LinkedList *head = NULL;
	while (selection != 0) {
		PrintMenu();
		scanf("%d", &selection);
		LoadData(&head);
		LinkedList *L = head;
		LinkedList *tmp = head;
		int list_index;
		switch (selection) {
		case -1: //for debug purposes
			while (head != NULL) {
				printf("ListID:%d\tListlength:%d\t\n", head->ListID, head->length);
				head = head->next;
			}
			head = L;
			break;
		case 1:
			printf("* Function Name: InitaList\n");
			printf("* Parameter: LinkedList &L\n");
			printf("* Return: Status(int)\n");
			printf("* Use: initialize the linear list\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head != NULL) {
				printf("Error, the list %d already exist.\n", list_index);
			}
			else {
				LinkedList *new_list = (LinkedList *)malloc(sizeof(LinkedList));
				if (IntiaList(*new_list) == OK) {
					printf("Inital the list %d succeed.\n", list_index);
					new_list->ListID = list_index;
					new_list->next = L;
					head = new_list;
				}
				else {
					printf("ERROR, something wrong with the RAM\n");
				}
			}
			printf("\n");
			break;
		case 2:
			printf("/*\n");
			printf("* Function Name: DestroyList\n");
			printf("* Parameter: LinkedList &L\n");
			printf("* Return: Status(int)\n");
			printf("* Use: destroy the linear list\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				break;
			}
			if (head->ListID == list_index) {
				head = head->next;
				DestroyList(*L);
				printf("List %d has been removed\n", list_index);
				break;
			}
			while (head->next != NULL) {
				if (head->next->ListID == list_index)
					break;
				head = head->next;
			}
			if (head->next == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				L = head->next;
				head->next = head->next->next;
				DestroyList(*L);
				printf("List %d has been removed\n", list_index);
				head = tmp;
			}
			printf("\n");
			break;
		case 3:
			printf("* Function Name: ClearList\n");
			printf("* Parameter: LinkedList &L\n");
			printf("* Return: Status(int)\n");
			printf("* Use: make the list empty\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				ClearList(*head);
				head = L;
				printf("the list %d has been cleared.\n", list_index);
			}

			printf("\n");
			break;
		case 4:
			printf("* Function Name: ListEmpty\n");
			printf("* Parameter: const LinkedList &L\n");
			printf("* Return: bool\n");
			printf("* Use: check if the list is empty.\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				bool isempty = ListEmpty(*head);
				head = L;
				if (isempty)
					printf("the list %d is empty.\n", list_index);
				else
					printf("the list %d is not empty.\n", list_index);

			}

			printf("\n");
			break;
		case 5:
			printf("* Function Name: ListLength\n");
			printf("* Parameter: LinkedList &L\n");
			printf("* Return: int\n");
			printf("* Use: returns the length of the list.\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				int length = ListLength(*head);
				head = L;
				printf("the list %d's length is %d.\n", list_index, length);
			}
			printf("\n");
			break;
		case 6:
			printf("* Function Name: GetElem\n");
			printf("* Parameter: const LinkedList &L, int i ElemType &e\n");
			printf("* Return: Status(int)\n");
			printf("* Use: get the i-th element of the list(i starts from 1)\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				printf("please enter the element number:\n");
				int num;
				ElemType value;
				scanf("%d", &num);
				status res = GetElem(*head, num, value);
				head = L;

				if (res == ERROR) {
					printf("Sorry, your number is out of bound.\n");
					break;
				}
				else
					printf("the element value is %d.\n", value);

			}
			printf("\n");
			break;
		case 7:
			printf("* Function Name: LocateElem\n");
			printf("* Parameter: const LinkedList &L, const ElemType &e\n");
			printf("* Return: int\n");
			printf("* Use: return the number of the element that equals the parameter(number starts from 1)\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				printf("please enter the element value:\n");
				ElemType value;
				scanf("%d", &value);
				int res = LocateElem(*head, value);
				head = L;

				if (res == 0) {
					printf("Sorry, no such element.\n");
					break;
				}
				else
					printf("the element number is %d.\n", res);

			}
			printf("\n");
			break;
		case 8:
			printf("* Function Name: PriorElem\n");
			printf("* Parameter: const LinkedList &L, ElemType &cur_e, ElemType &pre_e\n");
			printf("* Return: Status(int)\n");
			printf("* Use: get the the prior element of the specified element, pass it using parameter.\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				printf("please enter the element value:\n");
				ElemType cur;
				ElemType value;
				scanf("%d", &cur);
				status res = PriorElem(*head, cur, value);
				head = L;

				if (res == ERROR) {
					printf("Sorry, we encounter an error.\n");
					break;
				}
				else
					printf("the prior element number is %d.\n", value);

			}
			printf("\n");
			break;
		case 9:
			printf("* Function Name: NextElem\n");
			printf("* Parameter: const LinkedList &L, ElemType &cur_e, ElemType &next_e\n");
			printf("* Return: Status(int)\n");
			printf("* Use: get the the next element of the specified element, pass it using parameter.\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				printf("please enter the element value:\n");
				ElemType cur;
				ElemType value;
				scanf("%d", &cur);
				status res = NextElem(*head, cur, value);
				head = L;

				if (res == ERROR) {
					printf("Sorry, we encounter an error.\n");
					break;
				}
				else
					printf("the next element number is %d.\n", value);

			}
			printf("\n");
			break;
		case 10:
			printf("* Function Name: ListInsert\n");
			printf("* Parameter: LinkedList &L, int i, ElemType &e\n");
			printf("* Return: Status(int)\n");
			printf("* Use: insert an element after the specifyed number(the list must be non-empty)\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				int num;
				ElemType e;
				printf("please input the number of the element\n");
				scanf("%d", &num);
				printf("please input the inserted value:\n");
				scanf("%d", &e);
				status res = ListInsert(*head, num, e);
				head = L;
				if (res == ERROR) {
					printf("Sorry, we encounter an error.\n");
					break;
				}
				else
					printf("value %d has been successfully insert to the %d position of %d list.", e, num, list_index);
			}
			printf("\n");
			break;
		case 11:
			printf("* Function Name: ListDelete\n");
			printf("* Parameter: LinkedList &L, int i, ElemType &e\n");
			printf("* Return: Status(int)\n");
			printf("* Use: Delete the specified element.\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				int num;
				printf("please input the number of the element\n");
				scanf("%d", &num);
				ElemType e;
				status res = ListDelete(*head, num, e);
				head = L;
				if (res == ERROR) {
					printf("Sorry, we encounter an error.\n");
					break;
				}
				else
					printf("value %d has benn successfully delete, it's in %d position of %d list.", e, num, list_index);
			}
			printf("\n");
			break;
		case 12:
			printf("* Function Name: ListTraverse\n");
			printf("* Parameter: const LinkedList &L\n");
			printf("* Return: Status(int)\n");
			printf("* Use: Traverse the list and output its elements.\n");
			printf("please enter the id of the list:");
			scanf("%d", &list_index);
			while (head != NULL) {
				if (head->ListID == list_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the list %d does not exist.\n", list_index);
				head = L;
			}
			else {
				printf("Traverse the %d-th list:\n", list_index);
				ListTraverse(*head);
				head = L;
			}
			printf("\n");
			break;
		case 0:
			printf("Thank you for using~\n");
			break;
		default:
			printf("no such selection.\n");
			break;
		}
		SaveData(head);
	}
	return 0;
}

