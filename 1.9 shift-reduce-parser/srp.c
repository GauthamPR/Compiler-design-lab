//Shift Reduce parser

#define MAX_SIZE 100
#define EMPTY '\000'
#define START_SYMBOL 'S'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char PRODUCTION[10][10] = {
    {
        'S', '-', '>', 'S','+','S'
    },
    {
        'S', '-', '>', 'S','x','S'
    },
    {
        'S', '-', '>', 'i'
    }
};

char stack[MAX_SIZE];
int top = 0;

char queue[MAX_SIZE];
int front = 0;

//reduce handle
void reduce(int start, int end, int found){
    char tempStack[MAX_SIZE];
    int j = 0;

    for(int i=0; stack[i]!='\0'; i++){
        if(i<start || i>end){
            tempStack[j++] = stack[i];
        }else{
            tempStack[j++] = PRODUCTION[found][0];
            i=end;
        }
    }
    tempStack[j++] = '\0';
    strcpy(stack, tempStack);
    top = strlen(stack)-1;
    for(int i=top+2; stack[i]!='\0'; i++){
        stack[i] = '\0';
    }
}

//finds and reduces handles 
int findAndReduceHandles(){
    char handle[MAX_SIZE];
    int end, start;
    int found = -1;
    
    char* startAddr;

    startAddr = strstr(stack, "S+S");
    if(startAddr){
        found = 0;
        end = 3;
    }else{
        startAddr = strstr(stack, "SxS");
        if(startAddr){
            found = 1;
            end = 3;
        }else{
            startAddr = strstr(stack, "i");
            if(startAddr){
                found = 2;
                end = 1;
            }
        }
    }

    if(found>-1){
        printf("\t\tReduce %s\n", PRODUCTION[found]);
        for(int i=0; stack+i!=startAddr; i++){
            start = i+1;
        }
        end = start + end;
        
        //if production exist reduce handle
        reduce(start, end, found);
        return 1;
    }else{
        return 0;
    }

    //copy handle
    // strncpy(handle, stack + start, (end+1) - start);
    // char something[10] = {'>', '\0'};
    // handle[(end+1)-start] = '\0';
    // strcat(handle, something);


}

void printStackAndQ(){
    printf("%s\t\t", stack);
    for(int i=front; i<strlen(queue); i++){
        printf("%c", queue[i]);
    }
}

void parse(){

    while(!(stack[0]=='$' &&stack[1]==START_SYMBOL && queue[front]=='$')){
        
        printStackAndQ();
        
        if(findAndReduceHandles()!=1){
            printf("\t\tShift\n");
            top++;
            stack[top]=queue[front++];
        }
    }

    printStackAndQ();
    printf("\t\tString Accepted\n");
}

void main(){
    stack[0] = '$';

    printf("Enter expression: ");
    scanf("%s", queue);
    queue[strlen(queue)] = '$';
    printf("\n");

    printf("Stack\t\tInput\t\tOperation\n");
    printf("-----------------------------------------\n");
    parse();
}