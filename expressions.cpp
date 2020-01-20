#include "expressions.h"
#include "token.h"

Expression::Expression(string lhs_and_rhs) 
{
  this->lhs_and_rhs = lhs_and_rhs;
  
  is_evaluated = false;
  is_valid_variable = true;
  this->separate_lhs_and_rhs();
  
  check_lhs_variable_validity(this->lhs);
  this->vector_of_tokens = this->tokenize_rhs(this->rhs);
  check_rhs_expression_sanity(vector_of_tokens);

  if (this->is_valid_variable == true)
  {
  	this->postfix_token_q = this->infix2postfix(this->vector_of_tokens);
  }
  else
  {
  	this->answer = "invalid";
  }
  
}

int Expression::evaluate(queue<Token>& token_q, map<string,string>& my_map) //citation: this function's algorithm is a modified algorithm from lab7 led by instructor Khalid Mengal
{
	//return  1 > it was evaluated as number , therefore add to map the expression's answer (the number as string)
				//change bool is evaluated to true
	//return  2 > it contains an ivalid valiable or the operation to be perofrmes is invalid - add to map answer ("invalid)"
				//change bool is evaluated to true
	//return  3 > it cannot be evaluated yet - continue in the for loop to next expression
				//keep is evaluated as false
	vector<Token> my_vector;

	int n = token_q.size();
	for(int i =0; i<n; i++ )
	{
		Token tok2 =token_q.front();
		token_q.pop();
		token_q.push(tok2);
		my_vector.push_back(tok2);
		
	}

	stack <string> my_stack; //1. Create a stack of type string to store the operands
	
	int e = my_vector.size(); //2. Scan the postfix expression from left to right for every element
	for(int i =0; i<e; i++ )
	{
		Token tok = my_vector[i];
		
		//now we can work with tok - token, which is the current element of postfix that is scanned
		//	 a. if the element is an operand push it to the stack
		
		if (tok.type == "number")
		{
			
			my_stack.push(tok.value);
		}
		else if (tok.type == "variable")
		{
			if (!token_value_is_in_map(tok,my_map))
			{
				this->answer = "could not be evaluated";
				return 3;
			}
			else //tok vlaue is in map
			{
				if (my_map[tok.value]=="invalid")
				{
					this->is_evaluated = true;
					this->answer = "invalid";
					my_map[this->lhs]= answer;
					return 2;
				}
				else //there is a numerical value taken from the map
				{
					my_stack.push(my_map[tok.value]);
				}
			}
		}
		else if (tok.type == "unary_op") //b. if the element is a unary operator it from the stack
		{
			string str_a = my_stack.top(); my_stack.pop();
			string result = calculate_unary(tok.value, str_a); //apply the operator on it
			my_stack.push(result);
			// push the result back to the stack
		}
		else if (tok.type == "binary_op") //b. if the element is a binary operator it from the stack
		{
			string str_a = my_stack.top(); my_stack.pop();
			string str_b = my_stack.top(); my_stack.pop();
			if ((tok.value == "/" || tok.value == "%" || tok.value == "mod" ) && stod(str_a) == 0 ) //we do not allow division by zero, integer division by zero or mod on zero
			{
				this->is_evaluated = true;
				this->answer = "invalid";
				my_map[this->lhs]= answer;
				return 2;
			}

			string result = calculate_binary(str_b, tok.value, str_a); //apply the operator on it
			my_stack.push(result);
			// push the result back to the stack
		}
	}
	this->is_evaluated = true;
	this->answer = my_stack.top();
	my_map[this->lhs]= answer;
	return 1;
}

bool Expression::token_value_is_in_map(Token& tok, map<string,string>& my_map)
{
	auto search = my_map.find(tok.value);
    if (search != my_map.end()) {
        return true;
    } else {
        return false;
    }
}
string Expression::calculate_binary(string a, string operation, string b) //calculate result of a binary operation
{
	double num_a = stod(a);
	double num_b = stod(b);
	
	if (operation == "+")
		return to_string(num_a+num_b);
	
	else if (operation == "-")
		return to_string(num_a-num_b);
	
	else if (operation == "/")
		return to_string(num_a/num_b);

	else if (operation == "*")
		return to_string(num_a*num_b);
	
	else if (operation == "mod")
		return to_string(num_a-((floor(num_a/num_b))*num_b));
	
	else if (operation == "%")
		return to_string(floor(num_a/num_b));

}

string Expression::calculate_unary(string operation, string str_a) //calculate result of a unary operation
{
	double num_a = stod(str_a);
	
	if (operation == "-")
		return to_string(-num_a);
	
	else if (operation == "++")
		return to_string(num_a +1);
	
	else if (operation == "--")
		return to_string(num_a -1);

	else if (operation == "**")
		return to_string(num_a*num_a);

}



