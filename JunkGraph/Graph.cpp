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

status InsertVex(Graph &G, ElemType data) {
	int i = G.data.size();
	GNode node{ i,data };
	LinkedList list;
	IntiaList(list);
	G.data.push_back(std::make_pair(node, list));
	return OK;
}

status DeleteVex(Graph &G, int index) {
	if (index > G.data.size() - 1) return ERROR;
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

status DFSTraverse(Graph &G) {
	stack<GNode> s;
	for (int i = 0; i < G.data.size(); i++)
		G.data[i].first.visited = false;
	for (int i = 0; i < G.data.size(); i++) {
		if (G.data[i].first.visited == false) {
			cout << G.data[i].first.nodedata << " ";
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
					cout << G.data[p].first.nodedata << " ";
					G.data[G.data[p].first.nodeindex].first.visited = true;
					break;
				}
			}
			if (j > ListLength(G.data[top.nodeindex].second)) s.pop();
		}
	}
	return OK;
}

status BFSTraverse(Graph &G) {
	queue<GNode> q;
	for (int i = 0; i < G.data.size(); i++)
		G.data[i].first.visited = false;
	for (int i = 0; i < G.data.size(); i++) {
		if (G.data[i].first.visited == false) {
			cout << G.data[i].first.nodedata << " ";
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
					cout << G.data[p].first.nodedata << " ";
					G.data[G.data[p].first.nodeindex].first.visited = true;
				}
			}
		}
	}
	return OK;
}