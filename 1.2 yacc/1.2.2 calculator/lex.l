%{
    #include "y.tab.h"
%}

Digit               [0-9]+
Operators           \+|\-|\/|\*
Comment             (\/\/.*)|(\/\*([^\*\/])*\*\/)

%%
{Digit}                 {yylval = atoi(yytext);return(DIGIT);};
{Operators}             {yylval = yytext[0];return(OP);};
{Comment}               ;
.                       return yytext[0];
\n                      return yytext[0];
%%

int yywrap(){}