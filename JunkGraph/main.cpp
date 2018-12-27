#include "Graph.h"

void PrintMenu(void) {
	/*
	* Function Name: PrintMenu
	* Parameter: None
	* Return: None
	* Use: Print the main menu
	*/

	printf("\n+-----------------------------------------------------+\n");
	printf("|                   *THE* DAG DEMO                    |\n");
	printf("|                                                     |\n");
	printf("|                     Functions                       |\n");
	printf("|                                                     |\n");
	printf("|      1.CreateGraph            2.DestroyGraph        |\n");
	printf("|      3.LocateVex              4.GetVex              |\n");
	printf("|      5.PutVex                 6.FirstAdjVex         |\n");
	printf("|      7.NextAdjVex             8.InsertVex           |\n");
	printf("|      9.DeleteVex              10.InsertArc          |\n");
	printf("|     11.DeleteArc              12.DFSTraverse        |\n");
	printf("|     13.BFSTraverse                                  |\n");
	printf("|                                                     |\n");
	printf("|                      0.Exit                         |\n");
	printf("|                                                     |\n");
	printf("|                      78ij@8102                      |\n");
	printf("|                                                     |\n");
	printf("+-----------------------------------------------------+\n");
	printf("\n");

}

status LoadData(Graph **head) {
	/*
	* Function Name: LoadData
	* Parameter: none
	* Return Status(int)
	* Use: load data from file
	*/
	int *matrix = NULL;
	ElemType *nodedata = NULL;
	FILE *fp = fopen("SLDB", "r");
	if (fp == NULL)
		return ERROR;

	int size = 0;
	int count = 0;
	Graph *tmp = new Graph();
	int ID = 0;
	size = fread(&ID, sizeof(int), 1, fp);
	if (size == 0) {
		free(tmp);
		return OK;
	}
	tmp->GraphID = ID;
	size = fread(&ID, sizeof(int), 1, fp);
	tmp->vexs = ID;
	count++;
	size = tmp->vexs;
	if (size != 0) {
		matrix = (int *)malloc(size * size  * sizeof(int));
		nodedata = (ElemType *)malloc(size * sizeof(ElemType));
		fread(matrix, sizeof(int), size * size, fp);
		fread(nodedata, sizeof(int), size, fp);
		CreateGraph(*tmp, nodedata, matrix,size);
		free(matrix);
		free(nodedata);
	}

	*head = tmp;

	while (1) {
		Graph *tmp = new Graph();
		size = fread(&ID, sizeof(int), 1, fp);
		if (size == 0) {
			free(tmp);
			break;
		}
		tmp->GraphID = ID;
		size = fread(&ID, sizeof(int), 1, fp);
		tmp->vexs = ID;
		count++;
		size = tmp->vexs;
		if (size != 0) {
			matrix = (int *)malloc(size * size * sizeof(int));
			nodedata = (ElemType *)malloc(size * sizeof(ElemType));
			fread(matrix, sizeof(int), size * size, fp);
			fread(nodedata, sizeof(int), size, fp);
			CreateGraph(*tmp, nodedata, matrix, size);
			free(matrix);
			free(nodedata);
		}
		(*head)->next = tmp;
		*head = (*head)->next;
	}
	(*head)->next = NULL;
	*head = tmp;
	fclose(fp);
	return OK;
}

status SaveData(Graph *head) {
	/*
	* Function Name: SaveData
	* Parameter: BiTree *heAD
	* Return: Status(int)
	* Use: save data to file
	*/

	FILE *fp = fopen("SLDB", "w");
	if (fp == NULL)
		return ERROR;
	Graph *L = head, *p = head;
	while (L != NULL) {
		fwrite(&(L->GraphID), sizeof(int), 1, fp);
		fwrite(&(L->vexs), sizeof(int), 1, fp);
		write(*L,fp);
		p = L->next;
		DestroyGraph(*L);
		delete(L);
		L = p;
	}

	fclose(fp);
	return OK;
}


