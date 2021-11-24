//Operator precedence parser

#define MAX_SIZE 100
#define EMPTY '0'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//The operator precedence table
char opPredTable[5][5] = {
    //           i       +       x       $      E
    /* i */{    ' ',    '>',    '>',    '>',    '<'},
    /* + */{    '<',    '>',    '<',    '>',    '<'},
    /* x */{    '<',    '>',    '>',    '>',    '<'},
    /* $ */{    '<',    '<',    '<',    ' ',    '<'},
    /* E */{    '<',    '<',    '<',    '>',    ' '}
};

//returns the index of symbol in operator precedence table
char indexOf(char symbol){
    switch(symbol){
        case 'i': return 0;
        case '+': return 1;
        case 'x': return 2;
        case '$': return 3;
        case 'E': return 4;
    }
}

//reduce handle with Non-Terminal
char * reduce(char * expr, int start, int end, char NT){
    char* finalExpr = malloc(MAX_SIZE + 1);
    int j = 0;

    for(int i=0; expr[i]!='\0'; i++){
        if(i<start || i>end){
            finalExpr[j++] = expr[i];
        }
        if(i==end-1){
            if(NT != EMPTY)
                finalExpr[j++] = NT;
        }
    }

    return finalExpr;
}

//finds and reduces handles 
char * findAndReduceHandles(char *expr){
    char handle[MAX_SIZE];
    int end, start, flag=0;
    
    //find end and start of handle
    for(int i=0; expr[i]!='\0'; i++){
        if(expr[i]=='>'){
            end = i;
            flag++;
            break;
        }
    }
    for(int i=end; expr[i]!='$'; i--){
        if(expr[i]=='<'){
            start = i;
            flag++;
            break;
        }
    }

    if(flag != 2){
        return expr;
    }

    //copy handle
    strncpy(handle, expr + start, (end+1) - start);
    handle[(end+1)-start] = '\0';

    if(strcmp("<i>", handle)==0){
        expr = reduce(expr, start, end, 'E');
    }
    else if(strcmp("<E>", handle)==0){
        expr = reduce(expr, start, end, EMPTY);
    }
    else if(strcmp("<+>", handle)==0){
        expr = reduce(expr, start, end, EMPTY);
    }
    else if(strcmp("<x>", handle)==0){
        expr = reduce(expr, start, end, EMPTY);
    }

    printf("%s\n", expr);
    
    return expr;
}

//returns the precedence between two symbols
char findPrecedence(char symbol, char lookAhead){
    int symIdx, lookAheadIdx;
    symIdx = indexOf(symbol);
    lookAheadIdx = indexOf(lookAhead);

    return opPredTable[symIdx][lookAheadIdx];
}

//checks the whether the symbol is from expression or precedence
int isPrecedence(char symbol){
    if(symbol == '>' || symbol == '<' || symbol == '='){
        return 1;
    }

    return 0;
}

//returns an expression with precedence characters inserted
char * insertPrecedence(char * expr){
    char *exprWithPrecedence = malloc(MAX_SIZE + 1);
    int j=0;

    for(int i=0; expr[i]!='\0'; i++){
        exprWithPrecedence[j++] = expr[i++];
        
        //if last symbol
        if(i>0 && expr[i] == '$'){
            break;
        }

        //if precedence already calculated copy/skip else calculate and copy precedence
        if(isPrecedence(expr[i])==1){
            exprWithPrecedence[j++] = expr[i];
        }else{
            exprWithPrecedence[j++] = findPrecedence(expr[i-1], expr[i]);
        }
    }

    return exprWithPrecedence;
}

void parse(char * expr){
    int flag = 0, length;

    expr = insertPrecedence(expr);
    while(1){
        if(flag==2){
            break;
        }
        
        length = strlen(expr);
        expr = findAndReduceHandles(expr);

        if(strlen(expr)==length){
            flag++;
            expr = insertPrecedence(expr);
        }else{
            flag = 0;
        }
    }
}

void main(){
    char expr[MAX_SIZE];

    printf("Enter expression: ");
    scanf("%s", expr);
    printf("\n");

    parse(expr);
}