// Assignment #7
// Name: Rachel Guzman 
// ASU Email Address: rguzma15@asu.edu
// Description: push, pop, and print functions for the DFS function in Graph.h. Prints out
//              the stack and the final circuit to traverse the graph. 

#pragma once

#include <iostream>
#include <string>

using namespace std; 

//each element in the stack contains and Edge with 2 vertexes and a weight
struct Edge
{
  int vertex1;
  int vertex2; 
  int weight; 
};

class Stack
{
 private:
  int stackSize; 
  Edge* stack;
  //to track if the stack is empty
  int tracker; 
  
 public:
  Stack(int size);
  ~Stack();
  bool push(int vertex1, int vertex2, int weight);
  Edge pop();
  void printStack();
  void printCircuit();
};

//constructor
Stack::Stack(int size)
{
  stackSize = size; 

  //creates a stack with the given size
  stack = new Edge[stackSize];
  //initializes tracker to -1 to indicate it is empty
  tracker = -1; 
}

//destructor
Stack::~Stack()
{
  delete[] stack; 
}

//push method --> adds an edge to the stack
bool Stack::push(int vertex1, int vertex2, int weight)
{
  //creates the edge with the corresponding vertices and weight
  Edge add; 
  add.vertex1 = vertex1; 
  add.vertex2 = vertex2; 
  add.weight = weight; 

  //check for overflow
  if(tracker > stackSize-1)
    {
      //cout << "The stack is full" << endl;
      return false; 
    }
  //add to stack
  else
    {
      //tracker++; 
      //stack[tracker].vertex1 = vertex1; 
      //stack[tracker].vertex2 = vertex2; 
      //stack[tracker].weight = weight;
      stack[++tracker] = add;  
      return true; 
    }
}

//removes an edge from the stack
Edge Stack::pop()
{
  //makes an "empty" edge for when the stack is empty
  Edge temp; 
  temp.vertex1 = 0; 
  temp.vertex2 = 0; 
  temp.weight = 0; 

  //checks if stack is empty
  //returns "empty" edge if it is
  if(tracker == -1)
    {
      //cout << "the stack is empty" << endl;
      return temp; 
    }
  //stack isn't empty, pop out the element
  else
    {
      temp.vertex1 = stack[tracker].vertex1;
      temp.vertex2 = stack[tracker].vertex2;
      temp.weight = stack[tracker].weight; 
      //decrease the number of elements in the stack
      tracker--; 
      return temp;
    }
}

//print the stack
void Stack::printStack()
{
  //checks if the stack is empty or not
  if(tracker == -1)
    {
      cout << "Empty." << endl; 
      return; 
    }

  //loops through the stack and prints out the elements
  for(int i = -1; i < tracker; i++)
    {
      cout << "(" << stack[i+1].vertex1 << "," << stack[i+1].vertex2 << ") ";
    }
  cout << " " << endl; 

}

//prints the final circuit
void Stack::printCircuit()
{
  //loops through each element in the stack
  for(int i = -1; i < tracker; i++)
    {
      //prints the vertices
      cout << "(" << stack[i+1].vertex1 << "," << stack[i+1].vertex2 << ")" << endl; 
    }
}
