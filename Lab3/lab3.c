#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE* fi;
FILE* fo;

typedef struct{
    int *key;
    int top;
    int max_stack_size;
}Stack;

void Push(Stack* S, int X);
int Pop(Stack* S);
int Postfix(Stack* S, char input_str);
void DeleteStack(Stack *S);

Stack* CreateStack(int max){
    Stack* S = NULL;
    S = (Stack*)malloc(sizeof(Stack));
    S->key = (int*)malloc(sizeof(int)*max);
    S->max_stack_size = max;
    S->top = -1;
    return S;
}

void Push(Stack *S, int X){
    (S->top)++;
    (S->key)[(S->top)] = X;
}

int Pop(Stack* S){
    int n = (S->key)[(S->top)];
    (S->top)--;
    return n;
}
int Pl(Stack *S){
    int arg2 = Pop(S);
    int arg1 = Pop(S);
    Push(S, arg1+arg2);
    return arg1+arg2;
}
int Mi(Stack *S){
    int arg2 = Pop(S);
    int arg1 = Pop(S);
    Push(S, arg1-arg2);
    return arg1-arg2;
}
int Mu(Stack *S){
    int arg2 = Pop(S);
    int arg1 = Pop(S);
    Push(S, arg1*arg2);
    return arg1*arg2;
}
int Dv(Stack *S){
    int arg2 = Pop(S);
    int arg1 = Pop(S);
    if(!arg2){
        printf("cannot devide with 0");
        return 0;
    }
    Push(S, arg1/arg2);
    return arg1/arg2;
}
int Mo(Stack *S){
    int arg2 = Pop(S);
    int arg1 = Pop(S);
    if(!arg2){
        printf("cannot devide with 0");
        return 0;
    }
    Push(S, arg1%arg2);
    return arg1%arg2;
}

int Postfix(Stack* S, char input_str){
    int X = input_str;
    switch(X){
        case '+' :
            X = Pl(S);
            break;
        case '-' :
            X = Mi(S);
            break;
        case '*' : 
            X = Mu(S);
            break;
        case '/' :
            X = Dv(S);
            break;
        case '%' :
            X = Mo(S);
            break;
        default :
            X -= 48;
            Push(S, X);
            break;
    }
    fprintf(fo, "%d ", X);
    return X;
}

void DeleteStack(Stack *S){
    free(S);
}

void main(int argc, char* argv[]){
    
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    Stack* stack;
    char input_str[101];
    int max,i=0,a,b,result;

    fgets(input_str, 101, fi);
    max = 10;
    stack = CreateStack(max);
    
    fprintf(fo, "Top numbers :");

    for(i = 0; i<strlen(input_str) && input_str[i] !='#'; i++){
        result = Postfix(stack, input_str[i]);
    }

    fprintf(fo, "\nevaluation result : %d\n", result);
    fclose(fi);
    DeleteStack(stack);
}
