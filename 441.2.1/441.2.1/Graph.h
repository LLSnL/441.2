#pragma once
#include "Edge.h"
#include <list>
#include <exception>
/*
* @brief Класс граф - содержит информацию о графе, представленную в виде таблицы смежности и количества узлов графа. Матрица смежности выполнена как вектор векторов Edge.
*/
template <typename T>
class Graph {
private:
	/*
	* @brief Поле класса Graph, содержащее в себе информацию о графе - его матрицу смежности.
	*/
	std::vector<std::vector<Edge<T>>> adjacencyMatrix;

	/*
	* @brief Поле класса Graph, содержащее в себе информацию о графе - количество узлов в нём.
	*/
	size_t nodeCount;


	static bool BFS(Graph<T> g, size_t to, std::vector<bool>& visited, std::list<size_t>& buffer, std::vector<size_t>& parents);
	
	
	static size_t searchUniquePaths(Graph<T> g, size_t from, size_t to);
	
	
	static void getPath(size_t from, size_t to, std::vector<size_t> parents, std::vector<size_t>& paths);

public:
	/*
	* @brief Конструктор по умолчанию. Создает граф, содержащий вектор векторов из 0 элементов. nodeCount(кол-во узлов) = 0.
	*/
	Graph();

	/*
	* @brief Конструктор с параметрами.
	* @param adjacencyMatrix - матрица смежности, представленная вектором векторов Edge.
	* @param nodeCount - количество узлов графа.
	*/
	Graph(const std::vector<std::vector<Edge<T>>> adjacencyMatrix, const size_t nodeCount);


	void addNode(const std::vector<Edge<T>> connections);
	void deleteNode(const size_t nodeNumber);
	void editNodeConnections(const size_t nodeNumber, const std::vector<Edge<T>> connections);

	std::vector<std::vector<Edge<T>>> getAdjacencyMatrix() const;
	size_t getNodeCount() const;

	bool ivenAlgorithm(const size_t m) const;
	std::vector<T> dejkstraAlgorithm(const size_t nodeNumber) const;

	Graph(const Graph& other) = default;
	Graph& operator = (const Graph& other) = default;
	Graph(Graph&& other) noexcept = default;
	Graph& operator = (Graph&& other) noexcept = default;
	~Graph() = default;
};


template <typename T>
Graph<T>::Graph() : adjacencyMatrix(NULL), nodeCount(0) {};

template <typename T>
Graph<T>::Graph(const std::vector<std::vector<Edge<T>>> adjacencyMatrix, const size_t nodeCount) : adjacencyMatrix(adjacencyMatrix), nodeCount(nodeCount) {};

template <typename T>
void Graph<T>::addNode(const std::vector<Edge<T>> connections) {
	++this->nodeCount;
	if (connections.size() != this->getNodeCount())
		throw std::exception("Размеры массива, определяющего связи узла не совпадают с количеством узлов!");
	if (this->getNodeCount() == 1) {
		this->adjacencyMatrix.resize(this->getNodeCount());
		this->adjacencyMatrix[0].resize(this->getNodeCount());
		this->adjacencyMatrix[0][0] = connections[0];
	}
	else {
		this->adjacencyMatrix.resize(this->getNodeCount());
		this->adjacencyMatrix[this->getNodeCount() - 1] = connections;
		for (size_t i = 0; i < this->getAdjacencyMatrix().size(); i++)
		{
			this->adjacencyMatrix[i].resize(this->getNodeCount());
			this->adjacencyMatrix[i][this->getNodeCount() - 1] = connections[i];
		}
	}
};

