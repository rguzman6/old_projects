// Assignment #1
// Name: Rachel Guzman
// ASU Email Address: rguzma15@asu.edu
// Description: This program displays a menu of choices to a user
//        and performs the chosen task. It will keep asking a user to
//        enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

void printMenu();

int main()
   {
       // local variables, can be accessed anywhere from the main method
       char input1 = 'Z';
       string inputInfo;
       string clubName, univName;
       int index;
       string line;
       bool success = false;

       // instantiate a Linked List object
       LinkedList * list1 = new LinkedList();

       printMenu();


       do  // will ask for user input
        {
           cout << "What action would you like to perform?\n";
           cin.get(input1);
           input1 = toupper(input1);
           cin.ignore(20, '\n'); //flush the buffer
           // matches one of the case statement
           switch (input1)
            {
             case 'A':   //Add Club
               cout << "Please enter some club information:\n";
               cout << "Enter its club name:\n";
               getline(cin, clubName);

               cout << "Enter its university name:\n";
               getline(cin, univName);

               cout << "Enter an index to add:\n";
               cin >> index;
               cin.ignore(20, '\n'); //flush the buffer

               success = list1->addElement(clubName, univName, index);
     
               if (success == true)
                cout << clubName << " at " << univName << " added\n";
               else
                cout << clubName << " at " << univName << " not added\n";
               break;
             case 'D':   //Display Clubs
               list1->printList();
               break;
             case 'Q':   //Quit
               delete list1;
               break;
             case 'R':  //Remove Club
               cout << "Please enter a club information to remove:\n";
               cout << "Enter its club name:\n";
               getline(cin, clubName);

               cout << "Enter its university name:\n";
               getline(cin, univName);

               success = list1->removeElement(clubName, univName);
               if (success == true)
                cout << clubName << " at " << univName << " removed\n";
               else
                cout << clubName << " at " << univName << " does not exist\n";
               break;
             case '?':   //Display Menu
               printMenu();
               break;
             default:
               cout << "Unknown action\n";
               break;
            }

        } while (input1 != 'Q');

      return 0;
   }


  /** The method printMenu displays the menu to a user**/
  void printMenu()
   {
     cout << "Choice\t\tAction\n";
     cout << "------\t\t------\n";
     cout << "A\t\tAdd Club\n";
     cout << "D\t\tDisplay Clubs\n";
     cout << "Q\t\tQuit\n";
     cout << "R\t\tRemove Club\n";
     cout << "?\t\tDisplay Help\n\n";
  }


