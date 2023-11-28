#pragma once
#include "Edge.h"
#include <list>

#include <iostream>

/******************************************************************************************************************************************************************************************************
* Раздельной компиляции шаблонов нет: вы должны включать с помощью директивы #include определения шаблонов в каждую единицу трансляции, которая их использует. (c) A Tour of C++, adv. 7-6. Страуструп*
*******************************************************************************************************************************************************************************************************/

/*
* @brief Класс граф - содержит информацию о графе, представленную в виде таблицы смежности и количества узлов графа. Матрица смежности выполнена как вектор векторов Edge.
*/
template <typename T>
class Graph {
private:
	/*
	* @brief Поле класса Graph, содержащее в себе информацию о графе в виде матрицы смежности.
	*/
	std::vector<std::vector<Edge<T>>> adjacencyMatrix;

	/*
	* 
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
	Graph(std::vector<std::vector<Edge<T>>> adjacencyMatrix, size_t nodeCount);


	void addNode(std::vector<Edge<T>> connections);
	void deleteNode(size_t nodeNumber);
	void editNodeConnections(size_t nodeNumber, std::vector<Edge<T>> connections);

	std::vector<std::vector<Edge<T>>> getAdjacencyMatrix();
	size_t getNodeCount();

	bool ivenAlgorithm(size_t m);

	void printG(); // Вывод графа в виде матрицы - удалить после

	Graph(const Graph& other) = default;
	Graph& operator = (const Graph& other) = default;
	Graph(Graph&& other) noexcept = default;
	Graph& operator = (Graph&& other) noexcept = default;
	~Graph() = default;
};



template <typename T>
Graph<T>::Graph() : adjacencyMatrix(NULL), nodeCount(0) {};

template <typename T>
Graph<T>::Graph(std::vector<std::vector<Edge<T>>> adjacencyMatrix, size_t nodeCount) : adjacencyMatrix(adjacencyMatrix), nodeCount(nodeCount) {};

template <typename T>
void Graph<T>::addNode(std::vector<Edge<T>> connections) {
	++this->nodeCount;
	if (connections.size() != nodeCount)
		throw std::exception("Размеры массива, определяющего связи узла не совпадают с количеством узлов!");
	if (this->nodeCount == 1) {
		this->adjacencyMatrix.resize(nodeCount);
		this->adjacencyMatrix[0].resize(nodeCount);
		this->adjacencyMatrix[0][0] = connections[0];
	}
	else {
		this->adjacencyMatrix.resize(nodeCount);
		this->adjacencyMatrix[nodeCount - 1] = connections;
		for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
		{
			this->adjacencyMatrix[i].resize(nodeCount);
			this->adjacencyMatrix[i][nodeCount - 1] = connections[i];
		}
	}
};

template <typename T>
void Graph<T>::deleteNode(size_t nodeNumber) {
	if (this->nodeCount == 0)
		throw std::exception("Количество узлов графа не должно быть меньше 0!");
	if (nodeNumber >= nodeCount)
		throw std::exception("Номер узла превышает количество узлов графа!");
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

template <typename T>
void Graph<T>::editNodeConnections(size_t nodeNumber, std::vector<Edge<T>> connections) {
	if (nodeNumber >= nodeCount)
		throw std::exception("Номер узла превышает количество узлов графа!");
	if (connections.size() != nodeCount)
		throw std::exception("Размеры массива, определяющего связи узла не совпадают с количеством узлов!");
	this->adjacencyMatrix[nodeNumber] = connections;
	for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
	{
		this->adjacencyMatrix[i][nodeNumber] = connections[i];
	}
};

template <typename T>
std::vector<std::vector<Edge<T>>> Graph<T>::getAdjacencyMatrix() {
	return this->adjacencyMatrix;
};

template <typename T>
size_t Graph<T>::getNodeCount() {
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
	int preform = parents[to];
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
bool Graph<T>::ivenAlgorithm(size_t m) {
	Graph<T> newGraph = Graph<T>(this->adjacencyMatrix, this->nodeCount);
	for (size_t i = 0; i < m - 1; i++)
	{
		for (size_t j = i + 1; j < m; j++) {
			if (Graph::searchUniquePaths(*this, i, j) < m)
				return false;
		}
	}
	std::vector<Edge<T>> newNodeConnections;
	newNodeConnections.resize(newGraph.nodeCount + 1);
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

//Удалить после - вывод на экран
template <typename T>
void Graph<T>::printG() {
	for (size_t i = 0;i < this->adjacencyMatrix.size(); ++i)
	{
		for (size_t j = 0; j < this->adjacencyMatrix[i].size(); ++j)
		{
			std::cout << this->adjacencyMatrix[i][j].getInfo() << " ";
		}
		std::cout << std::endl;
	}
}