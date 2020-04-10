#include<stdio.h>

FILE *I, *O;
struct completeTree{
    int size;
    int nodeNum;
    int* element;
};

typedef struct completeTree* Tree;//Tree Type is pointer to completeTree struct.

void insert(Tree T, int V);
void printPreorder(Tree T, int index);
void printInorder(Tree T, int index);
void printPostorder(Tree T, int index);
void freeTree(Tree T);


int main(int argc, char* argv[]){
    I = fopen(argv[1], "r");
    O = fopen(argv[2], "wt");
    int size, i=1, j;
    Tree T;
    T = (Tree)malloc(sizeof(struct completeTree));
    T->element = (int*)malloc(sizeof(int));
    
    fscanf(I, "%d", &size);
    T->size = size;
    T->nodeNum = 0;

    while(!feof(I)){
        fscanf(I,"%d", &j);
        if(!feof(I))
            insert(T,j);
        fflush(stdin);
    }
    int a=1;
    fprintf(O,"Preorder:");
    printPreorder(T,1);
    fprintf(O,"\nInorder:");
    printInorder(T,1);
    fprintf(O,"\nPostorder");
    printPostorder(T,1);

    freeTree(T);
    fclose(I);
    fclose(O);
    return 0;
}

void insert(Tree T, int V){
    if(T->nodeNum < T->size){
        T->nodeNum++;
        T->element[T->nodeNum]= V;
    }else{
        fprintf(O,"Tree is full\n");
    }
}
void printPreorder(Tree T, int index){
    fprintf(O, " %d", T->element[index]);
    if(index*2 <= T->nodeNum){
        printPreorder(T, index*2);
    }
    if(index*2+1 <= T->nodeNum){
        printPreorder(T, index*2+1);
    }
}
void printInorder(Tree T, int index){
    if(index*2 <= T->nodeNum){
        printInorder(T, index*2);
    }
    fprintf(O, " %d", T->element[index]);
    if(index*2+1 <= T->nodeNum){
        printInorder(T, index*2+1);
    }
}
void printPostorder(Tree T, int index){
    if(index*2 <= T->nodeNum){
        printPostorder(T, index*2);
    }
    if(index*2+1 <= T->nodeNum){
        printPostorder(T, index*2+1);
    }
    fprintf(O, " %d", T->element[index]);
}
void freeTree(Tree T){
    free(T->element);
    free(T);
}
