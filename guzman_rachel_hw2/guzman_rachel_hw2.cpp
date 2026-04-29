/*
Name: Rachel Guzman
Date: June 10, 2021
Description: create a path from a starting point to a goal point, both points given by the user in a grid whose size is given by the user. The user also provides a percentage for how much of the grid they would like there to be obstacles, and the obstacles are assigned at random for each time the code it run. The path is created by a flood-filled integer grid then depicted with a character grid that shows the starting point, ending point, and one possible path. Environment can also be created by reading from a given file.  
Usage: basic command line syntax to compile and run. this code was written with C++. Command line syntax to compile: g++ -g -Wall guzman_rachel_assn2.cpp -o <exe>  To run: ./<exe>
user will be prompted on screen. Generate from a file - command line syntax to run: ./<exe> <fileToRead> -f
Read File Format: to read from a file to generate the environment, it must be formatted in this way:
<number of rows>
<number of columns> 
<grid of 0s and 1s to indicate initial environment (1s indicate an obstacle)>
*/

#include <iostream>
#include <iomanip>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <queue>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::setw;
using std::max;
using std::queue;

//outputs integer array to screen
void PrintEnvironment(int** array, int width, int height)
{
  for(int row = 0; row < height; row++)
    {
      for(int col = 0; col < width; col++)
	{
	  cout << setw(3)  << array[row][col];
	}
      cout << endl;
    }
}
//outputs character array to screen
void PrintCharEnvironment(char** array, int width, int height)
{
  for(int row = 0; row < height; row++)
    {
      for(int col = 0; col < width; col++)
	{
	  cout << setw(3) << array[row][col];
	}
      cout << endl;
    }
}


//flood fill algorithm
void numWave(int** array, int yGoal, int xGoal, int width, int height)
{ 
  //create 2 queues to hold the x and y value of the location
  queue<int> xValue;
  queue<int> yValue;
  //initialize queue with only the goal position
  xValue.push(xGoal); 
  yValue.push(yGoal); 

  //loops until the queue is empty
  while(!xValue.empty() && !yValue.empty())
    {
      //checks all 8 directions surrounding the current position to fill
      for(int i = -1; i <= 1; i++)
	{
	  for(int j = -1; j <= 1; j++)
	    {
	      //checks to make sure the direction traveling is in bounds and is not an obstacle
	      if((yValue.front()+i) < height && (yValue.front()+i) >= 0 && (xValue.front()+j) < width && (xValue.front()+j) >= 0 && array[yValue.front()+i][xValue.front()+j] == 0 )
		{
		  //if it is not an obstacle and in bounds, adds 1 to the value stored at the original location
		  array[yValue.front()+i][xValue.front()+j] = array[yValue.front()][xValue.front()] + 1;
		  //adds x and y values of direction went to queue
		  xValue.push(xValue.front()+j);
		  yValue.push(yValue.front()+i);
		}
	    }
	}
      //removes the x and y values of the current position so that it is known that it is already been filled
      xValue.pop();
      yValue.pop();
    }
}

//finds path
void findPath(int** array, char** charArray, int startx, int starty, int width, int height)
{
  //initializes the smallest number to use as path finder as the value at the start position
  int smallest = array[starty][startx];
  //keeps track of the current x and y position; initialized as the start position
  int xPos = startx;
  int yPos = starty; 
  //keeps track of whether or not the goal has been reached
  bool reachedGoal = false; 

  //continues to loop until to goal is reached
  while(!reachedGoal)
  {
    //travels in all 8 directions surrounding the current position
      for(int i = -1; i <= 1; i++)
	{
	  for(int j = -1; j <= 1; j++)
	    {
	      //if the direction traveling is in bounds, not an obstacle and less than the smallest value
	      if((yPos+i) < height && (yPos+i) >= 0 && (xPos+j) < width && (xPos+j) >= 0 && array[yPos+i][xPos+j] != -1 && array[yPos+i][xPos+j] < smallest)
		{
		  //if the direction traveled is the goal position updated reachedGoal to end loop
		  if(charArray[yPos+i][xPos+j] == '$')
		    {
		      reachedGoal = true; 
		    }
		  //if not the goal position is not yet reached and the direction traveled has not yet ben traveled (indicated by a '*' in the character array
		  //updated what the smallest value is and the x and y position to the smallest value's coordinates to know where to travel
		  else if(charArray[yPos+i][xPos+j] == ' ')
		    {
		      //mark the previous loop's minimum value on the character array
		      charArray[yPos][xPos] = '*';
		      //update the smallest number
		      smallest = array[yPos+i][xPos+j];
		      xPos = xPos+j;
		      yPos = yPos+i;
		    }
		}
	    }
	}
      //indicate path on character array from the minimum value of all the 8 directions
      charArray[yPos][xPos] = '*'; 
  }
}

