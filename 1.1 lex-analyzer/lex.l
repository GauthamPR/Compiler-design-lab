%{
    int keywordCount = 0;
    int identifierCount = 0;
    int literalCount = 0;
    int assignmentOperatorCount = 0;
    int arithmeticOperatorCount = 0;
    int relationalOperatorCount = 0;
    int logicalOperatorCount = 0;
%}

Keyword             auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|const|float|short|unsigned|continue|for|signed|void|default|goto|sizeof|volatile|do|if|static|while
Literal             (\".*\")|(\'[A-z]*\')|[0-9]*
Identifier          [A-z]([A-z]|_|[0-9])*
AssignmentOperator  =|\+=|\-=|\/=|%=
ArithmeticOperator  \+|\-|\/|\*
RelationalOperator  ==|!=|<=|>=|<|>
LogicalOperator     &&|\|\||!
Comment             (\/\/.*)|(\/\*(.|\n)*\*\/)

%%
{Keyword}               {printf("Keyword:\t\t\t\t %s\n", yytext); keywordCount++;};
{Literal}               {printf("Literal:\t\t\t\t %s\n", yytext); literalCount++;};
{Identifier}            {printf("Identifier:\t\t\t\t %s\n", yytext); identifierCount++;};
{AssignmentOperator}    {printf("Assignment operator:\t\t\t %s\n", yytext); assignmentOperatorCount++;};
{ArithmeticOperator}    {printf("Arithmetic operator:\t\t\t %s\n", yytext); arithmeticOperatorCount++;};
{RelationalOperator}    {printf("Relational operator:\t\t\t %s\n", yytext); relationalOperatorCount++;};
{LogicalOperator}       {printf("Logical operator:\t\t\t %s\n", yytext); logicalOperatorCount++;};
{Comment}               ;
.                       ;
\n                      ;
%%

int yywrap(){}

int main(){
    yylex();
    int total = 0;
    printf("---------------------------------------------------------");
    printf("\nNumber of Keywords:\t\t\t %d\n", keywordCount);
    total+=keywordCount;
    printf("Number of Identifiers:\t\t\t %d\n", identifierCount);
    total+=identifierCount;
    printf("Number of Literals:\t\t\t %d\n", literalCount);
    total+=literalCount;
    printf("Number of Arithmetic Operators:\t\t %d\n", arithmeticOperatorCount);
    total+=arithmeticOperatorCount;
    printf("Number of Assignment Operators:\t\t %d\n", assignmentOperatorCount);
    total+=assignmentOperatorCount;
    printf("Number of Relational Operators:\t\t %d\n", relationalOperatorCount);
    total+=relationalOperatorCount;
    printf("Number of Logical Operators:\t\t %d\n", logicalOperatorCount);
    total+=logicalOperatorCount;
    printf("---------------------------------------------------------");
    printf("\nTotal: \t\t\t\t\t%d\n", total);
    return 0;
}