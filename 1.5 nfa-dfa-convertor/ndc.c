#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TRANS 10
#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define EPSILON '#'

int newDFAStateFlag=0;

struct state{
    int value;
    int transitionTop;
    struct transition * transitions[MAX_TRANS];
};

struct transition{
    char symbol;
    struct state* nextState;
};

struct state *NFAStates[MAX_STATES];
struct state *DFAStates[MAX_STATES];
int finalStatesOfNFA[MAX_STATES], initState, nOfStates, nOfFinalStates;
char symbols[MAX_SYMBOLS];

void addSymbol(char symbol){
    for(int i=0; i<MAX_SYMBOLS; i++){
        if(symbols[i]==symbol)
            break;
        else if(symbols[i]=='\0'){
            symbols[i] = symbol;
            break;
        }
    }
}

void createNFAState(int value){
    NFAStates[value] = (struct state*) malloc(sizeof(struct state));
    NFAStates[value]->value = value;
    NFAStates[value]->transitionTop = 0;
}

void createNFATransition(struct state * fromState, struct state * nextState, char symbol){
    struct transition *t;
    t = (struct transition*) malloc(sizeof(struct transition));
    
    t->symbol = symbol;
    t->nextState = nextState;
    fromState->transitions[fromState->transitionTop] = t;
    fromState->transitionTop++;
}


//take necessary inputs from user
void UI(){

    char temp;
    int nOfTransitions, fromState, toState;
    char symbol;

    FILE *fptr = fopen("./input.txt", "r");
    if(fptr == NULL){
        printf("Error!");
    }


    //create nfa states
    printf("\nEnter number of states: ");
    fscanf(fptr, "%d", &nOfStates);

    printf("\nCreated states:");
    for(int i=0; i<nOfStates; i++){
        createNFAState(i);
        printf("\n\tname:q%d\t\tvalue:%d", i, NFAStates[i]->value);
    }


    printf("\nEnter total number of transitions: ");
    fscanf(fptr, "%d", &nOfTransitions);
    //create transitions from each states
    for(int i=0; i<nOfTransitions; i++){
        printf("\nEnter transition: (old state)     (symbol)    (new state): ");
        fscanf(fptr, " %d %c %d", &fromState, &symbol, &toState);
        createNFATransition(NFAStates[fromState], NFAStates[toState], symbol);
        addSymbol(symbol);
    }

    printf("\nEnter initial state: ");
    fscanf(fptr, "%d", &initState);

    printf("\nEnter number of final states: ");
    fscanf(fptr, "%d", &nOfFinalStates);

    printf("\nEnter final states: ");
    for(int i=0; i<nOfFinalStates; i++){
        fscanf(fptr, "%d", &finalStatesOfNFA[i]);
    }
    // printf("\n value: %d\n", states[0]->transitions[0]->nextState->value);
}

int * findEpsilonClosure(int * stateValues, int stateValue){
    int stateValueTop;
    for(stateValueTop=0 ; stateValues[stateValueTop]!=-1; stateValueTop++);
    stateValues[stateValueTop++] = stateValue;
    for(int i=0; i<=NFAStates[stateValue]->transitionTop; i++){
        if(NFAStates[stateValue]->transitions[i] && NFAStates[stateValue]->transitions[i]->symbol==EPSILON){
            findEpsilonClosure(stateValues, NFAStates[stateValue]->transitions[i]->nextState->value);
        }
    }
    return stateValues;
}

int * createDFAState(int stateValues[]){
    int sumOfStateValues = 0;
    for(int i=0; stateValues[i]!='\0'; i++){
        sumOfStateValues += stateValues[i];
    }

    //check if DFA state already exists
    if(!DFAStates[sumOfStateValues]->value){
        DFAStates[sumOfStateValues] = (struct state*) malloc(sizeof(struct state));
        DFAStates[sumOfStateValues]->value = pow(2, sumOfStateValues);
        DFAStates[sumOfStateValues]->transitionTop = 0;
    }
    return stateValues;
}

void constructDFA(int arr[]){
    int stateValues[MAX_STATES];
    for(int i=0; i<MAX_STATES; i++){
        stateValues[i] = -1;
    }
    // if(arr[0]=='\0'){
    //     printf("equal");
    // }
    // for(int i=0; arr[i]!='\0'; i++){
    findEpsilonClosure(stateValues, 0);
    createDFAState(stateValues);
    // }
}

void main(){

    int arr[MAX_STATES];
    arr[0] = 0;

    UI();
    constructDFA(arr);
}