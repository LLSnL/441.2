#include "Graph.h"

int main(){
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