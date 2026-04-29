/*
  Author: Rachel Guzman
  Date: July 6, 2021
  Description: method declarations for integer based bst
 */
#include "guzman_intBST.h"
#include <iostream>

using std::cout; 
using std::endl; 

/*************************
 Node class definitions
 ************************/

//default node constructor
BSTNode::BSTNode()
{
  data = 0; 
  left = NULL; 
  right = NULL;
}

//overloaded node constructor
//initializes data into the node
BSTNode::BSTNode(int value)
{
  data = value; 
  left = NULL;
  right = NULL; 
}

//getters and setters

//getter for data
int BSTNode::getData()
{
  return data;
}

//setter for data
void BSTNode::setData(int val)
{
  data = val; 
}

//getter for node to the left
BSTNode* BSTNode::getLeft()
{
  return this->left; 
}

//getter for node to the right
BSTNode* BSTNode::getRight()
{
  return this->right; 
}

//setter for node to the left
void BSTNode::setLeft(BSTNode* left)
{
  this->left = left; 
}

//setter for node to the right
void BSTNode::setRight(BSTNode* right)
{
  this->right = right; 
}

/**********************
BST class definitions
***********************/

//default constructor
BST::BST()
{
  this->root = NULL;
  this->size = 0;
}

//destructor
BST::~BST()
{
  this->empty(this->root);
}

//emptys the entire BST using post-order traversal
void BST::empty(BSTNode* root)
{
  //post-order -> L R M
  if(root != NULL)
    {
      empty(root->getLeft());
      empty(root->getRight());

      //cout << root->getData() << " ";
      delete root; 
    }
}

//finds a specific element in the BST
BSTNode* BST::find(int data)
{
  //check if element exists
  if(this->elementExists(data) == true)
    {
      BSTNode* toFind = this->root; 
      BSTNode* parent; 

      //if element exists goes through the BST to find its pointer
      while((toFind != NULL) && (toFind->getData() != data))
	{
	  if(data < toFind->getData())
	    {
	      parent = toFind; 
	      toFind = toFind->getLeft();
	    }
	  else
	    {
	      parent = toFind; 
	      toFind = toFind->getRight();
	    }
	}
      return toFind; 
    }
  //data isn't in the BST and lets the user know
  else
    {
      cout << "Item is not in the BST." << endl; 
      return NULL; 
    }
}// end find


//BST property through tree
//find place where new node belongs and build and put in tree
//if value is already in tree, return that pointer
BSTNode* BST::insert(int newData)
{  
  //check if inserting into empty tree
  //if it is, make the new node the root and return
  if(this->root == NULL)
    {
      this->root = new BSTNode(newData);
      return this->root; 
    }
  //not an empty tree
  else
    {
      BSTNode* walker = this->root; 
      bool keepWalking = true; 

      while(keepWalking)
	{
	  keepWalking = false; 
	  //check if item is in tree already
	  if(newData == walker->getData())
	    {
	      return walker;
	    }
	  else if(newData < walker->getData())
	    {
	      //less than goes left
	      if(walker->getLeft() != NULL)
		{
		  walker = walker->getLeft();
		  keepWalking = true; 
		}
	      //found place in tree
	      else
		{
		  //build and place new node
		  //update size of BST
		  walker->setLeft(new BSTNode(newData));
		  this->size++;
		  return walker->getLeft(); //return new node pointer
		}
	    }
	  else
	    {
	      //greater than goes right
	      if(walker->getRight() != NULL)
		{
		  walker = walker->getRight();
		  keepWalking = true; 
		}
	      //found place in tree
	      else
		{
		  //build and place new node
		  //update size of BST
		  walker->setRight(new BSTNode(newData));
		  this->size++;
		  return walker->getRight(); 
		}
	    }
	}//end while
    }//end else
  return NULL; //just in case return statement -> should never be reached 
}// end insert

//checks if an element exists in BST already
bool BST::elementExists(int data)
{
  //check if empty tree
  if(this->root == NULL)
    {
      return false; 
    }
  
  BSTNode* toFind = this->root; 
  BSTNode* parent; 

  //goes through BST to see if elemet exists
  //loops through until either finds the node or reaches the end of the BST (the node doesn't exist)
  while((toFind != NULL) && (toFind->getData() != data))
    {
      //if current node is less than data, go left
      if(data < toFind->getData())
	{
	  parent = toFind; 
	  toFind = toFind->getLeft();
	}
      //current node is greater than data, go right
      else
	{
	  parent = toFind; 
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
bool BST::remove(int toDelete)
{
  //checks if empty tree
  if(this->root == NULL)
    {
      return false; 
    }
  
  BSTNode* toRemove = this->root; 
  BSTNode* parent; 

  //loops through BST w/ a dragging pointer until found item to delete or item to delete is not in BST
  while( (toRemove != NULL) && (toRemove->getData() != toDelete))
    {
      if(toDelete < toRemove->getData())
	{
	  parent = toRemove; 
	  toRemove = toRemove->getLeft();
	}
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
  //if not NULL, found item but how is defined here:
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
void BST::deleteCaseOne(BSTNode* parent, BSTNode* remove)
{
  //remove has a right child, shuffle pointers
  if(remove->getRight() != NULL)
    {
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
void BST::deleteCaseTwo(BSTNode* parent, BSTNode* remove)
{
  BSTNode* pred = remove->getLeft(); 
  BSTNode* predParent; 

  //go left then all the way right
  while(pred->getRight() != NULL)
    {
      predParent = pred; 
      pred = pred->getRight(); 
    }

  //pred is now the predecessor, set remove to it to swap
  int temp = remove->getData(); 
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
int BST::length()
{
  return this->numNodes(this->root);  
}

//goes through BST and counts all the nodes
int BST::numNodes(BSTNode* root)
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
void BST::printTree()
{
  this->printTreeTraversal(this->root);
  //this->printTreePreOrder(this->root);
}

//helper method to print the BST
//prints using in-order traversal
void BST::printTreeTraversal(BSTNode* root)
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
void BST::printTreePreOrder(BSTNode* root)
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
int* BST::toArray()
{
  int* array = new int[this->length()];
  index = 0; 
  //helper method to put to array
  this->addToArray(this->root, array);
  return array;  
}

//puts nodes of BST into created array using in-order traversal
int* BST::addToArray(BSTNode* root, int* array)
{
  if(root != NULL)
    {
      addToArray(root->getLeft(), array);
      array[index++] = root->getData();
      addToArray(root->getRight(), array);
    }
  return array; 
}

