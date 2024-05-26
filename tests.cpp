#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph +, -, ++, --, +(), -(), <<")
{
    raphael::Graph g1;
    vector<vector<int>> graph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    g1.loadGraph(graph);
    raphael::Graph g2;
    vector<vector<int>> graph1 = {
        {-1, -2, -3},
        {-4, -5, -6},
        {-7, -8, -9}};
    g2.loadGraph(graph1);
    raphael::Graph g3;
    vector<vector<int>> graph2 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g3.loadGraph(graph2);
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};

    // check addition of graph
    raphael::Graph test = g1 + g2;
    CHECK(test.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]\n");

    // check soustraction
    test = g1 - g1;
    CHECK(test.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]\n");

    //check x++
    CHECK((g3++).printGraph() == "[1, 1, 1]\n[1, 1, 1]\n[1, 1, 1]\n");
    CHECK((g3).printGraph() == "[2, 2, 2]\n[2, 2, 2]\n[2, 2, 2]\n");

    //check ++x
    CHECK((++g3).printGraph() == "[3, 3, 3]\n[3, 3, 3]\n[3, 3, 3]\n");

    //check x--
    CHECK((g3--).printGraph() == "[3, 3, 3]\n[3, 3, 3]\n[3, 3, 3]\n");
    CHECK((g3).printGraph() == "[2, 2, 2]\n[2, 2, 2]\n[2, 2, 2]\n");

    //check --x
    CHECK((--g3).printGraph() == "[1, 1, 1]\n[1, 1, 1]\n[1, 1, 1]\n");

    //check +x
    CHECK((+g3).printGraph() == "[1, 1, 1]\n[1, 1, 1]\n[1, 1, 1]\n");

    //check -x
    CHECK((g1).printGraph() == (-g2).printGraph());

    //check with different algorithms
    vector<vector<int>> graph3 = {
        {1, 0, 3, 1},
        {4, 0, -1, 0},
        {4, 5, 6, -3},
        {7, 3, 2, 1}};

    vector<vector<int>> graph4 = {
        {-1, -1, -3, -3},
        {-5, 0, -1, 0},
        {-4, -7, -6, 4},
        {-9, -3, -1, -1}};
    g1.loadGraph(graph3);
    g2.loadGraph(graph4);
    test = g1 + g2;  //    ==  {0, -1, 0, -2},
                           //  {-1, 0, -2, 0},
                           //  {0, -2, 0, 1},
                           //  {-2, 0, 1, 0}};
    CHECK(raphael::Algorithms::isConnected(test) == true); 

        

        vector<vector<int>> graph5 = {
            {-1, 0, 0, -1, -1},
            {0, -1, 0, -1, -1},
            {0, 0, -1, 0, -1},
            {-1, -1, 0, -1, -1},
            {-1, -1, -1, -1, -1}};

        test.loadGraph(graph5);
        CHECK(raphael::Algorithms::isConnected(++test) == false); // ==    {0, 1, 1, 0, 0},
                                                                        // {1, 0, 1, 0, 0},
                                                                        // {1, 1, 0, 1, 0},
                                                                        // {0, 0, 1, 0, 0},
                                                                        // {0, 0, 0, 0, 0}};

        // check on shortest path
        vector<vector<int>> graph8 = {  // check for weithed graph with negative values and negative cycle
        {0, -1, 0, -1},
        {-1, 0, -2, 0},
        {0, -2, 0, 1},
        {-1, 0, 1, 0}};
        test.loadGraph(graph8);
        CHECK(raphael::Algorithms::shortestPath(--test, 0, 2) == "Graph contains a negative cycle");

        vector<vector<int>> graph6 = { 
            {0, -1, 0},
            {3, 0, 2},
            {0, 1, -1}};
        test.loadGraph(graph6);

        vector<vector<int>> graph7 = { 
            {0, -2, 0},
            {2, 0, 1},
            {0, 0, -1}};
        g2.loadGraph(graph7);
        test = test - g2;
        CHECK(raphael::Algorithms::shortestPath(test, 0, 2) == "The shortest path is: 0->1->2");

}

