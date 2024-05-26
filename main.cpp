#include "Graph.hpp"
#include "Algorithms.hpp"

#include <stdexcept>
#include <iostream>



using namespace std;
using namespace raphael;

//in this main I will shox how to use different operator of the graph
int main()
{
    Graph g;
    Graph g1;
    
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};

    vector<vector<int>> graph1 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    
    vector<vector<int>> graph2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};

    g.loadGraph(graph); // load the graph

    cout << g << endl;         // Should print: [0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]\n
    
    //unary minus
    g1 = -g;   
    cout << g1 << endl;        // Should print: [0, -1, -1]\n[-1, 0, -1]\n[-1, -1, 0]\n
    
    //++g
    cout << ++g1 << endl;       // Should print: [1, 0, 0]\n[0, 1, 0]\n[0, 0, 1]\n
    //--g
    cout << --g1 << endl; // Should print: [0, -1, -1]\n[-1, 0, -1]\n[-1, -1, 0]\n
    //g++
    cout << (g1++).printGraph() << endl; // Should print: [0, -1, -1]\n[-1, 0, -1]\n[-1, -1, 0]\n
    
    cout << g1 << endl;         // Should print: [1, 0, 0]\n[0, 1, 0]\n[0, 0, 1]\n
    //g--
    cout << (g1--).printGraph() << endl;         // Should print: [1, 0, 0]\n[0, 1, 0]\n[0, 0, 1]\n

    // -
    g1 = g1 - g1 ;
    cout << g1 << endl;  // Should print: [0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]\n
    // +
    g = g1 + g;
    cout << g << endl;        // Should print: [0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]\n
    //+=
    cout << (g+=g) << endl;   // Should print: [0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]\n
    //-=
    cout << (g-=g) << endl; // Should print: [0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]\n

    g.loadGraph(graph);
    g1.loadGraph(graph2);
    //*=
    cout << (g*=g1) << endl;   // Should print: [0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]\n
    // *
    g = g * g1;
    cout << (g) << endl;   // Should print: [0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]\n
    // *int
    g = g * 2;
    cout << (g) << endl;   // Should print: [0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]\n

    bool flag = false;
    g.loadGraph(graph1); g1.loadGraph(graph1);
    flag = (g == g1);
    // ==
    if (flag) cout << "g == g1" << endl; else cout << "(g == g1) --> FALSE" << endl;
    g1 *= 0;
    // !=
    flag = (g != g1);
    if (flag) cout << "g != g1" << endl; else cout << "(g != g1) --> FALSE" << endl;

    vector<vector<int>> graph3 = {
        {1, 2, 3},
        {5, 1, 1},
        {2, 1, 1}};

    vector<vector<int>> graph4 = {
        {1, 1},
        {1, 1}};

    g1.loadGraph(graph3); g.loadGraph(graph4);
    // <=
    flag = (g <= g1);
    if (flag) cout << "g <= g1" << endl; else cout << "(g <= g1) --> FALSE" << endl;
    // <
    flag = (g < g1);
    if (flag) cout << "g < g1" << endl; else cout << "(g < g1) --> FALSE" << endl;
    // >=
    flag = (g1 >= g);
    if (flag) cout << "g >= g1" << endl; else cout << "(g >= g1) --> FALSE" << endl;
    // >
    flag = (g1 > g);
    if (flag) cout << "g > g1" << endl; else cout << "(g > g1) --> FALSE" << endl;


    vector<vector<int>> graph5 = {
        {1, 0},
        {0, 1},
        {0, 0}};
    vector<vector<int>> graph6 = {
        {1, 0},
        {0, 1}};
    vector<vector<int>> graph7 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    try
    {
        g.loadGraph(graph5); // try to load the graph
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }
    g1.loadGraph(graph6); g.loadGraph(graph7);
    try
    {
        g += g1; // try to add two graph with different size
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "The graphs don't have the same num of vertices."
    }
    try
    {
        g -= g1; // try to subtract two graph with different size
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "The graphs don't have the same num of vertices."
    }
    try
    {
        g *= g1; // try to multiplicate two graph with different size
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "The graphs don't have the same num of vertices."
    }

    return 0;
}