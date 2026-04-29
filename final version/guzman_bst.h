/*
  Author: Rachel Guzman
  Date: July 6, 2021
  Description: declaration for a templated node class and a templated bst class
 */

#pragma once
#ifndef GUZMAN_INT_BST_H
#define GUZMAN_INT_BST_H

//Node class
template <class T>
class BSTNode
{
 private:
  T data; 
  
  BSTNode<T>* left; 
  BSTNode<T>* right; 

 public:
  //constructors
  BSTNode();
  BSTNode(T);

  //getter and setter for data variable
  T getData();
  void setData(T);

  //getters for nodes to left/right of root
  BSTNode<T>* getLeft();
  BSTNode<T>* getRight();
  
  //setters for nodes to left/right of root
  void setLeft(BSTNode<T>*);
  void setRight(BSTNode<T>*);
};


//BST class
template <class T>
class BST
{
 private:
  BSTNode<T>* root; 
  //variable tracks size of BST
  int size; 
  //variable used for toArray function to keep track of index of where to add node in array
  int index; 

 public:
  //constructor/destructor
  BST();
  ~BST();
  
  //methods
  BSTNode<T>* find(T);
  BSTNode<T>* insert(T);
  bool elementExists(T); 
  bool remove(T);
  void empty();
  int length();
  void printTree();
  T* toArray();


  //helper methods
 private:
  int numNodes(BSTNode<T>*);
  void treeTraversal(BSTNode<T>*);
  void printTreeTraversal(BSTNode<T>*);
  void printTreePreOrder(BSTNode<T>*);
  
  void deleteCaseOne(BSTNode<T>*, BSTNode<T>*); 
  void deleteCaseTwo(BSTNode<T>*, BSTNode<T>*);

  void remove(BSTNode<T>*);
  T* addToArray(BSTNode<T>*, T*);
};


#endif

#include <iostream>
using std::cout;
using std::endl;

/******************************
 Node class method definitions
*******************************/

//default node constructor
template<class T>
BSTNode<T>::BSTNode()
{
  data = 0;
  left = NULL;
  right = NULL;
}

//overloaded node constructor
//initializes data into the node
template <class T>
BSTNode<T>::BSTNode(T value)
{
  data = value;
  left = NULL;
  right = NULL;
}

//getters and setters

//getter for data
template <class T>
T BSTNode<T>::getData()
{
  return data;
}

//setter for data
template <class T>
void BSTNode<T>::setData(T val)
{
  data = val;
}

//getter for node to the left
template <class T>
BSTNode<T>* BSTNode<T>::getLeft()
{
  return this->left;
}

//getter for node to the right
template <class T>
BSTNode<T>* BSTNode<T>::getRight()
{
  return this->right;
}

//setter for node to the left
template <class T>
void BSTNode<T>::setLeft(BSTNode<T>* left)
{
  this->left = left;
}

//setter for node to the right
template <class T>
void BSTNode<T>::setRight(BSTNode<T>* right)
{
  this->right = right;
}

/***************************
BST class method definitions
****************************/

//default constructor
template <class T>
BST<T>::BST()
{
  this->root = NULL;
  this->size = 0;
}

//destructor
template <class T>
BST<T>::~BST()
{
  this->remove(this->root);
}

//emptys entire BST using helper method
//makes root NULL once empty
template <class T>
void BST<T>::empty()
{
  this->remove(this->root);
  this->root = NULL; 
}
//helper meothod that emptys the entire BST using post-order traversal
template <class T>
void BST<T>::remove(BSTNode<T>* root)
{
  //post-order -> L R M
  if(root != NULL)
    {
      remove(root->getLeft());
      remove(root->getRight());

      //cout << root->getData() << " ";
      delete root;
    }
}

//finds a specific element in the BST
template <class T>
BSTNode<T>* BST<T>::find(T data)
{
  //check if element exists
  if(this->elementExists(data) == true)
    {
      BSTNode<T>* toFind = this->root;
      //BSTNode<T>* parent;

      //if element exists goes through the BST to find its pointer
      //loop stops if reaches end of BST and isn't in it or finds elemet looking for
      while((toFind != NULL) && (toFind->getData() != data))
	{
	  //if the current pos isn't the element looking for and is less than, makes the tracking pointer the left child
	  if(data < toFind->getData())
	    {
	      //parent = toFind;
	      toFind = toFind->getLeft();
	    }
	  //if the current pos isn't the element looking for and is greater than, makes the tracking pointer the right child
	  else
	    {
	      //parent = toFind;
	      toFind = toFind->getRight();
	    }
	}
      return toFind;
    }
  //data isn't in the BST, returns NULL
  else
    {
      return NULL;
    }
}// end find


