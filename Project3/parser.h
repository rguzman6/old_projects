/*
 * Name: Rachel Guzman 
 * Email: rguzma15@asu.edu 
 *
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 * Modified by Jacob Anderson, 2022
 * Last Modified: 01/11/2022
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <string> 
#include "lexer.h"

using namespace std; 

struct Node
{
  string refType; 
  string rhs = ""; 
  string lhs = ""; 
  int rhsInt = -1; 
  int lineNum; 
};

struct Ref
{
  int ref; 
  int refCount = 0; 
};

class Parser {
  public:
    void ConsumeAllInput();
    vector<Node> parse_program();
    void parse_statements();
    Node parse_statement();
    Node parse_assignment();
    Node parse_collection();

  private:
    vector<Node> statementList; 
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);
};

#endif

