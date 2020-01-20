#include <cstdlib>
#include<bits/stdc++.h> 
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<queue>
#include<stack>
#include "token.h"
#include "expressions.h"
using namespace std;

int main(int numArg, char *args[])
{
	string inputFile;
	string outFile;
	bool output_file_is_specified;
	
	map<string,string> map1; //creating a map, where I will keep track of varaibles as they get evaluated
	map<string, string>::iterator itr; //map's iterator

	if (numArg !=4 && numArg !=5 ) // checking for correct input when opening file (4 arguments because outFile name can be unspecified)
	{
		cerr << "Insufficient Arguments." << endl;
		cerr<<"Usage: ./mycalc -i <inputFile> -o <outFile>"<<endl; //used to tell the user the proper invocation pattern
		return EXIT_SUCCESS;
	}
	//// if aarguemnts are sufficient in number, continue further
	else // checking for correct input when opening file
	{	
		//read main function arguemnts
		for (int i=1; i<numArg; i++)
		{
			if (string(args[i])=="-i" && i+1<numArg) //before accessing the next location, checking if it's valid 
				inputFile=args[i+1];
			
			if (string(args[i])=="-o" && i+1<numArg)
				outFile=(args[i+1]); 
		}
		//check if user specified outfile
		if (outFile == "")
		{
			output_file_is_specified = false;
		}
		else
		{
			output_file_is_specified = true;
		}
		
		// opening the input file
		ifstream fin(inputFile);
		//if the file is not open, the program terminates
		if(not fin.is_open())
		{
			cout<<"Can't open the file"<<inputFile<<endl;
			return EXIT_FAILURE;
		}
		//if the input file was entered and it exists and can be opened: continue further
		else
		{
			vector<Expression> expressions_vector; //creating vector of EXPRESSION objects (each line is an expression object)

			//readfile, save the content of each full line as an Expression object
			for( std::string line; getline( fin, line);) 
			{
			    Expression expr(line);
			    expressions_vector.push_back(expr); //push each object into expression vector
			}
			//important things that happened so far, upon the creation of the expression objects:
			//expressions vector with expression objects had been created
			//is_evaluated = false for every expression obj
			//is_valid_variable = true for every expression obj

			//lhs and rhs have been separated in constructor for each expression
			
			//sanity chcek for LHS, if invalid is_valid_variable = false
			
			//vector of tokens was created for each expression's RHS
			//chcek sanity of the RHS = i.e. chcek sanity of the vector of tokens
			//create a postfix queue for those expressions that are valid (i.e no synatx errors)
			//RUNNING THE EVALUATION LOOP
			int max_num_of_loops = expressions_vector.size();
			bool all_not_evaluated = true;
			int while_loop_counter = 0;
			int num_not_evaluated = 0;
			
			while (all_not_evaluated == true && while_loop_counter <= max_num_of_loops)
			{
				num_not_evaluated = 0;
				for (int i=0; i<expressions_vector.size(); i++)
				{
					if (expressions_vector[i].is_valid_variable == false)
					{
						//this is done on those expressions, which are invalid at the first sight e.g. with syntax errors
						map1[expressions_vector[i].lhs]=expressions_vector[i].answer; //answer = "invalid" - this is decied in constructor
						expressions_vector[i].is_evaluated = true;
					}
					else //we know that all these expressions are valid and have a queue that stores postfix
					{
						expressions_vector[i].evaluate(expressions_vector[i].postfix_token_q, map1);
						//the evaluate function puts the answers to the map and declares the objects evaluated if they can be evalated or it declares them invalid if they contain an ivalid variable
					}

					if (expressions_vector[i].is_evaluated == false)
						num_not_evaluated++;
					if (num_not_evaluated = 0)
						all_not_evaluated = false;
				}
				while_loop_counter++;
			}

			//printing output
			//if the output file is specified, a new file that contains the outcome of the evaluation is created
			if (output_file_is_specified)
			{
				cout<<"input file: "<<inputFile<<endl;
				cout<<"output file: "<<outFile<<endl;
				ofstream file;
				file.open (outFile);
				file<<"Evaluated expressions:"<<endl;
					for(int i=0; i<expressions_vector.size(); i++)
					{
						file<<expressions_vector[i].lhs<<" = "<<expressions_vector[i].answer<<'\n';
						
					}
					file.close();
			}
			else //if the output file is not specified, then print results in the terminal
			{
					cout<<"input file: "<<inputFile<<endl;
					cout<<endl;
					cout<<"Evaluated expressions:"<<endl;
					for(int i=0; i<expressions_vector.size(); i++)
					{
						cout<<expressions_vector[i].lhs<<" = "<<expressions_vector[i].answer<<'\n';	
					}
					
			}


		}

	}
	return 0;
}		

 