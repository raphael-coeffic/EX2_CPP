#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <stdexcept>
#include <vector>

#define TRUE 1
#define FALSE 0

using namespace std;
namespace raphael{
    
    class Graph {
    private:
        vector<vector<int>> mat;
        vector<bool> visited; 
        vector<bool> recStack;         // recursion for the directed graph
        int getNumEdges();
        void checkValidity(Graph& a, Graph&b);
        bool haveSameSize(Graph& a, Graph&b);
        bool haveSameEdgesValue(Graph& a, Graph&b);
        bool isSubGraph(Graph& other); 

    public:
        Graph() : mat(0), visited(false), recStack(false) {} //constructor
        void loadGraph(const vector<vector<int>>& mat); //load
        void printGraph() const; // print num of vertices and num of edges
        int isDirected();  // return 1 if the graph is directed and 0 if not
      
        void setVisited(int index, bool val); 
        void resetVisited(); 
        void resetRecStack(); 
        vector<bool> getVisited(); // receive all
        bool getVisited(int index); // overload the precedent function and return if a specific index was visited
        vector<vector<int>> getMatrix(); // return the matrix of the graph
        void setRecStack(int index, bool val); 
        bool getRecStack(int index);
        bool haveNegative(); // if we have a negative edge in the graph return 1 if not 0

        void setValue(size_t i, size_t j, int val);
        
        string printGraph();
        
        friend ostream& operator<<(ostream& out, Graph& g);

        Graph& operator++();  //++g
        Graph operator++(int); // g++
        Graph& operator--(); //--g
        Graph operator--(int); //g--

        Graph operator+(Graph& other);
        Graph& operator+=(Graph& other);
        Graph operator+();


        Graph operator-(Graph& other);
        Graph& operator-=(Graph& other);
        Graph operator-();

        Graph operator*(int multiplicator);
        Graph& operator*=(int multiplicator);
        Graph operator*(Graph& other);
        Graph& operator*=(Graph& other);

        bool operator==(Graph& other);
        bool operator!=(Graph& other);
        bool operator>(Graph& other);
        bool operator>=(Graph& other);
        bool operator<(Graph& other);
        bool operator<=(Graph& other);


    };
}



#endif