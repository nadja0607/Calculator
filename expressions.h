#ifndef EXPRESSION
#define EXPRESSION

#include <cstdlib>
#include<bits/stdc++.h> 
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<map>
#include<iostream>
#include<fstream>
#include<cmath>
#include "token.h"


using namespace std; 


class Expression{
	public:		
		Expression(string lhs_and_rhs);
		string lhs_and_rhs; //at the beginning when reading line
		string lhs; //upon calling separate rhs and lhs in constructor
		string rhs; //upon calling separate rhs and lhs in constructor
		string answer;
		

		bool is_valid_variable; //is true by default
		bool is_evaluated; //is false by default

		//vector of tokens
		vector <Token> vector_of_tokens;

		//postfix queue
		queue <Token> postfix_token_q;
		
		///functions
		void separate_lhs_and_rhs(); //separates right hand side and left hand side
		void check_lhs_variable_validity(string a); //chceks sanity of the left hand side
		
		vector <Token> tokenize_rhs(string a); //tokenizes the right hand side
		bool isAnAlphabet(char ch); //helper for tokenize

		void check_rhs_expression_sanity (vector<Token>& token_vec); //chceks sanity of the right hand side

		int convertOpToInt (Token tok); //helper for evaluation and postfix conversion
		bool isleq (Token a, Token b); //helper for postfix conversion
		queue <Token> infix2postfix (vector<Token>& token_vec); //conversion to postfix
		string print_postfix_q (queue<Token>& token_q, map<string,string>& my_map); //printing out postfix (not used, left for the instuctor in case he wants to chcek)
		string calculate_unary(string operation,string str_a); //compute unary operation
		string calculate_binary(string a, string operation, string b); //compute binary operation

		int evaluate(queue<Token>& token_q, map<string,string>& my_map); //evaluate postfix expression
		bool token_value_is_in_map(Token& tok, map<string,string>& my_map); //helper for evaluate function


};
#endif 