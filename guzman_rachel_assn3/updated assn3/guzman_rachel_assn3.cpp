/*
Author: Rachel Guzman 
Date: June 28, 2021
Description: Main code for calendar interface. What interacts with user to build calendar with reminders and errands. 
*/

#include "guzman_calendar.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl; 
using std::cin;
using std::string;
using std::getline;
using std::to_string; 

//helper methods
int  mainMenu(void);
string dayOptions(int);
int errandOptions(void);
int startHourChoice(void);
int startMinChoice(void);
int endHourChoice(int);
int endMinChoice(void);

int main(int argc, char** argv)
{
  //variable for beginning menu option
  int build;
  //variable to check validity of beginning menu option by user
  bool validBuild = false;
  Calendar* cal;

  //variables for what user chooses for main menu and specific day for various methods
  int menuChoice; 
  int dayChoice; 

  int toDelete; 
  bool validDeletion = false; 

  //variable for keeping track of what type of errand they want to create
  int errandType;
  //pointers for reminder and appointment
  Reminder* remind;
  Appointment* appt;
  //file name for printing to file
  string fileName;

  //welcome message
  cout << "Welcome to CSE240 Calendar" << endl;
  cout << '\n';

  //asks user if wants to build a calendar or exit
  //makes sure that the user inputs a valid option
  while (!validBuild)
    {
      cout << "1. Build a new Calendar \n2. Exit" << endl;
      cin >> build;
      if(build == 1 || build == 2)
	{
	  validBuild = true;
	}
      else
	{
	  cout << "Please choose either 1 or 2." << endl; 
	}
    }
  
  //continues to loop through beginning menu until user wants to quit -> allows for multiple calendar builing
  while(build == 1 || build == 2)
    {
      //user wants to make a calendar
      if(build == 1)
	{
	  string calendarTitle; 
	  int numDays; 
	  bool badTotalDays = false; 
	  int startDay; 
	  bool badStartDay = false;

	  //asks user for a name for their calendar
	  cout << '\n'; 
	  cout << "Building a new calendar." << endl; 
	  cout << "Give your calendar a title: " << endl;
	  cin.ignore();
	  getline(cin, calendarTitle);

	  //asks user for how many days they want in their calendar
	  //checks to make sure that they do not put 0 or negative days
	  while(!badTotalDays)
	    {
	      cout << "How many days should this calendar have? " << endl; 
	      cin >> numDays;
	      if(numDays > 0)
		{
		  badTotalDays = true; 
		}
	      else
		{
		  cout << "Please choose a number greater than 0" << endl;
		  badTotalDays = false; 
		}
	    }//end valid input checker total number of days

	  //asks user to choose from list of the 7 days in a week for what day they want their calendar to start on
	  //makes sure user chooses a valid option
	  while(!badStartDay)
	    {
	      cout << "\nWhat day does your calendar start on?" << endl; 
	      cout << "1. Monday \n2. Tuesday \n3. Wednesday \n4. Thursday \n5. Friday \n6. Saturday \n7. Sunday" << endl;
	      cin >> startDay; 
	      if(startDay == 1 || startDay == 2 || startDay == 3 || startDay == 4 || startDay == 5 || startDay == 6 || startDay == 7)
		{
		  badStartDay = true; 
		}
	      else
		{
		  cout << "Please choose a number 1-7" << endl; 
		  badStartDay = false; 
		}
	    }//end valid input checker start day 
      
	  //creates a new calendar based on user input of a name, number of days, and start day
	  cal = new Calendar(calendarTitle, numDays, startDay);
	  //lets user know their calendar has been created
	  cout << "\nYour Calendar has been created.\n" << endl;

	  //displays the main menu and stores the user's choice
	  menuChoice = mainMenu();

	  //continues to loop through so can do multiple thinks/call the main menu multiple times until the user wants to exit
	  while(menuChoice !=0)
	    {
	      //option 1 = displays the entire calendar
	      //shows main menu after displaying
	      if(menuChoice == 1)
		{
		  cout << '\n';
		  cal->displayCalendar();
		  menuChoice = mainMenu();
		}//end menu choice 1

	      //option 2 = displays a specific day's agenda
	      //shows main menu after displaying or if user chooses to go back to main menu and doesn't want to display a day anymore
	      if(menuChoice == 2)
		{
		  bool dayOption = false; 
		  cout << '\n';
		  //displays calendar so user knows their options
		  cal->displayCalendar();

		  //asks user which day they want to display
		  //makes sure is a valid day option
		  while(!dayOption)
		    {
		      cout << "Select which day to display: " << endl;
		      cout << dayOptions(numDays) << " (0 - Back to main menu)" << endl;
		      cin >> dayChoice; 
		      if(dayChoice >= 0 && dayChoice <= numDays)
			{
			  dayOption = true;
			}
		      else
			{
			  //error message to user
			  cout << "Please choose a day on the calendar or 0 to return to the main menu. " << endl; 
			}
		    }

		  //goes back to the main menu if user no longer wants to display a day's agenda
		  if(dayChoice == 0)
		    {
		      menuChoice = mainMenu(); 
		    }
		  //displays the chosen day's agenda
		  //goes back to main menu after displaying
		  else
		    {
		      cout << '\n'; 
		      cout << cal->getDay(dayChoice)->toString() << endl;
		      menuChoice = mainMenu();
		    }
		}//end menu choice 2

	      //option 3 = add an errand to a specific day
	      if(menuChoice == 3)
		{
		  bool dayOption = false; 
	      
		  cout << '\n';
		  //displays calendar so user knows their options
		  cal->displayCalendar();
		  //lets user know they are adding an errand
		  cout << "Add an Errand" << endl;
		  //asks user which day they want to add an errand to
		  //makes sure is a valid day option
		  while(!dayOption)
		    {
		      cout << "Select which day you want to add an Errand to:" << endl; 
		      cout << dayOptions(numDays); 
		      cin >> dayChoice; 

		      if(dayChoice >= 0 && dayChoice <= numDays)
			{
			  dayOption = true;
			}
		      else
			{
			  //error message if not a valid day
			  cout << "Please choose a day on the calendar. " << endl; 
			}
		    }

		  //asks user which type of errand they want to create: reminder or appointment
		  errandType = errandOptions();
		  //adding a reminder
		  //displays main menu after creating and adding reminder
		  if(errandType == 1)
		    {
		      string reminderText;
		      //lets user know creating a reminder, asks for what reminder is
		      cout << "\nCreating a Reminder." << endl;
		      cout << "Enter reminder text: ";
		      cin.ignore();
		      getline(cin, reminderText);
		      remind = new Reminder(reminderText);
		      //adds reminder to chosen day
		      cal->getDay(dayChoice)->addErrand(remind);
		      cout << '\n';
		      menuChoice = mainMenu(); 
		    }
		  //adding an appointment
		  //displays main menu after creating and adding appointment
		  if(errandType == 2)
		    {
		      int startHour; 
		      int startMin;
		      int endHour; 
		      int endMin;
		      string text;
		      //lets user know creating an appointment
		      cout << "\nCreating an Appointment." << endl;
		      //gets start and end time of appointment
		      startHour = startHourChoice();
		      startMin = startMinChoice();
		      endHour = endHourChoice(startHour);
		      endMin = endMinChoice(); 
		      //asks user for what the appointment is
		      cout << "Enter reminder text: ";
		      cin.ignore();
		      getline(cin, text);
		      appt = new Appointment(startHour, startMin, endHour, endMin, text);
		      //adds appointment to chosen day
		      cal->getDay(dayChoice)->addErrand(appt);
		      cout << '\n';
		      menuChoice = mainMenu();
		    }
		  //goes back to main menu if user chooses without adding any errand
		  if(errandType == 0)
		    {
		      menuChoice = mainMenu(); 
		    }

		}//end menu choice 3

	      //option 4 = deleteing an errand from a specific day
	      //goes back to main menu when done
	      if(menuChoice == 4)
		{
		  bool dayOption = false; 
		 
		  cout << '\n';
		  //displays calender so user knows options
		  cal->displayCalendar();
		  cout << "Remove an Errand" << endl;
		  //asks user which day want to delete an errand from
		  //makes sure is a valid day option - can choose 0 to go back to main menu without deleting any errand
		  while(!dayOption)
		    {
		      cout << "Select which day you want to remove an Errand from:" << endl;
		      cout << dayOptions(numDays) << " (0 - Back to main menu)" << endl; 
		      cin >> dayChoice; 

		      if(dayChoice >= 0 && dayChoice <= numDays)
			{
			  dayOption = true;
			}
		      else
			{
			  //error message if not a valid day
			  cout << "Please choose a day on the calendar or 0 to return to the main menu." << endl; 
			}
		    }
		  //goes back to main menu if user chooses without deleting any errand
		  if(dayChoice == 0)
		    {
		      menuChoice = mainMenu(); 
		    }
		  // cout << '\n';
		  //cal->displayCalendar();
		  //deletes an errand
		  else
		    {
		      //lets user know which day they chose to delete an errand from
		      cout << "\nYou have chosen " << cal->getDay(dayChoice)->toString();
		      //asks user which errand they want to delete is
		      //makes sure is a valid option to delete
		      //user can go back to main menu if choose to by choosing 0
		      while(!validDeletion)
			{
			  cout << "Errands:" << endl;
			  cout << cal->getDay(dayChoice)->listErrands();
			  cout << "0. Back to main menu" << endl;
			  cout << "Which would you like to delete?" << endl; 
			  cin >> toDelete;

			  if(toDelete >= 0 && toDelete <= cal->getDay(dayChoice)->numErrands())
			    {
			      validDeletion = true; 
			    }
			  else
			    {
			      //error message if not a valid errand option
			      cout << "That is not a valid errand. Please choose an errand from the list or 0 to return to the main menu." << endl; 
			    }
			}
		      //goes back to main menu if user no longer wants to delete an errand
		      if(toDelete == 0)
			{
			  menuChoice = mainMenu();
			}
		      //detes errand chosen from chosen day
		      //goes back to main menu after deleting
		      else
			{
			  cal->getDay(dayChoice)->removeErrand(toDelete);
			  cout << '\n';
			  menuChoice = mainMenu();
			}
		    }
		}//end menu choice 4

	      //option 5 = print calendar to file
	      //returns to main menu after printing to file
	      if(menuChoice == 5)
		{
		  //asks user for file name
		  cout << "\nPlease enter file name to store to" << endl; 
		  cin.ignore(); 
		  getline(cin, fileName);
		  //prints to file
		  cal->printToFile(fileName);
		  cout << '\n';
		  menuChoice = mainMenu();
		}//end menu choice 5
	    }
	  //if user wants to exit from the main menu, gets taken back to beginning menu
	  //allows for multiple new calendar creation
	  if(menuChoice == 0)
	    {
	      validBuild = false; 
	      while (!validBuild)
		{
		  cout << "\n1. Build a new Calendar \n2. Exit" << endl;
		  cin >> build;
		  if(build == 1 || build == 2)
		    {
		      validBuild = true;
		    }
		  else
		    {
		      cout << "Please choose either 1 or 2." << endl; 
		    }
		}
	    }
	}//end build calendar

      //user doesn't want to create a new calender -> exits program entirely
      else
	{
	  return -1; 
	}
    }//end while build = 1 or 2

  delete remind; 
  delete appt; 
  delete cal; 
  
  return 0; 
}

