#include <iostream>
#include "../Library/FindMinimalPathToNodes.h"
#include "../Library/CheckForGraphConnectivity.h"

/*
* @brief Точка входа в программу.
*/
int main(){

	/*
	* Пример работы с программой - использование алгоритма Клейтмана.
	*/
	size_t nodeNumber = 6;
	std::vector<std::vector<size_t>> matrix = {
	{0, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0},
	{1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 1},
	{0, 1, 0, 1, 0, 1},
	{1, 0, 0, 1, 1, 0}
	};
	Graph<size_t> g = Graph<size_t>(matrix, nodeNumber);

	CheckForGraphConnectivity<size_t> check;
	KleitmanAlgorithm<size_t> i1;
	check.setStrategy(&i1);

	size_t connectivity;
	std::cout << "Enter, which connectivity you want to test:" << std::endl;
	std::cin >> connectivity;

	if (check.useStrategy(g, connectivity))
		std::cout << "Graph connectivity is atleast " << connectivity << "." << std::endl;
	else
		std::cout << "Graph connectivity is not " << connectivity << "." << std::endl;
	return 0;
}