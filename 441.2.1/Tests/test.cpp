#include "pch.h"
#include "../441.2.1/Graph.h"

namespace ClasesTests{

	/*
	* @brief Класс для дальнейшего тестирования класса Graph, содержит различные векторы векторов
	*/
	class GraphTest : public testing::Test {
	protected:
		std::vector<std::vector<size_t>> xr1 = {
			{0, 1, 2, 3},
			{0, 1, 2, 3},
			{0, 1, 2, 3},
			{0, 1, 2, 3, 4}
		};
		std::vector<std::vector<size_t>> xr2 = {
			{3}
		};
		std::vector<std::vector<int>> xr3 = {
			{0, -2},
			{-2, -4}
		};
		size_t yr1 = 4, yr2 = 2, yr3 = 2;
		std::vector<std::vector<bool>> x1 = {
			{false, true, true, false, false, true},
			{true, false, true, false, true, false},
			{true, true, false, true, false, false},
			{false, false, true, false, true, true},
			{false, true, false, true, false, true},
			{true, false, false, true, true, false}
		};
		std::vector<std::vector<size_t>> x2 = {
			{0, 3, 2, 0, 0, 1},
			{3, 0, 8, 0, 1, 0},
			{2, 8, 0, 3, 0, 0},
			{0, 0, 3, 0, 5, 7},
			{0, 1, 0, 5, 0, 2},
			{1, 0, 0, 7, 2, 0}
		};
		std::vector<std::vector<size_t>> x3 = {
			{0,  7,  9,  0,  0, 14},
			{7,  0,  10, 15, 0, 0},
			{9,  10, 0,  11, 0, 2},
			{0,  15, 11, 0,  6, 0},
			{0,  0,  0,  6,  0, 9},
			{14, 0,  2,  0,  9, 0}
		};
		std::vector<std::vector<size_t>> x4 = {
			{0, 1, 0, 5},
			{1, 0, 9, 0},
			{0, 9, 0, 2},
			{5, 0, 2, 0}
		};
		std::vector<std::vector<float>> x5 = {
			{0.3f}
		};
		size_t y1 = 6, y2 = 6, y3 = 6, y4 = 4, y5 = 1;
		Graph<bool> g1 = Graph<bool>(x1, y1);
		Graph<size_t> g2 = Graph<size_t>(x2, y2);
		Graph<size_t> g3 = Graph<size_t>(x3, y3);
		Graph<size_t> g4 = Graph<size_t>(x4, y4);
		Graph<float> g5 = Graph<float>(x5, y5);
		Graph<size_t> g6 = Graph<size_t>();
		Graph<float> g7 = Graph<float>();
		Graph<int> gr1 = Graph<int>(xr3, yr3);
	};
	TEST_F(GraphTest, DefaultConstructorWorks) {
		EXPECT_EQ(g6.getAdjacencyMatrix().size(), 0);
		EXPECT_EQ(g6.getNodeCount(), 0);

		EXPECT_EQ(g7.getAdjacencyMatrix().size(), 0);
		EXPECT_EQ(g7.getNodeCount(), 0);
	}

	TEST_F(GraphTest, ParamConstructorWorks) {
		EXPECT_THROW(Graph(xr1, yr1), std::logic_error);
		EXPECT_THROW(Graph(xr2, yr2), std::logic_error);

		EXPECT_EQ(g1.getNodeCount(), x1.size());
		for (size_t i = 0; i < g1.getNodeCount(); i++)
		{
			for (size_t j = 0; j < g1.getNodeCount(); j++) {
				EXPECT_EQ(g1.getAdjacencyMatrix()[i][j], x1[i][j]);
			}
		}

		EXPECT_EQ(g2.getNodeCount(), x2.size());
		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			for (size_t j = 0; j < g2.getNodeCount(); j++) {
				EXPECT_EQ(g2.getAdjacencyMatrix()[i][j], x2[i][j]);
			}
		}

