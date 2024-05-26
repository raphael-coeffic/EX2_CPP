#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace raphael {
    void Graph::loadGraph(const vector<vector<int>>& matrix) 
    {
        size_t size = matrix.size();
        for (auto& row : matrix) 
        {
            if (row.size() != size) // check that we can receive a non square matrix
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
        this->mat.resize(size);
        for (size_t i = 0; i < size; ++i) this->mat[i].resize(size); 
        
        this->mat = matrix;
        this->visited.resize(size, false);
        this->recStack.resize(size, false);
    }

    void Graph::printGraph()const 
    {
        cout << "Graph with " << this->mat.size() << " vertices";
        int edgeCount = 0;
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (this->mat[i][j] > 0) edgeCount++;
            }
        }
        cout << " and " << edgeCount << " edges." << endl;
        
    }

    int Graph::isDirected()
    {
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                //if we have a difference between the matrix and his transpose the graph is directed
                if(this->mat[i][j] != this->mat[j][i])
                    return 1;
            }
            
        }
        return 0;
        
    }


    void Graph::resetVisited() {
        // init all visited to false
        fill(this->visited.begin(), this->visited.end(), 0);
    }

    void Graph::resetRecStack() {
        // init all recStack to false
        fill(this->recStack.begin(), this->recStack.end(), 0);
    }
    
    void Graph::setVisited(int index, bool val){
        //check if the index is on the graph
        if (this->mat.size() < static_cast<size_t>(index) || index < 0)
        {
            throw out_of_range("Invalid index: The graph doesn't countain this index.");
        }
        this->visited[static_cast<size_t>(index)] = val;
    }

    bool Graph::getVisited(int index){
        //check if the index is on the graph
        if (this->mat.size() <= static_cast<size_t>(index) || index < 0) 
        {
            throw out_of_range("Invalid index: The graph doesn't countain this index.");
        }
        return this->visited[static_cast<size_t>(index)];
    }

    vector<bool> Graph::getVisited(){
        return this->visited;
    }

    vector<vector<int>> Graph::getMatrix(){
        return this->mat;
    }

    void Graph::setRecStack(int index, bool val) {
        //check if the index is on the graph
        if (this->mat.size() <= static_cast<size_t>(index) || index < 0)
        {
            throw out_of_range("Invalid index: The graph doesn't countain this index.");
        }
        this->recStack[static_cast<size_t>(index)] = val;
    }

    bool Graph::getRecStack(int index) {
        //check if the index is on the graph
        if (index >= 0 && index < static_cast<int>(this->recStack.size())) {
            return recStack[static_cast<size_t>(index)];
        } else {
            throw out_of_range("Index out of range in getRecStack.");
        }
    }

    bool Graph::haveNegative() {
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (this->mat[i][j] < 0)
                {
                    return true;
                }
                
            }
            
        }
        return false;
    } 


    void Graph::setValue(size_t i, size_t j, int val) {
        this->mat[i][j] = val;
    }

    //return num of edges of the graph
    int Graph::getNumEdges() {
        int res = 0;
        size_t size = getMatrix().size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (mat[i][j] != 0)
                    res++;
            }
            
        }
        return res;
        
    }
    //return a string that show the graph
    string Graph::printGraph() {
        string res = "";
        size_t size = mat.size();

        for (size_t i = 0; i < size; ++i) {
            res += "[";
            for (size_t j = 0; j < size; ++j) {
                res += to_string(mat[i][j]);
                if (j < size - 1) {
                    res += ", "; // add a "," if it is not the last place
                }
            }
            res += "]";
            if (i < size) {
                res += "\n"; // new line 
            }
        }

        return res;
    }

    // operator that print the graph
    ostream& operator<<(ostream& out, Graph& g) {
        return out << g.printGraph() << endl;
    }

    
    // ++g     
    Graph& Graph::operator++() {
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                this->mat[i][j]++;
            }
        }
        return *this;
    }

    //g++
    Graph Graph::operator++(int) {
        Graph temp = *this;  
        ++(*this);       // we add one    
        return temp;      //but we return the graph befor the addition   
    }
    // --g
    Graph& Graph::operator--() {
        size_t size = this->mat.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                this->mat[i][j]--;// we subtract one
            }
        }
        return *this;
        
    }
    
    //g--
    Graph Graph::operator--(int) {
        Graph temp = *this;  
        --(*this);   // we subtract one
        return temp;  //but we return the graph before that       
    }
   
    // this function check if two graphs have the same size
    void Graph::checkValidity(Graph& a, Graph&b) {
        if (!haveSameSize(a, b))
        {
            throw invalid_argument("The graphs don't have the same num of vertices.");
        }
    }
    
    //g + g1
    Graph Graph::operator+(Graph& other) {

        checkValidity(*this, other);

        size_t size = this->mat.size();
        Graph res;
        
        res.loadGraph(mat);

        // Add the edges of the graphs
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < this->mat[0].size(); ++j) {
                res.setValue(i, j, (this->mat[i][j] + other.getMatrix()[i][j]));
            }
        }
        return res;
    }

    // g - g1
    Graph Graph::operator-(Graph& other) {

        checkValidity(*this, other);

        size_t size = this->mat.size();
        Graph res;
        
        res.loadGraph(mat);

        // subtract the edges of the graphs
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < this->mat[0].size(); ++j) {
                res.setValue(i, j, (this->mat[i][j] - other.getMatrix()[i][j]));
            }
        }
        return res;
    }

    // g += g1
    Graph& Graph::operator+=(Graph& other) {

        checkValidity(*this, other);

        // Add
        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < mat[0].size(); ++j) {
                mat[i][j] += other.mat[i][j];
            }
        }

        // Return this object
        return *this;
    }

    // g -= g1
    Graph& Graph::operator-=(Graph& other) {

        checkValidity(*this, other);

        // subtract
        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < mat[0].size(); ++j) {
                mat[i][j] -= other.mat[i][j];
            }
        }

        // Return this object
        return *this;
    }

    // unary plus
    Graph Graph::operator+() {
        return *this;
    }

    // unary minus
    Graph Graph::operator-() {
        Graph res;
        res = +(*this);
        size_t size = res.getMatrix().size();
        int val = 0;
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                val = res.getMatrix()[i][j];
                res.setValue(i, j, ((-1)*(val))); // all the edges * (-1)
            }
        }
        return res;
        
    }

    // g * int
    Graph Graph::operator*(int multiplicator) {
        Graph res;
        res.loadGraph(mat);

        size_t size = res.getMatrix().size();
        int val = 0;
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                val = res.getMatrix()[i][j];
                res.setValue(i, j, ((multiplicator)*(val))); // all the edges * int
            }
        }
        return res;
    }

    // g *= int
    Graph& Graph::operator*=(int multiplicator) {
        Graph res;
        res = (*this) * multiplicator;
        this->loadGraph(res.getMatrix());
        return *this;
    }

    // g * g1
    Graph Graph::operator*(Graph& other) {

        checkValidity(*this, other);

        size_t size = this->mat.size();
        Graph res;
        
        res.loadGraph(mat);
        int val = 0;
        // multiplicate the two graphs
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                for (size_t k = 0; k < size; k++)
                    val += (this->mat[i][k]) * (other.getMatrix()[k][j]);
                
                res.setValue(i, j, val);
                val = 0;
                
            }
        }
        return res;
    }

    // g *= g1
    Graph& Graph::operator*=(Graph& other) {

        Graph res;
        res = (*this) * other;
        this->loadGraph(res.getMatrix());
        return *this;
    }

    // g == g1
    bool Graph::operator==(Graph& other) {
        // check if the graphs have the same matrix
        if (haveSameSize(*this, other))
        {
            if (haveSameEdgesValue(*this, other))
                return true;
        }
        // check if anyone not bigger than the second
        return !(*this > other) && !(other > *this);
        
    }

    // g != g1
    bool Graph::operator!=(Graph& other) {
        return (!((*this) == other));
    }

    // g <= g1
    bool Graph::operator<=(Graph& other) {
        return ((*this < other) || *this == other);
    }

    // g >= g1
    bool Graph::operator>=(Graph& other) {
        return ((*this > other) || *this == other);
    }

    // g > g1
    bool Graph::operator>(Graph& other) {
       
        if (other.isSubGraph(*this))
            return true;
        
        if ((!isSubGraph(other)) && !((other).isSubGraph(*this)))
        {
            bool flag = false;
            if (haveSameSize(*this, other))
            {
                if (haveSameEdgesValue(*this, other))
                    flag = true;
            }
            if (flag == false)
            {
              if (getNumEdges() > other.getNumEdges())
                    return true;
        
                else if(getNumEdges() == other.getNumEdges()) {
                    if (other.mat.size() > mat.size())
                        return true;
                } 
            }
            
            
        }
        return false;
    }

    // g < g1
    bool Graph::operator<(Graph& other) {
        return (!(*this > other) && *this != other);
    }

    // check if a matrix is a submatrix of an other graph
    bool Graph::isSubGraph(Graph& other) {
        if (mat.size() > other.mat.size()) {
            return false; //check the num of vertices
        }
        bool flag = false;
        for (size_t i = 0; i < other.mat.size() - mat.size() + 1; i++)
        {
            for (size_t j = 0; j < other.mat.size() - mat.size() + 1; j++)
            {
                if (other.mat[i][j] == mat[0][0])
                {
                    flag = true;
                    for (size_t n = 0; n < mat.size(); n++)
                    {
                        for (size_t m = 0; m < mat.size(); m++)
                        {
                            if (other.mat[n+i][m+j] != mat[n][m])
                            {
                                flag = false;
                                break;
                            }
                        }
                        if (flag == false)
                            break;
                    }
                }
                if (flag == true)
                    return true; 
            }
        }
        return false;
    }

    bool Graph::haveSameSize(Graph& a, Graph&b) {
        return a.mat.size() == b.mat.size();
    }
    
    
    bool Graph::haveSameEdgesValue(Graph& a, Graph&b) {
        // assume that the two graph have the same num of vertices
        for (size_t i = 0; i < a.mat.size(); i++)
        {
            for (size_t j = 0; j < a.mat.size(); j++)
            {
                if (a.mat[i][j] != b.mat[i][j])
                    return false;
            }
        }
        return true;
    }
}