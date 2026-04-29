// Assignment #7
// Name: Rachel Guzman
// ASU Email Address: rguzma15@asu.edu
// Description: creates the graph, an array of linked lists,  calling on the Linked List's 
//              insert edge to create an edge for each element in the array. once the graph
//              has been created, it performs DFS to find the circuit to traverse the graph
//              only visiting each edge no more than once

#pragma once

#include "LinkedList.h"
#include "Stack.h"

#include <iostream>
#include <string>

using namespace std; 

class Graph
{
 private:
  LinkedList* graph;
  Stack* tempStack; 
  Stack* circuit; 

  int graphSize; 
  int numEdges; 

 public:
  Graph(int graphSize, int edges);
  ~Graph();
  void insertEdge(int vertex1, int vertex2, int weight);
  void DFS();
  void DFSVisit(int v, Node* temp);
  void printGraph();
};

//constructor
//creates the linked list for each element in the array
//creates the tempStack and circuit stack to keep track of the paths
Graph::Graph(int graphSize, int edges)
{
  this->graphSize = graphSize; 
  numEdges = edges; 

  //creates an array of linked list
  graph = new LinkedList[graphSize];

  //creates tempStack and circuit stack
  tempStack = new Stack(numEdges);
  circuit = new Stack(numEdges);
}

//destructor
Graph::~Graph()
{
  delete[] graph; 
}

//inserts an edge into the graph
//inserts the reverse version of the edge into the graph as well because it is an undirected graph
//calls the linked list insert edge function
void Graph::insertEdge(int vertex1, int vertex2, int weight)
{
  //insert edge
  graph[vertex1-1].insertEdge(vertex2, weight);
  //insert reverse of edge
  graph[vertex2-1].insertEdge(vertex1, weight); 
}

//performs DFS
//prints the final circuit
void Graph::DFS()
{
  cout << "Computing its circuit....\n" << endl;
  //goes through each element in the array to perform DFS on its corresponding linked list
  for(int i = 0; i < graphSize; i++)
    {
      //gets the linked list at the current array element
      Node* temp = graph[i].getHead();
      //calls DFSVisit on the linked list
      DFSVisit(i+1, temp); 
    }

  //prints out the final circuit to travel the undirected graph
  cout << "The circuit is: " << endl; 
  circuit->printCircuit();
}

//DFS helper method
//prints the stacks
void Graph::DFSVisit(int v, Node* temp)
{
  //loop through the linked list
  while(temp != NULL)
    {
      //checks if the node in the linked list has been visited already
      //notUsed = false --> not visited yet; notUsed = true --> visited
      if(temp->notUsed == false)
	{
	  //add this node to the stack
	  tempStack->push(v, temp->vertex, temp->weight);

	  //print out the current circuit
	  cout << "Circuit: ";
	  circuit->printStack();

	  //print out the current stack
	  cout << "Stack: ";
	  tempStack->printStack();
	  cout << " " << endl; 

	  //update visitation of the node in the linked list
	  temp->notUsed = true; 

	  //update visitation of reverse version of node in linked list bc it's an undirected graph so both ways need to be marked as visited
	  graph[temp->vertex-1].visitReverse(v, temp->weight);
	 
	  //recursive call to keep going theough to get the path
	  DFSVisit(temp->vertex, graph[temp->vertex-1].getHead());
	}

      //update current position for traversal
      temp = temp->next; 
    }

  //get the last element in the stack for the final circuit
  Edge tempEdge = tempStack->pop();

  //reverse the vertexes
  int vertex1 = tempEdge.vertex2; 
  int vertex2 = tempEdge.vertex1; 

  //skip the push if the pop returns the "empty" edge
  if(vertex1 == 0 || vertex2 == 0)
    {
      return; 
    }

//push the edge into the final stack
  circuit->push(vertex1, vertex2, tempEdge.weight);

//print the circuit and the stack again
  cout << "Circuit: ";
  circuit->printStack();
  cout << "Stack: ";
  tempStack->printStack();
  cout << " " << endl; 
}

//prints what the graph contains
//calls on the linked list printList() method
void Graph::printGraph()
{
  cout << "The Graph contains:" << endl; 
  cout << "------------------" << endl; 
  
  //loop through array
  for(int i = 0; i < graphSize; i++)
    {
      //get the number of degrees this vertex has
      int degree = graph[i].getLength(); 
      //print where going from and with how many degrees
      cout << "From: " << i+1 << " with degree " << degree << endl;
      //prints out all the elements in the linked list contained at this array element
      graph[i].printList();
      cout << "\n" << endl; 
    }
}
