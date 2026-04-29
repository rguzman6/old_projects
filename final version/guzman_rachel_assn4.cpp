/*
  Author: Rachel Guzman
  Date: July 6, 2021
  Description: code to test templated BST. Test using BST of types int, char, and string. 
 */
#include "guzman_bst.h"
#include <iostream>
#include <string>

using std::cout; 
using std:: endl; 
using std::string; 

int main(int argc, char** argv)
{
  //create BST on stack -> automatic garbage collection
  BST<int> intTree; 
  BST<char> charTree; 
  BST<string> stringTree; 

  /***********************
   BST of integers
   **********************/
  cout << "Integer BST:" << endl; 
  //adding random values to the tree
  for(int i = 0; i < 75; i++)
    {
      int value = rand() % 100;
      cout << "inserting: " << value << endl; 
      intTree.insert(value);
    }
  
  //printing the original tree
  intTree.printTree();

  //deleting random values in tree
  //values are randomly generated, so some are not in tree
  for(int i = 0; i < 25; i++)
    {
      int value = rand() % 100;
      cout << "Attempting to delete: " << value; 
      bool result = intTree.remove(value); 

      //feedback about whether or not the item attempted to delete was in the tree & deleted or not in the tree (fail)
      if(result == true)
	{
	  cout << " Success!" << endl; 
	}
      else
	{
	  cout << " Fail! " << endl;
	}
    }

  //tries to find 2 random values in the tree 
  //error message is printed if not in tree
  cout << "Attempting to find: 19"; 
  if(intTree.find(19) == NULL)
    {
      cout << " Fail! Not in tree." << endl;
    }
  else
    {
      cout << " Success! " << endl;
    }
  cout << "Attempting to find: 100";
  if(intTree.find(100) == NULL)
    {
      cout << " Fail! Not in tree. " << endl;
    }
  else
    {
      cout << " Success! " << endl; 
    }

  //gets number of nodes in tree & prints it out
  cout << "Length of tree: " << intTree.length() << endl;
  //creates an array of all the items in the BST
  int* array = intTree.toArray();
  cout << "array: " << endl; 
  //goes through BST array and prints to screen 
  for(int i = 0; i < intTree.length(); i++)
    {
      cout << array[i] << " ";
    }
  cout << "\n\n";

  /***************************
   BST of characters
   **************************/
  cout << "Character BST: " << endl;

  //adds random characters to BST
  charTree.insert('a');
  charTree.insert('w');
  charTree.insert('@');
  charTree.insert('u');
  charTree.insert('%');
  charTree.insert('g');
  charTree.insert('0'); 
  charTree.insert('/');
  charTree.insert('p');
  charTree.insert('k');
  charTree.insert('r');

  //outputs the length of the tree
  cout << "Length of tree: " << charTree.length() << endl;
  //creates array of the BST
  char* arr = charTree.toArray(); 
  cout << "array: "; 
  //prints array of BST
  for(int i = 0; i < charTree.length(); i++)
    {
      cout << arr[i] << " ";
    }
  cout << '\n';

  //deleting using elementExists first before deleting
  //checks if the element exists before trying to delete
  //gives feedback to user whether or not the element could be deleted
  cout << "Attempting to remove char j ";
  if(charTree.elementExists('j') == true)
    {
      charTree.remove('j');
      cout << "Success!" << endl; 
    }
  else
    {
      cout << "Could not remove char, it is not in the BST." << endl; 
    }

  //deleting using elementExists first before deleting
  //checks if the element exists before trying to delete
  //gives feedback to user whether or not the element could be deleted  
  cout << "Attempting to remove char % "; 
  if(charTree.elementExists('%') == true)
    {
      charTree.remove('%');
      cout << "Success!" << endl; 
    }
  else
    {
      cout << "Fail!" << endl; 
    }

  //prints the final tree after deletions
  charTree.printTree(); 
  cout << '\n';

  /***************************
   BST of strings
   **************************/
  cout << "String BST: " << endl; 
  //adds string to BST
  stringTree.insert("hello"); 
  stringTree.insert("CSE240");
  stringTree.insert("summer");
  stringTree.insert("dog");
  stringTree.insert("ASU"); 
  stringTree.insert("butterfly");
  stringTree.insert("sun");
  stringTree.insert("target"); 

  //gets length of BST and prints
  cout << "Length of tree: " << stringTree.length() << endl;
  //puts BST into array
  string* stringArr = stringTree.toArray();
  //prints array
  for(int i = 0; i < stringTree.length(); i++)
    {
      cout << stringArr[i] << " "; 
    }
  cout << '\n';

  //deleting using elementExists first before deleting
  //checks if the element exists before trying to delete
  //gives feedback to user whether or not the element could be deleted
  cout << "Attempting to remove: run "; 
  if(stringTree.elementExists("run") == true)
    {
      stringTree.remove("run");
      cout << "Success!" << endl; 
    }
  else
    {
      cout << "Fail!" << endl; 
    }

  //deleting using elementExists first before deleting
  //checks if the element exists before trying to delete
  //gives feedback to user whether or not the element could be deleted
  cout << "Attempting to remove: dog "; 
  if(stringTree.elementExists("dog") == true)
    {
      stringTree.remove("dog");
      cout << "Success!" << endl; 
    }
  else
    {
      cout << "Fail!" << endl; 
    }
  
  //gets final length of tree after deletiongs
  cout << "Length of tree: " << stringTree.length() << endl; 
  //repopulates the string array with updated deletions
  stringArr = stringTree.toArray();
  //prints BST using the array
  for(int i = 0; i < stringTree.length(); i++)
    {
      cout << stringArr[i] << " "; 
    }
  cout << '\n';

  //garbage collection
  delete[] array; 
  delete[] arr; 
  delete[] stringArr; 

  return 0; 
}
