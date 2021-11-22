# Lexical analyzer for C using lex tool

## Example

#### Input
```
void main(){
    char n= 'g';
    int n =0;
    if(n=='c'&& n=='b')
        printf("HELLO world");
    //Single line comment
    /*multi
    line
    comment*/
    n=n+1;
}
```
#### Output (*stdout*)
```
Keyword:                                 void
Identifier:                              main
Keyword:                                 char
Identifier:                              n
Assignment operator:                     =
Literal:                                 'g'
Keyword:                                 int
Identifier:                              n
Assignment operator:                     =
Literal:                                 0
Keyword:                                 if
Identifier:                              n
Relational operator:                     ==
Literal:                                 'c'
Logical operator:                        &&
Identifier:                              n
Relational operator:                     ==
Literal:                                 'b'
Identifier:                              printf
Literal:                                 "HELLO world"
Identifier:                              n
Assignment operator:                     =
Identifier:                              n
Arithmetic operator:                     +
Literal:                                 1
---------------------------------------------------------
Number of Keywords:                      4
Number of Identifiers:                   8
Number of Literals:                      6
Number of Arithmetic Operators:          1
Number of Assignment Operators:          3
Number of Relational Operators:          2
Number of Logical Operators:             1
---------------------------------------------------------
Total:                                  25
 ```