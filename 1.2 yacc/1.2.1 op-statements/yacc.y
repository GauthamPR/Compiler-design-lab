%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    int yyerror(char *);
%}

%token DIGIT ID

%left OP

%%
stmt :   ID '=' exp ';' {printf("Parsing successful\n");};
exp :    exp OP exp | DIGIT | ID;
%%

int yyerror(char *s){
    printf("%s\n", s);
    exit(0);
}

int main(void){
    yyparse();
    return 0;
}