//displays main menu, returns user's choice from main menu
//makes sure the user chooses a valid menu option
int mainMenu()
{
  bool badChoice = false; 
  int choice; 

  while(!badChoice)
    {
      cout << "What would you like to do?" << endl;
      cout << "1. Display Whole Calendar" << endl;
      cout << "2. Display a Single Day" << endl;
      cout << "3. Add an Errand" << endl;
      cout << "4. Delete an Errand" << endl; 
      cout << "5. Save to a file" << endl;
      cout << "0. Exit" << endl; 
      cin >> choice; 
      
      if(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 0)
	{
	  badChoice = true; 
	}
      else
	{
	  //error message if chooses a number not on the menu
	  cout << "That is not a menu option. Please choose a number from the menu. " << endl;
	  badChoice = false; 
	}
    }//end while

  return choice; 
}

//returns the range of days user can choose from
string dayOptions(int numDays)
{
  return "Day (1 - " + to_string(numDays) + ")";
}

//asks user what type of errand they want to create
//makes sure is a valid errand choice/go back to main menu
int errandOptions()
{
  bool badChoice = false; 
  int errandType; 

  while(!badChoice)
    {
      cout << "\nWhat type of Errand? \n1. Reminder \n2. Appointment \n0. Back to main menu \n";
      cin >> errandType; 
      
      if(errandType == 1 || errandType == 2 || errandType == 0)
	{
	  badChoice = true; 
	}
      else
	{
	  //error message if chooses a number that does not correspond to errand
	  cout << "That is not an errand option. Please choose a number from the menu." << endl;
	  badChoice = false; 
	}
    }//end while

  return errandType; 
}

