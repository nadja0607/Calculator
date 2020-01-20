#include "token.h"



Token::Token (string v, string t) {
  value = v;
  type = t;
  /*type options:     
    "variable"    | 
    "number"      | 
    "left_par"    | 
    "right_par"   | 
    "unary_op"    | 
    "binary_op"   | 
    "invalid"     | 
    "semicol"     | 
  */    

 }