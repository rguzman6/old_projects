/*
 * Name: Rachel Guzman 
 * Email: rguzma15@asu.edu
 */

#include "parser.h"
#include "compiler.h"

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string>
#include <map> 
#include <cctype>

using namespace std;

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR !!!\n";
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

// var_section body inputs
struct InstructionNode* Parser::parse_program()
{
  InstructionNode* instList; 

  parse_var_section();
  instList = parse_body();
  parse_inputs();
  expect(END_OF_FILE);
  return instList;
}

// id_list SEMICOLON
void Parser::parse_var_section()
{
  parse_id_list();
  expect(SEMICOLON);
  //cout << "end var_section" << endl; 
  return; 
}

// ID COMMA id_list | ID
void Parser::parse_id_list()
{
  Token token; 

  token = lexer.peek(1);
  location(token.lexeme);
  expect(ID);

  token = lexer.peek(1);
  if(token.token_type == COMMA)
    {
      expect(COMMA);
      parse_id_list();
    }
  /*
  else if(token.token_type == SEMICOLON)
    {
      return; 
    }
  
  else
    {
      syntax_error();
    }
  */
  //cout << "end id_list" << endl; 
  return; 
}

// LBRACE stmt_list RBRACE
struct InstructionNode* Parser::parse_body()
{
  Token token; 
  InstructionNode* instList;
  expect(LBRACE);
  instList = parse_stmt_list();
  //cout << "after stmt list" << endl; 
  //lexer.peek(1).Print(); 
  expect(RBRACE);
  //cout << "end body" << endl; 
  return instList; 
}

// stmt stmt_list | stmt
struct InstructionNode* Parser::parse_stmt_list()
{
  Token token; 
  InstructionNode* inst1; 
  InstructionNode* inst2; 
  InstructionNode* temp; 

  inst1 = parse_stmt();

  token = lexer.peek(1);
  if(token.token_type == ID)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  else if(token.token_type == WHILE)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  else if(token.token_type == IF)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  else if(token.token_type == SWITCH)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  else if(token.token_type == FOR)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  else if(token.token_type == OUTPUT)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  else if(token.token_type == INPUT)
    {
      inst2 = parse_stmt_list();
      temp = inst1; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = inst2; 
    }
  
  else if(token.token_type == RBRACE)
    {
      return inst1; 
    }
  /*
  else
    {
      syntax_error();
    }
  */
  //cout << "end stmt_list" << endl; 
  return inst1; 
}

// assign_stmt | while_stmt | if_stmt | switch_stmt | for_stmt | output_stmt | input_stmt
struct InstructionNode* Parser::parse_stmt()
{
  Token token; 
  token = lexer.peek(1);

  InstructionNode* node = new InstructionNode();

  //cout << token.lexeme << endl; 
  if(token.token_type == ID)
    {
      //cout << "assignment" << endl; 
      node = parse_assign_stmt();
    }
  else if(token.token_type == WHILE)
    {
      //cout << "while" << endl; 
       node = parse_while_stmt();
    }
  else if(token.token_type == IF)
    {
      //cout << "if" << endl; 
      node = parse_if_stmt();
    }
  else if(token.token_type == SWITCH)
    {
      //cout << "switch" << endl; 
      node = parse_switch_stmt();
    }
  else if(token.token_type == FOR)
    {
      //cout << "for" << endl; 
      node = parse_for_stmt();
    }
  else if(token.token_type == OUTPUT)
    {
      //cout << "output" << endl; 
      node = parse_output_stmt();
    }
  else if(token.token_type == INPUT)
    {
      //cout << "input" << endl; 
      node = parse_input_stmt();
    }
  /*
  else
    {
      syntax_error();
    }
  */
  //cout << "end stmt" << endl; 
  return node; 
}

// ID EQUAL primary SEMICOLON | ID EQUAL expr SEMICOLON
struct InstructionNode* Parser::parse_assign_stmt()
{
  Token token; 
  InstructionNode* inst = new InstructionNode();

  inst->type = ASSIGN; 
  inst->assign_inst.left_hand_side_index = location(lexer.peek(1).lexeme);
  expect(ID);
  expect(EQUAL);

  token = lexer.peek(2);
  if(token.token_type == SEMICOLON)
    {
      inst->assign_inst.op = OPERATOR_NONE; 
      inst->assign_inst.operand1_index = parse_primary();
    }
  else if(token.token_type == PLUS)
    {
      inst->assign_inst.op = OPERATOR_PLUS; 
      inst = parse_expr(inst);
    }
  else if(token.token_type == MINUS)
    {
      inst->assign_inst.op = OPERATOR_MINUS; 
      inst = parse_expr(inst);
    }
  else if(token.token_type == MULT)
    {
      inst->assign_inst.op = OPERATOR_MULT; 
      inst = parse_expr(inst);
    }
  else if(token.token_type == DIV)
    {
      inst->assign_inst.op = OPERATOR_DIV; 
      inst = parse_expr(inst);
    }
  inst->next = NULL; 
  expect(SEMICOLON);
  return inst; 
}

