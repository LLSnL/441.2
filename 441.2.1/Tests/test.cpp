#include "pch.h"
#include "../441.2.1/Graph.h"

namespace ClasesTests{

	/*
	* @brief Класс для тестирования конструктора по умолчанию класса Edge.
	*/
	class EdgeDefaultConstructorTest : public testing::Test {
	protected:
		Edge<bool> t1;
		Edge<char> t2;
		Edge<int> t3;
		Edge<size_t> t4;
		Edge<long long> t5;
		Edge<float> t6;
	};
	TEST_F(EdgeDefaultConstructorTest, DefaultConstructorWorks) {
		EXPECT_EQ(t1.getInfo(), false);
		EXPECT_EQ(t2.getInfo(), 0);
		EXPECT_EQ(t3.getInfo(), 0);
		EXPECT_EQ(t4.getInfo(), 0);
		EXPECT_EQ(t5.getInfo(), 0);
		EXPECT_FLOAT_EQ(t6.getInfo(), 0);

	}

	/*
	* @brief Класс для тестирования конструктора с параметрами класса Edge.
	*/
	class EdgeParamConstructorTest : public testing::Test {
	protected:
		Edge <bool> t1 = Edge<bool>(true);
		Edge <char> t2 = Edge<char>('r');
		Edge <int> t3 = Edge<int>(-4);
		Edge <size_t> t4 = Edge<size_t>(5);
		Edge <long long> t5 = Edge<long long>(7000000000);
		Edge <float> t6 = Edge<float>(0.5f);
	};
	TEST_F(EdgeParamConstructorTest, ParamConstructorWorks) {
		EXPECT_EQ(t1.getInfo(), true);
		EXPECT_EQ(t2.getInfo(), 'r');
		EXPECT_EQ(t3.getInfo(), -4);
		EXPECT_EQ(t4.getInfo(), 5);
		EXPECT_EQ(t5.getInfo(), 7000000000);
		EXPECT_FLOAT_EQ(t6.getInfo(), 0.5f);
	}
	
	/*
	* @brief Класс для тестирования сеттера класса Edge.
	*/
	class EdgeSetterTest : public testing::Test {
	protected:
		Edge<bool> t1;
		Edge<char> t2;
		Edge<int> t3;
		Edge<size_t> t4;
		Edge<long long> t5;
		Edge<float> t6;
		void SetUp() override {
			t1.setInfo(true);
			t2.setInfo('b');
			t3.setInfo(INT_MIN);
			t4.setInfo(UINT32_MAX);
			t5.setInfo(LLONG_MIN);
			t6.setInfo(0.16f);
		}
	};
	TEST_F(EdgeSetterTest, SetterWorks) {
		EXPECT_EQ(t1.getInfo(), true);
		EXPECT_EQ(t2.getInfo(), 'b');
		EXPECT_EQ(t3.getInfo(), INT_MIN);
		EXPECT_EQ(t4.getInfo(), UINT32_MAX);
		EXPECT_EQ(t5.getInfo(), LLONG_MIN);
		EXPECT_FLOAT_EQ(t6.getInfo(), 0.16f);
	}

	/*
	* @brief Класс для дальнейшего тестирования класса Graph, содержит различные векторы векторов
	*/
	class GraphTest : public testing::Test {
	protected:
		std::vector<std::vector<Edge<size_t>>> xr1 = {
			{0, 1, 2, 3},
			{0, 1, 2, 3},
			{0, 1, 2, 3},
			{0, 1, 2, 3, 4}
		};
		std::vector<std::vector<Edge<size_t>>> xr2 = {
			{1}
		};
		size_t yr1 = 4, yr2 = 2;
		std::vector<std::vector<Edge<bool>>> x1 = {
			{false, true, true, false, false, true},
			{true, false, true, false, true, false},
			{true, true, false, true, false, false},
			{false, false, true, false, true, true},
			{false, true, false, true, false, true},
			{true, false, false, true, true, false}
		};
		std::vector<std::vector<Edge<size_t>>> x2 = {
			{0, 3, 2, 0, 0, 1},
			{3, 0, 8, 0, 1, 0},
			{2, 8, 0, 3, 0, 0},
			{0, 0, 3, 0, 5, 7},
			{0, 1, 0, 5, 0, 2},
			{1, 0, 0, 7, 2, 0}
		};
		std::vector<std::vector<Edge<size_t>>> x3 = {
			{0,  7,  9,  0,  0, 14},
			{7,  0,  10, 15, 0, 0},
			{9,  10, 0,  11, 0, 2},
			{0,  15, 11, 0,  6, 0},
			{0,  0,  0,  6,  0, 9},
			{14, 0,  2,  0,  9, 0}
		};
		std::vector<std::vector<Edge<size_t>>> x4 = {
			{0, 1, 0, 5},
			{1, 0, 9, 0},
			{0, 9, 0, 2},
			{5, 0, 2, 0}
		};
		std::vector<std::vector<Edge<float>>> x5 = {
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
				EXPECT_EQ(g1.getAdjacencyMatrix()[i][j].getInfo(), x1[i][j].getInfo());
			}
		}

