#include "Graph.h"

void printG(Graph a);

int main(){
	std::vector<Edge> y = {0};
	std::vector<Edge> y2 = { 1, 0 };
	std::vector<Edge> y3 = { 0, 1, 0 };
	std::vector<Edge> y4 = { 1, 1, 0 , 0 };
	std::vector<Edge> y42 = { 1,1,1,0 };
	std::vector<Edge> y32 = { 1, 1, 0, 1};
	Graph a = Graph();
	a.addNode(y);
	//printG(a);
	a.deleteNode(0);
	//printG(a);
	a.addNode(y);
	a.addNode(y2);
	a.addNode(y3);
	a.addNode(y4);
	printG(a);
	a.editNodeConnections(2, y32);
	printG(a);
	a.deleteNode(1);
	//printG(a);
	a.addNode(y42);
	//printG(a);

	return 0;
}

void printG(Graph a) {
	for (size_t i = 0;i < a.adjacencyMatrix.size(); ++i)
	{
		for (size_t j = 0; j < a.adjacencyMatrix[i].size(); ++j)
		{
			std::cout << a.adjacencyMatrix[i][j].getInfo() << " ";
		}
		std::cout << std::endl;
	}
}