int main() {
	int selection = -1;
	Graph *head = NULL;
	while (selection != 0) {
		PrintMenu();
		scanf("%d", &selection);
		LoadData(&head);
		Graph *L = head;
		Graph *tmp = head;
		int graph_index;
		switch (selection) {
		case -1:
			while (head != NULL) {
				printf("GraphID:%d\tVexs:%d\t", head->GraphID, head->vexs);
				cout << "DFS Traverse: ";
				DFSTraverse(*head);
				cout << endl;
				head = head->next;
			}
			head = L;
			break;
		case 1:
			printf("* Function Name: CreateGraph\n");
			printf("* Parameter: Graph &G, ElemType *Nodedata, int *matrix, int length\n");
			printf("* Return: Status(int)\n");
			printf("* Use: create a graph.\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head != NULL) {
				printf("Error, the tree %d already exist.\n", graph_index);
			}
			else {
				Graph *new_graph = new Graph();
				new_graph->data = vector<std::pair<GNode, LinkedList>>();
				int length;
				cout << "Please insert the graph vertex count:" << endl;
				cin >> length;
				int *matrix = (int *)malloc(sizeof(int) * length * length);
				ElemType *nodedata = (ElemType *)malloc(sizeof(ElemType) * length);
				cout << "Please insert the graph adjacent matrix:" << endl;
				for (int i = 0; i < length * length; i++) {
					cin >> matrix[i];
				}
				cout << "Please insert the node data" << endl;
				for (int i = 0; i < length; i++) {
					cin >> nodedata[i];
				}
				if (CreateGraph(*new_graph, nodedata, matrix, length) == OK) {
					printf("Creation the graph %d succeed.\n", graph_index);
					new_graph->GraphID = graph_index;
					new_graph->next = L;
					head = new_graph;
				}
				else {
					printf("ERROR, something wrong with the RAM\n");
				}
				free(matrix);
				free(nodedata);
			}

			printf("\n");
			break;
		case 2:
			printf("* Function Name: DestroyGraph\n");
			printf("* Parameter: Graph &G\n");
			printf("* Return: Status(int)\n");
			printf("* Use: destroy a graph.\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			if (head == NULL) {
				printf("Error, the Graph %d does not exist.\n", graph_index);
				break;
			}
			if (head->GraphID == graph_index) {
				head = head->next;
				DestroyGraph(*L);
				printf("Graph %d has been removed\n", graph_index);
				break;
			}
			while (head->next != NULL) {
				if (head->next->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head->next == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				L = head->next;
				head->next = head->next->next;
				DestroyGraph(*L);
				printf("Graph %d has been removed\n", graph_index);
				head = tmp;
			}
			printf("\n");
			break;
		case 3:
			printf("* Function Name: LocateVex\n");
			printf("* Parameter: Graph &G,int index\n");
			printf("* Return: Status(int)\n");
			printf("* Use: locate the desired node.\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int index;
				cout << "please insert the index" << endl;
				cin >> index;
				if (LocateVex(*head, index) != OK) {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 4:
			printf("* Function Name: GetVex\n");
			printf("* Parameter: Graph &G,int index\n");
			printf("* Return: Status(int)\n");
			printf("* Use: get the data of the desired vertex.\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				ElemType data;
				cout << "please insert the data" << endl;
				cin >> data;
				if (GetVex(*head, data) != OK) {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 5:
			printf("* Function Name: PutVex\n");
			printf("* Parameter: Graph &G,int index,ElemType &data\n");
			printf("* Return: Status(int)\n");
			printf("* Use: assign the desired node a value\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int index;
				ElemType data;
				cout << "please insert the index" << endl;
				cin >> index;
				cout << "please insert the data." << endl;
				cin >> data;
				if (PutVex(*head, index, data) == OK) {
					cout << "successfully insert data " << data << "to vertex index " << index << endl;
				}
				else {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 6:
			printf("* Function Name: FirstAdjVex\n");
			printf("* Parameter: Graph &G,int index\n");
			printf("* Return: Status(int)\n");
			printf("* Use: find the first adjacent vertex\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int index;
				cout << "please insert the index" << endl;
				cin >> index;
				if (FirstAdjVex(*head,index) != OK) {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 7:
			printf("* Function Name: NextAdjVex\n");
			printf("* Parameter: Graph &G, int index, int &adj\n");
			printf("* Return: Status(int)\n");
			printf("* Use: find the next adjacent vertex\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int index,w;
				cout << "please insert the index" << endl;
				cin >> index;
				cout << "please insert the adjacent index" << endl;
				cin >> w;
				if (NextAdjVex(*head, index,w) != OK) {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 8:
			printf("* Function Name: InsertVex\n");
			printf("* Parameter: Graph &G, ElemType data\n");
			printf("* Return: Status(int)\n");
			printf("* Use: insert a vertex\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				ElemType data;
				cout << "please insert the data" << endl;
				cin >> data;
				if (InsertVex(*head, data) == OK) {
					cout << "node with data " << data << "has been successfully inserted." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 9:
			printf("* Function Name: DeleteVex\n");
			printf("* Parameter: Graph &G, int index\n");
			printf("* Return: Status(int)\n");
			printf("* Use: delete the desired vertex\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int index;
				cout << "please insert the index" << endl;
				cin >> index;
				if (DeleteVex(*head, index) == OK) {
					cout << "node " << index << "has been successfully deleted." << endl;
				}
				else {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 10:
			printf("* Function Name: InsertArc\n");
			printf("* Parameter: Graph &G, int v, int w\n");
			printf("* Return: Status(int)\n");
			printf("* Use: insert a specified arc\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int v,w;
				cout << "please insert the index1" << endl;
				cin >> v;
				cout << "please insert the index2" << endl;
				cin >> w;
				if (InsertArc(*head, v,w) == OK) {
					cout << "arc with nodes " << v << "and " << w << " has been successfully inserted." << endl;
				}
				else {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 11:
			printf("* Function Name: DeleteArc\n");
			printf("* Parameter: Graph &G, int v, int w\n");
			printf("* Return: Status(int)\n");
			printf("* Use: delete a specified arc\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				int v, w;
				cout << "please insert the index1" << endl;
				cin >> v;
				cout << "please insert the index2" << endl;
				cin >> w;
				if (DeleteArc(*head, v, w) == OK) {
					cout << "arc with nodes " << v << "and " << w << " has been successfully deleted." << endl;
				}
				else {
					cout << "sorry, we encounter an ERROR." << endl;
				}
				head = L;
			}
			printf("\n");
			break;
		case 12:
			printf("* Function Name: DFSTraverse\n");
			printf("* Parameter: Graph &G\n");
			printf("* Return: Status(int)\n");
			printf("* Use: DFS Traverse\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				cout << "DFS Traverse: ";
				DFSTraverse(*head);
				head = L;
			}
			printf("\n");
			break;
		case 13:
			printf("* Function Name: BFSTraverse\n");
			printf("* Parameter: Graph &G\n");
			printf("* Return: Status(int)\n");
			printf("* Use: BFS Traverse\n");
			printf("please enter the id of the graph:");
			scanf("%d", &graph_index);
			while (head != NULL) {
				if (head->GraphID == graph_index)
					break;
				head = head->next;
			}
			if (head == NULL) {
				printf("Error, the graph %d does not exist.\n", graph_index);
				head = L;
			}
			else {
				cout << "BFS Traverse: ";
				DFSTraverse(*head);
				head = L;
			}
			printf("\n");
			break;
		}
		SaveData(head);
	}
}