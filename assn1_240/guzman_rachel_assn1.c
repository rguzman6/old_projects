/*
Author: Rachel Guzman
Date: May 30, 2021
Description: Turn hex digits into art and invert the hex turned art; creation of art and inversion of art are two separate actions/"programs"
Usage: this program was written in C. 
       To complie the code: gcc -g -Wall guzman_rachel_assn1.c -o <exe>
       To run the code: ./<exe> <inputFile> <-a | -i> <outputFile>
          must use lower-case for -a and -i, or will be improper syntax
	  -a will turn a hex sequence into ASCII art, -i will invert the ASCII art
	  must us -i after use of -a, or have file that is already in ASCIII or a bunch of Es will print to the file
*/

#include <stdio.h>
#include <string.h>

//will take a single hex character and turn it into a "binary" sequence where 0s are - and 1s are # that is 4 bits wide
char* hexToArt(inChar)
{
  //checks to see if the parameter character is a number
  if(inChar == '0' || inChar == '1' || inChar == '2' || inChar == '3' || inChar == '4' || inChar == '5' || inChar == '6' || inChar == '7' || inChar == '8' || inChar == '9')
    {
      //switch for what number the parameter is
      //converts the hex number into its binary equivalent with the corresponding symbols
      //if somehow a number but not one in the cases, the default equivalent is eeee
      switch (inChar)
	{
	case '0':
	  return "----";
	case '1': 
	  return "---#";
	case '2':
	  return "--#-";
	case '3':
	  return "--##";
	case '4':
	  return "-#--";
	case '5':
	  return "-#-#";
	case '6':
	  return "-##-";
	case '7':
	  return "-###";
	case '8':
	  return "#---";
	case '9':
	  return "#--#";
	default: 
	  return "eeee";
	}
    }
  //for when the parameter is not a number, i.e. is a letter or a character
  else
    {
      //switch for converting the hex letter into its binary equivalent
      //ignores upper/lower case (ex. a and A will return the same thing)
      //default case for when the parameter is not a letter that is part of hex or is a random character will return eeee
      switch (inChar)
	{
	case 'a': 
	case 'A': 
	  return "#-#-";
	case 'b':
	case 'B':
	  return "#-##";
	case 'c':
	case 'C':
	  return "##--";
	case 'd':
	case 'D':
	  return "##-#";
	case 'e':
	case 'E':
	  return "###-";
	case 'f':
	case 'F':
	  return "####";
	default: 
	  return "eeee";
	}
    }
}

//function that takes file that is already in ASCII art and switches the 0s(-) and 1s(#) to invert the original art
//only takes one symbol at a time as its parameter (either a - or a # or a random symbol)
char* invArt(inChar)
{
  //checks if the parameter is a - (a 0)
  //changes it to a # (a 1)
  if(inChar == '-')
    return "#";

  //checks if the parameter is a # (a 1)
  //changes it to a - (a 0)
  else if(inChar == '#')
    return "-";

  //just in case case where will return E if parameter is anything else besides a - or a #
  else
    return "E";
}

//main method, will run from command line
int main(int argc, char** argv)
{
  //create pointers for a file to read and a file to write
  FILE* writeFile; 
  FILE* readFile; 

  //variable for hex sequence to turn into ASCII art to store each line in the file as it gets read
  //given that one line is no longer than 255 characters
  char hex[255];
  //variable for inverting the ASCII art to store each line in the file as it gets read
  //given that one line for inversion is no longer than 1020 characters
  char inv[1020]; 

  //variables to hold the inputed input/output file names from the command line for ease of use later
  char* inputFileName;
  char* outputFileName;

  //first check if the command line syntax is correct (needs 4 arguments in total)
  if(argc == 4)
    {
      //initializes variables for input/output file names based on the corresponding arguments from the command line
      //first argument that isn't the executable name is the input file name
      inputFileName = argv[1];
      //last argument in command line is the output file name
      outputFileName = argv[3];
      
      //opens the files to read and write to be used to create or invert the ASCII art
      readFile = fopen(inputFileName, "r");
      writeFile = fopen(outputFileName, "w");
  
      //checks to make sure there is a file to read to execute the program
      if(readFile == NULL)
	{
	  printf("Error: File cannot be opened.");
	  return -1;
	}
  
      //this set of if/else statements is the next check to make sure command line syntax is correct (including the checking of upper/lower case)
      //checks to see if the user wants to create art from hex sequences
      if(strcmp(argv[2], "-a") == 0)
	{
	  //goes through the file, line by line, ends once reads the end file symbol (\0)
	  while(fscanf(readFile, "%s", hex) != EOF)
	    {
	      //variable for index for for loop
	      int i; 
	      //gets the length of the line for cleaner code use
	      int length = strlen(hex);
	      //variable to hold what the hexToArt funtion will return
	      char* art;
	      //variable to get the character that will be the parameter of the hexToArt function
	      char toArt;
      
	      //iterates through the current line, character by character to pass it through the hexToArt function and print to the file
	      for(i = 0; i < length; i++)
		{
		  toArt = hex[i];
		  art = hexToArt(toArt);
		  //prints the corresponding art for the hex character to the file
		  fprintf(writeFile, "%s", art);
		}
	      //goes to next, new line in file to convert the next hex line into art on a new line
	      fprintf(writeFile, "\n");
	    }
	}

      //checks to see if user wants to invert ASCII art that has already been created
      else if(strcmp(argv[2], "-i") == 0)
	{
	  //goes through the file, line by line until the end file symbol (\0) is read
	  while(fscanf(readFile, "%s", inv) != EOF)
	    {
	      //variable for index for for loop
	      int j; 
	      //gets length of the current line for cleaner code use 
	      int lineLength = strlen(inv);
	      //variable to hold what the invArt function will return
	      char* inverted;
	      //variable to get the character that will be passed as the parameter of invArt function
	      char toInvert; 

	      //iterates through the line, character by character to pass it through the invArt function and print to the file
	      for(j = 0; j < lineLength; j++)
		{
		  toInvert = inv[j];
		  inverted = invArt(toInvert);
		  //prints inverted single character/symbol into the file
		  fprintf(writeFile, "%s", inverted);
		}
	      //prints a new line at the end of the newly printed inverted art line so next line to invert starts on a new line
	      fprintf(writeFile, "\n");
	    }
	}
      //checks for proper command line syntax
      //compensates for any random characters, upper case use of -a and -i, wrong placement of file names, random names, etc.
      else
	{
	  printf("Error: improper command line syntax. Please supply an input file, what action you would like to perform(-a to create art, -i to invert already created art), and an output file. The command line should be formated as <exe> <inputFile> <-a | -i> <outputFile>\n");
	}
    
      //closes the open read and write files
      fclose(readFile);
      fclose(writeFile);
    }
  //checks for proper command line syntax
  //for all time that there are not exactly 4 arguments in the command line. 
  else
    {
      printf("Error: improper command line syntax. Please supply an input file, what action you would like to perform(-a to create art, -i to invert already created art), and an output file. The command line should be formated as <exe> <inputFileName> <-a | -i> <outputFileName>\n");
    }
  
  return 0;
}
