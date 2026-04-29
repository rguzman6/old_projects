/*
 * Name: Rachel Guzman 
 * Email: rguzma15@asu.edu
 * 
 * Copyright (C) Rida Bazzi, 2020
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 * Modified by Jacob Anderson, 2022
 * Last Modified: 01/11/2022
 */

#include "parser.h"

#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <string> 

using namespace std;

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR !!&%!!\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();

    if (t.token_type != expected_type)
        syntax_error();

    return t;
}

// Parsing

// This function is simply to illustrate the GetToken() function
// you will not need it for your project and you can delete it
// the function also illustrates the use of peek()
void Parser::ConsumeAllInput()
{
    Token token;
    int i = 1;

    token = lexer.peek(i);
    token.Print();

    while (token.token_type != END_OF_FILE)
    {
        i = i+1;
        token = lexer.peek(i);
        token.Print();
    }

    token = lexer.GetToken();
    token.Print();

    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }

}

//statement
vector<Node> Parser::parse_program()
{
  parse_statements();
  expect(END_OF_FILE);
  return statementList; 
}

//statement statements | statement
void Parser::parse_statements()
{
  Token token;

  statementList.push_back(parse_statement());

  token = lexer.peek(1);
  if(token.token_type == REF || token.token_type == COLLECT)
    {
      parse_statements();
    }
  else if(token.token_type == END_OF_FILE)
    {
      return; 
    }
  else
    {
      syntax_error();
    }

  return; 
}


//assignment | collection
Node Parser::parse_statement()
{
  Token token; 
  token = lexer.peek(1);

  Node statement; 

  if(token.token_type == REF)
    {
      statement = parse_assignment();
    }
  else if(token.token_type == COLLECT)
    {
      statement = parse_collection();
    }
  else
    {
      syntax_error();
    }

  return statement; 
}

//REF ID EQUAL NUM SEMICOLON
//REF ID EQUAL ID SEMICOLON
Node Parser::parse_assignment()
{
  Token token; 
  Node statement; 

  statement.refType = "ASSN";

  expect(REF);
  statement.lhs = expect(ID).lexeme;
  expect(EQUAL);

  token = lexer.peek(1);
  if(token.token_type == NUM)
    {
      statement.lineNum = lexer.peek(1).line_no; 
      statement.rhs = expect(NUM).lexeme;
      statement.rhsInt = stoi(statement.rhs);
      expect(SEMICOLON);
    }
  else if(token.token_type == ID)
    {
      statement.lineNum = lexer.peek(1).line_no; 
      statement.rhs = expect(ID).lexeme;
      expect(SEMICOLON);
    }
  else
    {
      syntax_error(); 
    }

  return statement; 
}

//COLLECT SEMICOLON
Node Parser::parse_collection()
{
  Node statement; 
  statement.refType = "COLLECT";
  statement.lineNum = lexer.peek(1).line_no; 

  expect(COLLECT);
  expect(SEMICOLON);
  return statement; 
}


//check for garbage when COLLECT is read
set<int> collectGarbage(vector<Ref> reference, set<int> collected)
{
  set<int> garbage; 

  for(int r = 0; r < reference.size(); r++)
    {
      //if reference count is zero
      if(reference[r].refCount == 0)
	{
	  //check that it hasn't already been collected as garbage
	  if(collected.find(reference[r].ref) == collected.end())
	    {
	      //collect garbage
	      garbage.insert(reference[r].ref);
	    }
	}
    }

  if(garbage.empty())
    {
      cout << "NO GARBAGE TO COLLECT!" << endl; 
      cout << endl; 
    }
  else
    {
      cout << "COLLECTED GARBAGE: ";
      for(int g : garbage)
	{
	  cout << g << " ";
	}
      cout << endl; 
    }
  return garbage; 
}

//checks for memory leaks at end of program
void endCollectGarbage(vector<Ref> reference, set<int> collected)
{
  set<int> garbage; 

  for(int r = 0; r < reference.size(); r++)
    {
      //check if reference count is 0
      if(reference[r].refCount == 0)
	{
	  //check that it hasn't been collected already
	  if(collected.find(reference[r].ref) == collected.end())
	    {
	      //add to uncollected garbage
	      garbage.insert(reference[r].ref);
	    }
	}
    }

  if(garbage.empty())
    {
      cout << "HOORAY! NO MEMORY LEAKS EXIST!" << endl; 
    }
  else
    {
      cout << "UH OH! MEMORY LEAKS EXIST!" << endl; 
      cout << "UNCOLLECTED GARBAGE: ";
      for(int g : garbage)
	{
	  cout << g << " ";
	}
      cout << endl;       
    }
}

