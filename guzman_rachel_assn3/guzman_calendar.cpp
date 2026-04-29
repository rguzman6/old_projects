/* 
Author: Rachel Guzman
Date: June 28, 2021
Description: compilable code for class definitions for creating a calendar
*/

#include "guzman_calendar.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::ofstream;
 
/**************************************
 *Reminder Class
 *************************************/
//default constructor
Reminder::Reminder()
{
  this->text = "";
}

//overloaded constructor
Reminder::Reminder(string text)
{
  this->text = text; 
}

//deconstructor
Reminder::~Reminder()
{
}

//setter for the text of the Reminder
void Reminder::setText(string reminder)
{
  this->text = reminder;
}

//getter for the text of the Reminder
string Reminder::getText()
{
  return this->text;
}

//toString to display the Reminder
string Reminder::toString()
{
  return "Reminder - " + this->getText();
}

/**************************************
 *Appointment Class
 *************************************/
//default constructor, inherits Reminder defualt constructor to have text
Appointment::Appointment() : Reminder()
{
  this->startTimeHour = 0;
  this->startTimeMin = 0;
  this->endTimeHour = 0;
  this->endTimeMin = 0;
}

//overloaded constructor, inherits Reminder overloaded constructor to have text
Appointment::Appointment(int startHour, int startMin, int endHour, int endMin, string text) : Reminder (text)
{
  this->startTimeHour = startHour; 
  this->startTimeMin = startMin;
  this->endTimeHour = endHour; 
  this->endTimeMin = endMin; 
}

//destructor for Appointment
Appointment::~Appointment()
{
}

//getters for start and end time hours and minutes
int Appointment::getStartTimeHour()
{
  return this->startTimeHour;
}

int Appointment::getStartTimeMin()
{
  return this->startTimeMin;
}

int Appointment::getEndTimeHour()
{
  return this->endTimeHour;
}

int Appointment::getEndTimeMin()
{
  return this->endTimeMin;
}

//setters for start and end time hours and minutes
void Appointment::setStartTimeHour(int startHour)
{
  this->startTimeHour = startHour;
}

void Appointment::setStartTimeMin(int startMin)
{
  this->startTimeMin = startMin;
}

void Appointment::setEndTimeHour(int endHour)
{
  this->endTimeHour = endHour;
}

void Appointment::setEndTimeMin(int endMin)
{
  this->endTimeMin = endMin;
}

//getter for text of Appointment, calls on the inherited getText() from Reminder
string Appointment::getText()
{
  return Reminder::getText();
}

//setter for text of Appointment, calls on inherited getText() from Reminder
void Appointment::setText(string text)
{
  Reminder::setText(text);
}

//formats the start time of Appointment into hh:mm
string Appointment::formatStartTime()
{
  char startTime[6];
  sprintf(startTime, "%02d:%02d", this->getStartTimeHour(), this->getStartTimeMin());
  return startTime; 
}

//formats the end time of Appointment into hh:mm
string Appointment::formatEndTime()
{
  char endTime[6]; 
  sprintf(endTime, "%02d:%02d", this->getEndTimeHour(), this->getEndTimeMin());
  return endTime; 
}

//toString displays time and text of Appointment
string Appointment::toString()
{
  string message = "Appointment - " + this->formatStartTime() + " - " + this->formatEndTime() + " - " + this->getText();
  return message;
}

/**************************************
 *Day Class
 *************************************/
//default constructor
Day::Day()
{
  this->dayNum = 0; 
  this->day = ""; 
}

//overloaded constructor
Day::Day(int dayNum, string day)
{
  this->dayNum = dayNum;
  this->day = day; 
}

//destructor
Day::~Day()
{
}

//adds an errand to this day
void Day::addErrand(Reminder* reminder)
{
  this->errand.push_back(reminder);
}

//removes an errand from the list of errands on this day
void Day::removeErrand(int toRemove)
{
  if(errand.empty())
    {
      cout << "There are no errands on this day to remove." << endl;
      return; 
    }
  //stores text of what is to be deleted
  string errandToDelete = this->errand[toRemove-1]->getText();
  this->errand.erase(errand.begin()+(toRemove-1));
  //lets user know which errand was deleted
  cout << "Errand \"" << errandToDelete << "\" deleted." << endl;   
}

//getter for what day it is on the calendar
int Day::getDayNum()
{
  return this->dayNum;
}

//setter for what day it is on the calendar
void Day::setDayNum(int num)
{
  this->dayNum = num; 
}

//getter for what day of the week it is
string Day::getDay()
{
  return this->day;
}

//setter for what day of the week it is
void Day::setDay(string day)
{
  this->day = day; 
}

//total number of errands on this day
int Day::numErrands()
{
  return this->errand.size();
}

//essentially a toString
//tells what day it is on the calendar and what day of the week it is
string Day::dayInfo()
{
  return to_string(this->getDayNum()) + " - " + this->getDay() + ": ";
}

//lists the errands on this day
string Day::errands()
{
  string errandList = "";
  //checks if vector is empty -> shows a different message than if there are errands
  if(errand.empty())
    {
      return "     No Errands\n";
    }
  else
    {
      //goes through vector and stores errands in a string
      for(unsigned i = 0; i < errand.size(); ++i)
	{
	  errandList += "     ";
	  errandList += errand[i]->toString();
	  errandList += "\n";
	}
      return errandList;
    }
}