		EXPECT_EQ(g5.getNodeCount(), x5.size());
		for (size_t i = 0; i < g5.getNodeCount(); i++)
		{
			for (size_t j = 0; j < g5.getNodeCount(); j++) {
				EXPECT_FLOAT_EQ(g5.getAdjacencyMatrix()[i][j], x5[i][j]);
			}
		}
	}

	TEST_F(GraphTest, AddNodeWorks) {
		std::vector<size_t> newNode1 = { 1, 1, 1, 1, 1, 1, 0 };
		std::vector<size_t> newNode2 = { 0 };
		Graph<size_t> gt1 = g6;
		Graph<size_t> gt2 = g2;
		EXPECT_THROW(gt1.addNode(newNode1), std::logic_error);
		EXPECT_THROW(gt2.addNode(newNode2), std::logic_error);
		EXPECT_NO_FATAL_FAILURE(g6.addNode(newNode2));
		EXPECT_NO_FATAL_FAILURE(g2.addNode(newNode1));

		EXPECT_EQ(g2.getNodeCount(), newNode1.size());
		EXPECT_EQ(g6.getNodeCount(), newNode2.size());
		for (size_t i = 0; i < g6.getNodeCount(); i++)
		{
			EXPECT_EQ(g6.getAdjacencyMatrix()[g6.getNodeCount() - 1][i], newNode2[i]);
			EXPECT_EQ(g6.getAdjacencyMatrix()[i][g6.getNodeCount() - 1], newNode2[i]);
		}

		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			EXPECT_EQ(g2.getAdjacencyMatrix()[g2.getNodeCount() - 1][i], newNode1[i]);
			EXPECT_EQ(g2.getAdjacencyMatrix()[i][g2.getNodeCount() - 1], newNode1[i]);
		}
	}

	TEST_F(GraphTest, DeleteNodeWorks) {
		std::vector<std::vector<size_t>> xt1 = {
			{0, 0, 5},
			{0, 0, 2},
			{5, 2, 0}
		};
		EXPECT_THROW(g6.deleteNode(0), std::logic_error);
		EXPECT_THROW(g3.deleteNode(7), std::out_of_range);
		EXPECT_NO_FATAL_FAILURE(g5.deleteNode(0));
		EXPECT_NO_FATAL_FAILURE(g4.deleteNode(1));

		EXPECT_EQ(g5.getNodeCount(), 0);
		EXPECT_EQ(g5.getAdjacencyMatrix().size(), 0);
		EXPECT_EQ(g4.getNodeCount(), xt1.size());
		for (size_t i = 0; i < g4.getNodeCount(); i++)
		{
			for (size_t j = 0; j < g4.getNodeCount(); j++) {
				EXPECT_EQ(g4.getAdjacencyMatrix()[i][j], xt1[i][j]);
			}
		}
		
	}

	TEST_F(GraphTest, EditNodeConnectionsWorks) {
		std::vector<size_t> newConnections1 = { 1, 1, 1, 1, 1, 1};
		size_t conspot1 = 0, conspot2 = 3;
		std::vector<float> newConnections2 = { 0.0f };
		std::vector<size_t> nc = {};

		EXPECT_THROW(g6.editNodeConnections(0, nc), std::logic_error);
		EXPECT_THROW(g3.editNodeConnections(8, newConnections1), std::out_of_range);
		EXPECT_THROW(g4.editNodeConnections(2, newConnections1), std::logic_error);

		EXPECT_NO_FATAL_FAILURE(g5.editNodeConnections(conspot1, newConnections2));
		EXPECT_NO_FATAL_FAILURE(g2.editNodeConnections(conspot2, newConnections1));

		for (size_t i = 0; i < g5.getNodeCount(); i++)
		{
			EXPECT_EQ(g5.getAdjacencyMatrix()[conspot1][i], newConnections2[i]);
			EXPECT_EQ(g5.getAdjacencyMatrix()[i][conspot1], newConnections2[i]);
		}

		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			EXPECT_EQ(g2.getAdjacencyMatrix()[conspot2][i], newConnections1[i]);
			EXPECT_EQ(g2.getAdjacencyMatrix()[i][conspot2], newConnections1[i]);
		}
	}

	TEST_F(GraphTest, IvenAlgorithmWorks) {
		EXPECT_FALSE(g7.ivenAlgorithm(1));
		EXPECT_FALSE(g5.ivenAlgorithm(2));

		for (size_t i = 0; i < g1.getNodeCount(); i++)
		{
			if (i < 4) {
				EXPECT_TRUE(g1.ivenAlgorithm(i));
			}
			else {
				EXPECT_FALSE(g1.ivenAlgorithm(i));
			}
			EXPECT_EQ(g1.ivenAlgorithm(i), g2.ivenAlgorithm(i));
		}

		EXPECT_TRUE(g3.ivenAlgorithm(2));
		EXPECT_TRUE(g4.ivenAlgorithm(2));
		EXPECT_FALSE(g3.ivenAlgorithm(3));
		EXPECT_FALSE(g4.ivenAlgorithm(3));

		EXPECT_TRUE(gr1.ivenAlgorithm(1));
		EXPECT_FALSE(gr1.ivenAlgorithm(2));
	}

	TEST_F(GraphTest, DejkstraAlgorithmWorks) {
		std::vector<size_t> pg20 = { 0, 3, 2, 5, 3, 1 };
		std::vector<size_t> pg22 = { 2, 5, 0, 3, 5, 3 };
		std::vector<size_t> pg30 = { 0, 7, 9, 20, 20, 11 };
		std::vector<size_t> pg32 = { 9, 10, 0, 11, 11, 2 };
		std::vector<size_t> pg34 = { 20, 21, 11, 6, 0, 9 };
		std::vector<size_t> pg40 = { 0, 1, 7, 5 };
		std::vector<size_t> pg43 = { 5, 6, 2, 0 };
		std::vector<float> pg50 = { 0 };


		std::vector<size_t> pgt20 = g2.dejkstraAlgorithm(0);
		std::vector<size_t> pgt22 = g2.dejkstraAlgorithm(2);
		std::vector<size_t> pgt30 = g3.dejkstraAlgorithm(0);
		std::vector<size_t> pgt32 = g3.dejkstraAlgorithm(2);
		std::vector<size_t> pgt34 = g3.dejkstraAlgorithm(4);
		std::vector<size_t> pgt40 = g4.dejkstraAlgorithm(0);
		std::vector<size_t> pgt43 = g4.dejkstraAlgorithm(3);
		std::vector<float> pgt50 = g5.dejkstraAlgorithm(0);

		EXPECT_THROW(g7.dejkstraAlgorithm(0), std::logic_error);
		EXPECT_THROW(g5.dejkstraAlgorithm(2), std::out_of_range);
		EXPECT_THROW(gr1.dejkstraAlgorithm(1), std::logic_error);
		EXPECT_THROW(g1.dejkstraAlgorithm(3), std::logic_error);

		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			EXPECT_EQ(pgt20[i], pg20[i]);
			EXPECT_EQ(pgt22[i], pg22[i]);
			EXPECT_EQ(pgt30[i], pg30[i]);
			EXPECT_EQ(pgt32[i], pg32[i]);
			EXPECT_EQ(pgt34[i], pg34[i]);
		}
		for (size_t i = 0; i < g4.getNodeCount(); i++)
		{
			EXPECT_EQ(pgt40[i], pg40[i]);
			EXPECT_EQ(pgt43[i], pg43[i]);
		}
		EXPECT_FLOAT_EQ(pgt50[0], pg50[0]);
	}
}