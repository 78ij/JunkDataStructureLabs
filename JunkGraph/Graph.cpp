#include "Graph.h"

status CreateGraph(Graph &G, ElemType *Nodedata, int *matrix, int length) {
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

status DestroyGraph(Graph &G) {
	for (int i = 0; i < G.data.size(); i++) {
		ClearList(G.data[i].second);
	}
	G.data.clear();
	return OK;
}

status LocateVex(Graph &G, int index) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	cout << "Data: " << G.data[index].first.nodedata << endl;
	cout << "AdjVex: ";
	ListTraverse(G.data[index].second);
	cout << endl;
	return OK;
}

status GetVex(Graph &G, int index) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	cout << "Data: " << G.data[index].first.nodedata << endl;
	return OK;
}

status PutVex(Graph &G, int index, ElemType &data) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	G.data[index].first.nodedata = data;
	return OK;
}

status FirstAdjVex(Graph &G, int index, GNode &vex) {
	if (index < 0 || index >= G.data.size()) return ERROR;
	cout << "First Adjacent Vertex: ";
	ElemType e;
	GetElem(G.data[index].second, 1, e);
	cout << e << endl;
}

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
