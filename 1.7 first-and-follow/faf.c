//First and follow

#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

char NTAdded[MAX_SIZE];
char firstOfNT[MAX_SIZE][MAX_SIZE];
char followOfNT[MAX_SIZE][MAX_SIZE];

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

void addToFollowSymbol(char NT, char symbol){
    int idx = addNT(NT);
    int firstNTIdx = addNT(NT);
    NTAdded[idx] = NT;
    for(int i=0; i<MAX_SIZE; i++){
        if(followOfNT[idx][i] != '\0'){
            followOfNT[idx][i] = symbol;
        }
    }
}

void addToFollowFirstOf(char NT, char firstNT){
    int idx = addNT(NT);
    int firstNTIdx = addNT(NT);
    NTAdded[idx] = NT;
    int j = 0;
    for(int i=0; i<MAX_SIZE; i++){
        if(followOfNT[idx][i] != '\0'){
            if(firstOfNT[firstNTIdx][j]=='\0'){
                break;
            }
            followOfNT[idx][i] = firstOfNT[firstNTIdx][j++];
        }
    }
}

int nullInFirst(char NT){
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]==NT){
            return i;
        }else if(NTAdded[i]=='\0'){
            return -1;
        }
    }
}

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
        if(firstOfNT[symIdx][i]=='\316'){
            continue;
        }
        for(int j=0; j<MAX_SIZE; j++){
            if(firstOfNT[NTIdx][j] == '\0' || firstOfNT[NTIdx][j]==firstOfNT[symIdx][i]){
                firstOfNT[NTIdx][j] = firstOfNT[symIdx][i];
                break;
            }
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
    for(int i=0; i<MAX_SIZE; i++){
        if(prod[i]=='\0'){
            break;
        }
        if(prod[i] == '='){
            i+=1;
            if(flag==0){
                if(prod[i]>='A' && prod[i]<='Z'){
                    i--;
                    do{
                        i++;
                        addNT(NT);
                        addNT(prod[i]);
                        mergeFirstTo(NT, prod[i]);
                    }while(nullInFirst(prod[i])!=-1 && i<MAX_SIZE && prod[i]);
                    if(nullInFirst(prod[i]!=-1)){
                        addToFirst(NT, '\316');
                    }
                }else{
                    flag = 1;
                    addToFirst(NT, prod[i]);
                }
            }
        }
    }
}

void follow(char * prod){
    char NT = prod[0];
    addNT(NT);
    int flag = 0;
    for(int i=0; i<MAX_SIZE; i++){
        if(prod[i]=='\0'){
            break;
        }
        if(prod[i]=='='){
            flag = 1;
        }
        if(flag==1){
            if(prod[i]>='A' && prod[i]<='Z'){
                if(prod[i+1]=='\0'){
                    //follow of prod[0]
                }else{
                    if(prod[i+1]>='A' && prod[i+1]<='Z'){
                        if(nullInFirst(prod[i+1])!=-1){
                            addNT(prod[i]);
                            addToFollowFirstOf(prod[i], prod[i+1]);
                        }
                    }else{
                        addToFollowSymbol(prod[i], prod[i+1]);
                    }
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

void printFollow(){
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]=='\0'){
            break;
        }
        printf("\nFollow of %c:\n", NTAdded[i]);
        for(int j=0; j<MAX_SIZE; j++){
            if(followOfNT[i][j]=='\0'){
                break;
            }else if(followOfNT[i][j]=='\316'){
                printf(" ε");
            }else
                printf(" %c", followOfNT[i][j]);
        }
    }
}


void start(){
    int nOfProds;
    char prods[MAX_SIZE][MAX_SIZE];
    char temp;

    FILE *fptr = fopen("./input.txt", "r");

    fscanf(fptr, "%d", &nOfProds);
    if(fptr == NULL){
        printf("Error!");
    }

    for(int i=0; i<nOfProds; i++){
        fscanf(fptr, "%c", &temp);
        fscanf(fptr, "%[^\n]", prods[i]);
        if(i==0){
            int idx = addNT(prods[0][0]);
            followOfNT[idx][0] = '$';
        }
        first(prods[i]);
        follow(prods[i]);
    }
}

void main(){
    start();
    start();
    
    printFirst();
    printf("\n------------------------------\n");
    printFollow();
    printf("\n------------------------------\n");
}