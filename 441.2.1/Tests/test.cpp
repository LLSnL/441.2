#include "pch.h"
#include "../Library/CheckForGraphConnectivity.h"
#include "../Library/FindMinimalPathToNodes.h"

namespace Tests{

	class ParametersForTests {
	protected:
		std::vector<std::vector<bool>> x1 = {
			{false, true, true, false, false, true},
			{true, false, true, false, true, false},
			{true, true, false, true, false, false},
			{false, false, true, false, true, true},
			{false, true, false, true, false, true},
			{true, false, false, true, true, false}
		};
		std::vector<std::vector<size_t>> x2 = {
			{0,  7,  9,  0,  0, 14},
			{7,  0,  10, 15, 0, 0},
			{9,  10, 0,  11, 0, 2},
			{0,  15, 11, 0,  6, 0},
			{0,  0,  0,  6,  0, 9},
			{14, 0,  2,  0,  9, 0}
		};
		std::vector<std::vector<size_t>> x3 = {
			{0, 1, 0, 5},
			{1, 0, 9, 0},
			{0, 9, 0, 2},
			{5, 0, 2, 0}
		};
		size_t y1 = 6, y2 = 6, y3 = 4;
	};

	namespace TestsForGraph {

		/*
		* @brief Класс для тестирования класса Graph.
		*/
		class GraphTest : public testing::Test, public Tests::ParametersForTests {
		protected:
			Graph<int> g = Graph<int>();
			Graph<bool> g1 = Graph<bool>(x1, y1);
			Graph<size_t> g2 = Graph<size_t>(x2, y2);
			Graph<size_t> g3 = Graph<size_t>(x3, y3);
		};

		TEST_F(GraphTest, DefaultConstructorWorks) {
			EXPECT_EQ(g.getAdjacencyMatrix().size(), 0);
			EXPECT_EQ(g.getNodeCount(), 0);
		}

		TEST_F(GraphTest, ParamConstructorThrows) {
			std::vector<std::vector<int>> x1 = {
				{-1}
			};
			std::vector<std::vector<int>> x2 = {
				{-1, 0}, 
				{2}
			};
			std::vector<std::vector<int>> x3 = {
				{0, 1},
				{0, 1}
			};
			size_t y1 = 2, y2 = 2, y3 = 2;
			EXPECT_THROW(Graph(x1, y1), std::logic_error);
			EXPECT_THROW(Graph(x2, y2), std::logic_error);
			EXPECT_THROW(Graph(x3, y3), std::logic_error);
		}

		TEST_F(GraphTest, ParamConstructorWorksWithBools) {
			EXPECT_EQ(g1.getNodeCount(), x1.size());
			for (size_t i = 0; i < g1.getNodeCount(); i++)
			{
				for (size_t j = 0; j < g1.getNodeCount(); j++) {
					EXPECT_EQ(g1.getAdjacencyMatrix()[i][j], x1[i][j]);
				}
			}
		}

		TEST_F(GraphTest, ParamConstructorWortksWithInts) {
			EXPECT_EQ(g2.getNodeCount(), x2.size());
			for (size_t i = 0; i < g2.getNodeCount(); i++)
			{
				for (size_t j = 0; j < g2.getNodeCount(); j++) {
					EXPECT_EQ(g2.getAdjacencyMatrix()[i][j], x2[i][j]);
				}
			}
		}

		TEST_F(GraphTest, AddNodeThrows) {
			std::vector<size_t> newNode = { 0 };
			EXPECT_THROW(g2.addNode(newNode), std::logic_error);
		}

		TEST_F(GraphTest, AddNodeWorks) {
			std::vector<size_t> newNode1 = { 1, 1, 1, 1, 1, 1, 0 };
			EXPECT_NO_FATAL_FAILURE(g2.addNode(newNode1));
			EXPECT_EQ(g2.getNodeCount(), newNode1.size());

			for (size_t i = 0; i < g2.getNodeCount(); i++)
			{
				EXPECT_EQ(g2.getAdjacencyMatrix()[g2.getNodeCount() - 1][i], newNode1[i]);
				EXPECT_EQ(g2.getAdjacencyMatrix()[i][g2.getNodeCount() - 1], newNode1[i]);
			}
		}

		TEST_F(GraphTest, DeleteNodeThrows) {
			EXPECT_THROW(g.deleteNode(0), std::logic_error);
			EXPECT_THROW(g3.deleteNode(7), std::out_of_range);
		}

