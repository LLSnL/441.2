#pragma once
#include "../Library/DejkstraAlgorithm.h"

/*
* @brief Контекст, использующий стратегию для решения задачи поиска кратчайших путей до узлов графа.
*/
template <typename T>
class FindMinimalPathToNodes {
protected:
	/*
	* @brief Ссылка на виртуальный класс Strategy, позволяющий переключаться между задачами.
	*/
	FindMinimalPathToNodesStrategy<T>* operation;
public:
	/*
	* @brief Деструктор.
	*/
	~FindMinimalPathToNodes() = default;
	/*
	* @brief Конструктор по умолчанию.
	*/
	FindMinimalPathToNodes() = default;

	/*
	* @brief Метод для установки стратегии.
	* @param s - стратегия, которую нужно задать.
	*/
	void setStrategy(FindMinimalPathToNodesStrategy<T>* s);

	/*
	* @brief Метод, позволящий использовать выбранную стратегию.
	* @param graph - граф, для которого применяется стратегия.
	* @param nodeNumber - узел, из котрого ищутся пути.
	* @return вектор минимальных длин путей до каждого из узлов.
	*/
	std::vector<T> useStrategy(Graph<T> graph, size_t nodeNumber);
};

template <typename T>
void FindMinimalPathToNodes<T>::setStrategy(FindMinimalPathToNodesStrategy<T>* s) {
	if(s == nullptr)
		throw std::logic_error("Стратегия не должна отсутствовать!");
	operation = s;
};

template <typename T>
std::vector<T> FindMinimalPathToNodes<T>::useStrategy(Graph<T> graph, size_t nodeNumber) {
	return this->operation->use(graph, nodeNumber);
};