//lists errands with a number preceding it 
string Day::listErrands()
{
  string listedErrands = "";
  //checks if vector is empty -> shows a different message than if there are errands
  if(errand.empty())
    {
      return "No Errands\n";
    }
  else
    {
      //goes through vector and stores errands in a string with a number preceding it
      for(unsigned i = 0; i < errand.size(); ++i)
	{
	  listedErrands += to_string(i+1);
	  listedErrands += ". ";
	  listedErrands += errand[i]->toString();
	  listedErrands += "\n";
	}
      return listedErrands;
    }
}

//abbreviated version of the errands of the day -> tells number of errands on day
string Day::abbrvErrands()
{
  if(errand.empty())
    {
      return "No Errands\n";
    }
  else
    {
      return to_string(this->numErrands()) + " Errands\n"; 
    }
}

//toString() -> date, day of the week, errands if there are any
string Day::toString()
{
  return this->dayInfo() + "\n" + this->errands() + "\n"; 
}

/**************************************
 *Calendar Class
 *************************************/
//default constructor
//creates a calendar called Calendar, with 30 days starting on a Monday
Calendar::Calendar()
{
  this->title = "Calendar";
  this->numOfDays = 30;
  this->startDay = "Monday";
  this->days = new Day*[numOfDays];
  int start = 1; 
  string dayConvert; 

  for(int i = 0; i < numOfDays; i++)
    {
      int conversion = ((i+start-1)%7); 
      //switch statement with day assignment to string dayConvert
      switch(conversion)
      {
      case 0:
	dayConvert = "Monday";
	break;
      case 1:
	dayConvert = "Tuesday";
	break;
      case 2:
	dayConvert = "Wednesday";
	break;
      case 3:
	dayConvert = "Thursday";
	break;
      case 4:
	dayConvert = "Friday";
	break;
      case 5: 
	dayConvert = "Saturday";
	break; 
      case 6:
	dayConvert = "Sunday";
	break;
      }
      //assigns each day in array with appropriate day number in calendar and day of the week
      days[i] = new Day(i+1, dayConvert);
    }
} 

//overloaded constructor
Calendar::Calendar(string title, int numDays, int start)
{
  this->title = title; 
  this->numOfDays = numDays; 
  this->setStartDay(start);
  this->startDay = this->getStartDay();
  this->days = new Day*[numOfDays];

  string dayConvert; 

  for(int i = 0; i < numOfDays; i++)
    {
      int conversion = ((i+start-1)%7); 
      //switch statement with day assignment to string dayConvert
      switch(conversion)
      {
      case 0:
	dayConvert = "Monday";
	break;
      case 1:
	dayConvert = "Tuesday";
	break;
      case 2:
	dayConvert = "Wednesday";
	break;
      case 3:
	dayConvert = "Thursday";
	break;
      case 4:
	dayConvert = "Friday";
	break;
      case 5: 
	dayConvert = "Saturday";
	break; 
      case 6:
	dayConvert = "Sunday";
	break;
      }
      //assigns each day in array to approriate day number in calendar and day of the week
      days[i] = new Day(i+1, dayConvert);
    }
}

//destructor
Calendar::~Calendar()
{
  delete this->days; 
}

//getter for name of calendar
string Calendar::getTitle()
{
  return this->title;
}

//setter for name of calendar
void Calendar::setTitle(string title)
{
  this->title = title; 
}

//getter for number of days in calendar
int Calendar::getNumOfDays()
{
  return this-> numOfDays;
}

//setter for number of days in calendar
void Calendar::setNumOfDays(int numDays)
{
  this->numOfDays = numDays;
}

//getter for start day of the week for calendar
string Calendar::getStartDay()
{
  return this->startDay;
}

//setter for start day of the week for calendar
//converts user's choice of 1-7 to corresponsing to a day of the week (1 = Monday, etc) 
void Calendar::setStartDay(int num)
{
  if(num == 1)
    {
      this->startDay = "Monday";
    }
  if(num == 2)
    {
      this->startDay = "Tuesday";
    }
  if(num == 3)
    {
      this->startDay = "Wednesday";
    }
  if(num == 4)
    {
      this->startDay = "Thursday";
    }
  if(num == 5)
    {
      this->startDay = "Friday";
    }
  if(num == 6)
    {
      this->startDay = "Satday";
    }
  if(num == 7)
    {
      this->startDay = "Sunday";
    }
}

//gets a specific day in Day array
Day* Calendar::getDay(int dayNum)
{
  return days[dayNum-1];
}

//displays the calendar with abbreviated version of errands
string Calendar::displayCalendar()
{
  cout << "Calendar \"" << this->getTitle() << "\": " << endl;
  //display day number
  //display day of week
  //display number of errands for each day
  for(int i = 0; i < numOfDays; i++)
    {
      cout << days[i]->dayInfo() << days[i]->abbrvErrands() << endl; 
    }
  return "";
}

//display a specific day with all its errands listed
string Calendar::displayDay(int dayNum)
{
  cout << days[dayNum-1]->toString() << endl; 
  return ""; 
}

//prints calendar to file
//gets a file name from user
void Calendar::printToFile(string fileName)
{
  outFile.open(fileName);
  outFile << this->getTitle() << endl;
  outFile << "-------------" << endl; 
  for(int i = 0; i < numOfDays; i++)
    {
      //prints day number in calendar, day of the week and number of errands first
      outFile << days[i]->dayInfo() << days[i]->abbrvErrands() << endl;
      //if there are errands on anyday, prints them fully underneath the respective day
      if(days[i]->numErrands() > 0)
	{
	  outFile << days[i]->errands() << endl; 
	}
    }
  //lets user know that their calendar has been written to a file
  cout << "Calendar successfully written to file: " << fileName << endl;

  outFile.close(); 
}
