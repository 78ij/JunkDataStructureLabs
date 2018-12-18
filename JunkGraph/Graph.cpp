#include "Graph.h"

void write(Graph &G, FILE *fp) {
	for (int i = 0; i < G.vexs; i++) {
		for (int j = 0; j < G.vexs; j++) {
			LinkedList tmp = G.data[i].second;
			if (LocateElem(tmp, j) != 0) {
				int t = 1;
				fwrite(&t, sizeof(int), 1, fp);
			}
			else {
				int t = -1;
				fwrite(&t, sizeof(int), 1, fp);
			}
		}
	}
	for (int i = 0; i < G.vexs;  i++) {
		fwrite(&(G.data[i].first.nodedata), sizeof(ElemType), 1, fp);
	}

}

/*
* Function Name: CreateGraph
* Parameter: Graph &G, ElemType *Nodedata, int *matrix, int length
* Return: Status(int)
* Use: create a graph.
*/
status CreateGraph(Graph &G, ElemType *Nodedata, int *matrix, int length) {
	G.vexs = length;
	for (int i = 0; i < length; i++) {
		GNode node{ i,*(Nodedata + i) };
		LinkedList list;
		IntiaList(list);
		G.data.push_back(std::make_pair(node, list));
	}
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (*(matrix + length * i + j) != -1)
				Pushback(G.data[i].second, j);
		}
	}
	return OK;
}

/*
* Function Name: DestroyGraph
* Parameter: Graph &G
* Return: Status(int)
* Use: destroy a graph.
*/
status DestroyGraph(Graph &G) {
	for (int i = 0; i < G.data.size(); i++) {
		ClearList(G.data[i].second);
	}
	G.data.clear();
	return OK;
}

/*
* Function Name: LocateVex
* Parameter: Graph &G,int index
* Return: Status(int)
* Use: locate the desired node.
*/
status LocateVex(Graph &G, int index) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	cout << "Data: " << G.data[index].first.nodedata << endl;
	cout << "AdjVex: ";
	ListTraverse(G.data[index].second);
	cout << endl;
	return OK;
}

/*
* Function Name: GetVex
* Parameter: Graph &G,int index
* Return: Status(int)
* Use: get the data of the desired vertex.
*/
status GetVex(Graph &G, int index) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	cout << "Data: " << G.data[index].first.nodedata << endl;
	return OK;
}

/*
* Function Name: PutVex
* Parameter: Graph &G,int index,ElemType &data
* Return: Status(int)
* Use: assign the desired node a value
*/
status PutVex(Graph &G, int index, ElemType &data) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	G.data[index].first.nodedata = data;
	return OK;
}

/*
* Function Name: FirstAdjVex
* Parameter: Graph &G,int index
* Return: Status(int)
* Use: find the first adjacent vertex
*/
status FirstAdjVex(Graph &G, int index) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	cout << "First Adjacent Vertex: ";
	ElemType e;
	GetElem(G.data[index].second, 1, e);
	cout << e << endl;
	return OK;
}

/*
* Function Name: NextAdjVex
* Parameter: Graph &G, int index, int &adj
* Return: Status(int)
* Use: find the next adjacent vertex
*/
status NextAdjVex(Graph &G, int index, int &adj) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	int i = LocateElem(G.data[index].second, adj);
	int next;
	if (NextElem(G.data[index].second, i, next) != ERROR) {
		cout << "Next is : " << next;
		return OK;
	}
	return ERROR;
}

/*
* Function Name: InsertVex
* Parameter: Graph &G, ElemType data
* Return: Status(int)
* Use: insert a vertex
*/
status InsertVex(Graph &G, ElemType data) {
	G.vexs++;
	int i = G.data.size();
	GNode node{ i,data };
	LinkedList list;
	IntiaList(list);
	G.data.push_back(std::make_pair(node, list));
	return OK;
}

