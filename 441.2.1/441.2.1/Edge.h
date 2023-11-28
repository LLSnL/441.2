#pragma once
#include <vector>

/*
* @brief Класс ребро - содержит информацию о ребре графа (присутствие/отсутствие ребра, его длину)
*/
template <typename T>
class Edge {
	T size;
public:
	Edge();
	Edge(T size);
	void setInfo(T newSize);
	T getInfo();

	Edge(const Edge& other) = default;
	Edge& operator = (const Edge& other) = default;
	Edge(Edge&& other) noexcept = default;
	Edge& operator = (Edge&& other) noexcept = default;
	~Edge() = default;
};


template <typename T>
Edge<T>::Edge() : size(NULL) {};

template <typename T>
Edge<T>::Edge(T size) : size(size) {};

template <typename T>
void Edge<T>::setInfo(T newSize) {
	this->size = newSize;
};

template <typename T>
T Edge<T>::getInfo() {
	return this->size;
};
