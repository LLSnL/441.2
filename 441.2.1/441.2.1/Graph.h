#pragma once
#include <stdexcept>
#include <vector>
#include <limits>
#include <cmath>
/*
* @brief Класс граф - содержит информацию о неориентированном графе, представленную в виде таблицы длин рёбер между узлами (если ребра нет, то его длина записывается как 0) и количества узлов графа.
*/
template <typename T>
class Graph {
private:
	/*
	* @brief Поле класса Graph, содержащее в себе информацию о графе - его таблицу длин рёбер между узлами.
	*/
	std::vector<std::vector<T>> adjacencyMatrix;

	/*
	* @brief Поле класса Graph, содержащее в себе информацию о графе - количество узлов в нём.
	*/
	size_t nodeCount;
public:
	/*
	* @brief Конструктор по умолчанию. Создает граф, содержащий вектор векторов из 0 элементов. nodeCount(кол-во узлов) = 0.
	*/
	Graph();

	/*
	* @brief Конструктор с параметрами.
	* @param adjacencyMatrix - матрица длин рёбер между зулами, представленная вектором векторов T.
	* @param nodeCount - количество узлов графа.
	*/
	Graph(const std::vector<std::vector<T>> adjacencyMatrix, const size_t nodeCount);

	/*
	* @brief Метод, позволяющий добавить узел в граф. Узел добавляется в конец (номер нового узла = nodeCount).
	* @param connections - вектор, содержащий инфомацию о рёбрах нового узла.
	*/
	void addNode(const std::vector<T> connections);

	/*
	* @brief Метод, позволяющий удалить узел из графа.
	* @param nodeNumber - номер узла, который необходимо удалить.
	*/
	void deleteNode(const size_t nodeNumber);

	/*
	* @brief Метод, позволяющий отредактировать связи конкретного узла в графе
	* @param nodeNumber - номер узла, в котором необходимо поменять связи.
	* @param connections - вектор, содержащий инфомацию о рёбрах изменённого узла.
	*/
	void editNodeConnections(const size_t nodeNumber, const std::vector<T> connections);

	/*
	* @brief Геттер adjacencyMatrix.
	* @return Матрица длин рёбер графа в виде вектора векторов T.
	*/
	std::vector<std::vector<T>> getAdjacencyMatrix() const;

	/*
	* @brief Геттер nodeCount.
	* @return Количество узлов в графе.
	*/
	size_t getNodeCount() const;

	/*
	* @brief Конструктор копирования
	*/
	Graph(const Graph& other) = default;

	/*
	* @brief Оператор копирования
	*/
	Graph& operator = (const Graph& other) = default;

	/*
	* @brief Конструктор перемещения
	*/
	Graph(Graph&& other) noexcept = default;

	/*
	* @brief Оператор перемещения
	*/
	Graph& operator = (Graph&& other) noexcept = default;

	/*
	* @brief Деструктор
	*/
	~Graph() = default;
};


template <typename T>
Graph<T>::Graph() : adjacencyMatrix(), nodeCount(0) {};

template <typename T>
Graph<T>::Graph(const std::vector<std::vector<T>> adjacencyMatrix, const size_t nodeCount) {
	if (adjacencyMatrix.size() != nodeCount)
		throw std::logic_error("Размеры матрицы несовпадают с заявленным количеством узлов!");
	for (size_t i = 0; i < nodeCount; i++)
	{
		if(adjacencyMatrix[i].size() != nodeCount)
			throw std::logic_error("Размеры матрицы несовпадают с заявленным количеством узлов!");
	}
	for (size_t i = 0; i < nodeCount; i++)
	{
		for (size_t j = i; j < nodeCount; j++) {
			if (std::fabsl(adjacencyMatrix[i][j] - adjacencyMatrix[j][i]) > std::numeric_limits<T>::epsilon())
				throw std::logic_error("Граф должен быть неориентированным!");
		}
	}
	this->adjacencyMatrix = adjacencyMatrix;
	this->nodeCount = nodeCount;
};

template <typename T>
void Graph<T>::addNode(const std::vector<T> connections) {
	++this->nodeCount;
	if (connections.size() != this->getNodeCount())
		throw std::logic_error("Размеры массива, определяющего связи узла не совпадают с количеством узлов!");
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
		throw std::logic_error("Количество узлов графа не должно быть меньше 0!");
	if (nodeNumber >= this->getNodeCount())
		throw std::out_of_range("Номер узла превышает количество узлов графа!");
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
void Graph<T>::editNodeConnections(const size_t nodeNumber, const std::vector<T> connections) {
	if (this->nodeCount == 0)
		throw std::logic_error("Нельзя изменять связи в графе без узлов!");
	if (nodeNumber >= this->getNodeCount())
		throw std::out_of_range("Номер узла превышает количество узлов графа!");
	if (connections.size() != this->getNodeCount())
		throw std::logic_error("Размеры массива, определяющего связи узла не совпадают с количеством узлов!");
	this->adjacencyMatrix[nodeNumber] = connections;
	for (size_t i = 0; i < this->getAdjacencyMatrix().size(); i++)
	{
		this->adjacencyMatrix[i][nodeNumber] = connections[i];
	}
};

template <typename T>
std::vector<std::vector<T>> Graph<T>::getAdjacencyMatrix() const {
	return this->adjacencyMatrix;
};

template <typename T>
size_t Graph<T>::getNodeCount() const {
	return this->nodeCount;
};