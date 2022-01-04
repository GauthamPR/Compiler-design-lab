%{
    #include "y.tab.h"
    #include <string.h>
%}

Identifier          [A-z]([A-z]|_|[0-9])*
Digit               [0-9]+
Operators           \+|\-|\/|\*
Comment             (\/\/.*)|(\/\*([^\*\/])*\*\/)

%%
{Identifier}            {strcpy(yylval.id, yytext);return(ID);};
{Digit}                 {strcpy(yylval.id, yytext);return(DIGIT);};
{Operators}             {strcpy(yylval.id, yytext);return(OP);};
{Comment}               ;
.                       return *yytext;
\n                      return *yytext;
%%

int yywrap(){}