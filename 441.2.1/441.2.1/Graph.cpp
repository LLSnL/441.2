#include "Graph.h"

Graph::Graph() : adjacencyMatrix(NULL), nodeCount(0) {};

Graph::Graph(std::vector<std::vector<Edge>> adjacencyMatrix, size_t nodeCount) : adjacencyMatrix(adjacencyMatrix), nodeCount(nodeCount) {};

void Graph::addNode(std::vector<Edge> connections) {
	++this->nodeCount;
	if (connections.size() != nodeCount)
		throw std::exception("–азмеры массива, определ€ющего св€зи узла не совпадают с количеством узлов!");
	if (this->nodeCount == 1) {
		this->adjacencyMatrix.resize(nodeCount);
		this->adjacencyMatrix[0].resize(nodeCount);
		this->adjacencyMatrix[0][0] = connections[0];
	} else {
		this->adjacencyMatrix.resize(nodeCount);
		this->adjacencyMatrix[nodeCount - 1] = connections;
		for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
		{
			this->adjacencyMatrix[i].resize(nodeCount);
			this->adjacencyMatrix[i][nodeCount - 1] = connections[i];
		}
	}
};

void Graph::deleteNode(size_t nodeNumber) {
	if (this->nodeCount == 0)
		throw std::exception(" оличество узлов графа не должно быть меньше 0!");
	if (nodeNumber >= nodeCount)
		throw std::exception("Ќомер узла превышает количество узлов графа!");
	--this->nodeCount;
	for (size_t i = nodeNumber; i < this->adjacencyMatrix.size() - 1; i++)
	{
		this->adjacencyMatrix[i] = this->adjacencyMatrix[i + 1];
	}
	for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
	{
		for (size_t j = nodeNumber; j < this->adjacencyMatrix.size() - 1; j++) {
			this->adjacencyMatrix[i][j] = this->adjacencyMatrix[i][j + 1];
		}
	}

	this->adjacencyMatrix.resize(nodeCount);
	for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
	{
		this->adjacencyMatrix[i].resize(nodeCount);
	}
};

void Graph::editNodeConnections(size_t nodeNumber, std::vector<Edge> connections) {
	if (nodeNumber >= nodeCount)
		throw std::exception("Ќомер узла превышает количество узлов графа!");
	if(connections.size() != nodeCount)
		throw std::exception("–азмеры массива, определ€ющего св€зи узла не совпадают с количеством узлов!");
	this->adjacencyMatrix[nodeNumber] = connections;
	for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
	{
		this->adjacencyMatrix[i][nodeNumber] = connections[i];
	}
};