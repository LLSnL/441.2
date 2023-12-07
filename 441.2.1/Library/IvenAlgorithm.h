#pragma once
#include "../Library/CheckForGraphConnectivityStrategy.h"
#include <list>
/*
* @brief Класс - конкретная реализация алгоритма проверки графа на связность - реализация алгоритма Ивена.
*/
template <typename T>
class IvenAlgorithm : public CheckForGraphConnectivityStrategy<T> {
	/*
	* @brief Статический вспомогательный метод для работы метода use класса IvenAlgorithm. Определяет есть ли путь между двумя узлами графа. В ходе работы  в векторе parents устанавливаются значения для восстановления маршрута.
	* @param g - граф, в котором нужно найти путь между 2мя узлами.
	* @param to - номер узла, который является конечной точкой.
	* @param visited - вектор посещённых узлов. Для корректной работы вводится вектор размер которого совпадает со значением nodeCount графа g, все значения должны быть = false.
	* @param buffer - буфер, в который помещается номер узла, из которого ищется путь.
	* @param parents - векто, использующийся для последующего восстановления маршрута. Для корректной работы вводится вектор размер которого совпадает со значением nodeCount графа g, все значения должны быть = 0. 
	* @return true - если маршрут между узлами существует,
	* @return false - если нет.
	*/
	static bool BFS(Graph<T> g, size_t to, std::vector<bool>& visited, std::list<size_t>& buffer, std::vector<size_t>& parents);
	
	/*
	* @brief Статический вспомогательный метод для работы метода use класса IvenAlgorithm. Ищет маршруты между 2мя узлами графа.
	* @param g - граф, в котором проводятся расчёты.
	* @param from - номер узла, который является начальной точкой.
	* @param to - номер узла, который является конечной точкой.
	* @return Количество маршрутов с разделёнными узлами.
	*/
	static size_t searchUniquePaths(Graph<T> g, size_t from, size_t to);
	
	/*
	* @brief Статический вспомогательный метод для работы метода use класса IvenAlgorithm. Восстанавливает найденный путь между двумя узлами по значениям вектора parents. Путь записывается в вектор paths.
	* @param from - номер узла, который является начальной точкой.
	* @param to - номер узла, который является конечной точкой.
	* @param parents - вектор, с помощью которого восстанавливается маршрут. Для корректной работы вводится вектор, полученный в ходе работы метода use класса BFS.
	* @param paths - вектор, в который записываются маршруты по порядку. Для корректной работы вводится вектор нулевого размера.
	*/
	static void getPath(size_t from, size_t to, std::vector<size_t> parents, std::vector<size_t>& paths);
public:
	/*
	* @brief Переопределение метода use для оценки связности графа. Использование алгоритма Ивена.
	* @param a - граф, в котором нужно оценить коэффициент связности.
	* @param m - коэффициент связности, который необходимо проверить.
	* @return true - если связность графа равна по крайней мере m,
	* @return false - если связность меньше m.
	*/
	bool use(Graph<T> a, size_t connectivity) override;

	/*
	* @brief Конструктор по умолчанию
	*/
	IvenAlgorithm() = default;

	/*
	* @brief Конструктор копирования
	*/
	IvenAlgorithm(const IvenAlgorithm& other) = default;

	/*
	* @brief Оператор копирования
	*/
	IvenAlgorithm& operator = (const IvenAlgorithm& other) = default;

	/*
	* @brief Конструктор перемещения
	*/
	IvenAlgorithm(IvenAlgorithm&& other) noexcept = default;

	/*
	* @brief Оператор перемещения
	*/
	IvenAlgorithm& operator = (IvenAlgorithm&& other) noexcept = default;

	/*
	* @brief Деструктор
	*/
	~IvenAlgorithm() = default;
};

template <typename T>
bool IvenAlgorithm<T>::BFS(Graph<T> g, size_t to, std::vector<bool>& visited, std::list<size_t>& buffer, std::vector<size_t>& parents) {
	if (buffer.empty())
		return false;

	size_t from = buffer.front();
	buffer.pop_front();
	visited[from] = true;
	if (from == to) {
		return true;
	}

	for (size_t i = 0; i < g.getNodeCount(); ++i)
	{
		if (g.getAdjacencyMatrix()[from][i] == 0)
			continue;
		if (visited[i] == true)
			continue;
		if (find(buffer.begin(), buffer.end(), i) != buffer.end())
			continue;
		parents[i] = from;
		buffer.push_back(i);
	}

	return BFS(g, to, visited, buffer, parents);
};

template <typename T>
void IvenAlgorithm<T>::getPath(size_t from, size_t to, std::vector<size_t> parents, std::vector<size_t>& paths) {
	if (to == from) {
		paths.push_back(to);
		return;
	}
	size_t preform = parents[to];
	getPath(from, preform, parents, paths);

	paths.push_back(to);
};

template <typename T>
size_t IvenAlgorithm<T>::searchUniquePaths(Graph<T> g, size_t from, size_t to) {
	size_t k = 0;
	while (true) {
		if (from == to)
			return k;
		std::list<size_t> buffer;
		buffer.push_back(from);
		std::vector<bool> visited(g.getNodeCount());
		for (size_t i = 0; i < visited.size(); i++)
		{
			visited[i] = false;
		}
		std::vector<size_t> parents(g.getNodeCount());
		if (BFS(g, to, visited, buffer, parents) == true) {
			std::vector<size_t> paths;
			IvenAlgorithm<T>::getPath(from, to, parents, paths);
			if (paths.size() == 2) {
				std::vector<T> newNode = g.getAdjacencyMatrix()[paths[0]];
				newNode[paths[1]] = 0;
				g.editNodeConnections(paths[0], newNode);
			}
			else {
				size_t l = 0;
				for (size_t i = 1; i < paths.size() - 1; i++)
				{
					if (paths[i] - l < to) {
						--to;
					}
					if (paths[i] - l < from) {
						--from;
					}
					g.deleteNode(paths[i] - l);
				}
			}
			++k;
		}
		else {
			break;
		}
	}
	return k;
};

template <typename T>
bool IvenAlgorithm<T>::use(Graph<T> a, size_t connectivity) {
	if (connectivity >= a.getNodeCount())
		return false;
	if (connectivity == 0)
		return true;
	Graph<T> newGraph = Graph<T>(a.getAdjacencyMatrix(), a.getNodeCount());
	for (size_t i = 0; i < connectivity - 1; i++)
	{
		for (size_t j = i + 1; j < connectivity; j++) {
			if (IvenAlgorithm::searchUniquePaths(a, i, j) < connectivity)
				return false;
		}
	}
	std::vector<T> newNodeConnections;
	newNodeConnections.resize(newGraph.getNodeCount() + 1);
	for (size_t i = 0; i < connectivity; i++)
	{
		newNodeConnections[i] = true;
	}
	for (size_t i = connectivity; i < newNodeConnections.size(); i++) {
		newNodeConnections[i] = false;
	}
	newGraph.addNode(newNodeConnections);
	for (size_t i = connectivity; i < newGraph.getNodeCount() - 1; i++)
	{
		if (IvenAlgorithm::searchUniquePaths(newGraph, i, newGraph.getNodeCount() - 1) < connectivity)
			return false;
		newNodeConnections[i] = true;
		newGraph.editNodeConnections(newGraph.getNodeCount() - 1, newNodeConnections);
	}
	return true;
};