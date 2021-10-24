#include <stdio.h>
/*

Recursive Descent Parser
------------------------

Grammar:
    E   ->  rE'
    E'  ->  +rE'| ε
*/

char l;

void match(char c){
    if(l == c){
        l = getchar();
    }else{
        printf("error");
    }
}

void Ed(){
    if(l=='+'){
        match('+');
        match('r');
        Ed();
    }else{
        return;
    }
}

void E(){
    if(l=='r'){
        match('r');
        Ed();
    }
}

int main(){
    l = getchar();
    E();
    if(l=='$'){
        printf("Successfully parsed\n");
    }else{
        printf("Unsuccessful parsing\n");
    }
}