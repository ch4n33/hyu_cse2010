#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;


//code skeleton
typedef int ElementType;

typedef struct Node{
    ElementType element;
    struct Node* next;//address of next node
}Node;
typedef Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);

void Insert(ElementType X, List L, Position P);
void PrintList(List L);
void Delete(ElementType X, List L);
Position Find (ElementType X, List L);


//my code
Position FindPrev(Position P,List L);
void Find1(ElementType X, List L);
List MakeEmptyList(){
    List L;
    L = (List) malloc(sizeof(struct Node));
    L->element = -1;
    L->next = NULL;
    return L;
}

void DeleteList(List L){
    Position P, tmp;
    P = L->next;
    while(P != NULL){
        tmp = P->next;
        free(P);
        P = tmp;
    }
}
int IsEmpty(List L){
    return IsLast(L,L);
}

int IsLast(Position P, List L){
    if(P->next ==NULL){
        return 1;
    }
    return 0;
}
void Find1(ElementType X, List L){
    Position P = Find(X, L);
    if(P == NULL){
        fprintf(output, ": find error\n");
    }else {
        Position Pprev = FindPrev(P, L);
        if (Pprev == L) {
            fprintf(output, "previous key of %d: head\n", P->element);
        } else {
            fprintf(output, "previous key of %d: %d\n", P->element, Pprev->element);
        }
    }
}

Position Find(ElementType X, List L){
    if(X == -1){
        return L;
    }
    Position p;
    p = L->next;
    while(p!=NULL && p->element!= X){
        p = p->next;
    }
    if(p == NULL){
        fprintf(output, "cannot find %d ", X);
    }
    return p;
}

Position FindPrev(Position P,List L){

    Position iter = L;
    while(iter->next != NULL && iter->next != P){
        iter = iter->next;
    }
    return iter;
}

void Delete(ElementType X, List L){
    Position P;
    P = Find(X,L);
    if(P == NULL){
        fprintf(output, ": delete error\n");
        return;
    }
    Position Pprev = FindPrev(P,L);
    Pprev->next = P->next;
    free(P);
}

void PrintList(List L){
    Position iter = L->next;
    if(IsEmpty(L)){
        fprintf(output, "no keys:printlist error\n");
    }
    while(iter != NULL){
        fprintf(output,"key : %d ", iter->element);

        iter =(iter->next);
    }
    fprintf(output,"\n");
}

void Insert(ElementType X, List L, Position P){
    if(P == NULL){
        fprintf(output, ": insert(%d) error\n", X);
        return;
    }
    Position tmp;
    tmp = (Position) malloc(sizeof(struct Node));
    tmp->element = X;
    tmp->next = P->next;
    P->next = tmp;

}
void inp(char* a[]){
    input = fopen(a[1], "r");
    output = fopen(a[2], "wt");
}
void outp(){
    fclose(input);
    fclose(output);
}
void io(List L, char * a[]){
    inp(a);

    int ivalue, itarget,  dvalue,  fvalue;
    char mode = 'i';
    //while loop
    while(mode != 'p'){
        fscanf(input, "%c", &mode);

        //if branch
        if(mode == 'i'){
            ///input

            fscanf(input, "%d%d", &ivalue, &itarget);
            Insert(ivalue,L,Find(itarget,L));

        }if(mode == 'd'){
            ///delete

            fscanf(input, "%d", &dvalue);
            Delete(dvalue, L);
        }if(mode == 'f'){
            ///find

            fscanf(input, "%d", &fvalue);
            Find1(fvalue,L);

        }if(mode == 'p'){
            ///print list

            PrintList(L);

        }

    }
    outp();
}

int main(int argc, char *argv[]) {
    List L = MakeEmptyList();

    io(L,argv);
    return 0;
}