// primary op primary
struct InstructionNode* Parser::parse_expr(InstructionNode* node)
{
  node->assign_inst.operand1_index = parse_primary(); 
  parse_op();
  node->assign_inst.operand2_index = parse_primary();
  return node; 
}

// ID | NUM
int Parser::parse_primary()
{
  Token token; 
  token = lexer.peek(1);
  
  int index = location(token.lexeme);

  if(token.token_type == ID)
    {
      expect(ID); 
    }
  else if(token.token_type == NUM)
    {
      expect(NUM);
    }
  /*
  else
    {
      syntax_error();
    }
  */
  return index; 
}

// PLUS | MINUS | MULT | DIV
void Parser::parse_op()
{
  Token token; 
  token = lexer.peek(1);

  if(token.token_type == PLUS)
    {
      expect(PLUS);
    }
  else if(token.token_type == MINUS)
    {
      expect(MINUS);
    }
  else if(token.token_type == MULT)
    {
      expect(MULT);
    }
  else if(token.token_type == DIV)
    {
      expect(DIV);
    }

  return; 
}

// output ID SEMICOLON
struct InstructionNode* Parser::parse_output_stmt()
{
  InstructionNode* outNode = new InstructionNode();

  expect(OUTPUT);
  outNode->type = OUT; 
  outNode->output_inst.var_index = location(lexer.peek(1).lexeme);
  outNode->next = NULL; 
  expect(ID);
  expect(SEMICOLON);
  return outNode; 
}

// input ID SEMICOLON
struct InstructionNode* Parser::parse_input_stmt()
{
  InstructionNode* inNode = new InstructionNode();

  expect(INPUT);
  inNode->type = IN; 
  inNode->input_inst.var_index = location(lexer.peek(1).lexeme);
  inNode->next = NULL; 
  expect(ID);
  expect(SEMICOLON);
  return inNode; 
}

// WHILE condition body
struct InstructionNode* Parser::parse_while_stmt()
{
  InstructionNode* inst = new InstructionNode();
  InstructionNode* temp;
 
  expect(WHILE);
  //inst->type = CJMP; 
  inst = parse_condition(inst);
  temp = parse_body();

  InstructionNode* noop = new InstructionNode();
  noop->type = NOOP; 
  noop->next = NULL;
  InstructionNode* jmp = new InstructionNode();
  jmp->type = JMP; 
  jmp->jmp_inst.target = inst; 
  jmp->next = NULL; 

  inst->next = temp; 
  while(temp->next != NULL)
    {
      temp = temp->next;
    }
  temp->next = jmp; 

  jmp->next = noop;
  inst->cjmp_inst.target = noop; 

  return inst; 
}

// IF condition body
struct InstructionNode* Parser::parse_if_stmt()
{
  InstructionNode* inst = new InstructionNode();
  InstructionNode* temp; 

  expect(IF);
  //inst->type = CJMP; 
  inst = parse_condition(inst);
  temp = parse_body();

  InstructionNode* noop = new InstructionNode();
  noop->type = NOOP; 
  noop->next = NULL;

  inst->next = temp; 
  while(temp->next != NULL)
    {
      temp = temp->next; 
    }
  temp->next = noop; 

  inst->cjmp_inst.target = noop; 

  return inst; 
}

// primary relop primary 
struct InstructionNode* Parser::parse_condition(InstructionNode* node)
{
  node->type = CJMP; 
  node->cjmp_inst.operand1_index = parse_primary();
  node = parse_relop(node);
  node->cjmp_inst.operand2_index = parse_primary();
  return node; 
}

// GREATER | LESS | NOTEQUAL
struct InstructionNode* Parser::parse_relop(InstructionNode* node)
{
  Token token; 
  token = lexer.peek(1); 

  if(token.token_type == GREATER)
    {
      expect(GREATER);
      node->cjmp_inst.condition_op = CONDITION_GREATER; 
    }
  else if(token.token_type == LESS)
    {
      expect(LESS);
      node->cjmp_inst.condition_op = CONDITION_LESS;
    }
  else if(token.token_type == NOTEQUAL)
    {
      expect(NOTEQUAL);
      node->cjmp_inst.condition_op = CONDITION_NOTEQUAL; 
    }
  return node; 
}

// SWITCH ID LBRACE case_list RBRACE | SWITCH ID LBRACE cause_list default_case RBACE
struct InstructionNode* Parser::parse_switch_stmt()
{
  Token token; 
  InstructionNode* inst = new InstructionNode();
  InstructionNode* noop = new InstructionNode();
  noop->type = NOOP; 
  noop->next = NULL;
  string id; 

  expect(SWITCH);
  id = lexer.peek(1).lexeme; 
  expect(ID);
  expect(LBRACE);
  inst = parse_case_list(noop, id);