template <typename T>
void Graph<T>::deleteNode(const size_t nodeNumber) {
	if (this->getNodeCount() == 0)
		throw std::exception("Количество узлов графа не должно быть меньше 0!");
	if (nodeNumber >= this->getNodeCount())
		throw std::exception("Номер узла превышает количество узлов графа!");
	--this->nodeCount;
	for (size_t i = nodeNumber; i < this->getAdjacencyMatrix().size() - 1; i++)
	{
		this->adjacencyMatrix[i] = this->adjacencyMatrix[i + 1];
	}
	for (size_t i = 0; i < this->getAdjacencyMatrix().size(); i++)
	{
		for (size_t j = nodeNumber; j < this->getAdjacencyMatrix().size() - 1; j++) {
			this->adjacencyMatrix[i][j] = this->adjacencyMatrix[i][j + 1];
		}
	}

	this->adjacencyMatrix.resize(this->getNodeCount());
	for (size_t i = 0; i < this->getAdjacencyMatrix().size(); i++)
	{
		this->adjacencyMatrix[i].resize(this->getNodeCount());
	}
};

template <typename T>
void Graph<T>::editNodeConnections(const size_t nodeNumber, const std::vector<Edge<T>> connections) {
	if (nodeNumber >= this->getNodeCount())
		throw std::exception("Номер узла превышает количество узлов графа!");
	if (connections.size() != this->getNodeCount())
		throw std::exception("Размеры массива, определяющего связи узла не совпадают с количеством узлов!");
	this->adjacencyMatrix[nodeNumber] = connections;
	for (size_t i = 0; i < this->getAdjacencyMatrix().size(); i++)
	{
		this->adjacencyMatrix[i][nodeNumber] = connections[i];
	}
};

template <typename T>
std::vector<std::vector<Edge<T>>> Graph<T>::getAdjacencyMatrix() const {
	return this->adjacencyMatrix;
};

template <typename T>
size_t Graph<T>::getNodeCount() const {
	return this->nodeCount;
};

template <typename T>
bool Graph<T>::BFS(Graph<T> g, size_t to, std::vector<bool>& visited, std::list<size_t>& buffer, std::vector<size_t>& parents) {
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

template <typename T>
void Graph<T>::getPath(size_t from, size_t to, std::vector<size_t> parents, std::vector<size_t>& paths) {
	if (to == from) {
		paths.push_back(to);
		return;
	}
	size_t preform = parents[to];
	getPath(from, preform, parents, paths);

	paths.push_back(to);
};

template <typename T>
size_t Graph<T>::searchUniquePaths(Graph<T> g, size_t from, size_t to) {
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
			Graph<T>::getPath(from, to, parents, paths);
			if (paths.size() == 2) {
				std::vector<Edge<T>> newNode = g.getAdjacencyMatrix()[paths[0]];
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

template <typename T>
bool Graph<T>::ivenAlgorithm(const size_t m) const {
	if (m >= this->getNodeCount())
		return false;
	Graph<T> newGraph = Graph<T>(this->getAdjacencyMatrix(), this->getNodeCount());
	for (size_t i = 0; i < m - 1; i++)
	{
		for (size_t j = i + 1; j < m; j++) {
			if (Graph::searchUniquePaths(*this, i, j) < m)
				return false;
		}
	}
	std::vector<Edge<T>> newNodeConnections;
	newNodeConnections.resize(newGraph.getNodeCount() + 1);
	for (size_t i = 0; i < m; i++)
	{
		newNodeConnections[i].setInfo(true);
	}
	for (size_t i = m; i < newNodeConnections.size(); i++) {
		newNodeConnections[i].setInfo(false);
	}
	newGraph.addNode(newNodeConnections);
	for (size_t i = m; i < newGraph.getNodeCount() - 1; i++)
	{
		if (Graph::searchUniquePaths(newGraph, i, newGraph.getNodeCount() - 1) < m)
			return false;
		newNodeConnections[i].setInfo(true);
		newGraph.editNodeConnections(newGraph.getNodeCount() - 1, newNodeConnections);
	}
	return true;
};

template <typename T>
std::vector<T> Graph<T>::dejkstraAlgorithm(const size_t nodeNumber) const {
	if(nodeNumber >= this->getNodeCount())

	std::vector<bool> visited = std::vector<bool>(this->getNodeCount());
	std::vector<T> minPaths = std::vector<T>(this->getNodeCount());
};