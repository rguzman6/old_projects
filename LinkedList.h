// Assignment #1
// Name: Rachel Guzman
// ASU Email Address: rguzma15@asu.edu
// Description: Creates the linked list class, with each entry consisting of the club name and the univeristy name. The class has methods that add an entry, removes an entry, and prints all the clubs in the linked list. 

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings

using namespace std;

//struct Club represents some club information
struct Club
{
    string clubName;
    string univName;
    struct Club * next;
};

//class LinkedList will contains a linked list of clubs
class LinkedList
{
    private:
    struct Club * head;
    
    public:
    LinkedList(); //constructor
    ~LinkedList(); //destructor
    bool addElement(string clubName, string univName, int index); //add a club
    bool removeElement(string clubName, string univName); //remove a club
    void printList(); //print all the clubs
};

//Constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//removes all elements in the linked list and frees the memory
//keeps track of the number of entries in the linked list and prints out how many items it removed. 
LinkedList::~LinkedList()
{
  //integer to keep track of the number of elements removed
  int removed = 0;

  //to keep the linked lists' integrity to keep being able to remove all its elements
  Club* trailer; 
  
  //loop through entire linked list
  while(head != NULL)
    {
      //shift to right, save pos in node to keep track of list
      trailer = head->next; 
      //delete previous position
      delete head;
      //increase the number of items removed
      removed++; 
      //make a "new" head with the next node in the list
      head = trailer; 
    }
  //relay how many clubs were deleted to the user
  cout << "The number of clubs deleted is " << to_string(removed) << "\n" << endl; 
}

//adds a club from a specific university to the linked list to a specific position in the linekd list
//if the position is too large or too small or there is no memory to create the position, it returns false
bool LinkedList::addElement(string newClubName, string newUnivName, int index)
 {

   //node to keep track of the new element to add
   Club* toAdd; 
   //node to keep track of position so don't move the head
   Club* temp;

   //checks for valid index (greater than 0)
   if(index < 0)
     {
       return false; 
     }

  //checks if trying to add the element to the beginning of the linked list
   if(index == 0)
     {
       //checks if adding to an empty list
       if(head == NULL)
	 {
	   //create new node and assign club and university name given by the parameters
	   toAdd = new Club;
	   toAdd->clubName = newClubName; 
	   toAdd->univName = newUnivName;
	   //sets the head to this new node
	   head = toAdd; 
	   return true; //Club successfully added
	 }
       //linked list is not empty but want to put the new element at the beginning of the list
       else
	 {
	   //create new node and store club and university name to be added
	   toAdd = new Club; 
	   toAdd->clubName = newClubName; 
	   toAdd->univName = newUnivName; 
	   //shift what was at the head to the next node after current
	   toAdd->next = head; 
	   //link the new node by setting the head to the new node
	   head = toAdd; 
	   return true; //successful add
	 }       
     }
   //user wants to put the new club/university not at the beginning of the list
   else
     {
       //create new node to hold new club at a university to be added
       toAdd = new Club; 
       toAdd->clubName = newClubName; 
       toAdd->univName = newUnivName; 
       //set a temporary node to traverse through linked list without moving the head
       temp = head; 
       //have a node to trail behind the current position to put the new node in the correct place
       Club* trailer; 
       //traverse through the linked list making sure there is something in the linked list and the indes is valid
       while(index > 0 && temp!= NULL)
	 {
	   //put trailer at current position to possibly be used later
	   trailer = temp; 
	   //move to next node in linked list
	   temp = temp->next; 
	   //decrement index to keep track of where trying to place
	   index--; 
	 }
       //if index = 0 and temp != NULL (not at the end of the linked list), add the node
       if(index == 0)
	 {
	   //connects the last place was to the new node
	   trailer->next = toAdd; 
	   //links the new node with the other part of the linked list
	   toAdd->next = temp;
	   return true; //successfully added
	 }
       //this catches if the index is out of bounds
       else
	 {
	   return false; 
	 }
       //just in case nothing works, returns false
       return false; 
     }
 }

//removes a specific club at a specific univeristy from the linked list
//if the club does not exist at a specific university or the club doesn't exist at any university in the list, returns false. 
bool LinkedList::removeElement(string someClubName, string someUnivName)
 {
   //node to keep track of position so don't move head node
   Club* pos; 
   //assign pos node to the head so can begin to use list without moving the head
   pos = head; 

   //checks if linked list is empty or not
   if(pos == NULL)
     {
       return false; //unsuccessful removal --> no items to delete
     }
       
   //checks if there is only one node in the linked list and it matches what want to delete
   if(pos->next == NULL && pos->clubName.compare(someClubName) == 0 && pos->univName.compare(someUnivName) == 0)
     {
       //"clears" list by making the head NULL
       head = NULL; 
       return true; //successful removal
     }

   //checks if first element in the linked list matches and there are more elements in the list
   else if(pos->clubName.compare(someClubName) == 0 && pos->univName.compare(someUnivName) == 0)
     {
       //shifts the head right one, disconnecting/deleting the original head
       head = head->next; 
       return true; //successful removal
     }

   //element want to delete is not the first element in the list
   else 
     { 
       //loop through linked list
       //makes sure not at the end of the linked list, that there is something to link to
       while(pos->next != NULL)
	 {
	   //checks if current position link to next node matches the element to remove
	   //removes if matches
	   if(pos->next->clubName.compare(someClubName) == 0 && pos->next->univName.compare(someUnivName) == 0)
	     {
	       //re-links the list, ignoring the one that matches, linking the node with the node two positions over "ignoring" (removing) the node that want to remove
	       pos->next = pos->next->next; 
	       return true; //successful removal
	     }
	     //if the current position doesn't match the element to remove, go to next element in the linked list to continue the loop
	     else
	     {
	       pos = pos->next; 
	     }
	 }
	     
       return false; //unsuccessful removal --> club doesn't exist
     }

 }

//prints the entirety of the linked list, listing the club name followed by the univeristy name for each club. Each entry in the linked list has its own line.
//prints a message if the list is empty 
void LinkedList::printList()
{
  //create node to loop through the list without moving the head
  Club* currentElement; 
  //set new node to the head to begin the traversal
  currentElement = head; 

  //checks if the linked list is empty
  if(currentElement == NULL)
    {
      //prints corresponding message if empty
      cout << "The list is empty\n" << endl; 
    }
  //linked list has nodes in it
  else
    {
      //loops through linked list
      while(currentElement != NULL)
	{
	  //prints the club name and university at current node
	  cout << "Club Name: " << currentElement->clubName << ", University Name: " << currentElement->univName << "\n" << endl; 
	  //continues to next node to continue the loop
	  currentElement = currentElement->next; 
	} 
    }
}
