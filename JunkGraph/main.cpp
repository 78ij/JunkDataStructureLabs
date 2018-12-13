#include "Graph.h"

int main() {
	int matrix[] = { -1,1,1,1,-1,-1,-1,-1,-1 };
	ElemType data[] = { 0,1,2 };
	Graph g;
	CreateGraph(g, data, matrix, 3);
	int adj = 1;
	NextAdjVex(g,0,adj);
	return 0;
}