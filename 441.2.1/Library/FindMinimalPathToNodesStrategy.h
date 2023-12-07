#pragma once
#include "../441.2.1/Graph.h"

/*
* @brief Класс Strategy для алгоритмов поиска минимальных путей в графе.
*/
template <typename T>
class FindMinimalPathToNodesStrategy {
public:
	/*
	* @brief Виртуальный метод, переопределяемый для конкретной реализации алгоритмов.
	* @param a - граф, для которого применяется метод.
	* @param nodeNumber - номер узла, для котрого применяется метод.
	* @return вектор, содержащий длины минимальных путей для каждого узла в графе размера T.
	*/
	virtual std::vector<T> use(Graph<T> a, size_t nodeNumber) = 0;
};