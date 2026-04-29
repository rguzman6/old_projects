// Assignment #6
// Name: Rachel Guzman
// ASU Email Address: rguzma15@asu.edu
// Description: binary search tree of clubs, where each node is a club that has a club name and a university name. each club node has methods to get and set its left, right, and parent node, getters for its club name and university name, and a print method. the binary search tree implements a pre, post, and in-order walk of the tree, an insert node operation, a right and left rotate operation, a search operation, a tree minimum and maximum operation and tree successor and predecessor operation 

#include <iostream> //to use cout
#include <string> //to use strings
#include <cstdlib> //to use atoi

using namespace std;

//Club represents some club information
class Club
 {
  private: 
    string clubName;
    string universityName;
    Club * left, * right, * parent;


  public:
    //The following two functions are constructors
    Club()
     { 
      clubName = "?";
      universityName = "?";
      parent = NULL;
      left = NULL;
      right = NULL;
     }


    Club(string clubName1, string universityName1)
     {
      clubName = clubName1;
      universityName = universityName1;
     
      parent = NULL;
      left = NULL;
      right = NULL;
     }

    //The following functions are accessor functions
    Club * getLeft()
     {
      return left;
     }

    Club * getRight()
     {
      return right;
     }

    Club * getParent()
     {
      return parent;
     }
     
    string getClubName()
     {
         return clubName;
     }
     string getUniversityName()
     {
         return universityName;
     }
     

    //The following functions are mutator functions
    void setLeft(Club * other)
     {
       left = other;
     }

    void setRight(Club * other)
     {
       right = other;
     }

    void setParent(Club * other)
     {
       parent = other;
     }

    //The print method prints the clubName and universityName
    void print()
     {
         cout << "Club Name: " << clubName << endl;
         cout << "University Name: " << universityName << endl << endl;
     }
 };

//class BinarySearchTree will contains clubs
class BinarySearchTree
 {
  private:
     Club * root;
     int size;
     
  public:
     BinarySearchTree();
     ~BinarySearchTree();
     int postOrderTreeDelete(Club *);
     bool isEmpty();
     void inOrderTreePrint();
     void preOrderTreePrint();
     void postOrderTreePrint();
     void inOrderTreeWalk(Club *);
     void preOrderTreeWalk(Club *);
     void postOrderTreeWalk(Club *);
     Club * treeSearchNode(Club *, string, string);
     Club * treeSearch(string, string);
     Club * treeMinimum();
     Club * treeMaximum();
     Club * treeMinimumNode(Club *);
     Club * treeMaximumNode(Club *);
     Club * treeSuccessor(string,string);
     Club * treePredecessor(string,string);
     bool treeInsert(string,string); 
     bool rightRotate(string, string);
     bool leftRotate(string, string);
 };

//The constructor initialize the root to be NULL
//initializes size to 0 --> size used to count how many deletions occured
BinarySearchTree::BinarySearchTree()
 {
  root = NULL;
  size = 0; 
 }

//The destructor should delete all nodes in the tree 
//and perform garbage collections starting from leaves (bottom-up order). 
//The destructor should also print “The number of nodes deleted: X” 
//where X is the number of nodes deleted
BinarySearchTree::~BinarySearchTree()
 {
   //calls helper methos postOrderTreeDelete() on whole tree
   int numberDeletions = postOrderTreeDelete(root);
   //tells user how many nodes were in the tree (deleted)
   cout << "The number of nodes deleted: " << numberDeletions << endl; 
 }

//deletes all the nodes in the tree using post-order traversal (bottom-up order)
//keeps track of number of nodes were in the tree (gets deleted) and returns that number
int BinarySearchTree::postOrderTreeDelete(Club* node)
{
  if(node != NULL)
    {
      postOrderTreeDelete(node->getLeft());
      postOrderTreeDelete(node->getRight());
      delete node; //deletes the node
      size++; //increases the number of nodes in tree/were deleted
    }
  
  //returns number of nodes that were in the tree/were deleted
  return size; 
}

//Checks if the tree is empty
bool BinarySearchTree::isEmpty()
 {
   if (root == NULL)
    return true;
   else
    return false; 
 }

//prints all nodes using in-order
void BinarySearchTree::inOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    //calls helper method
    inOrderTreeWalk(root);
    cout << "\n";
   }
 }

//own method and helper method for inOrderTreePrint()
//goes through the tree from a specific node and prints all the nodes using in-order traversal
void BinarySearchTree::inOrderTreeWalk(Club* node)
{
  if(node != NULL)
    {
      inOrderTreeWalk(node->getLeft());
      node->print();
      inOrderTreeWalk(node->getRight());
    }
}

//prints all nodes using pre-order
void BinarySearchTree::preOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    //calls helper method
    preOrderTreeWalk(root);
    cout << "\n";
   }
 }

