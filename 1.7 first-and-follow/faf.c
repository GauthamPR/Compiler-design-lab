//First and follow

#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

char NTAdded[100];
char firstOfNT[100][100];


int findIdxOfAdded(char NT){
    //Returns the index of NT if NT is in NTAdded else the next free space
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]==NT){
            return i;
        }else if(NTAdded[i]=='\0'){
            return i;
        }
    }
}

int findIdxToAdd(int idx, char symbol){
    //Returns the index of next free space in first of NT
    for(int i=0; i<MAX_SIZE; i++){
        if(firstOfNT[idx][i] == '\0' || firstOfNT[idx][i]==symbol){
            return i;
        }
    }
    printf("ERROR");
}

void addToFirst(char symbol, char NT){
    int idx = findIdxOfAdded(NT);
    NTAdded[idx] = NT;
    int symIdx = findIdxToAdd(idx, symbol);

    firstOfNT[idx][symIdx] = symbol;
}

void first(char * prod){
    char NT = prod[0];
    int flag = 0;
    for(int i=0; i<100; i++){
        if(prod[i]=='\0'){
            break;
        }
        if(prod[i] == '='){
            i+=1;
            if(flag==0){
                if(prod[i]>='A' && prod[i]<='Z'){
                    //process symbol
                }else{
                    flag = 1;
                    addToFirst(prod[i], NT);

                }
            }
        }
    }
}

void printFirst(){
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]=='\0'){
            break;
        }
        printf("\nFirst of %c:\n", NTAdded[i]);
        for(int j=0; j<MAX_SIZE; j++){
            if(firstOfNT[i][j]=='\0'){
                break;
            }else if(firstOfNT[i][j]=='\316'){
                printf(" ε");
            }else
                printf(" %c", firstOfNT[i][j]);
        }
    }
}

void main(){
    int nOfProds;
    char prods[100][100];
    char temp;

    FILE *fptr = fopen("./input.txt", "r");

    printf("Enter number of Productions: ");
    fscanf(fptr, "%d", &nOfProds);
    if(fptr == NULL){
        printf("Error!");
    }

    for(int i=0; i<nOfProds; i++){
        fscanf(fptr, "%c", &temp);
        fscanf(fptr, "%[^\n]", prods[i]);
        first(prods[i]);
        printf("%s", prods[i]);
    }
    
    printFirst();
    printf("\n------------------------------\n");
}