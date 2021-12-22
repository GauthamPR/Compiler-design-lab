%{
    #include "y.tab.h"
%}

Digit               [0-9]+
Identifier          [A-z]([A-z]|_|[0-9])*
Operators           \+|\-|\/|\*
Comment             (\/\/.*)|(\/\*([^\*\/])*\*\/)

%%
{Digit}                 {return(DIGIT);};
{Identifier}            {return(ID);};
{Operators}             {return(OP);};
{Comment}               ;
.                       return yytext[0];
\n                      ;
%%

int yywrap(){}