/*
* Function Name: DeleteVex
* Parameter: Graph &G, int index
* Return: Status(int)
* Use: delete the desired vertex
*/
status DeleteVex(Graph &G, int index) {
	if (index > G.data.size() - 1) return ERROR;
	G.vexs--;
	DestroyList(G.data[index].second);
	G.data.erase(G.data.begin() + index);
	for (int i = 0; i < G.data.size(); i++) {
		for (int j = 1;; j++) {
			ElemType p;
			GetElem(G.data[i].second, j, p);
			if (p > index) p--;
			if (p == index) break;
			if (j > ListLength(G.data[i].second)) break;
		}
	}
	return OK;
}

/*
* Function Name: InsertArc
* Parameter: Graph &G, int v, int w
* Return: Status(int)
* Use: insert a specified arc
*/
status InsertArc(Graph &G, int v, int w){
	if (v > G.data.size() - 1 || w > G.data.size() - 1) return ERROR;
	ElemType p;
	for (int j = 1; j <= ListLength(G.data[v].second); j++) {
		GetElem(G.data[v].second, j, p);
		if (p == w) return ERROR;
	}
	ListInsert(G.data[v].second, ListLength(G.data[v].second), w);
	return OK;
}

/*
* Function Name: DeleteArc
* Parameter: Graph &G, int v, int w
* Return: Status(int)
* Use: delete a specified arc
*/
status DeleteArc(Graph &G, int v, int w) {
	if (v > G.data.size() - 1 || w > G.data.size() - 1) return ERROR;
	ElemType p;
	int j;
	for (j = 1; j <= ListLength(G.data[v].second); j++) {
		GetElem(G.data[v].second, j, p);
		if (p == w) break;
	}
	if (j == ListLength(G.data[v].second)) return ERROR;
	else {
		ListDelete(G.data[v].second, j,p);
		return OK;
	}
}

/*
* Function Name: DFSTraverse
* Parameter: Graph &G
* Return: Status(int)
* Use: DFS Traverse
*/
status DFSTraverse(Graph &G) {
	stack<GNode> s;
	for (int i = 0; i < G.data.size(); i++)
		G.data[i].first.visited = false;
	for (int i = 0; i < G.data.size(); i++) {
		if (G.data[i].first.visited == false) {
			cout << G.data[i].first.nodedata << "(" << G.data[i].first.nodeindex << ")" << " ";
			s.push(G.data[i].first);
			G.data[s.top().nodeindex].first.visited = true;
		}
		while (!s.empty()) {
			GNode top = s.top();
			int j;
			for (j = 1; j <= ListLength(G.data[top.nodeindex].second); j++) {
				ElemType p;
				GetElem(G.data[top.nodeindex].second, j, p);
				if (G.data[p].first.visited == false) {
					s.push(G.data[p].first);
					cout << G.data[p].first.nodedata << "(" << G.data[p].first.nodeindex << ")" << " ";
					G.data[G.data[p].first.nodeindex].first.visited = true;
					break;
				}
			}
			if (j > ListLength(G.data[top.nodeindex].second)) s.pop();
		}
	}
	return OK;
}

/*
* Function Name: BFSTraverse
* Parameter: Graph &G
* Return: Status(int)
* Use: BFS Traverse
*/
status BFSTraverse(Graph &G) {
	queue<GNode> q;
	for (int i = 0; i < G.data.size(); i++)
		G.data[i].first.visited = false;
	for (int i = 0; i < G.data.size(); i++) {
		if (G.data[i].first.visited == false) {
			cout << G.data[i].first.nodedata << "(" << G.data[i].first.nodeindex << ")" << " ";
			q.push(G.data[i].first);
			G.data[i].first.visited = true;
		}
		while (!q.empty()) {
			GNode top = q.front();
			q.pop();
			for (int j = 1; j <= ListLength(G.data[top.nodeindex].second); j++) {
				ElemType p;
				GetElem(G.data[top.nodeindex].second, j, p);
				if (G.data[p].first.visited == false) {
					q.push(G.data[p].first);
					cout << G.data[p].first.nodedata << "(" << G.data[p].first.nodeindex << ")" << " ";
					G.data[G.data[p].first.nodeindex].first.visited = true;
				}
			}
		}
	}
	return OK;
}