int main(int argc, char** argv)
{
  int width; //width of grid
  int height; //height of grid
  int impassible; //percent impassible 
  char badInput; //checker for if user inputs over 40% for impassible
  double percentImpass; //decimal value of percent impassible
  int obstacles; //actual number of obstacles in the gird based on percent impassible
  int** intGrid; //array for the grid
  int goalx; //x value/"coordinate" for the goal user wants to reach
  int goaly; //y value/"coordinate" for the goal user wants to reach
  char** charGrid; //array for character version of grid
  int startx; //x value/"coordinate" for starting position to make path to goal
  int starty; //y value/"coordinate" for starting position to make path to goal
  ofstream outFile; //file for final environment wave and character path
  bool validGoal = false; //makes sure the goal position is valid
  bool validStart = false; //makes sure the start position is valid
  bool validGrid = false; //makes sure the grid is big enough

  //welcome message and asks user for side of the grid they would like, asking for width and height individually
  cout << "Welcome to Rachel Guzman's CSE240 WaveFront Pather\n\n";
  //checks to see if has correct command line syntax and wants to read from the file (indicated by the -f in the last argument)
  //if command line syntax is wrong, the code will run as if there was no file to read from
  if(argc == 3 && strcmp(argv[2], "-f") == 0)
    {
 
      ifstream inFile; 
      //opens the given file by the user to read from
      inFile.open(argv[1]);
      
      //makes sure that the file can be opened
      if(inFile.fail())
	{
	  cout << "Error: File cannot be opened" << endl;
	  return -1;
	}
      
      //line count to know if reading the height and width or the array
      //0 indicates we are at the top of the file, about to read the first line
      int linecount = 0;
      //queue to store all the values in the given grid to later assign obstacles to the grid that will be used for the rest of the code
      queue<int> array;
      //checks that we are not at the end of the file
      while(!inFile.eof())
	{
	  int read; 
	  //reads each number that is in the file
	  inFile >> read; 
	  //checks that we are reading the first line, which indicates the number of rows the user wishes the grid to have
	  //also checks that we are not at the end of the file
	  if(!inFile.eof() && linecount == 0)
	    {
	      //assigns the height of the grid to the number of rows the user indicated
	      height = read;
	      cout << "Height: " << height << endl;
	      //increases the line count so we know we will read line 2 next (the number of columns)
	      linecount++; 
	    }
	  //checks that we are reading the second line, which indicates the number of columns the user wishes the grid to have
	  else if(!inFile.eof() && linecount == 1)
	    {
	      //assigns the width of the grid to the number of columns the user indicated
	      width = read; 
	      cout << "Width: " << width << endl; 
	      //increases the line count so we know that we are now reading the values of the array
	      linecount++;
	    }
	  //when we are not reading the first or second line, we are reading the values of the array
	  else
	    {
	      //adds all the values of the array to a queue row by row to later use to make the array that we will use for the rest of the code
	      array.push(read);
	    }
	} //end while
      //create integer array and initialize to 0 based on the width and height in the file
      intGrid = new int*[height];
      for(int row = 0; row < height; row++)
	{
	  intGrid[row] = new int[width];
	  for(int col = 0; col < width; col++)
	    {
	      intGrid[row][col] = 0; 
	    }
	}
      
      //goes through the grid to mark the obstacles that are given by a 1 in the file
      for(int row = 0; row < height; row ++)
	{
	  for(int col = 0; col < width; col++)
	    {
	      //checks is the number in the array, the front of the queue is a 1
	      //if it is a 1, mark that same spot on the integer array with a -1 to show an obstacle
	      //remove that number from the queue since we already added it to the environment array
	      if(array.front() == 1)
		{
		  intGrid[row][col] = -1;
		  array.pop();
		}
	      //if the number in the file array, the front of the queue is not a 1/obstacle, simply removes that number from the queue to make sure everything lines up correctly
	      //don't need to assign the intGrid to the queue value since we initialized the intGrid array at 0
	      else
		{
	          array.pop();
		}
	    }
	}
      //prints the environment that was given in the file
      PrintEnvironment(intGrid, width, height);

      inFile.close();
    }
  else
    {
      //asks user how big of an environment that want to create
      cout << "Please tell me about the grid you want to generate.\n";
      //makes sure that the grid is at least 10x10
      while(!validGrid)
	{
	  cout << "Enter the width (at least 10): ";
	  cin >> width; 
	  cout << "Enter the height (at least 10): ";
	  cin >> height; 
	  if(width >= 10 && height >= 10)
	    {
	      validGrid = true;
	    }
	  //if not at least 10x10 informs user and reprompts
	  else
	    {
	      cout << "Please make your grid at least 10x10." << endl;
	    }
	}

      //create integer array and initialize to 0
      intGrid = new int*[height];
      for(int row = 0; row < height; row++)
	{
	  intGrid[row] = new int[width];
	  for(int col = 0; col < width; col++)
	    {
	      intGrid[row][col] = 0; 
	    }
	}
      //ask user how much of the environment should be impassible/have obstacles
      cout << "Enter the percent of impassible terrain (0 - 100): ";
      cin >> impassible; 
      //gives warning if they want to do more than 40% obstacles
      if(impassible > 40)
	{
	  cout << "Having a value greater than 40% might create poor results, do you wish to continue? (y/n): "; 
	  cin >> badInput; 
	  //if the user doesn't want to create poor results, reprompts for how much of the environment they want to be impassible
	  if(badInput == 'n')
	    {
	      cout << "Enter the percent of impassible terrain (0 - 100): ";
	      cin >> impassible; 
	      cout << impassible; 
	    }
	}
  
      //gets decimal value of percent to calculate total number of obstacles
      percentImpass = ((double)impassible)/100;
      //calculates total number of obstacles
      obstacles = percentImpass * (width * height);
    
      srand(time(0)); //to get different random position each time the code is run
      int randx; 
      int randy; 
      //set number of obstacles to -1 in array
      //assigns obstacles randomly
      for(int obs = 0; obs < obstacles; obs++)
	{
	  randx = (rand()%height);
	  randy = (rand()%width); 
      
	  if((intGrid[randx][randy]) == -1)
	    {
	      obs--; 
	    }
	  else
	    {
	      intGrid[randx][randy] = -1;
	    }
	}


      //print the grid to screen
      PrintEnvironment(intGrid, width, height);
    }
  //asks user what they want their goal/ending position to be
  //asks for x and y coordinates
  while(!validGoal)
    {
      cout << "Please enter the Goal Position X: ";
      cin >> goalx; 
      cout << "Please enter the Goal Position Y: ";
      cin >> goaly; 
  
      //makes sure the goal position the user gave is within bounds
      //if its not in bounds, tells user its out of bounds and reprompts for new position
      if(goalx >= width || goaly >= height || (goalx >= width && goaly >= height))
	{
	  cout << "Sorry, that position is out of bounds\n";
	}
      //makes sure goal position user gave isn't the same position as an obstacle
      //if it is, tells user and reprompts for new position
      else if(intGrid[goaly][goalx] == -1)
	{
	  cout << "Sorry, that position is inside an obstacle\n";
	}
      else
	{
	  validGoal = true; 
	}
    }

  //set goal to 1
  intGrid[goaly][goalx] = 1;

  //flood fill array
  numWave(intGrid, goaly, goalx, width, height);
  //output flood filled array to screen
  PrintEnvironment(intGrid, width, height);
 
  //create character array parallel to integer array - initalize as empty spaces
  charGrid = new char*[height];
  for(int row = 0; row < height; row++)
    {
      charGrid[row] = new char[width];
      for(int col = 0; col < width; col++)
	{
	  charGrid[row][col] = ' '; 
	}
    }

  //marks obstacles that are in the integer array (-1) in the character array(#)
  //marks the goal position in the character array ($)
  for(int row = 0; row < height; row++)
    {
      for(int col = 0; col < width; col++)
	{
	  if(intGrid[row][col] == -1)
	    {
	      charGrid[row][col] = '#';
	    }
	  else if(intGrid[row][col] == 1)
	    {
	      charGrid[row][col] = '$';
	    }
	  else
	    {
	      continue; 
	    }
	}
    }

  //asks user where they would like the starting position to be for the path to get to the goal
  //asks for an x and y coordinate
  while(!validStart)
    {
    cout << "Please enter the Start Position X: ";
    cin >> startx; 
    cout << "Please enter the Start Position Y: ";
    cin >> starty;
    //checks that the starting position given is in bounds
    //if it's out of bounds, informs user and reprompts for new starting position
    if(startx > width || starty > height || (startx > width && starty > height))
      {
	cout << "Sorry that position is out of bounds\n";
      }
    //checks that the starting position isn't the same place as an obstacle
    //reprompts user if starting point is within if an obstale
    else if(intGrid[starty][startx] == -1)
      {
	cout << "Sorry, that position is inside an obstacle\n";
      }
    else
      {
	validStart = true; 
      }
    }

    //perform greedy path algorithm to find a path from the starting position to the goal position
    //place * to represent path
    findPath(intGrid, charGrid, startx, starty, width, height);

    //mark start position w/ @
    charGrid[starty][startx] = '@';

    //print character array to screen to show the completed path
    PrintCharEnvironment(charGrid, width, height);
    
    //print both the integer and character environments to a file
    outFile.open("wave.txt"); 
    //prints the flood filled  integer environment to the file
    //not using PrintEnvironment bc its a void function - instructions say to create PrintEnvironment as void
    for(int row = 0; row < height; row++)
      {
	for(int col = 0; col < width; col++)
	  {
	    outFile << setw(3) << intGrid[row][col];
	  }
	outFile  << endl;
      }
    //prints two lines to separate the environments
    outFile << '\n' << '\n' << endl;
    //print character array with path to file
    //not using PrintCharEnvironment bc its a void function
    for(int row = 0; row < height; row++)
      {
	for(int col = 0; col < width; col++)
	  {
	    outFile << setw(2) << charGrid[row][col];
	  }
	outFile << endl;
      }
    outFile.close();

    //garbage collect integer array
    for(int row = 0; row < height; row++)
      {
	delete[] intGrid[row];
      }
    delete[] intGrid;

    //garbage collect character array
    for(int row = 0; row < height; row++)
      {
	delete[] charGrid[row];
      }
    delete[] charGrid;
 
  return 0; 
}
