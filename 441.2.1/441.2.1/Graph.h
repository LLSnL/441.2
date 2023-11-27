#pragma once
#include "Edge.h"
#include <list>

#include <iostream>

class Graph {
private:
	std::vector<std::vector<Edge>> adjacencyMatrix;
	size_t nodeCount;

	static bool BFS(Graph g, size_t to, std::vector<bool>& visited, std::list<size_t>& buffer, std::vector<size_t>& parents);
	static size_t searchUniquePaths(Graph g, size_t from, size_t to);
	static void getPath(size_t from, size_t to, std::vector<size_t> parents, std::vector<size_t>& paths);

public:
	Graph();
	Graph(std::vector<std::vector<Edge>> adjacencyMatrix, size_t nodeCount);
	void addNode(std::vector<Edge> connections);
	void deleteNode(size_t nodeNumber);
	void editNodeConnections(size_t nodeNumber, std::vector<Edge> connections);

	std::vector<std::vector<Edge>> getAdjacencyMatrix();
	size_t getNodeCount();

	bool ivenAlgorithm(size_t m);

	void printG(); // Вывод графа в виде матрицы смежности

	Graph(const Graph& other) = default;
	Graph& operator = (const Graph& other) = default;
	Graph(Graph&& other) noexcept = default;
	Graph& operator = (Graph&& other) noexcept = default;
	~Graph() = default;
};