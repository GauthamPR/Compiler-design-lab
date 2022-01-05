%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    int yyerror(char *);
%}

%token DIGIT

%left OP

%%
stmt :   exp '='{printf("%d\n", $1);exit(0);};
exp :    exp OP exp {$$ = ($2=='+')?($1+$3) : ($2=='-')?($1-$3) :($2=='*')?($1*$3) :($2=='/')?($1/$3) : 0;} | DIGIT;
%%

int yyerror(char *s){
    printf("%s\n", s);
    exit(0);
}

int main(void){
    yyparse();
    return 0;
}