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

std::vector<std::vector<Edge>> Graph::getAdjacencyMatrix() {
	return this->adjacencyMatrix;
};

size_t Graph::getNodeCount() {
	return this->nodeCount;
};

bool Graph::BFS(Graph g, size_t to, std::vector<bool>& visited, std::list<size_t>& buffer, std::vector<size_t>& parents) {
	if (buffer.empty())
		return false;

	size_t from = buffer.front();
	buffer.pop_front();
	visited[from] = true;
	if (from == to) {
		return true;
	}

	for (size_t i = 0; i < g.getNodeCount(); ++i)
	{
		if (g.getAdjacencyMatrix()[from][i].getInfo() == 0)
			continue;
		if (visited[i] == true)
			continue;
		if (find(buffer.begin(), buffer.end(), i) != buffer.end())
			continue;
		parents[i] = from;
		buffer.push_back(i);
	}

	return BFS(g, to, visited, buffer, parents);
};

void Graph::getPath(size_t from, size_t to, std::vector<size_t> parents, std::vector<size_t>& paths) {
	if (to == from) {
		paths.push_back(to);
		return;
	}
	int preform = parents[to];
	getPath(from, preform, parents, paths);

	paths.push_back(to);
};

size_t Graph::searchUniquePaths(Graph g, size_t from, size_t to) {
	size_t k = 0;
	while (true) {
		std::list<size_t> buffer;
		buffer.push_back(from);
		std::vector<bool> visited(g.getNodeCount());
		for (size_t i = 0; i < visited.size(); i++)
		{
			visited[i] = false;
		}
		std::vector<size_t> parents(g.getNodeCount());
		if (BFS(g, to, visited, buffer, parents) == true) {
			std::vector<size_t> paths;
			getPath(from, to, parents, paths);
			if (paths.size() == 2) {
				std::vector<Edge> newNode = g.getAdjacencyMatrix()[paths[0]];
				newNode[paths[1]] = 0;
				g.editNodeConnections(paths[0], newNode);
			}
			else {
				for (size_t i = 1; i < paths.size() - 1; i++)
				{
					if (paths[i] < to) {
						--to;
					}
					if (paths[i] < from) {
						--from;
					}
					g.deleteNode(paths[i]);
				}
			}
			++k;
		}
		else {
			break;
		}
	}
	return k;
};

bool Graph::ivenAlgorithm(size_t m) {
	Graph newGraph = Graph(this->adjacencyMatrix, this->nodeCount);
	for (size_t i = 0; i < m - 1; i++)
	{
		for (size_t j = i + 1; j < m; j++) {
			if (Graph::searchUniquePaths(*this, i, j) < m)
				return false;
		}
	}
	std::vector<Edge> newNodeConnections;
	newNodeConnections.resize(newGraph.nodeCount + 1);
	for (size_t i = 0; i < m; i++)
	{
		newNodeConnections[i].setInfo(1);
	}
	for (size_t i = m; i < newNodeConnections.size(); i++) {
		newNodeConnections[i].setInfo(0);
	}
	newGraph.addNode(newNodeConnections);
	for (size_t i = m; i < newGraph.getNodeCount() - 1; i++)
	{
		if (Graph::searchUniquePaths(newGraph, i, newGraph.getNodeCount() - 1) < m)
			return false;
		newNodeConnections[i].setInfo(1);
		newGraph.editNodeConnections(newGraph.getNodeCount() - 1, newNodeConnections);
	}
	return true;
};

//вывод
void Graph::printG() {
	for (size_t i = 0;i < this->adjacencyMatrix.size(); ++i)
	{
		for (size_t j = 0; j < this->adjacencyMatrix[i].size(); ++j)
		{
			std::cout << this->adjacencyMatrix[i][j].getInfo() << " ";
		}
		std::cout << std::endl;
	}
}