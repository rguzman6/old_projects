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
 * Last Modified: 02/18/2022
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include "parser.h"

using namespace std;

void Parser::syntax_error() {
  cout << "SYNTAX ERROR\n";
  exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type) {
  Token t = lexer.GetToken();
  if (t.token_type != expected_type)
    syntax_error();
  return t;
}

// Parsing

//tokens_section INPUT_TEXT
vector<toks> Parser::parse_input()
{
  parse_tokens_section();
  text = expect(INPUT_TEXT).lexeme;
  //cut off quotation marks
  text = text.substr(1, text.length()-2);
  expect(END_OF_FILE);
  return list_toks; 
}

// token_list HASH
void Parser::parse_tokens_section()
{
  parse_token_list();
  expect(HASH);
  return; 
}

// token | token COMMA token_list
void Parser::parse_token_list()
{
  Token token; 

  list_toks.push_back(parse_token());
  token = lexer.peek(1);

  if(token.token_type == COMMA)
    {
      expect(COMMA);
      parse_token_list();
    }

  return;
}

// ID expr
toks Parser::parse_token()
{
  toks single; 
  single.name = expect(ID).lexeme;
  single.expr = parse_expr();

  return single; 
}

// CHAR 
// LPAREN expr RPAREN DOT LPAREN expr RPAREN
// LPAREN expr RPAREN OR LPAREN expr RPAREN
// LPAREN expr RPAREN STAR
// UNDERSCORE (epsilon) 
REG* Parser::parse_expr()
{
  Token token; 
  token = lexer.peek(1);

  REG* empty = new REG(); 

  if(token.token_type == CHAR)
    {
      char c;
      string val = token.lexeme;
      c = val[0]; 
      expect(CHAR);

      REG* node = new REG();
      node->start = new REG_node();
      node->start->first_neighbor = new REG_node();
      node->start->first_label = c; 
      node->accept = node->start->first_neighbor; 
      node->makeEpsilon = false; 
    
      return node; 
    }
  else if(token.token_type == LPAREN)
    {
      expect(LPAREN);
      REG* r1 = new REG();
      r1 = parse_expr();
      expect(RPAREN);
      token = lexer.peek(1);
      
      if(token.token_type == DOT)
	{
	  expect(DOT);
	  expect(LPAREN);
	  REG* r2 = new REG();
	  r2 = parse_expr();
	  expect(RPAREN);

	  REG* r = new REG();
	  r->start = new REG_node(); 
	  r->accept = new REG_node(); 
	  r1->accept->first_neighbor = r2->start; 
	  r1->accept->first_label = '_';
	  r->start = r1->start; 
	  r->accept = r2->accept; 

	  if(r1->makeEpsilon == true && r2->makeEpsilon == true)
	    {
	      r->makeEpsilon = true; 
	    }
	  else
	    {
	      r->makeEpsilon = false; 
	    }

	  delete r1; 
	  delete r2; 
	  return r; 
	}
      else if(token.token_type == OR)
	{
	  expect(OR);
	  expect(LPAREN);
	  REG* r2 = new REG();
	  r2 = parse_expr();
	  expect(RPAREN);

	  REG* r = new REG();
	  r->start = new REG_node(); 
	  r->accept = new REG_node(); 
	  r->start->first_neighbor = r1->start; 
	  r->start->first_label = '_';
	  r->start->second_neighbor = r2->start; 
	  r->start->second_label = '_'; 
	  
	  r1->accept->first_neighbor = r->accept; 
	  r1->accept->first_label = '_'; 
	  r2->accept->first_neighbor = r->accept; 
	  r2->accept->first_label = '_'; 

	  if(r1->makeEpsilon == true || r2->makeEpsilon == true)
	    {
	      r->makeEpsilon = true;
	    }
	  else
	    {
	      r->makeEpsilon = false; 
	    }

	  delete r1; 
	  delete r2; 
	  return r; 
	}
      else if(token.token_type == STAR)
	{
	  expect(STAR);
	  
	  REG* r = new REG(); 
	  r->start = new REG_node(); 
	  r->accept = new REG_node(); 
	  r->start->first_neighbor = r1->start; 
	  r->start->first_label = '_';
	  
	  r1->accept->first_neighbor = r->accept; 
	  r1->accept->first_label = '_';
	  r1->accept->second_neighbor = r1->start; 
	  r1->accept->second_label = '_'; 

	  r->start->second_neighbor = r->accept; 
	  r->start->second_label = '_';
	  r->makeEpsilon = true; 

	  delete r1; 
	  return r; 
	}
      else
	{
	  syntax_error(); 
	}
    }
  else if(token.token_type == UNDERSCORE)
    {
      expect(UNDERSCORE);
     
      REG* node = new REG();
      node->start = new REG_node();
      node->start->first_neighbor = new REG_node();
      node->start->first_label = '_'; 
      node->accept = node->start->first_neighbor; 
      node->makeEpsilon = true; 
    
      return node; 
    }
  else
    {
      syntax_error();
    }
  
  return empty; 
}

