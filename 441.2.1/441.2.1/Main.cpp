#include "Graph.h"
#include <iostream>
/*
* @brief Функция вывода графа в виде таблицы смежности на экран с помощью std::cout.
* @param a - граф, таблицу смежности которого нужно вывести.
*/
template <typename T>
void printG(Graph<T> a);

/*
* @brief Точка входа в программу.
*/
int main(){
	Graph<size_t> b = Graph<size_t>();
	std::vector<Edge<size_t>> y = { 0 };
	std::vector<Edge<size_t>> y2 = { 1, 0 };
	std::vector<Edge<size_t>> y3 = { 0, 0 };
	b.addNode(y);
	b.addNode(y2);
	printG(b);
	b.editNodeConnections(1, y3);
	b.deleteNode(0);
	printG(b);
	std::vector<std::vector<Edge<size_t>>> x = { 
		{0, 3, 2, 0, 0, 1}, 
		{3, 0, 1, 0, 1, 0}, 
		{2, 1, 0, 3, 0, 0}, 
		{0, 0, 3, 0, 5, 7}, 
		{0, 1, 0, 5, 0, 2}, 
		{1, 0, 0, 7, 2, 0} 
	};
	Graph<size_t> a = Graph<size_t>(x, 6);
	printG(a);
	size_t m;
	std::cout << "Enter your m: ";
	std::cin >> m;
	
	if (a.ivenAlgorithm(m))
		std::cout << "The graph's connectivity is at least " << m << std::endl;
	else
		std::cout << "The graph's connectivity not " << m << std::endl;

	std::vector<Edge<size_t>> y4 = { 0, 0, 1, 1, 1, 1 };
	a.editNodeConnections(0, y4);
	printG(a);

	return 0;
}

template <typename T>
void printG(Graph<T> a) {
	for (size_t i = 0; i < a.getNodeCount(); ++i)
	{
		for (size_t j = 0; j < a.getAdjacencyMatrix()[i].size(); ++j)
		{
			std::cout << a.getAdjacencyMatrix()[i][j].getInfo() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}