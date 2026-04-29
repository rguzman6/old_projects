//Name: Rachel Guzman 
//ASU Email Address: rguzma15@asu.edu
//Description: assignment files' descriptions

Assignment 7.cpp
Reads from the given file to create a graph and creates a graph by calling on the Graph.h file functions
prints out the what is in the graph for each vertes
prints out the circuit and stack for finding the circuit

Graph.h
implements LinkedList.h and Stack.h
creates an undirected graph provided vertices and weight from the main file
performs DFS on the graph to find the circuit path, keeps track of the paths taken and the true circuit by calling on the Stack.h file functions

Stack.h
has a push, pop, and two print functions to be used in the DFS algorithm in the Graph.h file

LinkedList.h
inserts an edge from a given index to another index with a specific weight and is called in the insertEdge function in Graph.h
it prints the edges in order, called on in Graph.h

Makefile
type "make" to compile
type "./assignment7" to run