string Expression::print_postfix_q (queue<Token>& token_q, map<string,string>& my_map) //this function is never called, nevertheless we kept it for the instructor in case he wanted to check the corectness of our postfix conversions
{
	int n = token_q.size();
	for(int i =0; i<n; i++ )
	{
		Token tok =token_q.front();
		token_q.pop();
		token_q.push(tok);
		cout<<tok.value<<" ";
	}
	return "-------------";
}

void Expression::check_rhs_expression_sanity (vector<Token>& token_vec) //chceks the sanity of the right hand side
{	  
	int count_left=0;
  	int count_right=0;
  	int count_semicol =0;
	for (int i=0; i<token_vec.size(); i++)
  			
		{
			if (token_vec[i].type == "invalid" && is_valid_variable)
			{
				is_valid_variable = false;
				
			}

			if (token_vec[i].type =="left_par")
				count_left=count_left+1;
			else if (token_vec[i].type =="right_par")
				count_right=count_right+1;
			else if (token_vec[i].type =="semicol")
				count_semicol=count_semicol+1;


		}
	if (count_right!=count_left) //chcek for correct number of paranthesis
		is_valid_variable = false;
	if (count_semicol !=1) //check that each expression is ended by semicolon
		is_valid_variable = false;

}

queue <Token> Expression::infix2postfix (vector<Token>& token_vec) //infix to postfix convertor, citation: this function's algorithm was adopted from lab7 led by instructor Khalid Mengal
{
	
	stack<Token> mystack;
	queue<Token> postfix_q;
	//1. Push “(“onto Stack, and add “)” to the end of INFIX.
	//in our case, we are pushing tokens:
	Token left_p("(","left_par");
	Token right_p(")","right_par");

    token_vec.push_back(right_p);
    mystack.push(left_p);

     //2. Scan INFIX - token_vec from left to right and repeat Step 3 to 6 for each element of X 
    //until the Stack is empty.3.   If an operand 


    int i=0;

    while(!mystack.empty())
    {   
        Token ch = token_vec[i++];
   
        //3.    If an operand is encountered, add it to POSTFIX.
        if (ch.type == "number" || ch.type == "variable")
            {
            	postfix_q.push(ch);
            }

        //4.    If a left parenthesis is encountered, push it onto Stack.
        else if (ch.type == "left_par" )
            mystack.push(ch);

        //5.    If an operator is encountered, then: 
        else if (ch.type == "binary_op" || ch.type == "unary_op")
        {   //a.    Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack) 
            //which has the same precedence as or higher precedence than operator.
            while ((mystack.top().type == "binary_op" || mystack.top().type == "unary_op" )  && isleq(ch,mystack.top()))
            {
                
                postfix_q.push(mystack.top());
                mystack.pop();
            }
            //b.    Add operator to Stack.
            mystack.push(ch);
        }
        
        //.6.   If a right parenthesis is encountered, then: 
        else if (ch.type == "right_par" )
        {
            //a.    Repeatedly pop from Stack and add to POSTFIX each operator 
            //(on the top of Stack) until a left parenthesis is encountered.
            while(mystack.top().type!="left_par")
            {
                postfix_q.push(mystack.top());
                mystack.pop();
            }
            
            //b.    Remove the left Parenthesis.
            mystack.pop();
        }
    }
    

    return postfix_q;
}


bool Expression::isleq (Token a, Token b) //helper method, citation: this function's algorithm was adopted from lab7 led by instructor Khalid Mengal
{
	return (convertOpToInt(a)<=convertOpToInt(b));
}

int Expression::convertOpToInt (Token tok) //helper method
{
	if ( tok.type == "unary_op" ) 
		return 3;
	else if ( tok.type == "binary_op"  ) 
	{
		if ( tok.value == "+" || tok.value == "-") 
			return 1;
		else 
			return 2;
	}
	else
		cout<<"Error converting operators"<<endl;


}

void Expression::separate_lhs_and_rhs(){ //separates left and right hand sign upon finding the first minus in the line
	//is called in constructor
	int pos_of_equal_sign;
	pos_of_equal_sign = lhs_and_rhs.find("=");
	lhs = lhs_and_rhs.substr(0,pos_of_equal_sign);
	rhs = lhs_and_rhs.substr(pos_of_equal_sign+1,lhs_and_rhs.length()-1);
	
}

