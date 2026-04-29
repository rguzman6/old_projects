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
  parsePolynomial();
  parseEvaluations();
  expect(END_OF_FILE);
  return; 
}

//POLY expression SEMICOLON
void Parser::parsePolynomial()
{
  expect(POLY);
  parseExpression();
  expect(SEMICOLON);
  return; 
}

//term PLUS expression | term
void Parser::parseExpression()
{
  Token token; 

  parseTerm();
  token = lexer.peek(1);

  if(token.token_type == PLUS)
    {
      expect(PLUS);
      parseExpression();
    }

  return; 
}

//monomial MULT term | monomial
void Parser::parseTerm()
{
  Token token; 

  parseMonomial();
  token = lexer.peek(1);

  if(token.token_type == MULT)
    {
      expect(MULT);
      parseTerm();
    }

  return; 
}

//ID exponent | ID | NUM
void Parser::parseMonomial()
{
  Token token; 
  token = lexer.peek(1);

  if(token.token_type == ID)
    {
      expect(ID);
      token = lexer.peek(1); 
      if(token.token_type == POWER)
	{
	  parseExponent();
	}
   }
  else //if(token.token_type == NUM)
    {
      expect(NUM);
    }
  
  return;
}

//POWER NUM
void Parser::parseExponent()
{
  expect(POWER);
  expect(NUM);
  return; 
}

//evaluation evaluations | evaluation
void Parser::parseEvaluations()
{
  Token token; 

  parseEvaluation();
  token = lexer.peek(1);

  if(token.token_type == EVAL)
    {
      parseEvaluations();
    }

  return; 
}

//EVAL inputs
void Parser::parseEvaluation()
{
  expect(EVAL);
  parseInputs();
  return; 
}

//input inputs | input
void Parser::parseInputs()
{
  Token token; 

  parseInput();
  token = lexer.peek(1);

  if(token.token_type == INPUT)
    {
      parseInputs();
    }

  return; 
}

//INPUT ID EQUAL NUM SEMICOLON
void Parser::parseInput()
{
  expect(INPUT);
  expect(ID);
  expect(EQUAL);
  expect(NUM);
  expect(SEMICOLON);
  return; 
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