TEST_CASE("Test graph *int, g1*g2, *=g") // with some algorithms
{
    // *int
    raphael::Graph test;
    vector<vector<int>> graph = { 
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    test.loadGraph(graph);
    test = test * 2;
    raphael::Graph test2;
    test2.loadGraph(graph);
    test2 *= 2;
    CHECK((test).printGraph() == "[0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]\n");
    CHECK(raphael::Algorithms::isContainsCycle(test) == "The cycle is: 0->1->2->0");
    CHECK(test == test2);

    raphael::Graph test1;
    vector<vector<int>> graph1 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    test1.loadGraph(graph1);
    test1 = test1 * 0;
    CHECK(raphael::Algorithms::isContainsCycle(test1) == "0");

    //g*g1
    vector<vector<int>> graph2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};

    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};

    test.loadGraph(graph2);
    test1.loadGraph(graph3);
    test = test * test1;    //  == {0, 1, 1},
                                // {1, 0, 1},
                                // {1, 1, 0}};

    CHECK((test).printGraph() == "[0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]\n");
    CHECK(raphael::Algorithms::isContainsCycle(test) == "The cycle is: 0->1->2->0");

    // g*=g1
    test.loadGraph(graph2);
    test1.loadGraph(graph3);
    test *= test1;    //       ==  {0, 1, 1},
                                // {1, 0, 1},
                                // {1, 1, 0}};
    
    CHECK((test).printGraph() == "[0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]\n");
    CHECK(raphael::Algorithms::isContainsCycle(test) == "The cycle is: 0->1->2->0");

    CHECK(raphael::Algorithms::isBipartite(test) == "0");

    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};

    test.loadGraph(graph4);
    test1.loadGraph(graph2);
    test *= test1;

    CHECK(raphael::Algorithms::isBipartite(test) == "The graph is bipartite: A={0, 2}, B={1}");


    CHECK(raphael::Algorithms::negativeCycle(test) == "No negative cycle found.");

    vector<vector<int>> graph5 = { 
        {0, 3, 0, -1},
        {3, 0, -5, 0},
        {0, -5, 0, 2},
        {-1, 0, 2, 0}};
    test.loadGraph(graph5);
    

    vector<vector<int>> graph6 = {      
        {0, 4, 0, 0},
        {0, 0, -6, 0},
        {0, 0, 0, 3},
        {-2, 0, 0, 0}};

    test1.loadGraph(graph6);
    test1 *= test;
    
    CHECK(raphael::Algorithms::negativeCycle(test) == "The negative cycle is: 3->0->1->2->3");
}

TEST_CASE("Test graph ==, !=, <, <=, >, >=")
{   
    // have the same matrix
    raphael::Graph test;
    vector<vector<int>> graph = { 
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    test.loadGraph(graph);

    raphael::Graph test1;
    vector<vector<int>> graph1 = { 
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    test1.loadGraph(graph1);

    CHECK(test == test1);
    CHECK(!(test != test1));
    CHECK(test >= test1);
    CHECK(test <= test1);

    vector<vector<int>> graph2 = {
        {1, 2, 3},
        {5, 1, 1},
        {2, 1, 1}};
    test1.loadGraph(graph2);

    vector<vector<int>> graph3 = {
        {1, 1},
        {1, 1}};
    test.loadGraph(graph3);

    CHECK (test < test1); // the matrix contains the other matrix
    CHECK (!(test > test1));
    CHECK (test != test1);

    vector<vector<int>> graph4 = {
        {1, 1},
        {1, 0}};
    test.loadGraph(graph4);


    CHECK (test < test1); // the matrix doesn't countain the other matrix but tue other matrix has more edges
    CHECK (test <= test1);
    CHECK (test1 > test);
    CHECK (test1 >= test);

    vector<vector<int>> graph5 = {
        {0, 0},
        {0, 0}};
    test.loadGraph(graph5);

    vector<vector<int>> graph6 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    test1.loadGraph(graph6);

    CHECK (test < test1); // the size of the matrix of test1 is bigger
    CHECK (test <= test1);
    CHECK (test1 > test);
    CHECK (test1 >= test);
}


TEST_CASE("Invalid operations")
{
    raphael::Graph test;

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    test.loadGraph(graph);

    raphael::Graph test1;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(test1.loadGraph(weightedGraph)); // not a square matrix

    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    test1.loadGraph(graph2); 
    CHECK_THROWS(test * test1); // not same size
    CHECK_THROWS(test*= test1);
    CHECK_THROWS(test + test1);
    CHECK_THROWS(test += test1);
    CHECK_THROWS(test - test1);
    CHECK_THROWS(test -= test1);
    
}