%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    int yyerror(char *);
    int tCount=0;
%}

%union
{
	char id[30];
}
%token<id> DIGIT ID OP
%type<id> exp

%left OP
%%
stmt :   ID'='exp{
            printf("%s := t%d\n", $1, tCount);
            exit(0);
        }
exp :    exp OP exp {
            printf("t%d := %s %s %s\n", tCount, $1, $2, $3);
            sprintf($$, "t%d", tCount++);
        } 
        | DIGIT
        ;
%%

int yyerror(char *s){
    printf("%s\n", s);
    exit(0);
}

int main(void){
    yyparse();
    return 0;
}