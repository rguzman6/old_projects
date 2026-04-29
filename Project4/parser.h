/*
 * Name: Rachel Guzman
 * Email: rguzma15@asu.edu
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <string>
#include "lexer.h"

using namespace std; 

class Parser {
  public:
  //InstructionNode* parse_generate_intermediate_representation();
  struct InstructionNode* parse_program();
  void parse_var_section();
  void parse_id_list(); 
  struct InstructionNode* parse_body();
  struct InstructionNode* parse_stmt_list();
  struct InstructionNode* parse_stmt();
  struct InstructionNode* parse_assign_stmt();
  struct InstructionNode* parse_expr(InstructionNode* node);
  int parse_primary();
  void parse_op();
  struct InstructionNode* parse_output_stmt();
  struct InstructionNode* parse_input_stmt();
  struct InstructionNode* parse_while_stmt();
  struct InstructionNode* parse_if_stmt();
  struct InstructionNode* parse_condition(InstructionNode* node);
  struct InstructionNode* parse_relop(InstructionNode* node);
  struct InstructionNode* parse_switch_stmt();
  struct InstructionNode* parse_for_stmt();
  struct InstructionNode* parse_case_list(InstructionNode* noop, string id);
  struct InstructionNode* parse_case(InstructionNode* noop, string id);
  struct InstructionNode* parse_default_case();
  void parse_inputs();
  void parse_num_list();

  map <string, int> locations_map; 
  int location(string);

  private:
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);
};

#endif

