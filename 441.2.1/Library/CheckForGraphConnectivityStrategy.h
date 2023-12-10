#pragma once
#include "../Library/Graph.h"

/*
* @brief Класс Strategy для алгоритмов проверки графов на связность.
*/
template <typename T>
class CheckForGraphConnectivityStrategy {
public:
	/*
	* @brief Виртуальный метод, переопределяемый для конкретной реализации алгоритмов.
	* @param graph - граф, для которого применяется метод.
	* @param connectivity - коэффициент связности.
	* @return результат - равняется ли связность графа хотя бы пар	аметру connectivity.
	*/
	virtual bool use(Graph<T> graph, size_t connectivity) = 0;
	virtual ~CheckForGraphConnectivityStrategy() = default;
};