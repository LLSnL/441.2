#include "Graph.h"

/*
* @brief Точка входа в программу.
*/
int main(){
	Graph<size_t> b = Graph<size_t>();
	std::vector<Edge<size_t>> y = { 0 };
	b.addNode(y);
	b.printG();
	std::vector<std::vector<Edge<size_t>>> x = { 
		{0, 1, 2, 0, 0, 4}, 
		{1, 0, 1, 0, 1, 0}, 
		{2, 1, 0, 3, 0, 0}, 
		{0, 0, 3, 0, 1, 1}, 
		{0, 1, 0, 1, 0, 1}, 
		{4, 0, 0, 1, 1, 0} 
	};
	Graph<size_t> a = Graph<size_t>(x, 6);
	a.printG();
	size_t m;
	std::cout << std::endl;
	std::cout << "Enter your m: ";
	std::cin >> m;

	if (a.ivenAlgorithm(m))
		std::cout << "The graph's connectivity is at least " << m;
	else
		std::cout <<"The graph's connectivity not " << m;
	return 0;
}