/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 * Modified by Jacob Anderson, 2022
 * Last Modified: 01/11/2022
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include <set>
#include "lexer.h"

using namespace std; 

struct Node
{
  string data;
  string type; 
  Node* left = NULL; 
  Node* right = NULL; 
};

struct Block 
{
  string key; 
  int value; 
  int lineNum; 
  int evalLineNum; 
  int errorCode = 0; 
};

class Parser {
  public:
    void ConsumeAllInput();
    void start();
    Node* parsePolynomial();
    Node* parseExpression();
    Node* parseTerm();
    Node* parseMonomial();
    Node* parseExponent();
    void parseEvaluations();
    vector<Block> parseEvaluation();
    vector<Block> parseInputs(vector<Block> single);
    Block parseInput();

    void postorder(Node* root);
    void evalBlock(Node* root); 
    int DFS(vector<Block> single, Node* root);
    int getNum(vector<Block> single, Node* node);
    void errorCheck();
    void secondErrorCheck();
    void printEvals();
    
  private:
    LexicalAnalyzer lexer;
    vector <vector<Block>> blocks;
    set<string> variables; 
    int evalLine; 
    void syntax_error();
    Token expect(TokenType expected_type);
};

#endif

