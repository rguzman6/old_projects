/*
Author: Rachel Guzman 
Date: June 28,2021
Description: Library file for calendar. Has a Reminder class, an Appointment class that inherits the Reminder class, a Day class, and a Calendar class. 
*/

#pragma once
#ifndef GUZMAN_CALENDAR_H
#define GUZMAN_CALENDAR_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ofstream;   

//Reminder class
class Reminder
{
  //protected so that the Appointment class can also use
 protected:
  //variable for text of the reminder
  string text;

 public:
  //constructors/destructor
  Reminder();
  Reminder(string);
  virtual ~Reminder();
  //getter and setter for the text of a reminder
  string getText();
  void setText(string);
  //toString that can be overwritten by Appointment class
  virtual string toString();

};

//Appointment class
//Appointment is a Reminder -> inherits Reminder class
class Appointment : public Reminder
{
 private:
  //variables to store the time that the appointment occurs
  int startTimeHour;
  int startTimeMin;
  int endTimeHour;
  int endTimeMin;

 public:
  //contructors/destructors
  Appointment();
  Appointment(int,int,int,int,string);
  ~Appointment();
  //getters for time
  int getStartTimeHour();
  int getStartTimeMin();
  int getEndTimeHour();
  int getEndTimeMin();
  //setters for time
  void setStartTimeHour(int);
  void setStartTimeMin(int);
  void setEndTimeHour(int);
  void setEndTimeMin(int);
  //getter/setter for appointment text
  string getText();
  void setText(string);
  //to format the start and end time into hh:mm
  string formatStartTime();
  string formatEndTime(); 
  //toString overwrites Reminder toString
  string toString();

};

//Day class
class Day
{
 private: 
  //variables that keep track of what day of the month the day is, what day of the week it is, and all the Reminders for that day
  int dayNum;
  string day;
  vector<Reminder*> errand;

 public: 
  //constructors/destructors
  Day();
  Day(int, string);
  ~Day();
  //getters/setters for what day of the month it is, what day of the week it is
  int getDayNum();
  void setDayNum(int);
  string getDay();
  void setDay(string);
  //add an errand to the day
  void addErrand(Reminder*);
  //remove an errand from the day
  void removeErrand(int);
  //track number of errands in a day
  int numErrands();
  //lists all the errands with an accompanying number
  string listErrands();
  //how many errands there are in a day in a string format
  string abbrvErrands();
  //string format of what day of the calendar and what day of the week it is
  string dayInfo();
  //lists all the errands
  string errands(); 
  //toString
  string toString();
};

class Calendar
{
 private:
  //variables to hold the title of a claendar, number of days a calendar has, what day of the week the calender starts at, an array of Days, an outFile to be able to write the calendar to a file
  string title;
  int numOfDays;
  string startDay; 
  Day** days;
  ofstream outFile; 

 public:
  //constructors/destructor
  Calendar();
  Calendar(string, int, int);
  ~Calendar();
  //getters/setters for title, number of days in the calendar, start day
  string getTitle();
  void setTitle(string);
  int getNumOfDays();
  void setNumOfDays(int);
  string getStartDay();
  void setStartDay(int);
  //gets a specific day from the Day array
  Day* getDay(int);
  //displays the entire calendar
  string displayCalendar();
  //displays a single day's agenda
  string displayDay(int);
  //writes calendar to file
  void printToFile(string);
};
#endif
