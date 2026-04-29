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
    LinkedList();
    ~LinkedList();
    bool addElement(string clubName, string univName, int index);
    bool removeElement(string clubName, string univName);
    void printList();
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
  //to keep store waht needs to be deleted
  //Club* current = head; 
  
  //loop through entire linked list
  while(head != NULL)
    {
      //shift to right, save pos in node to keep track of list
      trailer = head->next; 
      //delete previous position
      delete head; 
      removed++; 
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
       if(index == 0)// && temp != NULL)
	 {
	   //connects the last place was to the new node
	   trailer->next = toAdd; 
	   //links the new node with the other part of the linked list
	   toAdd->next = temp;
	   return true; //successfully added
	 }
       /*
       else if(index == 0 && temp == NULL)
	 {
	 }*/
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
    //To be completed
   Club* pos; 
    
   //checks if linked list is empty or not
   if(head == NULL)
     {
       return false; //unsuccessful deletion --> no items to delete
     }

   pos = head;
   //else
     //{
       //checks if there is only one node in the linked list and it matches what want to delete
       if(pos->next == NULL && pos->clubName.compare(someClubName) == 0 && pos->univName.compare(someUnivName) == 0)
	 {
	   //"clears" list by making the head NULL
	   head = NULL; 
	   return true; //successful deletetion
	 }
       //checks if first element in the linked list matches and there are more elements in the list
       else if((pos->clubName.compare(someClubName) == 0) && (pos->univName.compare(someUnivName) == 0))
	 {
	   //shifts the head right one, disconnecting/deleting the original head
	   head = head->next; 
	   return true; //successful deletion
	 }
       //element want to delete is not the first element in the list
       //else
	 //{
	   //node to keep track of where at --> start at second node since already checked for matches with the first node above
	   Club* nextNode = pos->next; 
	   //loop through linked list
	   while(nextNode != NULL)
	     {
	       //checks if current position matches the element to remove
	       //removes if matches
	       if((nextNode->clubName.compare(someClubName) == 0) && (nextNode->univName.compare(someUnivName) == 0))
		 {
		   nextNode = nextNode->next; 
		   return true; //successful deletion
		 }
	       //if the current position doesn't match the element to remove, go to next element in the linked list
	       else
		 {
		   nextNode = nextNode->next; 
		 }
	     }
	   return false; //unsuccessful deletion --> club doesn't exist
	 //}
     //}
 }

//prints the entirety of the linked list, listing the club name followed by the univeristy name for each club. Each entry in the linked list has its own line.
//prints a message if the list is empty 
void LinkedList::printList()
{
  Club* currentElement; 
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
	  cout << "Club Name: " << currentElement->clubName << ", University Name: " << currentElement->univName << endl; 
	  //continues to next node to continue the loop
	  currentElement = currentElement->next; 
	} 
    }
}
