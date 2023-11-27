#pragma once
#include <vector>

/*
* @brief Класс ребро - содержит информацию о ребре графа (присутствие/отсутствие ребра, его длину)
*/
class Edge {
	size_t size;
public:
	Edge();
	Edge(size_t size);
	void setInfo(size_t newSize);
	size_t getInfo();

	Edge(const Edge& other) = default;
	Edge& operator = (const Edge& other) = default;
	Edge(Edge&& other) noexcept = default;
	Edge& operator = (Edge&& other) noexcept = default;
	~Edge() = default;
};