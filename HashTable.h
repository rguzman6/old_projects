//Assignment #5
//Name: Rachel Guzman
//ASU Email Address: rguzma15
//Description: creates a hash table class, with each element in the hash table consisting of a course (created by a struct) that contains the course ID, the credits, capacity, days and time that the course occurs and the number of collisions that entry had. The class has methods that perform double-hashing, inserting a course, searching for a course, changing a course's capacity, and printing the entire hash table. 

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct of all the elements a Course has for the hash table
struct Course
{
  string courseId;
  int credits; 
  int capacity; 
  string days; 
  string time; 
  int collisions; 
}; 

//hash table class
class HashTable
{
 private: 
  Course* table; //actual hash table
  int tableSize; //size of hash table
  int currSize; //to keep track of how many elements have been added 

 public: 
  HashTable(int);
  ~HashTable();
  int h(int, int); //double-hashing
  int h1(int); //hash function 1
  int h2(int); //hash function 2
  void insertElement(string, int, int, string, string);
  void searchElement(string);
  void changeElement(string, int);
  void printTable(); 

};

//constructor
HashTable::HashTable(int tableSize)
{
  this->tableSize = tableSize; 
  //creates hash table of size given by user
  this->table = new Course[tableSize];
  //initializes number of added elements to 0
  currSize = 0; 

  //set default value for every position in the hash table
  //default "none" for strings and 0 for integers
  for(int i = 0; i < tableSize; i++)
    {
      table[i].courseId = "none";
      table[i].credits = 0; 
      table[i].capacity = 0; 
      table[i].days = "none";
      table[i].time = "none";
      table[i].collisions = 0; 
    }
}

//destructor
HashTable::~HashTable()
{
  delete[] table; 
}

//double-hashing
int HashTable::h(int key, int index)
{
  return ((h1(key) + h2(key) * index) % tableSize);
}

//hash function 1
int HashTable::h1(int key)
{
  return (key % tableSize);
}

//hash function 2
int HashTable::h2(int key)
{
  return (7-(key % 7)); 
}

//insert a course into the hash table
void HashTable::insertElement(string id, int credits, int capacity, string days, string time)
{
  //use for double-hashing calculation
  int index = 0; 
  int j; 
  //boolean so that can tell user if the element was unable to be added
  bool added = false;
  //use for double-hashing calaculation
  int key = 0; 

  //turn each char in the courseID to their corresponding ASCII value and add them up to use for double-hashing
  for(int i = 0; i < id.length(); i++)
    {
      key += int(id.at(i));
    }

  do
    {
      //get an index to inset at using hash function
      j = h(key, index); 
      //check if spot trying to insert is empty aka has the default value of "none"
      //if empty, put the course info inputed by the user into the hash table
      if(table[j].courseId.compare("none") == 0)
	 {
	   table[j].courseId = id; 
	   table[j].credits = credits; 
	   table[j].capacity = capacity; 
	   table[j].days = days; 
	   table[j].time = time;
	   //change boolean to true to indicate a spot was found
	   added = true;
	   //increase the number of slots filled in the hash table by 1
	   currSize++;
	   break; 
	 }
      //if a spot doesn't have a default value, increase the number of collisions at that spot
      else
	 {
	  table[j].collisions += 1; 
	 }
      //increment the index if the spot was not found to try a new spot
      index++; 

    } while(currSize != tableSize); 
  
  //print out message if the table is full
  if(added == false)
    {
      cout << "The table is full." << endl; 
    }
}

//searches for a specific course in the hash table
void HashTable::searchElement(string id)
{
  //use for double-hashing calculation
  int index = 0; 
  int j; 
  //boolean to indicate if the element searching for is found or not
  bool found = false; 
  //key for double-hashing calculation
  int key = 0; 

  //loop through each character in the course ID's string and change to corresponding ASCII value and add them all together to use for double-hashing
  for(int i = 0; i < id.length(); i++)
    {
      key += int(id.at(i));
    }

  do
    {
      //find spot to insert using double-hashing
      j = h(key, index);
      //check if the spot seaching is the same as the inputed course seaching for
      //print a found message if true
      if(table[j].courseId.compare(id) == 0)
	{
	  cout << id << " found with credit(s) " << to_string(table[j].credits) << ", capacity " << to_string(table[j].capacity) << " in the days: " << table[j].days << " and the time: " << table[j].time << endl;
	  //change found boolean to true
	  found = true; 
	  break; 
	}
      //increase index by 1 if not found to calculate a new spot to check using double-hashing
      index++; 

    }while(index != tableSize);

  //if not found in the table, print a not found message
  if(found == false)
    {
      cout << id << " not found" << endl; 
    }
}

//changes the capacity of a course
void HashTable::changeElement(string id, int newCapacity)
{
  //use for double-hashing calcuations
  int index = 0; 
  int j; 
  //boolean to see if the course want to change capacity for exists in the hash table
  bool found = false; 
  //use for double-hashing calculations
  int key = 0; 

  //loop through course ID's string and change each character to their corresponding ASCII value and add them up to use as the key for double-hashing
  for(int i = 0; i < id.length(); i++)
    {
      key += int(id.at(i));
    }

  do
    {
      //double-hashing calculation to find an index to check
      j = h(key, index); 
      //check if the spot checking matches the course trying to change capacity of
      //if it matches, change the capacity and print an updated message
      if(table[j].courseId.compare(id) == 0)
	{
	  table[j].capacity = newCapacity;
	  cout << id << " updated" << endl; 
	  //change found boolean to true
	  found = true; 
	  break;
	}
      //increase index by 1 to check another spot in the hash table using double-hashing
      index++; 

    }while(index != tableSize);

  //print a not found message if the element is not in the table
  if(found == false)
    {
      cout << id << " not found" << endl; 
    }
}

//prints the hash table
void HashTable::printTable()
{
  //titles of the columns
  cout << "index\tcollisions\tCourseId\tCredits\tCapacity\tDays\tTime" << endl;
  //loops through the hash table and prints each element of a course as well as the index that they are located
  for(int i = 0; i < tableSize; i++)
    {
      cout << "\t"; 
      cout << to_string(i) << "\t\t"; 
      cout << to_string(table[i].collisions) << "\t\t";
      cout << table[i].courseId << "\t\t";
      cout << to_string(table[i].credits) << "\t\t\t";
      cout << to_string(table[i].capacity) << "\t\t";
      cout << table[i].days << "\t\t";
      cout << table[i].time << endl; 
    }
}
