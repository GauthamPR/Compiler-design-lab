//First and follow

#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

char NTAdded[100];
char firstOfNT[100][100];

void mergeFirstTo(char NT, char symbol){
    int symIdx = -1, NTIdx = -1;
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]==symbol){
            symIdx = i;
        }
        if(NTAdded[i]==NT){
            NTIdx = i;
        }
    }
    
    for(int i=0; firstOfNT[symIdx][i] != '\0' || i<MAX_SIZE; i++){
        for(int j=0; j<MAX_SIZE; j++){
            if(firstOfNT[NTIdx][j] == '\0' || firstOfNT[NTIdx][j]==firstOfNT[symIdx][i]){
                firstOfNT[NTIdx][j] = firstOfNT[symIdx][i];
                break;
            }
        }
    }
}

int addNT(char NT){
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]==NT){
            return i;
        }else if(NTAdded[i]=='\0'){
            NTAdded[i] = NT;
            return i;
        }
    }
}

void addToFirst(char NT, char symbol){
    int idx = addNT(NT);
    
    NTAdded[idx] = NT;
    int symIdx;
    for(int i=0; i<MAX_SIZE; i++){
        if(firstOfNT[idx][i] == '\0' || firstOfNT[idx][i]==symbol){
            symIdx = i;
            break;
        }
    }

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
                    addNT(NT);
                    mergeFirstTo(NT, prod[i]);
                }else{
                    flag = 1;
                    addToFirst(NT, prod[i]);
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
        printf("First of %c:\n", NTAdded[i]);
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


void start(){
    int nOfProds;
    char prods[100][100];
    char temp;

    FILE *fptr = fopen("./input.txt", "r");

    fscanf(fptr, "%d", &nOfProds);
    if(fptr == NULL){
        printf("Error!");
    }

    for(int i=0; i<nOfProds; i++){
        fscanf(fptr, "%c", &temp);
        fscanf(fptr, "%[^\n]", prods[i]);
        first(prods[i]);
    }
}

void main(){
    start();
    start();
    
    printFirst();
    printf("\n------------------------------\n");
}