		TEST_F(GraphTest, DeleteNodeWorks) {
			std::vector<std::vector<size_t>> xt1 = {
				{0, 0, 5},
				{0, 0, 2},
				{5, 2, 0}
			};

			EXPECT_NO_FATAL_FAILURE(g3.deleteNode(1));
			EXPECT_EQ(g3.getNodeCount(), xt1.size());
			for (size_t i = 0; i < g3.getNodeCount(); i++)
			{
				for (size_t j = 0; j < g3.getNodeCount(); j++) {
					EXPECT_EQ(g3.getAdjacencyMatrix()[i][j], xt1[i][j]);
				}
			}

		}

		TEST_F(GraphTest, EditNodeConnectionsThrows) {
			std::vector<size_t> newConnections1 = { 1, 1, 1, 1, 1, 1 };
			std::vector<int> nc = {};
			EXPECT_THROW(g.editNodeConnections(0, nc), std::logic_error);
			EXPECT_THROW(g2.editNodeConnections(8, newConnections1), std::out_of_range);
			EXPECT_THROW(g3.editNodeConnections(2, newConnections1), std::logic_error);
		}

		TEST_F(GraphTest, EditNodeConnectionsWorks) {
			std::vector<size_t> newConnections1 = { 1, 1, 1, 1, 1, 1 };
			size_t conspot = 3;
			std::vector<size_t> nc = {};

			EXPECT_NO_FATAL_FAILURE(g2.editNodeConnections(conspot, newConnections1));
			for (size_t i = 0; i < g2.getNodeCount(); i++)
			{
				EXPECT_EQ(g2.getAdjacencyMatrix()[conspot][i], newConnections1[i]);
				EXPECT_EQ(g2.getAdjacencyMatrix()[i][conspot], newConnections1[i]);
			}
		}
	}

	namespace GraphConnectivityAlgorithmsTests {

		/*
		* @brief Класс для подготовки значений для тестирования группы классов, связанных с проверкой графа на связность, и для тестирования класса CheckForGraphConnectivity.
		*/
		class CheckForGraphConnectivityTest : public testing::Test, public Tests::ParametersForTests{
		protected:
			Graph<bool> g1 = Graph<bool>(x1, y1);
			Graph<size_t> g2 = Graph<size_t>(x2, y2);
			Graph<size_t> g3 = Graph<size_t>(x3, y3);
			CheckForGraphConnectivity<bool> check1;
			CheckForGraphConnectivity<size_t> check2;
			IvenAlgorithm<bool> i1;
			IvenAlgorithm<size_t> i2;
			KleitmanAlgorithm<bool> k1;
			KleitmanAlgorithm<size_t> k2;
		};

		TEST_F(CheckForGraphConnectivityTest, SetStrategyWorks) {
			EXPECT_NO_FATAL_FAILURE(check2.setStrategy(&i2));
		};

		TEST_F(CheckForGraphConnectivityTest, UseStrategyWorks) {
			check2.setStrategy(&i2);
			EXPECT_NO_FATAL_FAILURE(check2.useStrategy(g2, 3));
		}

		/*
		* @brief Класс для тестирования класса IvenAlgorithm.
		*/
		class IvenAlgorithmTest : public CheckForGraphConnectivityTest {
		protected:
			void SetUp() override {
				check1.setStrategy(&i1);
				check2.setStrategy(&i2);
			}
		};

		TEST_F(IvenAlgorithmTest, IvenAlgorithmWorksWithBools) {
			for (size_t i = 0; i < 4; i++)
			{
				EXPECT_TRUE(check1.useStrategy(g1, i));
			}
			EXPECT_FALSE(check1.useStrategy(g1, 4));
		}

		TEST_F(IvenAlgorithmTest, IvenAlgorithmWorksWithInts) {
			for (size_t i = 0; i < 3; i++)
			{
				EXPECT_TRUE(check2.useStrategy(g2, i));
				EXPECT_TRUE(check2.useStrategy(g3, i));
			}
			EXPECT_FALSE(check2.useStrategy(g2, 4));
			EXPECT_FALSE(check2.useStrategy(g3, 3));
		}

		/*
		* @brief Класс для тестирования класса KleitmanAlgorithm.
		*/
		class KleitmanAlgorithmTest : public CheckForGraphConnectivityTest {
			void SetUp() override {
				check1.setStrategy(&k1);
				check2.setStrategy(&k2);
			}
		};

