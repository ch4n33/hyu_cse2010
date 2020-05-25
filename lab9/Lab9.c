#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Queue {
    int* key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};
struct _Graph{
    int *node;
    int size;
    int **matrix;
};
typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

Graph CreateGraph(int* nodes);//each nodes are positive integer
void InsertEdge(Graph G, int a, int b);
void TopSort(Graph G);//if same priority, smaller key first.
Queue MakeNewQueue(int x);
void Enqueue(Queue Q, int x);
int Dequeue(Queue Q);
int findOrder(int* keys, int size, int key);
void printGraph(Graph G);
int getDegree(Graph G, int i);

FILE *I, *O;
int CreateGraphSize;
/*Start of main function here----------------------------------------------*/
int main(int argc, char* argv[]){
    I = fopen(argv[1], "r");
    O = fopen(argv[2], "w");
    int arr[100];
    char firstLine[100];
    fgets(firstLine, sizeof(firstLine), I);
    int i, j=0;
    for (int i = 0; i < sizeof(firstLine); i+= 2) {
        if ('0' <= firstLine[i] && firstLine[i] <= '9'){
            arr[j] = firstLine[i]-48;
            j++;
        }else {
            break;
        }
    }
    CreateGraphSize = j;
    Graph G = CreateGraph(arr);
    char secondLine[4];
    while(EOF!= fscanf(I, "%s", secondLine)){
        InsertEdge(G, secondLine[0]-48, secondLine[2]-48);
    }
    TopSort(G);
    fclose(I);
    fclose(O);
    free(G->node);
    free(G->matrix[0]);
    free(G->matrix);
    free(G);
    return 0;
}
Graph CreateGraph(int *nodes){
    Graph G = (Graph) malloc(sizeof(struct _Graph));
    G->size = CreateGraphSize;
    G->node = (int*) malloc(sizeof(int)*CreateGraphSize);
    int i;
    for (i=0; i<CreateGraphSize; i++){
        G->node[i] = nodes[i];
    }
    G->matrix = (int**) malloc(sizeof(int*)* CreateGraphSize);
    G->matrix[0] = (int*) calloc (CreateGraphSize*CreateGraphSize, sizeof(int)*CreateGraphSize*CreateGraphSize);
    for (i=0; i < CreateGraphSize-1; i++) {
        G->matrix[i+1] = G->matrix[i]+CreateGraphSize;
    }
    return G;
}
void InsertEdge(Graph G, int a, int b){
    G->matrix [findOrder(G->node, G->size, a)][findOrder(G->node, G->size, b)] = 1;
}
Queue MakeNewQueue(int x){
    Queue Q = (Queue) malloc(sizeof(struct _Queue));
    Q->key = (int*) malloc(sizeof(int)*x);
    Q->first = Q->rear = Q->qsize = 0;
    Q->max_queue_size = x;
    return Q;
}
void Enqueue(Queue Q, int x){
    if (Q->qsize == Q->max_queue_size){
        return;///abort insertion.
    }
    Q->key[Q->rear] = x;
    Q->rear++;
    Q->qsize++;
}
int Dequeue(Queue Q){
    if(Q->qsize == 0){
        return -1;
    }
    int i = Q->key[Q->first];
    Q->first++;
    Q->qsize--;
    return i;
}
void Sort(Graph G, int* arr){
    int i,j, temp;
    for ( i = 1; i < arr[0]; ++i) {
        for (j = i+1; j < arr[0]; ++j) {
            if(G->node[arr[i]] > G->node[arr[j]]){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
int findOrder(int* keys, int size,int key){
    int i;
    for (i=0; i<size; i++){
        if (keys[i] == key)
            return i;
    }
    return -1;
}
void printGraph(Graph G){
    int size = G->size;
    int i, j;
    fprintf(O,"  ");
    for (i=0; i<size; i++){//1st line
        fprintf(O," %2d", G->node[i]);
    }
    fprintf(O,"\n");
    for (i=0; i<size; i++){
        fprintf(O,"%2d", G->node[i]);
        for (j = 0; j < size; j++) {
            fprintf(O,"  %d", G->matrix[i][j]);
        }
        fprintf(O,"\n");
    }
    fprintf(O,"\n");

}
int getDegree(Graph G, int i){
    int j, sum=0;
    for (j = 0; j < G->size; ++j) {
        sum+=G->matrix[j][i];
    }
    return sum;
}
void TopSort(Graph G){///body of Topological sort.
    printGraph(G);
    int *degree = (int*) malloc(G->size * sizeof(int));///degree :각 edge를 향하는 edge의 개수
    int *inputList = (int*) calloc(G->size +1,(G->size+1) * sizeof(int));

    int i, j;
    for(i=0; i < G->size; i++){
        degree[i]=getDegree(G, i);
    }
    Queue Q = MakeNewQueue(G->size);
    for (i = 0; i < G->size; ++i) {
        if(degree[i] == 0) {
            inputList[0]++;
            inputList[inputList[0]] = i;
        }
    }
    Sort(G, inputList);
    for (i=1; i<=inputList[0]; i++){
        for (j = 0; j < G->size; ++j) {
            if (G->matrix[inputList[i]][j] == 1){
                degree[j]--;
            }
        }
        Enqueue(Q, inputList[i]);
    }
    while(Q->qsize != 0){
        inputList[0] =0;
        int v = Dequeue(Q);
        if(v >=0){
            fprintf(O,"%d ", G->node[v]);
        }
        for (i = 0; i < G->size; ++i) {
            if ( G->matrix[v][i] == 1 && degree[i] == 0){
                inputList[0]++;
                inputList[inputList[0]] = i;
            }
        }
        Sort(G, inputList);
        for (i = 1; i <= inputList[0]; ++i) {
            for (j = 0; j < G->size; ++j) {
                if (G->matrix[inputList[i]][j] == 1){
                    degree[j]--;
                }
            }
            Enqueue(Q, inputList[i]);
        }
    }
    fprintf(O,"\n");
    free(degree);
    free(inputList);
    free(Q->key);
    free(Q);
}