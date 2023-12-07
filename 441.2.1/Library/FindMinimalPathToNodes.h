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
	*/
	void setStrategy(FindMinimalPathToNodesStrategy<T>* s);

	/*
	* @brief Метод, позволящий использовать выбранную стратегию
	*/
	std::vector<T> useStrategy(Graph<T> a, size_t nodeNumber);
};

template <typename T>
void FindMinimalPathToNodes<T>::setStrategy(FindMinimalPathToNodesStrategy<T>* s) {
	operation = s;
};

template <typename T>
std::vector<T> FindMinimalPathToNodes<T>::useStrategy(Graph<T> a, size_t nodeNumber) {
	return this->operation->use(a, nodeNumber);
};