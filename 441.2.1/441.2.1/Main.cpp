#include "Graph.h"

/*
* @brief Точка входа в программу.
*/
int main(){
	Graph b = Graph();
	std::vector<Edge> y = { 0 };
	b.addNode(y);
	b.printG();

	std::vector<std::vector<Edge>> x = { 
		{0, 1, 1, 0, 0, 1}, 
		{1, 0, 1, 0, 1, 0}, 
		{1, 1, 0, 1, 0, 0}, 
		{0, 0, 1, 0, 1, 1}, 
		{0, 1, 0, 1, 0, 1}, 
		{1, 0, 0, 1, 1, 0} 
	};
	Graph a = Graph(x, 6);
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