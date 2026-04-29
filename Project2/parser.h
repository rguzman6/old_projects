/*
 * Name: Rachel Guzman
 * Email: rguzma15@asu.edu
 *
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 *
 * Modified by Jacob Anderson, 2022
 * Last Modified: 02/18/2022
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>
#include "lexer.h"

using namespace std; 

struct REG_node
{
  struct REG_node* first_neighbor = NULL; 
  char first_label = ' ';
  struct REG_node* second_neighbor = NULL;
  char second_label = ' ';
};

struct REG
{
  struct REG_node* start = NULL; 
  struct REG_node* accept = NULL; 
  bool makeEpsilon; 
};

struct toks
{
  string name; 
  REG* expr; 
};

class Parser {
public:
  void ConsumeAllInput();
  vector<toks>  parse_input();
  void parse_tokens_section();
  void parse_token_list();
  toks parse_token();
  REG* parse_expr(); 

private:
  LexicalAnalyzer lexer;
  vector<toks> list_toks; 
  void syntax_error();
  Token expect(TokenType expected_type);
};

string text; 
void my_GetToken(vector<toks> toks_list, string s_input);
string match(REG expr, string input_s, int p);
set<REG_node*> match_one_char(set<REG_node*> S, char c);

#endif

