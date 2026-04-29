// Assignment #7
// Name: Rachel Guzman
// ASU Email Address: rguzma15@asu.edu
// Description:
//

#pragma once
//#ifndef LINKEDLIST_H
//#define LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std; 

struct Node
{
  int vertex; 
  int weight; 
  struct Node* next; 
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

LinkedList::LinkedList()
{
  head = NULL; 
  length = 0; 
}

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

bool LinkedList::insertEdge(int vertex, int weight)
{
  Node* add; 
  Node* temp; 

  add = new Node; 
  add->vertex = vertex; 
  add->weight = weight; 
  add->notUsed = false; 

  if(head == NULL || add->vertex < head->vertex)
    {
      //      if(head == NULL)
      //{
	  add->next = head; 
	  head = add; 
	  return true;
	  //}
      // }
      //else if(add->vertex <= head->vertex)
      //{
	  /*      if(add->vertex == head->vertex)
	{
	  if(head->weight > add->weight)
	    {
	      //temp = head;
	      //add = head; 
	      //add->next = temp; 
	      add->next = head; 
	      head = add; 
	      return true;
	    }
	  if(head->weight < add->weight)
	    {
	      add->next = head->next; 
	      head->next = add;
	      return true; 
	    }
	  
	  if(head->weight == add->weight)
	    {
	      return false; 
	    }
	  
	}
      //temp = head; 
      //add = head; 
      //add->next = temp; 
      add->next = head; 
      head = add; 
      return true; */ 
    }
  else
    {
      temp = head; 

      Node* trail = head; 

      while (temp->next != NULL && temp->next->vertex < add->vertex)
	{
	  trail = temp; 
	  
	  temp = temp->next; 
	}

      if(temp->vertex == add->vertex)
	{
	  //insert by weight
	  if(temp->weight < add->weight)
	    {
	      add->next = temp->next;
	      temp->next = add; 
	      return true; 
	    }
	  //already in list --> don't add again
	  /*
	  if(temp->weight == add->weight)
	    {
	      return false; 
	    }
	  */
	  else
	    {
	      add->next = trail->next; 
	      trail->next = add; 
	  //	  trail->next = add; 
	  // add->next = temp; 
	      return true; 
	    }
	}
      else
	{
	  add->next = temp->next;
	  temp->next = add; 
	  //trail->next = add; 
	  //add ->next = temp; 
	  return true; 
	}

      //catch all
      return false; 
    }
}

int LinkedList::getLength()
{
  Node* curr = head; 

  if (curr == NULL)
    {
      length = 0; 
    }
  else
    {
      while(curr != NULL)
	{
	  length++; 
	  curr = curr->next; 
	}
    }

  return length; 
}

Node* LinkedList::getHead()
{
  return head; 
}

void LinkedList::visitReverse(int vertex, int weight)
{
  Node* temp = head; 

  Node* trail; 
  /*
  while (temp != NULL && temp->vertex != vertex && temp->weight != weight)
    {
      trail = temp; 
	  
      temp = temp->next; 
    }

  temp->notUsed = true; 
  */
  while(temp->next != NULL && temp->next->vertex != vertex && temp->next->weight != weight)
    {
      temp = temp->next; 
    }
  temp->notUsed = true; 
}

void LinkedList::printList()
{
  Node* curr = head; 

  if(curr == NULL)
    {
      cout << "The list is empty\n" << endl; 
    }
  else
    {
      while(curr != NULL)
	{
	  cout << "To: " << curr->vertex << " with weight " << curr->weight << endl; 

	  curr = curr->next; 
	}
    }
}
