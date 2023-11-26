#pragma once
#include "Edge.h"

class Graph {
public: // public for now
	std::vector<std::vector<Edge>> adjacencyMatrix;
	size_t nodeCount;
public:
	Graph();
	Graph(std::vector<std::vector<Edge>> adjacencyMatrix, size_t nodeCount);
	void addNode(std::vector<Edge> connections);
	void deleteNode(size_t nodeNumber);
	void editNodeConnections(size_t nodeNumber, std::vector<Edge> connections);

	Graph(const Graph& other) = default;
	Graph& operator = (const Graph & other) = default;
	Graph(Graph && other) noexcept = default;
	Graph& operator = (Graph && other) noexcept = default;
	~Graph() = default;
};