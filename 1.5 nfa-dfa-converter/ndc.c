/*  
    NFA-DFA converter
    -----------------

    1.  Array indexes of states(NFA/DFA) = respective state value
    2.  State value of NFA = sum of(2^i), where i are the state values of DFA combined to make the NFA state
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TRANS 10
#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define EPSILON '#'

struct state{
    int value;
    int transitionTop; //stack top for transitions
    int finalState;
    struct transition * transitions[MAX_TRANS];
};

struct transition{
    char symbol;
    struct state* nextState;
};

struct state *NFAStates[MAX_STATES];
struct state *DFAStates[MAX_STATES * MAX_STATES];
int finalStatesOfNFA[MAX_STATES], initState, nOfStates, nOfFinalStates;
char symbols[MAX_SYMBOLS];

int createDFAState(int *);

//adds symbol uniquely to the global symbols array
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

//creates an NFA state from user input
void createNFAState(int value){
    NFAStates[value] = (struct state*) malloc(sizeof(struct state));
    NFAStates[value]->value = value;
    NFAStates[value]->transitionTop = 0;
    for(int i=0; i<MAX_STATES; i++){
        NFAStates[value]->transitions[i] = NULL;
    }
}

//creates NFA-transitions from user input
void createNFATransition(struct state * fromState, struct state * nextState, char symbol){
    struct transition *t;
    t = (struct transition*) malloc(sizeof(struct transition));
    
    t->symbol = symbol;
    t->nextState = nextState;
    fromState->transitions[fromState->transitionTop] = t;
    fromState->transitionTop++;
}

//create DFA transitions from and to state through a symbol
void createDFATransition(struct state * fromState, struct state * nextState, char symbol){
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

    //create nfa states
    printf("\nEnter number of states: ");
    scanf("%d", &nOfStates);

    printf("\nCreated states:");
    for(int i=0; i<nOfStates; i++){
        createNFAState(i);
        printf("\n\tname:q%d\t\tvalue:%d", i, NFAStates[i]->value);
    }


    printf("\nEnter total number of transitions: ");
    scanf("%d", &nOfTransitions);

    //create transitions from each states
    for(int i=0; i<nOfTransitions; i++){
        printf("\nEnter transition: (old state)     (symbol)    (new state): ");
        scanf(" %d %c %d", &fromState, &symbol, &toState);
        createNFATransition(NFAStates[fromState], NFAStates[toState], symbol);
        addSymbol(symbol);
    }

    printf("\nEnter initial state: ");
    scanf("%d", &initState);

    printf("\nEnter number of final states: ");
    scanf("%d", &nOfFinalStates);

    printf("\nEnter final states: ");
    for(int i=0; i<MAX_STATES; i++){
        if(i<nOfFinalStates)
            scanf("%d", &finalStatesOfNFA[i]);
        else
            finalStatesOfNFA[i] = -1;
    }
}

//find the epsilon closure of 2nd arg and store state-indexes/values in 1st arg
int * findEpsilonClosure(int * epsilonSetValues, int stateValue){
    int index;

    //find the next empty space in epsilon set or return function if epsilon-closure of state has already been found
    for(index=0 ; epsilonSetValues[index]!=-1; index++){
        if(epsilonSetValues[index] == stateValue){
            return epsilonSetValues;
        }
    };

    epsilonSetValues[index++] = stateValue; //every state in its own epsilon-closure

    //for each epsilon-transition from state, find the epsilon-closure of transition-next-state
    for(int i=0; i<NFAStates[stateValue]->transitionTop; i++){
        if(NFAStates[stateValue]->transitions[i] && NFAStates[stateValue]->transitions[i]->symbol==EPSILON){
            findEpsilonClosure(epsilonSetValues, NFAStates[stateValue]->transitions[i]->nextState->value);
        }
    }
    return epsilonSetValues;
}

//resets entire array
void resetArr(int * arr){
    for(int i=0; i<MAX_STATES; i++){
        arr[i] = -1;
    }
}

//create a DFA state from a combination of NFA states
int createDFAState(int NFAStateValues[]){
    
    int currentGrpValues[MAX_STATES]; // epsilon-closure of provided NFA states
    int nextGrpValues[MAX_STATES];  // epsilon-closure of NFA states after transition(calculated for each symbol)
    int sumOfGrpValues = 0, sumOfNextGrpValues = 0; //state value of new DFA state
    
    resetArr(currentGrpValues);

    for(int i=0; NFAStateValues[i]!=-1; i++){
        findEpsilonClosure(currentGrpValues, NFAStateValues[i]);
    }

    for(int i=0; currentGrpValues[i]!=-1; i++){
        sumOfGrpValues += pow(2, currentGrpValues[i]);
    }

    //check if DFA state already exists
    if(!DFAStates[sumOfGrpValues]){
        DFAStates[sumOfGrpValues] = (struct state*) malloc(sizeof(struct state));
        DFAStates[sumOfGrpValues]->value = sumOfGrpValues;
        DFAStates[sumOfGrpValues]->transitionTop = 0;
        DFAStates[sumOfGrpValues]->finalState = 0;
        
        for(int i=0; currentGrpValues[i]!=-1; i++){
            for(int j=0; j<nOfFinalStates; j++){
                if(finalStatesOfNFA[j]==currentGrpValues[i]){
                    DFAStates[sumOfGrpValues]->finalState = 1;
                    break;
                }
            }
        }
    }else{
        return sumOfGrpValues;
    }

    //for each symbol except epsilon find epsilon-closure of state after transition using the symbol
    for(int j=0; symbols[j]!='\0'; j++){
        resetArr(nextGrpValues);
        if(symbols[j] != EPSILON){
            for(int i=0; currentGrpValues[i]!=-1; i++){
                for(int k=0; NFAStates[currentGrpValues[i]]->transitions[k] != NULL; k++){
                    if(NFAStates[currentGrpValues[i]]->transitions[k]->symbol == symbols[j]){
                        findEpsilonClosure(nextGrpValues, NFAStates[currentGrpValues[i]]->transitions[k]->nextState->value);
                    }
                }
            }

            //create new DFA state and add transition
            sumOfNextGrpValues = createDFAState(nextGrpValues);
            createDFATransition(DFAStates[sumOfGrpValues], DFAStates[sumOfNextGrpValues], symbols[j]);
        }
    }
    return sumOfGrpValues;
}

void initializeDFAConstruction(){
    int arr[] = {initState , -1};
    createDFAState(arr);
}

void printDFA(){
    printf("\n\nDFA");
    printf("\n---");
    for(int i=0; i<MAX_STATES*MAX_STATES; i++){
        if(DFAStates[i]!=NULL){
            printf("\n\nState value: %d", DFAStates[i]->value);
            if(DFAStates[i]->finalState==1){
                printf(" (final)");
            }
            printf("\n-------------------");
            for(int j=0; j<DFAStates[i]->transitionTop; j++){
                printf("\nSymbol: %c", DFAStates[i]->transitions[j]->symbol);
                printf("\nNext state: %d", DFAStates[i]->transitions[j]->nextState->value);
            }
        }
    }
}

//for debug
void printNFA(){
    printf("\n\nNFA");
    printf("\n---");
    for(int i=0; i<MAX_STATES; i++){
        if(NFAStates[i]!=NULL){
            printf("\n\nState value: %d", NFAStates[i]->value);
            printf("\n-------------------");
            for(int j=0; j<NFAStates[i]->transitionTop; j++){
                printf("\nSymbol: %c", NFAStates[i]->transitions[j]->symbol);
                printf("\nNext state: %d", NFAStates[i]->transitions[j]->nextState->value);
            }
        }
    }
}

void main(){

    UI();
    // printNFA();
    initializeDFAConstruction();
    printDFA();
    printf("\n");
}