//own method and helper method of preOrderTreePrint()
//goes through the tree from a specific node and prints all the nodes using pre-order traversal
void BinarySearchTree::preOrderTreeWalk(Club* node)
{
  if(node != NULL)
    {
      node->print();
      preOrderTreeWalk(node->getLeft());
      preOrderTreeWalk(node->getRight());
    }
}

//prints all nodes using post-order
void BinarySearchTree::postOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    //calls helper method
    postOrderTreeWalk(root);
    cout << "\n";
   }
 }

//own method and helper method for postOrderTreePrint()
//goes through the tree from a specific node and prints all the nodes using post-order traversal
void BinarySearchTree::postOrderTreeWalk(Club* node)
{
  if(node != NULL)
    {
      postOrderTreeWalk(node->getLeft());
      postOrderTreeWalk(node->getRight());
      node->print();
    }
}

//searches for a specific node in the entire tree, identifying it by its clubName and universityName
Club* BinarySearchTree::treeSearch(string clubName, string uniName)
{
  //checks if the tree is empty
  if(isEmpty())
    {
      return NULL; 
    }
  //tree is not empty, perform the search on the entire tree
  else
    {
      //pass root, clubName, and uniName into treeSearchNode to search entire tree for node
      return treeSearchNode(root, clubName, uniName);
    }
}

//searches for a specific node in the tree starting at a specific node
Club* BinarySearchTree::treeSearchNode(Club* node, string clubName, string uniName)
{
  //key to identify if found the right node
  string key = uniName + clubName; 

  //check if node is NULL or the node is found
  if(node == NULL || (key.compare(node->getUniversityName() + node->getClubName()) == 0))
    {
      //returns NULL if not in the tree, returns the node if found
      return node; 
    }
  //continues through tree if not yet found, going left if the current node's value is greater than the node searching for
  else if(key.compare(node->getUniversityName() + node->getClubName()) < 0)
    {
      return treeSearchNode(node->getLeft(), clubName, uniName);
    }
  //continues through tree if not yet found, going right if the current node's value is less than the node searching for
  else
    {
      return treeSearchNode(node->getRight(), clubName, uniName);
    }
}

//finds the minimum of the entire tree
Club* BinarySearchTree::treeMinimum()
{
  //checks if tree is empty
  if(isEmpty())
    {
      return NULL; 
    }
  //tree is not empty, search entire tree by passing the root to treeMinimumNode method
  else
    {
      return treeMinimumNode(root);
    }
}

//finds the minimum of the tree starting from a specific node (may ignore part of tree if wish to by passing specific node)
Club* BinarySearchTree::treeMinimumNode(Club* node)
{
  //smallest node is all the way to the left
  //continue to move to the left until reach last leaf of tree on left
  while(node->getLeft() != NULL)
    {
      node = node->getLeft();
    }

  //return node at bottom left of tree
  return node; 
}

//finds the maximum of the entire tree
Club* BinarySearchTree::treeMaximum()
{
  //checks if tree is empty
  if(isEmpty())
    {
      return NULL; 
    }
  //tree is not empty, search entire tree by passing the root to treeMaximumNode method
  else
    {
      return treeMaximumNode(root);
    }
}

//finds maximum of tree starting from a specific node (may ingore part of tree if wish to by passing specific node)
Club* BinarySearchTree::treeMaximumNode(Club* node)
{
  //largest node is all the way to the right
  //continue to move all the way to the right until reach last leaf of tree on right
  while(node->getRight() != NULL)
    {
      node = node->getRight();
    }
  
  //return node at bottom right of tree
  return node; 
}

//finds the successor of a node in the tree
//smallest node greater than x
Club* BinarySearchTree::treeSuccessor(string clubName, string uniName)
{
  //creates a node using given clubName and universityName to try to find successor of
  //sees if exists in the tree --> treeSearch also checks if tree is empty
  Club* findSuccessor = treeSearch(clubName, uniName);

  //if node does not exsist in tree or tree is empty, return NULL
  if(findSuccessor == NULL)
    {
      return NULL; 
    }

  if(findSuccessor->getRight() != NULL)
    {
      //return minimum of right subtree tree of current node
      return treeMinimumNode(findSuccessor->getRight());
    }
  else
    {
      //set y to node trying to find successor for's parent
      Club* y = findSuccessor->getParent();

      //loop through while y doesn't equal NULL and the node is the right child of y 
      //move node and y up the tree until y = NULL or the node is no longer the right child of y
      while(y != NULL && findSuccessor == y->getRight())
	{
	  findSuccessor = y; 
	  y = y->getParent();
	}

      return y; 
    }
}