// This function is simply to illustrate the GetToken() function
// you will not need it for your project and you can delete it
// the function also illustrates the use of peek()
void Parser::ConsumeAllInput() {
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

void my_GetToken(vector<toks> toks_list, string s_input)
{
  int position = 0; 
  //go through the entire string to find longest strings
  while(position < s_input.length())
    {
      //ignore whitespaces 
      if(s_input.at(position) == ' ')
	{
	  position++; 
	  //cout << "position: " << position << endl; 
	  continue; 
	}

      string longest_tok_name = ""; 
      string longest_text = ""; 
      
      for(int i = 0; i < toks_list.size(); i++)
	{
	  //get the longest string possible using match
	  string current_text = match(*toks_list[i].expr, s_input, position);
	  //update the longest string and corresponding token if it is larger
	  //only updates if longest string possible is larger; if they are equal, use the first token in the set
	  if(current_text.length() > longest_text.length())
	    {
	      longest_text = current_text; 
	      //cout << "longest: " << longest_text << endl; 
	      longest_tok_name = toks_list[i].name; 
	      //cout << "name: " << longest_tok_name << endl; 
	    }
	}

      //check if it's empty - there is an invalid token in the inputted string 
      if(longest_text == "")
	{
	  cout << "ERROR" << endl; 
	  return; 
	}

      cout << longest_tok_name << " ,\" " << longest_text << "\"" << endl; 
      position += longest_text.length();
      //cout << "starting next round. position: " << position << endl; 
    }

  return; 
}

string match(REG expr, string input_s, int p)
{
  //cout << "entering match" << endl; 
  set<REG_node*> S; 
  //start with start node
  S.insert(expr.start); 
  //cout << "inserted start" << endl; 

  //set of nodes that can be reached from the start node with consuming no input
  set<REG_node*> S_Epsilon = match_one_char(S, '_');
  //iterator i; 
  //add nodes that can be reached from start node by consuming no input to set
  for(REG_node* node:S_Epsilon)
    {
      S.insert(node);
      //cout << "union" << endl; 
    }

  string seq; 
  vector<string> sequence;
  //make sure the set isn't empty and that you're not beyond the INPUT_TEXT length
  while(S.size() > 0 && p < input_s.length())
    {
      //white space in the middle is a delimiter - end of one possible string
      if(input_s.at(p) == ' ')
	{
	  break; 
	}
      S = match_one_char(S, input_s.at(p)); 
      if(S.empty())
	{
	  //cout << "is empty" << endl; 
	  break; 
	}
      seq += input_s.at(p);
      //cout << seq << endl; 
      p++; 
      //check if reached an accepted string
      if(S.find(expr.accept) != S.end())
	{
	  //cout << "accpeted sequence found" << endl; 
	  sequence.push_back(seq); 
	}
    }

  //check if there is anything there
  if(sequence.size() == 0)
    {
      return ""; 
    }
  //cout << "returning: " << sequence.back() << endl; 
  //return longest string
  return sequence.back(); 
}

set<REG_node*> match_one_char(set<REG_node*> S, char c)
{
  //cout << "enetering match one. checking: " << c << endl; 
  set<REG_node*> S_prime = {};
  for(REG_node* node:S)
    {
      //cout << "checking what can be reached by consuming c" << endl; 
      //cout << "check first neighbor" << endl; 
      if(node->first_label == c)// && (S.find(node->first_neighbor) == S.end()))
	{
	  //cout << "first neighbor added" << endl; 
	  S_prime.insert(node->first_neighbor);
	}
      //cout << "check second neighbor" << endl; 
      if(node->second_label == c)// && (S.find(node->second_neighbor) == S.end()))
	{
	  //cout << "second neighbor added" << endl; 
	  S_prime.insert(node->second_neighbor);
	}
    }

  if(S_prime.size() == 0)
    {
      //cout << "s prime is empty" << endl; 
      return S_prime; 
    }

  bool changed = true; 
  set<REG_node*> S_doubleprime = {};
  while(changed)
    {
      changed = false; 
      for(REG_node* node:S_prime)
	{
	  //cout << "checking what can be reached by consuming no input" << endl; 
	  S_doubleprime.insert(node);
	  //cout << "check first neighbor" << endl; 
	  if(node->first_label == '_' )//&& (S_doubleprime.find(node->first_neighbor) == S_doubleprime.end()))
	    {
	      S_doubleprime.insert(node->first_neighbor);
	      //cout << "first neighbor added" << endl; 
	    }
	  //cout << "check second neighbor" << endl; 
	  if(node->second_label == '_')// && (S_doubleprime.find(node->second_neighbor) == S_doubleprime.end()))
	    {
	      S_doubleprime.insert(node->second_neighbor);
	      //cout << "second neighbor added" << endl; 
	    }
	}

      if(S_prime != S_doubleprime)
	{
	  changed = true; 
	  S_prime = S_doubleprime; 
	  //cout << "reset s double prime" << endl; 
	  S_doubleprime = {};
	}
    }

  return S_prime; 
}

int main() {
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
  vector<toks> toks_list; 
  toks_list = parser.parse_input();

  vector<string> epsilon_toks; 

  for(int i = 0; i < toks_list.size(); i++)
    {
      if(toks_list[i].expr->makeEpsilon == true)
	{
	  epsilon_toks.push_back(toks_list[i].name);
	}
    }

  if(epsilon_toks.size() != 0)
    {
      cout << "EPSILON IS NOOOOOT A TOKEN !!! ";
      for(int j = 0; j < epsilon_toks.size(); j++)
	{
	  cout << epsilon_toks[j] << " "; 
	}
      cout << endl;
    }
  else
    {
      my_GetToken(toks_list, text);
    }

  return 0;
}