		TEST_F(KleitmanAlgorithmTest, KleitmanAlgorithmWorksWithBools) {
			for (size_t i = 0; i < 4; i++)
			{
				EXPECT_TRUE(check1.useStrategy(g1, i));
			}
			EXPECT_FALSE(check1.useStrategy(g1, 4));
		}

		TEST_F(KleitmanAlgorithmTest, KleitmanAlgorithmWorksWithInts) {
			for (size_t i = 0; i < 3; i++)
			{
				EXPECT_TRUE(check2.useStrategy(g2, i));
				EXPECT_TRUE(check2.useStrategy(g3, i));
			}
			EXPECT_FALSE(check2.useStrategy(g2, 4));
			EXPECT_FALSE(check2.useStrategy(g3, 3));
		}
	}

	namespace FindMinimalPathAlgorithmsTests {

		/*
		* @brief Класс для подготовки значений для тестирования группы классов, связанных с проверкой графа на связность, и для тестирования класса CheckForGraphConnectivity.
		*/
		class FindMinimalPathToNodesTest : public testing::Test, public Tests::ParametersForTests {
		protected:
			Graph<size_t> g0 = Graph<size_t>();
			Graph<bool> g1 = Graph<bool>(x1, y1);
			Graph<size_t> g2 = Graph<size_t>(x2, y2);
			Graph<size_t> g3 = Graph<size_t>(x3, y3);
			FindMinimalPathToNodes<bool> check1;
			FindMinimalPathToNodes<size_t> check2;
			DejkstraAlgorithm<bool> d1;
			DejkstraAlgorithm<size_t> d2;
		};

		TEST_F(FindMinimalPathToNodesTest, SetStrategyWorks) {
			EXPECT_NO_FATAL_FAILURE(check1.setStrategy(&d1));
		}

		TEST_F(FindMinimalPathToNodesTest, UseStrategyWorks) {
			check2.setStrategy(&d2);
			EXPECT_NO_FATAL_FAILURE(check2.useStrategy(g2, 2));
		}

		/*
		* @brief Класс для тестирования класса DejkstraAlgorithm.
		*/
		class DejkstraAlgorithmTest : public FindMinimalPathToNodesTest {
		protected:
			Graph<int> gn = Graph<int>({ {-1} }, 1);
			FindMinimalPathToNodes<int> checkNegative;
			DejkstraAlgorithm<int> dn;

			std::vector<size_t> mp20 = { 0, 7, 9, 20, 20, 11 };
			std::vector<size_t> mp24 = { 20, 21, 11, 6, 0, 9 };
			std::vector<size_t> mp30 = { 0, 1, 7, 5 };
			std::vector<size_t> mp33 = { 5, 6, 2, 0 };

			void SetUp() override {
				check1.setStrategy(&d1);
				check2.setStrategy(&d2);
				checkNegative.setStrategy(&dn);
			}
		};

		TEST_F(DejkstraAlgorithmTest, DejkstraAlgorithmThrows) {
			EXPECT_THROW(check2.useStrategy(g0, 2), std::logic_error);
			EXPECT_THROW(check1.useStrategy(g1, 2), std::logic_error);
			EXPECT_THROW(check2.useStrategy(g2, 10), std::out_of_range);
			EXPECT_THROW(checkNegative.useStrategy(gn, 1), std::logic_error);
		}

		TEST_F(DejkstraAlgorithmTest, DejkstraAlgorithmWorksFirstTest) {
			std::vector<size_t> p20 = check2.useStrategy(g2, 0);
			std::vector<size_t> p24 = check2.useStrategy(g2, 4);

			for (size_t i = 0; i < g2.getNodeCount(); i++)
			{
				EXPECT_EQ(mp20[i], p20[i]);
				EXPECT_EQ(mp24[i], p24[i]);
			}
		}

		TEST_F(DejkstraAlgorithmTest, DejkstraAlgorithmWorksSecondTest) {
			std::vector<size_t> p30 = check2.useStrategy(g3, 0);
			std::vector<size_t> p33 = check2.useStrategy(g3, 3);

			for (size_t i = 0; i < g3.getNodeCount(); i++)
			{
				EXPECT_EQ(mp30[i], p30[i]);
				EXPECT_EQ(mp33[i], p33[i]);
			}
		}
	}
}