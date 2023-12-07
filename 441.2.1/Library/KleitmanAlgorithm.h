#pragma once
#include "../Library/CheckForGraphConnectivityStrategy.h"

/*
* @brief Класс - конкретная реализация алгоритма проверки графа на связность - реализация алгоритма Клейтмана.
*/
template <typename T>
class KleitmanAlgorithm {
	/*
	* @brief Переопределение метода use для оценки связности графа. Использование алгоритма Клейтмана.
	* @param a - граф, в котором нужно оценить коэффициент связности.
	* @param m - коэффициент связности, который необходимо проверить.
	* @return true - если связность графа равна по крайней мере m,
	* @return false - если связность меньше m.
	*/
	bool use(Graph<T> a, size_t connectivity) override;

	/*
	* @brief Конструктор по умолчанию
	*/
	KleitmanAlgorithm() = default;

	/*
	* @brief Конструктор копирования
	*/
	KleitmanAlgorithm(const KleitmanAlgorithm& other) = default;

	/*
	* @brief Оператор копирования
	*/
	KleitmanAlgorithm& operator = (const KleitmanAlgorithm& other) = default;

	/*
	* @brief Конструктор перемещения
	*/
	KleitmanAlgorithm(KleitmanAlgorithm&& other) noexcept = default;

	/*
	* @brief Оператор перемещения
	*/
	KleitmanAlgorithm& operator = (KleitmanAlgorithm&& other) noexcept = default;

	/*
	* @brief Деструктор
	*/
	~KleitmanAlgorithm() = default;
};

template <typename T>
bool KleitmanAlgorithm<T>::use(Graph<T> a, size_t connectivity) {
	size_t k = 0, l = 0;
	if (connectivity == 0)
		return true;
	for (size_t l = 0; l != connectivity;)
	{
		for (size_t j = 0; j < a.getNodeCount(); j++)
		{
			if (a.getAdjacencyMatrix[0][j] != false) {
				++k;
			}
		}
		if (k >= connectivity) {
			a.deleteNode(0);
			++l;
		}
		else {
			return false;
		}
	}
	return true;
};