//asks user for start hour for their appointment
//makes sure is a valid start hour
int startHourChoice()
{
  bool badStartHour = false; 
  int sHour;

  while(!badStartHour)
    {
        cout << "Enter start time hour (24-hour clock): ";
	cin >> sHour;

	if(sHour >= 0 && sHour <= 24)
	  {
	    badStartHour = true;
	  }
	else
	  {
	    //error message if not a valid start hour
	    cout << "Please enter a number between 0 and 24." << endl;
	  }
    }

  return sHour; 
}

//asks user for start minutes for their appointment
//makes sure is a valid start minute
int startMinChoice()
{
  bool badStartMin = false; 
  int sMin;

  while(!badStartMin)
    {
      cout << "Enter start time minutes: ";
      cin >> sMin; 

	if(sMin >= 0 && sMin <= 59)
	  {
	    badStartMin = true;
	  }
	else
	  {
	    //error message if not a valid start minute
	    cout << "Please enter a number between 0 and 59." << endl;
	  }
    }

  return sMin; 
}

//asks user for end hour for their appointment
//passes the start hour to make sure that the appointment end hour occurs after the start time
//makes sure is a valid end hour
int endHourChoice(int startHour)
{
  bool badEndHour = false; 
  int eHour;

  while(!badEndHour)
    {
        cout << "Enter end time hour (24-hour clock): ";
	cin >> eHour;

	if(eHour >= 0 && eHour <= 24 && eHour >= startHour)
	  {
	    badEndHour = true;
	  }
	else
	  {
	    //error if not a valid end hour
	    cout << "Please enter a number between 0 and 24 that is after the start time." << endl;
	  }
    }

  return eHour;
}

//asks user for end minute for their appointment
//makes sure is a valid end minute
int endMinChoice()
{
  bool badEndMin = false; 
  int eMin;

  while(!badEndMin)
    {
        cout << "Enter end time minutes: ";
	cin >> eMin;

	if(eMin >= 0 && eMin <= 59)
	  {
	    badEndMin = true;
	  }
	else
	  {
	    cout << "Please enter a number between 0 and 59." << endl;
	  }
    }

  return eMin;
}

