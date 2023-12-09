#pragma once
#include "../Library/IvenAlgorithm.h"
#include "../Library/KleitmanAlgorithm.h"

/*
* @brief Контекст, использующий стратегию для решения задачи проверки графа на связность.
*/
template <typename T>
class CheckForGraphConnectivity {
protected:

	/*
	* @brief Ссылка на виртуальный класс Strategy, позволяющий переключаться между задачами.
	*/
	CheckForGraphConnectivityStrategy<T>* operation;
public:

	/*
	* @brief Деструктор.
	*/
	~CheckForGraphConnectivity() = default;

	/*
	* @brief Конструктор по умолчанию.
	*/
	CheckForGraphConnectivity() = default;

	/*
	* @brief Метод для установки стратегии.
	* @param s - ссылка на стратегию, которую мы хотим выбрать.
	*/
	void setStrategy(CheckForGraphConnectivityStrategy<T>* s);

	/*
	* @brief Метод, позволящий использовать выбранную стратегию.
	* @param graph - граф, для которого применяется стратегия.
	* @param connectivity - связность, которую необходимо проверить.
	* @return true - если связность равна по крайней мере параметру connectivity, false - если нет.
	*/
	bool useStrategy(Graph<T> graph, size_t connectivity);
};


template <typename T>
void CheckForGraphConnectivity<T>::setStrategy(CheckForGraphConnectivityStrategy<T>* s) {
	if (s == nullptr)
		throw std::logic_error("Стратегия не должна отсутствовать!");
	operation = s;
};

template <typename T>
bool CheckForGraphConnectivity<T>::useStrategy(Graph<T> graph, size_t nodeNumber) {
	return this->operation->use(graph, nodeNumber);
};