//BST property through tree
//find place where new node belongs and build and put in tree
//if value is already in tree, return that pointer
template <class T>
BSTNode<T>* BST<T>::insert(T newData)
{
  //check if inserting into empty tree
  //if it is, make the new node the root and return
  if(this->root == NULL)
    {
      this->root = new BSTNode<T>(newData);
      return this->root;
    }
  //not an empty tree
  else
    {
      BSTNode<T>* walker = this->root;
      //keep track if we still need to continue through the tree
      bool keepWalking = true;

      while(keepWalking)
	{
	  //assume don't need to keep walking, will change later if need to 
	  keepWalking = false;
	  //check if item is in tree already
	  if(newData == walker->getData())
	    {
	      return walker;
	    }
	  //less than walker pointer goes left
	  else if(newData < walker->getData())
	    {
	      //if has a child goes left again and keeps walking
	      if(walker->getLeft() != NULL)
		{
		  walker = walker->getLeft();
		  keepWalking = true;
		}
	      //found place in tree -> there's no child
	      else
		{
		  //build and place new node
		  //update size of BST
		  walker->setLeft(new BSTNode<T>(newData));
		  this->size++;
		  return walker->getLeft(); //return new node pointer
		}
	    }
	  //greater than walker pointer goes right
	  else
	    {
	      //if has a child goes right and keeps walking
	      if(walker->getRight() != NULL)
		{
		  walker = walker->getRight();
		  keepWalking = true;
		}
	      //there's no child -> found place in tree
	      else
		{
		  //build and place new node
		  //update size of BST
		  walker->setRight(new BSTNode<T>(newData));
		  this->size++;
		  return walker->getRight();
		}
	    }
	}//end while
    }//end else
  return NULL; //just in case return statement -> should never be reached
}// end insert

//checks if an element exists in BST already
template <class T>
bool BST<T>::elementExists(T data)
{
  //check if empty tree
  if(this->root == NULL)
    {
      return false;
    }

  BSTNode<T>* toFind = this->root;
  //BSTNode<T>* parent;

  //goes through BST to see if elemet exists
  //loops through until either finds the node or reaches the end of the BST (the node doesn't exist)
  while((toFind != NULL) && (toFind->getData() != data))
    {
      //if current node is less than data, go left
      if(data < toFind->getData())
	{
	  //parent = toFind;
	  toFind = toFind->getLeft();
	}
      //current node is greater than data, go right
      else
	{
	  //parent = toFind;
	  toFind = toFind->getRight();
	}
    }

  //returns true/false if node is in BST or not
  if(toFind == NULL)
    {
      return false;
    }
  else
    {
      return true;
    }
}// end elementExists

//removes a node from the BST
//BST property through tree w/ parent pointer behind
//if find, make NULL and return false
template <class T>
bool BST<T>::remove(T toDelete)
{
  //checks if empty tree
  if(this->root == NULL)
    {
      return false;
    }

  BSTNode<T>* toRemove = this->root;
  BSTNode<T>* parent;

  //loops through BST w/ a dragging pointer until found item to delete or item to delete is not in BST
  while( (toRemove != NULL) && (toRemove->getData() != toDelete))
    {
      //less than, go left
      if(toDelete < toRemove->getData())
	{
	  parent = toRemove;
	  toRemove = toRemove->getLeft();
	}
      //greater than go right
      else
	{
	  parent = toRemove;
	  toRemove = toRemove->getRight();
	}
    }

  //either remove is NULL or found item
  if(toRemove == NULL)
    {
      return false;
    }
  //if not NULL, found item but how is defined here(where came from):
  //node to remove has no children
  if((toRemove->getLeft() == NULL) && (toRemove->getRight() == NULL))
    {
      //case 0
      if(parent->getLeft() == toRemove)
	{
	  parent->setLeft(NULL);
	}
      else
	{
	  parent->setRight(NULL);
	}
      delete toRemove;
    }
  //node to remove has two children
  else if((toRemove->getLeft() != NULL) && (toRemove->getRight() != NULL))
    {
      //case 2
      this->deleteCaseTwo(parent, toRemove);
    }
  //node to remove has one child
  else
    {
      //case 1
      this->deleteCaseOne(parent, toRemove);
      delete toRemove;
    }

  this->size--;
  return true;
}