  token = lexer.peek(1);
  if(token.token_type == DEFAULT)
    {
      InstructionNode* n = new InstructionNode();
      n = inst; 
      while(n->next != NULL)
	{
	  n = n->next;
	}
      n->next = parse_default_case();
    }

  InstructionNode* temp = new InstructionNode();
  temp = inst; 
  while(temp->next != NULL)
    {
      temp = temp->next; 
    }
  temp->next = noop; 

  expect(RBRACE);  
  
  return inst; 
}

// FOR LPAREN assign_stmt condition SEMICOLON assing_stmt RPAREN body
struct InstructionNode* Parser::parse_for_stmt()
{
  InstructionNode* assn1 = new InstructionNode(); 
  InstructionNode* assn2 = new InstructionNode(); 
  InstructionNode* temp = new InstructionNode(); 
  InstructionNode* con = new InstructionNode();; 

  expect(FOR);
  expect(LPAREN);
  assn1 = parse_assign_stmt();
  //con->type = CJMP; 
  con = parse_condition(con);
  //assn1->next->type = CJMP; 
  expect(SEMICOLON);
  assn2 = parse_assign_stmt();
  expect(RPAREN);
  temp = parse_body();

  InstructionNode* noop = new InstructionNode();
  noop->type = NOOP; 
  noop->next = NULL;
  InstructionNode* jmp = new InstructionNode();
  jmp->type = JMP; 
  jmp->jmp_inst.target = con;
  jmp->next = NULL; 

  assn1->next = con; 
  //assn1->next->next = temp;
  con->next = temp; 
  //cout << "before while" << endl; 
  while(temp->next != NULL)
    {
      temp = temp->next; 
    }
  //cout << "after while" << endl; 
  temp->next = assn2; 
  //cout << "after temp->next" << endl; 
  
  assn2->next = jmp; 
  //cout << "after assn2->next" << endl; 
  jmp->next = noop;
  //cout << "after jmp->next" << endl;  
  assn1->next->cjmp_inst.target = noop;  
  return assn1; 
}

// case case_list | case
struct InstructionNode* Parser::parse_case_list(InstructionNode* noop, string id)
{
  Token token; 
  InstructionNode* inst = new InstructionNode();
  InstructionNode* temp = new InstructionNode();

  inst = parse_case(noop, id);

  token = lexer.peek(1);
  if(token.token_type == CASE)
    {
      temp = inst; 
      while(temp->next != NULL)
	{
	  temp = temp->next; 
	}
      temp->next = parse_case_list(noop, id);
    }
  return inst; 
}

// CASE NUM COLON body
struct InstructionNode* Parser::parse_case(InstructionNode* noop, string id)
{
  InstructionNode* inst = new InstructionNode();
  InstructionNode* temp = new InstructionNode();

  expect(CASE);
  string num = lexer.peek(1).lexeme; 
  expect(NUM);
  expect(COLON);
  inst = parse_body();

  InstructionNode* cjmp = new InstructionNode();
  cjmp->type = CJMP;
  cjmp->cjmp_inst.condition_op = CONDITION_NOTEQUAL; 
  cjmp->cjmp_inst.operand1_index = location(id);
  cjmp->cjmp_inst.operand2_index = location(num);
  cjmp->cjmp_inst.target = inst;
  cjmp->next = NULL;
  InstructionNode* jmp = new InstructionNode();
  jmp->type = JMP; 
  jmp->jmp_inst.target = noop; 
  jmp->next = NULL; 

  //cjmp->next = inst
  temp = inst; 
  while(temp->next != NULL)
    {
      temp = temp->next;
    }
  temp->next = jmp;

  return cjmp; 
}

// DEFAULT COLON body
struct InstructionNode* Parser::parse_default_case()
{
  InstructionNode* inst = new InstructionNode();
  expect(DEFAULT);
  expect(COLON);
  inst = parse_body();
  return inst; 
}

// num_list
void Parser::parse_inputs()
{
  parse_num_list();
  return; 
}

// NUM | NUM num_list
void Parser::parse_num_list()
{
  Token token; 

  inputs.push_back(stoi(expect(NUM).lexeme));

  token = lexer.peek(1);
  if(token.token_type == NUM)
    {
      parse_num_list();
    }
  return; 
}

int Parser::location(string key)
{
  int index; 
  if(locations_map.find(key) != locations_map.end())
    {
      index = locations_map.find(key)->second; 
    }
  else
    {
      locations_map.insert({key, next_available});
      index = next_available; 
      if(isdigit(key[0]))
	{
	  mem[next_available] = stoi(key);
	  next_available++; 
	}
      else
	{
	  mem[next_available] = 0; 
	  next_available++;
	}
    }
  return index; 
}

//"main"
InstructionNode* parse_generate_intermediate_representation()
{

    Parser parser;
    InstructionNode* start;
    start = parser.parse_program();
    //cout << "Success!" << endl; 
    return start;
}
