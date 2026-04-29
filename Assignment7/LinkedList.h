// Assignment #7
// Name: Rachel Guzman
// ASU Email Address: rguzma15@asu.edu
// Description: there is a linked list for every element in the array - this is the linked list
//              This file creates the linked list, inserts edges in the correct spot into the
//              linked list, prints the list, and identifies if the reverse version of a node
//              has been visited or not

#pragma once

#include <iostream>
#include <string>

using namespace std; 

//each element in the linked list contains a Node 
struct Node
{
  int vertex; 
  int weight; 
  struct Node* next; 
  //variable used for DFS to see if the node has been visited yet
  bool notUsed; 
};

class LinkedList
{
 private:
  struct Node* head; 
  int length; 

 public:
  LinkedList();
  ~LinkedList();
  bool insertEdge(int vertex, int weight);
  int getLength();
  Node* getHead();
  void visitReverse(int vertex, int weight);
  void printList();
};

//constructor
LinkedList::LinkedList()
{
  head = NULL; 
  length = 0; 
}

//destructor
LinkedList::~LinkedList()
{
  Node* trailer; 

  while(head != NULL)
    {
      trailer = head->next; 
      delete head; 
      head = trailer; 
    }
}

//inserts an edge (which vertex it goes to) with its corresponding weight in the correct spot in the linked list
bool LinkedList::insertEdge(int vertex, int weight)
{
  Node* add; 
  Node* temp; 

  add = new Node; 
  add->vertex = vertex; 
  add->weight = weight; 
  //  add->notUsed = false; 

  //if element to be added needs to be inserted at the front of the linked list
  //element is inserted at the from if the list is empty or the vertex it is going to is less than the vertex that is currently at the head of the linked lsit
  if(head == NULL || add->vertex < head->vertex)
    {
      add->next = head; 
      head = add; 
      return true;
    }
  //the vertex to add is greater than or equal to the value at the head
  else
    {
      temp = head; 

      Node* trail = head; 

      //loop through linked list until find place need to insert
      while (temp->next != NULL && temp->vertex < add->vertex)
	{
	  trail = temp; 
	  
	  temp = temp->next; 
	}

      //if the vertex to add is larger, add it to the right of the current node
      if(temp->vertex < add->vertex)
	{
	  add->next = temp->next;
	  temp->next = add; 
	  return true; 
	}
      //if the vertexes are equal, we need to check the weights to insert it into the proper spot
      else
	{
	  //insert by weight
	  //add to right if the weight is larger than the node that is currently in the list
	  if(temp->weight < add->weight)
	    {
	      add->next = temp->next;
	      temp->next = add; 
	      return true; 
	    }
	  //weight is less than node that is currently in the list --> add to left of node
	  //use trailer node to insert it in the right place
	  else
	    {
	      add->next = trail->next; 
	      trail->next = add; 
	      return true; 
	    }
	}
      //catch all
      return false; 
    }
}

//getLength() is used to ge the degree of the element in the array
int LinkedList::getLength()
{
  Node* curr = head; 

  //checks if list is empty
  if (curr == NULL)
    {
      length = 0; 
    }
  //list is not empty
  else
    {
      //loop through the list
      while(curr != NULL)
	{
	  //increase the number of elements in the list
	  length++; 
	  //update position in traversal
	  curr = curr->next; 
	}
    }

  //return the number of nodes in the linked list (its length)
  return length; 
}

//returns the head of the linked list
//used for DFS
Node* LinkedList::getHead()
{
  return head; 
}

//used for DFS
//marks the reverse version of an element as visited so that edge is already traveled both ways because this is an undirected graph
void LinkedList::visitReverse(int vertex, int weight)
{
  Node* temp = head; 

  //loop through list
  while(temp != NULL)
    {
      //check if the node we are at is the correct node
      if(temp->vertex == vertex && temp->weight == weight)
	{
	  //mark this node as visited
	  temp->notUsed = true; 
	  return; 
	}
      //update where we are in the traversal
      temp = temp->next; 
    }
}

//prints out the vertexes in the linked list
void LinkedList::printList()
{
  Node* curr = head; 

  //checks if the list is empty
  if(curr == NULL)
    {
      cout << "The list is empty\n" << endl; 
    }
  //list is not empty
  else
    {
      //loop through the elements in the list
      while(curr != NULL)
	{
	  //indicate what vertex the current element in the array is going to and what its weight is
	  cout << "To: " << curr->vertex << " with weight " << curr->weight << endl; 

	  //update position in traversal
	  curr = curr->next; 
	}
    }
}
