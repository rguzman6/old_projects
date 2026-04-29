/*
  Author: Rachel Guzman
  Date: July 6, 2021
  Description: declaration for a node class and an integer based bst class
 */

#pragma once
#ifndef GUZMAN_INT_BST_H
#define GUZMAN_INT_BST_H

//Node class
class BSTNode
{
 private:
  int data; 
  
  BSTNode* left; 
  BSTNode* right; 

 public:
  //constructors
  BSTNode();
  BSTNode(int);

  //getter and setter for data variable
  int getData();
  void setData(int);

  //getters for nodes to left/right of root
  BSTNode* getLeft();
  BSTNode* getRight();
  
  //setters for nodes to left/right of root
  void setLeft(BSTNode*);
  void setRight(BSTNode*);
};

//BST class
class BST
{
 private:
  BSTNode* root; 
  //variable tracks size of BST
  int size; 
  //variable used for toArray function to keep track of index of where to add
  int index; 

 public:
  //constructor/destructor
  BST();
  ~BST();
  
  //methods
  BSTNode* find(int);
  BSTNode* insert(int);
  bool elementExists(int); 
  bool remove(int);

  void empty(BSTNode*);
  int length();
  void printTree();
  int* toArray();


  //helper methods
 private:
  int numNodes(BSTNode*);
  void treeTraversal(BSTNode*);
  void printTreeTraversal(BSTNode*);
  void printTreePreOrder(BSTNode*);
  
  void deleteCaseOne(BSTNode*, BSTNode*); 
  void deleteCaseTwo(BSTNode*, BSTNode*);

  int* addToArray(BSTNode*, int*);
};


#endif
