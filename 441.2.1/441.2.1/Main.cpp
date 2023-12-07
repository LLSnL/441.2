#include "../Library/FindMinimalPathToNodes.h"

/*
* @brief Точка входа в программу.
*/
int main(){
	std::vector<std::vector<size_t>> x2 = {
	{0, 3, 2, 0, 0, 1},
	{3, 0, 8, 0, 1, 0},
	{2, 8, 0, 3, 0, 0},
	{0, 0, 3, 0, 5, 7},
	{0, 1, 0, 5, 0, 2},
	{1, 0, 0, 7, 2, 0}
	};
	Graph<size_t> a = Graph<size_t>(x2, 6);
	FindMinimalPathToNodes<size_t> y;
	DejkstraAlgorithm<size_t> b;
	y.setStrategy(&b);
	auto ans = y.useStrategy(a, 3);
	return 0;
}