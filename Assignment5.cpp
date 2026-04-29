//Assignment #5
//Name: Rachel Guzman
//ASU Email Address: rguzma15@asu.edu
//Description: create a hash table using double hashing that stores class 
//             information
//Hash analysis: For the main hash function, I used the regular double-hashing equation. For the first hash function (h1()), I chose p to be the hash table size because it can reduces what can be chosen to the size of the table. I chose 7 as the p for the second hash function (h2()) because it is a small prime number not a power of 2. I also tested multiple different larger prime numbers and this worked the best. My hash functioned worked well, as the highest number of collisions is less than 5. 

#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

void printMenu();

int main()
{
  //declare variables
  char action = 'Z';
  string courseId; 
  int hashTableSize; 
  string courseInfo; //use to parse
  string idAndCapacity; //use to parse
  int credits; 
  int capacity; 
  string daysAndTime; //use to parse
  string days; 
  string time; 
  string commaDelimiter = ","; //use to parse
  string colonDelimiter = ":"; //use to parse


  //ask user for hash table size
  cout << "Please enter a hash table size." << endl; 
  //store user input
  cin >> hashTableSize;
  //flush the buffer
  cin.ignore(20, '\n'); 

  //create the hash table
  HashTable table(hashTableSize);

  //display options to user once
  printMenu(); 
  
  do
    {
      //ask user what they would like to do
      cout << "What action would you like to perform?" << endl; 
      //store user input
      cin.get(action);
      //makes sure input is upper case
      action = toupper(action);
      //flush the buffer
      cin.ignore(20, '\n'); 

      //commands based on user input
      switch(action)
	{
	  //case A adds an course element to the hash table
	case 'A':
	  //asks user to input information about the course they want to add
	  cout << "Enter a course information using the format courseId:credits:capacity:days,time" << endl;
	  getline(cin, courseInfo);
	  
	  //parse the inputed string
	  int pos;
	  //parse the course ID
	  pos = courseInfo.find(colonDelimiter);
	  courseId = courseInfo.substr(0, pos);
	  courseInfo.erase(0, pos + colonDelimiter.length());
	  //parse the credits
	  pos = courseInfo.find(colonDelimiter);
	  credits = stoi(courseInfo.substr(0, pos));
	  courseInfo.erase(0, pos + colonDelimiter.length());
	  //parse the capacity
	  pos = courseInfo.find(colonDelimiter);
	  capacity = stoi(courseInfo.substr(0, pos));
	  courseInfo.erase(0, pos + colonDelimiter.length());
	  //days and time are the remaining part of the string
	  daysAndTime = courseInfo; 

	  //parse the days and time of the course --> different delimiter
	  int curr;
	  //parse the days
	  curr = daysAndTime.find(commaDelimiter);
	  days = daysAndTime.substr(0, curr);
	  daysAndTime.erase(0, curr + commaDelimiter.length());
	  //time is the reaining part of the string
	  time = daysAndTime; 
	  
	  //add the element into the hash table
	  table.insertElement(courseId, credits, capacity, days, time); 
	  break;

	  //case B searches if a course is in the hash table
	case 'B': 
	  //asks user for which course they would like to find
	  cout << "Enter a courseId" << endl; 
	  getline(cin, courseId);

	  //search for element in the hash table
	  table.searchElement(courseId);
	  break; 

	  //case C updates the capacity of a course 
	case 'C':
	  cout << "Enter a courseId and a capacity value to change to using the format courseId:capacity" << endl; 
	  getline(cin, idAndCapacity);

	  //parse the course ID and capacity that was inputed
	  int position; 
	  //parse the course ID
	  position = idAndCapacity.find(colonDelimiter);
	  courseId = idAndCapacity.substr(0, position);
	  idAndCapacity.erase(0, position + colonDelimiter.length());
	  //the capacity is the rest of the string
	  capacity = stoi(idAndCapacity);

	  //update the element in the hash table
	  table.changeElement(courseId, capacity);
	  break; 

	  //prints the entire hash table
	case 'D':
	  table.printTable(); 
	  break; 

	  //exit
	case 'Q':
	  break; 

	  //default catch-all
	default:
	  cout << "Unknown action" << endl; 
	  break; 
	}
    } while (action != 'Q'); //end loop when user hits Q to quit

  return 0;
}

//prints the menu options for user
void printMenu()
{
  cout << "Choice\t\tAction" << endl;
  cout << "------\t\t------" << endl;
  cout << "A\t\tAdd Course" << endl;
  cout << "B\t\tSearch for Course" << endl;
  cout << "C\t\tChange Course Capacity" << endl;
  cout << "D\t\tPrint Courses" << endl; 
  cout << "Q\t\tQuit" << endl;
} 
