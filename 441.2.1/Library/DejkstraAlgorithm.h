#pragma once
#include "../Library/FindMinimalPathToNodesStrategy.h"
#include <typeinfo>
#include <list>

template <typename T>
class DejkstraAlgorithm : public FindMinimalPathToNodesStrategy<T> {
public:
	/*
	* @brief Переопределение метода use для нахождение минимальных длин путей для узлов. Реализует алгоритм Дейкстры.
	* @param graph - граф, в котором нужно найти минимальные пути из определённого узла.
	* @param nodeNumber - узел, который является начальной точкой для поиска маршрутов.
	* @return Вектор T, содержащий значения кратчайших путей из узла nodeNumber до каждого из узлов по очереди.
	*/
	std::vector<T> use(Graph<T> graph, size_t nodeNumber) override;

	/*
	* @brief Конструктор по умолчанию
	*/
	DejkstraAlgorithm() = default;

	/*
	* @brief Конструктор копирования
	*/
	DejkstraAlgorithm(const DejkstraAlgorithm& other) = default;

	/*
	* @brief Оператор копирования
	*/
	DejkstraAlgorithm& operator = (const DejkstraAlgorithm& other) = default;

	/*
	* @brief Конструктор перемещения
	*/
	DejkstraAlgorithm(DejkstraAlgorithm&& other) noexcept = default;

	/*
	* @brief Оператор перемещения
	*/
	DejkstraAlgorithm& operator = (DejkstraAlgorithm&& other) noexcept = default;

	/*
	* @brief Деструктор
	*/
	~DejkstraAlgorithm() = default;
};

template <typename T>
std::vector<T> DejkstraAlgorithm<T>::use(Graph<T> graph, size_t nodeNumber) {
	if (typeid(T).name() == typeid(bool).name())
		throw std::logic_error("Алгоритм не работает с булевыми переменными!");
	if (graph.getNodeCount() == 0)
		throw std::logic_error("Нельзя посчитать пути в графе без узлов!");
	if (nodeNumber >= graph.getNodeCount())
		throw std::out_of_range("Номер узла превышает количество узлов в графе!");
	for (size_t i = 0; i < graph.getNodeCount(); i++)
	{
		for (size_t j = 0; j < graph.getNodeCount(); j++) {
			if (graph.getAdjacencyMatrix()[i][j] < 0)
				throw std::logic_error("В графе присутствуют дуги с отрицательным весом!");
		}
	}

	std::vector<bool> visitedNodes = std::vector<bool>(graph.getNodeCount());
	std::vector<T> minPaths;
	std::list<size_t> indexBuffer;
	size_t k, index = 0;
	std::list<T> minimalBuffer;
	T minimal;

	for (size_t i = 0; i < graph.getNodeCount(); i++)
	{
		minPaths.push_back(graph.getAdjacencyMatrix()[nodeNumber][i]);
		visitedNodes[i] = false;
	}
	minPaths[nodeNumber] = false;
	visitedNodes[nodeNumber] = true;

	while (true) {
		k = 0;
		for (size_t i = 0; i < visitedNodes.size(); i++)
		{
			if (visitedNodes[i])
				++k;
		}
		if (k == visitedNodes.size())
			break;

		for (size_t i = 0; i < graph.getNodeCount(); i++)
		{
			if (!visitedNodes[i] && minPaths[i] != false) {
				minimalBuffer.push_back(minPaths[i]);
				indexBuffer.push_back(i);
			}
		}
		if (indexBuffer.empty())
			break;
		while (!indexBuffer.empty()) {
			index = indexBuffer.back();
			minimal = minimalBuffer.back();
			indexBuffer.pop_back();
			minimalBuffer.pop_back();
			for (size_t i = 0; i < graph.getNodeCount(); i++)
			{
				if (!visitedNodes[i] && minPaths[i] == false && graph.getAdjacencyMatrix()[index][i] != false)
					minPaths[i] = minimal + graph.getAdjacencyMatrix()[index][i];
				if (!visitedNodes[i] && graph.getAdjacencyMatrix()[index][i] != false && minPaths[i] > (minimal + graph.getAdjacencyMatrix()[index][i]))
					minPaths[i] = minimal + graph.getAdjacencyMatrix()[index][i];
			}
		}
		visitedNodes[index] = true;
	}

	return minPaths;
};