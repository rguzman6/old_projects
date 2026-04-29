/*
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
#include <vector>
#include <algorithm>

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

//polynomial evaluations
void Parser::start()
{
  Node* node = new Node();
  node = parsePolynomial();
  //postorder(node);
  parseEvaluations();
  expect(END_OF_FILE);
  //printEvals();
  //does error check 1 and 2 before running DFS at all
  errorCheck();
  secondErrorCheck();
  evalBlock(node);
  return; 
}

//check that the AST is built correctly

void Parser::postorder(Node* root)
{
  if(root == NULL)
    {
      return; 
    }

  postorder(root->left);
  postorder(root->right);
  cout << root->data << " "; 
}


void Parser::errorCheck()
{
  bool error1 = false; 
  for(int i = 0; i < blocks.size(); i++)
    { 
      vector<Block> duplicates; 
      for(int j = 0; j < blocks[i].size(); j++)
	{
	  for(int k = 0; k < blocks[i].size(); k++)
	    {
	      if(blocks[i][j].key == blocks[i][k].key && j != k)
		{
		  if(blocks[i][j].errorCode == 0)
		    {
		      error1 = true; 
		      blocks[i][j].errorCode = 1;  
		      duplicates.push_back(blocks[i][j]);
		    }
		}
	    }
	}

        if(!duplicates.empty())
	  {
	    cout << "ERROR CODE 1: ";
	    for(int i = 0; i < duplicates.size(); i++)
	      {
		cout << duplicates[i].lineNum << " "; 
	      }
	    cout << endl; 
	  }
    }

  //if an error 1 exists, the program will exit
  if(error1)
    {
      exit(1);
    }
}

void Parser::secondErrorCheck()
{
  vector<string> polyVariables{variables.begin(), variables.end()};
  bool error2 = false; 
  
  for(int i = 0; i < blocks.size(); i++)
    {
      vector<Block> singleBlock; 
      vector<Block> check; 
      singleBlock = blocks[i];
      int numVariablesMissing = 0; 
      int blockNum; 

      for(int j = 0; j < polyVariables.size(); j++)
	{
	  for(int k = 0; k < singleBlock.size(); k++)
	    {
	      if(polyVariables[j] == singleBlock[k].key)
		{
		  check.push_back(singleBlock[k]);
		}

	      blockNum = singleBlock[k].evalLineNum; 
	    }
	}
     
      if(check.size() < polyVariables.size())
	{
	  error2 = true; 
	  numVariablesMissing += (polyVariables.size()-check.size());
	}
      else
	{
	  if(check.size() == polyVariables.size())
	    {
	      numVariablesMissing = 0; 
	    }
	  else
	    {
	      error2 = true; 
	      numVariablesMissing += (check.size()-polyVariables.size());
	    }
	}
	  
      if(numVariablesMissing != 0)
	{
	  cout << "ERROR CODE 2: ";
	  for(int i = 0; i < numVariablesMissing; i++)
	    {
	      cout << blockNum << " "; 
	    }
	  cout << endl; 
	}
    }

  //if there are error 2s, the DFS will not run and the program exits
  if(error2)
    {
      exit(1);
    }
}

//separate each evaluation block and perform DFS on each individual block
void Parser::evalBlock(Node* root)
{

  for(int i = 0; i < blocks.size(); i++)
    {
      vector<Block> singleBlock; 
      singleBlock = blocks[i];
      int value = DFS(singleBlock, root);
      cout << value << endl; 
    }
}

//DFS post-order to evaluate the expression
int Parser::DFS(vector<Block> single, Node* root)
{
  if(root == NULL)
    {
      return 0; 
    }

  //get the actual numerical value
  if(root->right == NULL && root->left == NULL)
    {
      return getNum(single, root);
    }

  int left = DFS(single, root->left);
  int right = DFS(single, root->right);

  if(root->data == "+")
    {
      return left+right; 
    }

  if(root->data == "*")
    {
      return left*right; 
    }

  int power = 1;
  if(right == 0)
    {
      return 1; 
    }
  for(int i = 1; i <= right; i++)
    {
      power = power*left; 
    }
  return power; 

}

//get the value of the number or get the variable's numeral equivalent
int Parser::getNum(vector<Block> single, Node* node)
{
  int numVal; 

  if(node->type == "int")
    {
      numVal = stoi(node->data);
      return numVal; 
    }

  else
    {
      for(int i = 0; i < single.size(); i++)
	{
	  if(node->data == single[i].key)
	    {
	      numVal = single[i].value; 
	      break; 
	    }
	}
      
      return numVal; 
    }
}

//test symbol table is correct
void Parser::printEvals()
{
  cout << "Symbol Table" << endl;

  for(int i = 0; i < blocks.size(); i++)
    {
      for(int j = 0; j < blocks[i].size(); j++)
	{
	  cout << "key: " << blocks[i][j].key << " value: " << blocks[i][j].value << endl; 
	}
      cout << endl; 
    }
  
}

//POLY expression SEMICOLON
Node* Parser::parsePolynomial()
{
  Node* node = new Node();
  expect(POLY);
  node = parseExpression();
  expect(SEMICOLON);
  return node; 
}

//term PLUS expression | term
Node* Parser::parseExpression()
{
  Token token; 
  Node* node = new Node();
  node = parseTerm();
  token = lexer.peek(1);

  if(token.token_type == PLUS)
    {
      Node* node2 = new Node();
      node2->left = node;
      node2->data = "+";
      node2->type = "op";
      expect(PLUS);
      node2->right = parseExpression();
      return node2; 
    }

  return node; 
}

//monomial MULT term | monomial
Node* Parser::parseTerm()
{
  Token token; 
  Node* node = new Node();
  node = parseMonomial();
  token = lexer.peek(1);

  if(token.token_type == MULT)
    {
      Node* node2 = new Node();
      node2->left = node;
      node2->data = "*";
      node2->type = "op";
      expect(MULT);
      node2->right = parseTerm();
      return node2; 
    }

  return node; 
}

//ID exponent | ID | NUM
Node* Parser::parseMonomial()
{
  Token token; 
  token = lexer.peek(1);

  Node* node = new Node();
  if(token.token_type == ID)
    {
      node->data = token.lexeme;
      node->type = "var";
      variables.insert(token.lexeme);
      expect(ID);
      token = lexer.peek(1); 
      if(token.token_type == POWER)
	{
	  Node* node2 = new Node();
	  node2 = parseExponent();
	  node2->left = node;
	  return node2; 
	}
   }
  else if(token.token_type == NUM)
    {
      node->data = lexer.peek(1).lexeme;
      node->type = "int";
      expect(NUM);
    }
  else
    {
      syntax_error();
    }
  
  return node;
}

//POWER NUM
Node* Parser::parseExponent()
{
  Node* node = new Node();
  node->data = "^";
  node->type = "op";
  expect(POWER);
  Node* node2 = new Node();
  node2->data = lexer.peek(1).lexeme;
  node2->type = "int";
  node->right = node2; 
  expect(NUM);
  return node; 
}

//evaluation evaluations | evaluation
void Parser::parseEvaluations()
{
  Token token; 
  
  blocks.push_back(parseEvaluation());
  token = lexer.peek(1);

  if(token.token_type == EVAL)
    {
      parseEvaluations();
    }

  return; 
}

//EVAL inputs
vector<Block> Parser::parseEvaluation()
{
  vector<Block> block;
  evalLine = lexer.peek(1).line_no; 
  expect(EVAL);
  block = parseInputs(block);
  return block; 
}

//input inputs | input
vector<Block> Parser::parseInputs(vector<Block> single)
{
  Token token; 

  single.push_back(parseInput());
  token = lexer.peek(1);

  if(token.token_type == INPUT)
    {
      return parseInputs(single);
    }

  return single;  
}

//INPUT ID EQUAL NUM SEMICOLON
Block Parser::parseInput()
{
  Block sect;
  sect.evalLineNum = evalLine; 
  expect(INPUT);
  sect.lineNum = lexer.peek(1).line_no;
  sect.key = lexer.peek(1).lexeme;
  expect(ID);
  expect(EQUAL);
  sect.value = stoi(lexer.peek(1).lexeme);
  expect(NUM);
  expect(SEMICOLON);
  return sect; 
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
    parser.start(); 

    return 0;
}
