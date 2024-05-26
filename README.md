# EX2 (GRAPH OPERATORS) IN C++

_Author: Raphael Coeffic, 337614747, racoeffic@gmail.com_

In this project, I implemented a add to the first project a lot of operators for graphs.

Like in the precedent project, I work on graph with adjency matrix and I keept all the functions of ex1 but with a lot of new functions.
I implement some help finctions but I am going to explane about the main functions. The friend operator **<<** print the graph.
I divide all the others functions to 3 categories: add/sub, multiplication, boolean of comparison.

## ADD/SUB
First, we have unary plus and minus that return for the + the graph himself and for - the graph*-1.
Secondly, we  have 4 oprator of incrementation. we have `++ and --` but before the object and we have too after the object.
Last, we have the operators of `+,-,+=,-=`.
*for addition or subtract two graphs they need to have the same size.

## Multiplication
Here we have operators that can multiplicate two graph and operator that can multiplicate a graph with a squalar.

## Boolean of comparaison
Here, I implemented all the classic boolean: **==, !=, <, <=, >, >=** by the instructions of the exercice.

I have 3 other files: `tests.cpp`, `main.cpp` and `Makefile`.
For compile all the programs please enter in the terminal please enter `make`
For clean: `make clean`
For run the tests: `./tests`
For run the main: `./main`
In file tests.cpp I test all my operators and show that the algorithms of ex1 still work.
In file main.cpp I show how to use the operators.


