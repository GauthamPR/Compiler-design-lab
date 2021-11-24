//Operator precedence parser

#define MAX_SIZE 100
#define EMPTY '\000'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//The operator precedence table
char opPredTable[5][5] = {
    //           i       +       x       $
    /* i */{    ' ',    '>',    '>',    '>'},
    /* + */{    '<',    '>',    '<',    '>'},
    /* x */{    '<',    '>',    '>',    '>'},
    /* $ */{    '<',    '<',    '<',    ' '}
};

char stack[MAX_SIZE];
int top = 0;

char queue[MAX_SIZE];
int front = 0;

//returns the index of symbol in operator precedence table
char indexOf(char symbol){
    switch(symbol){
        case 'i': return 0;
        case '+': return 1;
        case 'x': return 2;
        case '$': return 3;
    }
}

//reduce handle
void reduce(int start, int end){
    char tempStack[MAX_SIZE];
    int j = 0;

    for(int i=0; stack[i]!='\0'; i++){
        if(i<start || i>end){
            tempStack[j++] = stack[i];
        }
        if(i==end-1){
            tempStack[j++] = EMPTY;
        }
    }

    strcpy(stack, tempStack);
    top = strlen(stack)-1;
}

//finds and reduces handles 
void findAndReduceHandles(){
    char handle[MAX_SIZE];
    int end = top, start;
    
    for(int i=end; stack[i]!='$'; i--){
        if(stack[i]=='<'){
            start = i;
            break;
        }
    }

    //copy handle
    strncpy(handle, stack + start, (end+1) - start);
    handle[(end+1)-start] = '\0';

    //if production exist reduce handle
    if(strcmp("<i", handle)==0){
        reduce(start, end);
    }
    else if(strcmp("<+", handle)==0){
        reduce(start, end);
    }
    else if(strcmp("<x", handle)==0){
        reduce(start, end);
    }

}

//returns the precedence between two symbols
char findPrecedence(char symbol, char lookAhead){
    int symIdx, lookAheadIdx;
    symIdx = indexOf(symbol);
    lookAheadIdx = indexOf(lookAhead);

    return opPredTable[symIdx][lookAheadIdx];
}

void printStackAndQ(){
    printf("%s\t\t", stack);
    for(int i=front; i<strlen(queue); i++){
        printf("%c", queue[i]);
    }
}

void parse(){
    char precedence;

    while(!(stack[top]=='$' && queue[front]=='$')){
        
        printStackAndQ();

        precedence = findPrecedence(stack[top], queue[front]);
        
        if(precedence == '>'){
            printf("Reduce\n");
            findAndReduceHandles();
        }else{
            printf("Shift\n");
            top++;
            stack[top++] = precedence;
            stack[top]=queue[front++];
        }
    }

    printf("\t\tString Accepted\n");
}

void main(){
    char expr[MAX_SIZE];

    stack[0] = '$';

    printf("Enter expression: ");
    scanf("%s", queue);
    printf("\n");

    printf("Stack\t\tInput\t\tOperation\n");
    parse();
}