int main()
{
    // NOTE: The Parser class has a private variable, `lexer`, representing
    // an instantianted LexicalAnalyzer (lexer) object.
    //
    // You should **NOT** declare an additional LexicalAnalyzer object. You should
    // use the lexer object in the parser functions as demonstrated in the above
    // function: `ConsumeAllInput`.
    //
    // If you use a separate LexicalAnalyzer object, lexical analysis will not
    // work effectively.

    Parser parser;
    //parser.ConsumeAllInput();
    vector<Node> statementList = parser.parse_program();
    set<string> resource; 
    vector<Ref> reference; 
    set<int> collectedGarbage; 
    int section = 0; 


    for(int i = 0; i < statementList.size(); i++)
      {
	if(statementList[i].refType == "ASSN")
	  {
	    //check if rhs is a digit or a variable
	    if(statementList[i].rhsInt != -1)
	      {
		bool exists = false; 
		for(int x = 0; x < reference.size(); x++)
		  {
		    if(statementList[i].rhsInt == reference[x].ref)
		      {
			exists = true; 
		      }
		  }

		if(exists == false)
		  {
		    Ref newRef; 
		    newRef.ref = statementList[i].rhsInt; 
		    newRef.refCount = 1; 

		    //if lhs already exists, decrement what it was originally pointing to
		    if(resource.find(statementList[i].lhs) != resource.end())
		      {
			int toDecr; 
			for(int j = 0; j < i; j++)
			  {
			    if(statementList[i].lhs == statementList[j].lhs)
			      {
				toDecr = statementList[j].rhsInt;
			      }
			  }
			//cout << "toDecr: " << toDecr << endl; 
			for(int k = 0; k < reference.size(); k++)
			  {
			    if(reference[k].ref == toDecr)
			      {
				if(reference[k].refCount > 0)
				  {
				    reference[k].refCount--; 
				    //cout << "decreased reference count of " << reference[k].ref << endl; 
				  }
			      }
			  }
		      }
		    reference.push_back(newRef);
		    resource.insert(statementList[i].lhs);
		  }
		else
		  {
		    resource.insert(statementList[i].lhs);
		    
		    bool duplicate = false;  
		    for(int n = 0; n < i; n++)
		      {
			if(statementList[i].rhs == statementList[n].rhs && statementList[i].lhs == statementList[n].lhs)
			  {
			    duplicate = true; 
			  }
		      }

		    if(duplicate == false)
		      {
			for(int m = 0; m < reference.size(); m++)
			  {
			    if(reference[m].ref == statementList[i].rhsInt)
			      {
				reference[m].refCount++; 
			      }
			  }
		      }
		  }
		/*
		for(int k = 0; k < reference.size(); k++)
		  {
		    cout << reference[k].ref << "," << reference[k].refCount << endl; 
		  }
		*/
	      }
	    //rhs is a variable
	    else
	      {
		//variable is already defined
		if(resource.find(statementList[i].rhs) != resource.end())
		  {
		    int toIncr; 
		    for(int n = 0; n < i; n++)
		      {
			if(statementList[n].lhs == statementList[i].rhs)
			  {
			    toIncr = statementList[n].rhsInt; 
			  }
		      }
		    statementList[i].rhsInt = toIncr; 
		    bool sameRef = false; 
		    if(resource.find(statementList[i].lhs) != resource.end())
		      {
			for(int m = 0; m < i; m++)
			  {
			    if(statementList[i].lhs == statementList[m].lhs)
			      {
				if(statementList[m].rhsInt == toIncr)
				  {
				    sameRef = true; 
				  }
			      }
			  }
		      }

		    if(sameRef == false)
		      {
			for(int p = 0; p < reference.size(); p++)
			  {
			    if(reference[p].ref == toIncr)
			      {
				reference[p].refCount++;
			      }
			  }		      
		      }
		    resource.insert(statementList[i].lhs);
		  }
		//variable is not already defined - RUNTIME ERROR
		else
		  {
		    cout << "ERROR: L" << statementList[i].lineNum << ": \"" << statementList[i].rhs << "\" UNINITIALIZED" << endl; 
		    cout << endl; 
		    cout << "PROGRAM CRASHED" << endl; 
		    cout << "UH OH! SOME RUNTIME ERRORS EXIST!" << endl; 
		    return 0; 
		  }
		
	      }
	  }
	else
	  {
	    set<int> collected;
	    collected = collectGarbage(reference, collectedGarbage);
	    collectedGarbage.insert(collected.begin(), collected.end());
	    //reference.clear();
	    //resource.clear();
	    //section = statementList[i].lineNum; 
	  }
      }

    cout << "PROGRAM TERMINATED" << endl; 
    /*
    for(int g : collectedGarbage)
      {
	cout << g << " ";
      }
    cout << endl;
    */ 
    endCollectGarbage(reference, collectedGarbage);

    return 0;
}