bool Expression::isAnAlphabet(char ch){
	return (ch >= 65 && ch <= 90)||(ch >= 97 && ch <= 122);	// checks asci codes if they are an alphabet a-z or A-Z	
}

void Expression::check_lhs_variable_validity(string a) //sanity chcek for the left hand side
{
	int var_cntr=0;
		int i=0;
		while ( i< a.length() ) //while you dont reach the end of the lhs string
		{
			
	 		
	 		if (isAnAlphabet(a[i]) || a[i]==95) // if it starts with alphabet or underscore
	 		{
	 			
	 			int e=1;
	 			while (isAnAlphabet(a[i+e])|| a[i+e]==95 || isdigit(a[i+e])) //while the next character is an underscore alphabet or a digit
	 			{
	 				e++;	
	 			}
	 			
	 			string variable;
	 			variable = a.substr(i,e);
	 			this->lhs=variable;
	 			var_cntr++;
	 			i=i+e; //examine other parts of the string, explore next index

	 			continue;
	 		}
	 		
	 		else if (a[i] == ' ') //if it is a space dont do anything - we dont want to tokenize spaces
	 		{
	 			
	 			i++; //explore next index
	 			continue;
	 		}

	 		else
	 		{ //if you find anything other character other than variable , declare varailbe as invalid
	 			
	 			this->is_valid_variable = false;
	 			i++;
	 		}
	 	} //end of while loop

	 	if (var_cntr != 1)
	 	{
	 		this->is_valid_variable = false; //check for if there is only one variable (e.g.: abc cd = 5; would be invalid becasue there is space between abc and cd)
	 		
	 	}
	 	
	 	
		
}


