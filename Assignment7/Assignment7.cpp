//Assignment #7
//Name: Rachel Guzman
//ASU Email Address: rguzma15@asu.edu
//Description: reads from file to get the number of nodes and the number of edges then reads
//             in the start and end vertex and weight of each node to create an undirected
//             graph. It calls on the graph class to print the graph and perform DFS to print
//             out the circuit to travel through the graph

#include "Graph.h"

#include <iostream> //use cin and cout
#include <string> //to use strings
#include <fstream> //read file

using namespace std; 

int main()
{
    
  ifstream file; 
  int numNodes; 
  int numEdges;
  int vertex1; 
  int vertex2; 
  int weight;  

  //open file
  file.open("graph.txt");
  
  //make sure the file has valid information
  if(file.fail())
    {
      cout << "Cannot open file" << endl; 
      return 0; 
    }

  //the first line of the file is the number of nodes and number of edges
  //read in and store the number of nodes and number of edges
  file >> numNodes >> numEdges; 
  //create a graph with the correct number of nodes and edges
  Graph g(numNodes, numEdges);

  //read in the vertexes information as well as the weight
  while(file >> vertex1 >> vertex2 >> weight)
    {
      //add the vertexes with the corresponding weight to the graph
      g.insertEdge(vertex1, vertex2, weight);
    }

  //print out what is contained in the graph
  g.printGraph();
  //perform DFS to find the circuit to travel the graph
  g.DFS();

  //close the file
  file.close();
  
  return 0; 
}