		EXPECT_EQ(g2.getNodeCount(), x2.size());
		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			for (size_t j = 0; j < g2.getNodeCount(); j++) {
				EXPECT_EQ(g2.getAdjacencyMatrix()[i][j].getInfo(), x2[i][j].getInfo());
			}
		}

		EXPECT_EQ(g5.getNodeCount(), x5.size());
		for (size_t i = 0; i < g5.getNodeCount(); i++)
		{
			for (size_t j = 0; j < g5.getNodeCount(); j++) {
				EXPECT_FLOAT_EQ(g5.getAdjacencyMatrix()[i][j].getInfo(), x5[i][j].getInfo());
			}
		}
	}

	TEST_F(GraphTest, AddNodeWorks) {
		std::vector<Edge<size_t>> newNode1 = { 1, 1, 1, 1, 1, 1, 0 };
		std::vector<Edge<size_t>> newNode2 = { 0 };
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
			EXPECT_EQ(g6.getAdjacencyMatrix()[g6.getNodeCount() - 1][i].getInfo(), newNode2[i].getInfo());
			EXPECT_EQ(g6.getAdjacencyMatrix()[i][g6.getNodeCount() - 1].getInfo(), newNode2[i].getInfo());
		}

		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			EXPECT_EQ(g2.getAdjacencyMatrix()[g2.getNodeCount() - 1][i].getInfo(), newNode1[i].getInfo());
			EXPECT_EQ(g2.getAdjacencyMatrix()[i][g2.getNodeCount() - 1].getInfo(), newNode1[i].getInfo());
		}
	}

	TEST_F(GraphTest, DeleteNodeWorks) {
		std::vector<std::vector<Edge<size_t>>> xt1 = {
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
				EXPECT_EQ(g4.getAdjacencyMatrix()[i][j].getInfo(), xt1[i][j].getInfo());
			}
		}
		
	}

	TEST_F(GraphTest, EditNodeConnectionsWorks) {
		std::vector<Edge<size_t>> newConnections1 = { 1, 1, 1, 1, 1, 1};
		size_t conspot1 = 0, conspot2 = 3;
		std::vector<Edge<float>> newConnections2 = { 0.0f };
		std::vector<Edge<size_t>> nc = {};

		EXPECT_THROW(g6.editNodeConnections(0, nc), std::logic_error);
		EXPECT_THROW(g3.editNodeConnections(8, newConnections1), std::out_of_range);
		EXPECT_THROW(g4.editNodeConnections(2, newConnections1), std::logic_error);

		EXPECT_NO_FATAL_FAILURE(g5.editNodeConnections(conspot1, newConnections2));
		EXPECT_NO_FATAL_FAILURE(g2.editNodeConnections(conspot2, newConnections1));

		for (size_t i = 0; i < g5.getNodeCount(); i++)
		{
			EXPECT_EQ(g5.getAdjacencyMatrix()[conspot1][i].getInfo(), newConnections2[i].getInfo());
			EXPECT_EQ(g5.getAdjacencyMatrix()[i][conspot1].getInfo(), newConnections2[i].getInfo());
		}

		for (size_t i = 0; i < g2.getNodeCount(); i++)
		{
			EXPECT_EQ(g2.getAdjacencyMatrix()[conspot2][i].getInfo(), newConnections1[i].getInfo());
			EXPECT_EQ(g2.getAdjacencyMatrix()[i][conspot2].getInfo(), newConnections1[i].getInfo());
		}
	}

	TEST_F(GraphTest, IvenAlgorithmWorks) {
		//EXPECT_NO_FATAL_FAILURE(g5.ivenAlgorithm(2));
		//EXPECT_FALSE(g5.ivenAlgorithm(2));

		//for (size_t i = 0; i < g1.getNodeCount(); i++)
		//{
		//	if (i < 4) {
		//		EXPECT_TRUE(g1.ivenAlgorithm(i));
		//	}
		//	else {
		//		EXPECT_FALSE(g1.ivenAlgorithm(i));
		//	}
		//	EXPECT_EQ(g1.ivenAlgorithm(i), g2.ivenAlgorithm(i));
		//}
	}

	TEST_F(GraphTest, DejkstraAlgorithmWorks) {

	}
}