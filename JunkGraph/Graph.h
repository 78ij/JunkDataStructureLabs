#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"
#include "common.h"

//有向无权图
typedef struct GNode {
	int nodeindex = 0;
	ElemType nodedata = 0;
	bool visited = false;// used for dfs/bfs
};

typedef struct Graph {
	vector<std::pair<GNode,LinkedList>> data;
	int GraphID = -1;
	Graph *next;
} Graph;

status CreateGraph(Graph &G, ElemType *Nodedata, int *matrix, int length);
status DestroyGraph(Graph &G);
status LocateVex(Graph &G, int index);
status GetVex(Graph &G, int index);
status PutVex(Graph &G, int index, ElemType &data);
status FirstAdjVex(Graph &G, int index, GNode &vex);
status NextAdjVex(Graph &G, int index, int &adj);
status InsertVex(Graph &G, ElemType data);
status DeleteVex(Graph &G, int index);
status InsertArc(Graph &G, int v, int w);
status DeleteArc(Graph &G, int v, int w);
status DFSTraverse(Graph &G);
status BFSTraverse(Graph &G);

#endif