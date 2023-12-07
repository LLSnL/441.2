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
	*/
	void setStrategy(CheckForGraphConnectivityStrategy<T>* s);

	/*
	* @brief Метод, позволящий использовать выбранную стратегию
	*/
	bool useStrategy(Graph<T> a, size_t connectivity);
};


template <typename T>
void CheckForGraphConnectivity<T>::setStrategy(CheckForGraphConnectivityStrategy<T>* s) {
	operation = s;
};

template <typename T>
bool CheckForGraphConnectivity<T>::useStrategy(Graph<T> a, size_t nodeNumber) {
	return this->operation->use(a, nodeNumber);
};