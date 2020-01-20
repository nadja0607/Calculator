Data Structures
CS-UH 1050 – Spring 2019
Date: April 7th 2019
---------------------------------------------------------------------------------------------------------------------
Project Name: 
	My Calculator
---------------------------------------------------------------------------------------------------------------------
Tech/framework used:
	Sublime Text Editor
---------------------------------------------------------------------------------------------------------------------
Prerequisites:
	Linux/FreeBSD C++ environment
---------------------------------------------------------------------------------------------------------------------
Description: 
	In this project, I developed a calculator application named mycalc to evaluate multiple arithmetic
	expressions. The expressions, provided through a text file (every line defines one expression
	and is explicitly terminated by a semicolon), are processed for correctness, evaluated,
	and their outcome is written into either the standard output or a designated file.

	Program invocation format:
					
			mymachine-promt >> ./mycalc -i <inputfile> -o <outfile>
	
		*flag -i* lexeme that follows is the file name containing the expressions to be evaluated
		*flag -o* the name of the file where the outcome should be written into. (file created and writen to)
			If there is no -o flag provided - the outcome of the evaluation appears on the tty (standard output).

	The program should take as a parameter in its command line the name of a text file that contains the expressions
	to be evaluated regardless of operators type:
		* the binary operators used +, -, *, /, %, mod with % being the integer division and mod the
		  modulo operation (the string mod reserved for this purpose).
		* the unary operators used -, ++, --, **, all understood in prefix notation. 
			For example, (-3) indicates a negative float or simply -(3) while --count decrements the value 
			of count by one. No post-form (count--) is permissible in the input files. The operator ** 
			indicates the square of the following value/variable.

	Precedence has to be considered as well :
		* unary operators have precedence over their binary counterparts
		* within the binary set, operators *, /, %, mod have higher precedence than + and -

	Notes: 
		The operator - can be unary or binary. Its interpretation should be determined by the context.
		In particular, -ale means the negative value of the ale expression whereas 21-13 represents binary
		subtraction.
		All expressions should be output in the same order as that in which they appear in the input.
		The program produces the values for all left-hand-side expressions listed in the input file.

	• While dealing with an expression you may encounter a variable that has not been defined yet. 
	  I resolved this issue by “suspending” the evaluation of the expression and coming back to it when
	  the missing variables become available. 
	• I carried a sanity check for all the input expressions to ensure that they are properly parenthesized and unambiguous. 
	  If a problematic expression is encountered, the program reports it, abandons its computation and moves on to the next. 
	  Subsequent computations based on the just-abandoned variable(s) are also not evaluated and reported.



---------------------------------------------------------------------------------------------------------------------


	
