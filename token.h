#ifndef TOKEN
#define TOKEN

#include <cstdlib>
#include<bits/stdc++.h> 
#include<vector>
#include<string>
#include<queue>
#include<iostream>
#include<fstream>

using namespace std; 

class Token{
	public:		
		
		Token(string v, string t); 
		string value; //token value is for example "123" or "/" or "x"
		string type; //token type is "varaible", number, binary operator, unary operator...
		
};
#endif 