//helper method to remove a node if the node has one child
//determine where one child is, shuffle pointers
template <class T>
void BST<T>::deleteCaseOne(BSTNode<T>* parent, BSTNode<T>* remove)
{
  //remove has a right child, shuffle pointers
  if(remove->getRight() != NULL)
    {
      //check which direction traveled using parent(dragging) pointer
      //assigns which direction went in to the parent pointer
      if(parent->getRight() == remove)
	{
	  parent->setRight(remove->getRight());
	}
      else
	{
	  parent->setLeft(remove->getRight());
	}
      //isolate remove
      remove->setRight(NULL);
    }
  //remove has a left child, shuffle pointers
  else
    {
      //check which direction traveled using parent(dragging) pointer
      //assigns which direction went in to the parent pointer
      if(parent->getRight() == remove)
	{
	  parent->setRight(remove->getLeft());
	}
      else
	{
	  parent->setLeft(remove->getLeft());
	}
      //isolate remove
      remove->setLeft(NULL);
    }
}

//helper method to remove a node if the node has two children
//have 2 children and need nearest successor/predeccessor
template <class T>
void BST<T>::deleteCaseTwo(BSTNode<T>* parent, BSTNode<T>* remove)
{
  BSTNode<T>* pred = remove->getLeft();
  BSTNode<T>* predParent;

  //go left then all the way right
  while(pred->getRight() != NULL)
    {
      predParent = pred;
      pred = pred->getRight();
    }

  //pred is now the predecessor, set remove to it to swap
  T temp = remove->getData();
  remove->setData(pred->getData());
  pred->setData(temp);

  //delete pred
  if((pred->getRight() == NULL) && (pred->getLeft() == NULL))
    {
      //case 0 -> pred has no children
      if(predParent->getRight() == pred)
	{
	  predParent->setRight(NULL);
	  delete pred;
	}
      //case 1 -> pred has one child
      else
	{
	  this->deleteCaseOne(predParent,pred);
	  delete pred;
	}
    }
}

//return number of nodes in the BST
template <class T>
int BST<T>::length()
{
  return this->numNodes(this->root);
}

//goes through BST and counts all the nodes
template <class T>
int BST<T>::numNodes(BSTNode<T>* root)
{
  //checks if tree is empty/base case
  if(root == NULL)
    {
      return 0;
    }
  //counts number of nodes in left subtree & number of nodes in right subtree
  //adds together and adds one
  else
    {
      return numNodes(root->getLeft()) + numNodes(root->getRight()) + 1;
    }
}

//prints the BST in-order
template <class T>
void BST<T>::printTree()
{
  this->printTreeTraversal(this->root);
  cout << '\n'; 
  //this->printTreePreOrder(this->root);
}

//helper method to print the BST
//prints using in-order traversal
template <class T>
void BST<T>::printTreeTraversal(BSTNode<T>* root)
{
  //in-order -> L M R
  if(root != NULL)
    {
      printTreeTraversal(root->getLeft());
      cout << root->getData() << " ";
      printTreeTraversal(root->getRight());
    }
}

//helper method to print the BST
//prints using pre-order traversal
template <class T>
void BST<T>::printTreePreOrder(BSTNode<T>* root)
{
  //pre-order -> M L R
  if(root != NULL)
    {
      cout << root->getData() << " ";
      printTreeTraversal(root->getLeft());
      printTreeTraversal(root->getRight());
    }
}

//creates an array on command of the BST, returns the array
template <class T>
T* BST<T>::toArray()
{
  T* array = new T[this->length()];
  index = 0;
  //helper method to put to array
  this->addToArray(this->root, array);
  return array;
}

//puts nodes of BST into created array using in-order traversal
template <class T>
T* BST<T>::addToArray(BSTNode<T>* root, T* array)
{
  if(root != NULL)
    {
      addToArray(root->getLeft(), array);
      array[index++] = root->getData();
      addToArray(root->getRight(), array);
    }
  return array;
}

