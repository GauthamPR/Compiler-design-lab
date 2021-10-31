//First and follow

#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

char NTAdded[MAX_SIZE];
char firstOfNT[MAX_SIZE][MAX_SIZE];
char followOfNT[MAX_SIZE][MAX_SIZE];

int addNT(char);
void addToFollowSymbol(char, char);
void addToFollowFirstOf(char, char);
int nullInFirst(char);
void mergeFirstTo(char, char);
void mergeFollowTo(char, char);
void addToFirst(char, char);
void first(char *);
void follow(char *);
void printFirst();
void printFollow();
void startFirst();
void startFollow();

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

void addToFollowFirstOf(char NT, char firstSymbol){
    //NT is the symbol to whose follow, first(s) of firstSymbol(NT/T) is to be added
    int idx = addNT(NT);

    int isNT = 0;

    //check if firstSymbol is NT, try to add it to NT list only if it is not 
    if(firstSymbol>='A' && firstSymbol<='Z'){
        int firstNTIdx = addNT(firstSymbol);
        int j = 0;
        for(int i=0; i<MAX_SIZE; i++){
            if(followOfNT[idx][i] == '\0'){
                while(firstOfNT[firstNTIdx][j] == '\316'){
                    j++;
                }
                if(firstOfNT[firstNTIdx][j]=='\0'){
                    break;
                }else{
                    followOfNT[idx][i] = firstOfNT[firstNTIdx][j++];
                }
            }
        }
    }else{
        //if not a NT add that symbol to follow of NT
        int j = 0;
        for(int i=0; i<MAX_SIZE; i++){
            if(followOfNT[idx][i] == '\0'){
                followOfNT[idx][i] = firstSymbol;
                break;
            }
        }
    }
}

int nullInFirst(char symbol){
    /*
        Used to check whether a symbol(NT/T) has null as its first
        If yes returns the index else -1
    */
    int idx;
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]==symbol){
            idx = i;
            break;
        }else if(NTAdded[i]=='\0'){
            return -1;
        }
    }

    for(int i=0; firstOfNT[idx][i]!='\0'; i++){
        if(firstOfNT[idx][i]=='\316'){
            return i;
        }
    }

    return -1;
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

void mergeFollowTo(char NT, char symbol){
    int symIdx = -1, NTIdx = -1;
    for(int i=0; i<MAX_SIZE; i++){
        if(NTAdded[i]==symbol){
            symIdx = i;
        }
        if(NTAdded[i]==NT){
            NTIdx = i;
        }
    }
    
    for(int i=0; followOfNT[symIdx][i] != '\0' || i<MAX_SIZE; i++){
        if(followOfNT[symIdx][i]=='\316'){
            continue;
        }else if(followOfNT[symIdx][i] == '\0'){
            break;
        }
        for(int j=0; j<MAX_SIZE; j++){
            if(followOfNT[NTIdx][j] == '\0' || followOfNT[NTIdx][j]==followOfNT[symIdx][i]){
                followOfNT[NTIdx][j] = followOfNT[symIdx][i];
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
        if(flag==1){
            if(prod[i]>='A' && prod[i]<='Z'){
                if(prod[i+1]=='\0'){
                    addNT(prod[i]);
                    mergeFollowTo(prod[i], prod[0]);
                }else{
                    //Add follow of next j symbols until ε not in First(prod[i+j])
                    for(int j=1; j<MAX_SIZE; j++){
                        addNT(prod[i]);
                        addToFollowFirstOf(prod[i], prod[i+j]);
                        if(prod[i+j]=='\0'){
                            addNT(prod[i]);
                            mergeFollowTo(prod[i], prod[0]);
                            break;
                        }
                        if(nullInFirst(prod[i+j])==-1){
                            break;
                        }
                    }
                }
            }
        }

        if(prod[i]=='='){
            flag = 1;
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


void startFirst(){
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
    }
}

void startFollow(){
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
        follow(prods[i]);
    }
}

void main(){
    startFirst();
    startFirst();
    startFollow();
    
    printFirst();
    printf("\n------------------------------\n");
    printFollow();
    printf("\n------------------------------\n");
}