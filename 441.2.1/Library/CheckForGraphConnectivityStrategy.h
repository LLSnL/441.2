#pragma once
#include "../441.2.1/Graph.h"

/*
* @brief Класс Strategy для алгоритмов проверки графов на связность.
*/
template <typename T>
class CheckForGraphConnectivityStrategy {
public:
	/*
	* @brief Виртуальный метод, переопределяемый для конкретной реализации алгоритмов.
	* @param a - граф, для которого применяется метод.
	* @param connectivity - коэффициент связности.
	* @return результат - равняется ли связность графа хотя бы параметру connectivity.
	*/
	virtual bool use(Graph<T> a, size_t connectivity) = 0;
};