//finds predecessor of a node in the tree
//largest node smaller than x
Club* BinarySearchTree::treePredecessor(string clubName, string uniName)
{
  //creates a node using given clubName and universityName to try to find predecessor of
  //sees if exists in the tree --> treeSearch also checks if tree is empty
  Club* findPredecessor = treeSearch(clubName, uniName);

  //if node does not exist in tree or tree is empty return NULL
  if(findPredecessor == NULL)
    {
      return NULL; 
    }

  if(findPredecessor->getLeft() != NULL)
    {
      //return maximum of left subtree of current node
      return treeMaximumNode(findPredecessor->getLeft());
    }
  else
    {
      //set y to node trying to find predecessor for's parent
      Club* y = findPredecessor->getParent();

      //loop through while y doesn't equal NULL and the node is the left child of y
      //move node and y up the tree until y = NULL or the node is no longer the left child of y
      while(y != NULL && findPredecessor == y->getLeft())
	{
	  findPredecessor = y; 
	  y = y->getParent();
	}

      return y; 
    }
}

//insert a new node into the tree
//returns true or false if the node is inserted
bool BinarySearchTree::treeInsert(string clubName, string uniName)
{
  //create a new club node using the paramenters
  Club* toInsert = new Club(clubName, uniName); 

  //already exists in tree --> NO DUPLICATES
  if(treeSearch(clubName, uniName) != NULL)
    {
      return false; 
    }

  //y will be the parent of node wanting to insert
  Club* y = NULL; 
  //create a copy of the root so can go through tree without changing the root
  Club* x = root; 
  //key will be used to determine if found the right spot to insert
  string key = uniName + clubName;  

  //find the spot to insert the node into the tree
  while(x != NULL)
    {
      y = x; 

      //check if the node wanting to insert is less than the node currently looking at
      if(key.compare(y->getUniversityName() + y->getClubName()) < 0)
	{
	  //go left if node wanting to insert is less than
	  x = x->getLeft();
	}
      else
	{
	  //go right if node wanting to insert is greater than
	  x = x->getRight();
	}
    }

  //link inserted to tree
  toInsert->setParent(y);
      
  //tree is empty, set the root to the ndoe wanting to insert
  if(y == NULL)
    {
      root = toInsert;
      return true; 
    }
  //tree is not empty
  else
    { 
      //node wanting to insert is less than the parent
      if (key.compare(y->getUniversityName() + y->getClubName()) < 0)
	{
	  //set new node to the parent's left child
	  y->setLeft(toInsert);
	  return true; 
	}
      //node wanting to insert is greater than parent
      else
	{
	  //set new node to parent's right child
	  y->setRight(toInsert);
	  return true; 
	}
    }

  //not able to insert
  return false; 

}

//right rotate around a specified node
//returns true or false if able to rotate
bool BinarySearchTree::rightRotate(string clubName, string uniName)
{
  //creates a node using given clubName and universityName to try to find predecessor of
  //sees if exists in the tree --> treeSearch checks if tree is empty
  Club* findPredecessor = treeSearch(clubName, uniName);

  //if node does not exist in tree or tree is empty return NULL
  if(findPredecessor == NULL)
    {
      return NULL; 
    }

  if(findPredecessor->getLeft() != NULL)
    {
      //return maximum of left subtree of current node
      return treeMaximumNode(findPredecessor->getLeft());
    }
  else
    {
      //set y to node trying to find predecessor for's parent
      Club* y = findPredecessor->getParent();

      //loop through while y doesn't equal NULL and the node is the left child of y
      //move node and y up the tree until y = NULL or the node is no longer the left child of y
      while(y != NULL && findPredecessor == y->getLeft())
	{
	  findPredecessor = y; 
	  y = y->getParent();
	}

      return y; 
    }
}

//left rotate on a specific node
//returns true or false if able to rotate
bool BinarySearchTree::leftRotate(string clubName, string uniName)
{
  //creates a node using given clubName and universityName to try to rotate
  //sees if exists in the tree --> treeSearch also checks if tree is empty
  Club* rotate = treeSearch(clubName, uniName);

  //if node doesn't exist in tree or tree is empty, return NULL
  if(rotate == NULL)
    {
      return false; 
    }

  //makes sure there is a right child to rotate
  if(rotate->getRight() != NULL)
    {
      //set a node to the left child
      Club* y = rotate->getRight(); 
      //shift the node wanting to rotate
      rotate->setRight(y->getLeft());
      
      //makes sure left child exists
      if(y->getLeft() != NULL)
	{
	  //sets the left child's parent to the node to rotate
	  (y->getLeft())->setParent(rotate);
	}
      
      //set y parent to rotate parent
      y->setParent(rotate->getParent());

      //if node wanting to rotate was the root
      if(rotate->getParent() == NULL)
	{
	  root = y; 
	}
      //if node wanting to rotate was a child
      else
	{
	  //left child
	  if(rotate == (rotate->getParent())->getLeft())
	    {
	      (rotate->getParent())->setLeft(y);
	    }
	  //right child
	  else
	    {
	      (rotate->getParent())->setRight(y);
	    }
	}

      //set y right child to the node to rotate
      y->setLeft(rotate);
      //rotate y node
      rotate->setParent(y);
      return true; 
    }
  //if there is no right child, return false
  else
    {
      return false; 
    }
}

 