vector <Token> Expression::tokenize_rhs(string a){
	//used in constructor
	std::vector<Token> my_vector; //create vector of tokens
	int i=0;
	while ( i< a.length()) //while you dont reach the end of the expression, i.e scanning the right hand side 
	{
		
 		//create left_parahtesis token
 		if (a[i]== '(')
 		{
 			Token tok("(", "left_par");
 			my_vector.push_back(tok);
 			i++; //go to next token
 		} else if (a[i]== ')'){
 			Token tok(")", "right_par");
 			my_vector.push_back(tok);
 			i++; //go to next token
 		}
 		//create number token
 		else if (isdigit(a[i]))
 		{
 			int dot_cntr = 0;
 			int e=1;
 			while (isdigit(a[i+e])|| a[i+e]== 46) //number can be integer or float
 			{
 				if (a[i+e] == 46)
 					dot_cntr++; //count dots in a float number
 				e++;
 			}

 			if (dot_cntr > 1) //if there are more than one dots , for example x= 3.14.44 , declare as invalid
 			{
 				Token tok("invalid","invalid");
 				my_vector.push_back(tok);
 				break;
 			}
 			else
 			{
 				string number;
	 			number = a.substr(i,e);
	 			Token tok(number,"number");
	 			my_vector.push_back(tok); 
	 			i=i+e; //go to next token
 			}
 			
 		}
 		//creating variable or modulo tokens
 		else if (isAnAlphabet(a[i]) || a[i] == 95) // if it starts with alphabet or underscore
 		{
 			int e=1;
 			while (isAnAlphabet(a[i+e]) || a[i+e]==95 || isdigit(a[i+e])) //while the next character is an underscore/alphabet/digit
 			{
 				e++;
 				
 			}
 			
 			string variable;
 			variable = a.substr(i,e);
 			//tokenize as mod binary operator
 			if (variable == "mod" && a[i+e] == ' ') //check if var is mod modulus i.e the word "mod" must be strictly followed by a space, otherwise treat it as a variable, therefore we assume it is possible to have a variable called mod1 or mod4 
 			{
 				Token tok("mod","binary_op");
 				my_vector.push_back(tok);
 			}
 			
 			else //else tokenize it as a variable
 			{
 				Token tok(variable,"variable");
 				my_vector.push_back(tok);
 			}
 			i = i + e; //go to next token

 		}
 		
 		else if (a[i] == ' ') //if it is a space dont do anything - we dont want to tokenize spaces
 		{
 			i++; //go to next token
 		}

 		else if (a[i] == ';') //if it is a semicolon, tokenize as semiclon
 		{
 			Token tok(";","semicol");
 			my_vector.push_back(tok);
 			i++; //go to next token
 		}
 		
 		else if (a[i] == '+') //if it starts with a plus 
 		{
 			int e=1;
 			while (a[i+e]=='+') //while the next character is a plus
 				{
 					e++;
 				}
 			string variable;
 			variable = a.substr(i,e);
 			
 			
 			if (variable.length() == 1) //if there is exactly one plus
 				{
 					Token tok("+","binary_op");
 					my_vector.push_back(tok);
 				}
 			else if (variable.length() == 2) //if there is exactly two pluses
 				{
 					Token tok("++","unary_op");
 					my_vector.push_back(tok);
 					
 				}
 			else  //if you have more than two pluses in a row, its invalid , that means their sucession was not broken by paranthesis, therefore the input in ambiguous, we dont know what user ment to calculate
 				{
 					Token tok("invalid","invalid");
 					my_vector.push_back(tok);
 					break;
 				}
 			i += e;

 		}
 		//MINUS or MINUSES recognition
 		else if (a[i] == '-') //if it starts with a minus
 		{
 			int e=1;
 			while (a[i+e]=='-') //while the next character is minus
 			{
 				e++;
 				
 			}
 			string variable;
 			variable = a.substr(i,e);
 			//if you have more than two miuses in a row, that means their sucession was not broken by paranthesis, therefore the input in ambiguous, we dont know what user ment to calculate
 			if (variable.length() == 1 && i==1) //length 1 and at the first index
 				{
 					Token tok("-","unary_op");
 					my_vector.push_back(tok);
 				}
 			else if (variable.length() == 1 && a[i-1]== '(') //length one and after paranthesis
 				{
 					Token tok("-","unary_op");
 					my_vector.push_back(tok);
 				}
 			else if (variable.length() == 2) //exactly two minuses in a row
 				{
 					Token tok("--","unary_op");
 					my_vector.push_back(tok);
 				}
 			else if (variable.length() > 2) //more than two successive minuses --> declare as invalid
 				{
 					Token tok("invalid","invalid");
 					my_vector.push_back(tok);
 					break;
 				}
 			else //length one and binary
 				{
 					Token tok("-","binary_op");
 					my_vector.push_back(tok);
 				}
 				i += e;
 			
 		}

 		else if (a[i] == '*') //if it starts with a star
 		{
 			int e=1;
 			while (a[i+e]=='*') //while the next character is a star
 			{
 				e++;
 				
 			}
 			string variable;
 			variable = a.substr(i,e);
 			//if you have more than two stars in a row, that means their sucession was not broken by paranthesis, therefore the input in ambiguous, we dont know what user ment to calculate
 			if (variable.length() == 1) //if there is exactly one 
 				{
 					Token tok("*","binary_op");
 					my_vector.push_back(tok);
 					
 				}
 			else if (variable.length() == 2) //if there is exactly two 
 				{
 					Token tok("**","unary_op");
 					my_vector.push_back(tok);
 					
 					
 				}
 			else  //if you have more than two stars in a row, its invalid , that means their sucession was not broken by paranthesis, therefore the input in ambiguous, we dont know what user ment to calculate
 				{
 					Token tok("invalid","invalid");
 					my_vector.push_back(tok);
 					break;
 					
 					
 				}
 			i += e;
 			
 		}

  		else if (a[i] == '/') //if it starts with a /
 		{
 			int e=1;
 			while (a[i+e]=='/') //while the next character is a slash
 			{
 				e++;
 				
 			}
 			string variable;
 			variable = a.substr(i,e);
 			//if you have more than one slashes in a row, that means their sucession was not broken by paranthesis, therefore the input in ambiguous, we dont know what user ment to calculate
 			if (variable.length() > 1) 
 				{
 					//create invalid token
 					Token tok("invalid","invalid");
 					my_vector.push_back(tok);
 					break;
 					

 				}
 			else //if there is exactly one slash
 				{
 					//tokenize as binary
 					Token tok("/","binary_op");
 					my_vector.push_back(tok);
 					
 				}
 			i += e;
 			
 		}		

  		else if (a[i] == '%') //if it starts with a %
 		{
 			int e=1;
 			while (a[i+e]=='%') //while the next character is a percent sign
 			{
 				e++;
 				
 			}
 			string variable;
 			variable = a.substr(i,e);
 			//if you have more than one % in a row, that means their sucession was not broken by paranthesis, therefore the input in ambiguous, we dont know what user ment to calculate
 			if (variable.length() > 1) 
 				{
 					//create invalid token
 					Token tok("invalid","invalid");
 					my_vector.push_back(tok);
 					break;
 					

 				}
 			else //if there is exactly one percent sign
 				{
 					//tokenize as binary
 					Token tok("%","binary_op");
 					my_vector.push_back(tok);
 					

 				}
 			i += e;
 			
 		}
 		else
 		{
 			Token tok("invalid","invalid");
 			my_vector.push_back(tok);
 			break;
 			i++;
 		}

	}
	return my_vector;
}