#pragma once
#include <vector>

/*
* @brief Класс ребро - содержит информацию о ребре графа (присутствие/отсутствие ребра, его длину)
*/
template <typename T>
class Edge {

	/*
	* @brief Поле класса Edge, содержащее информацию о его длине,используя любой из стандарных типов данных. 0 (false для типа данных bool) используется для указания на отсутствие ребра.
	*/
	T size;
public:

	/*
	* @brief Конструктор по умолчанию. Создает ребро размера 0(false).
	*/
	Edge();

	/*
	* @brief Конструктор с параметром.
	* @param size - размер ребра.
	*/
	Edge(const T size);

	/*
	* @brief Сеттер size.
	* @param newSize - новый размер ребра.
	*/
	void setInfo(const T newSize);

	/*
	* @brief Геттер size.
	* @return Размер ребра.
	*/
	T getInfo() const;

	/*
	* @brief Конструктор копирования
	*/
	Edge(const Edge& other) = default;

	/*
	* @brief Оператор копирования
	*/
	Edge& operator = (const Edge& other) = default;

	/*
	* @brief Конструктор перемещения
	*/
	Edge(Edge&& other) noexcept = default;

	/*
	* @brief Оператор перемещения
	*/
	Edge& operator = (Edge&& other) noexcept = default;

	/*
	* @brief Деструктор
	*/
	~Edge() = default;
};


template <typename T>
Edge<T>::Edge() : size(false) {};

template <typename T>
Edge<T>::Edge(const T size) : size(size) {};

template <typename T>
void Edge<T>::setInfo(const T newSize) {
	this->size = newSize;
};

template <typename T>
T Edge<T>::getInfo() const {
	return this->size;
};
