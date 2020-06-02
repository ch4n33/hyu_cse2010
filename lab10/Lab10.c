#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIST 10000

FILE *O;
typedef struct Node{
    int vertex;
    int dist;
    int prev;
}Node;
typedef struct Graph{
    int size;
    int **vertices;
    Node *nodes;
}Graph;
typedef struct Heap{
    int Capacity;
    int Size;
    Node *Elements;
}Heap;
void DeleteGraph(Graph* graph){
    free(graph->vertices[0]);
    free(graph->vertices);
    free(graph->nodes);
    free(graph);
}
Graph *CreateGraph(int size){/////////////////////////////////////////
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->vertices = (int**) malloc(size * sizeof(int*));
    graph->vertices[0]= (int*)  calloc(size*size,size*size *sizeof(int));
    int i;
    for (i=1; i <size; i++){
        graph->vertices[i] = graph->vertices[i-1] + size;
    }
    graph->nodes = (Node*) malloc(size *sizeof(Node));
    graph->size = size;
    return graph;
}
char heapCapacity(Heap *H){
    return H->Capacity >= H->Size;
}
Heap* CreateMinHeap(int Heapsize){///////////////////////////////////
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->Elements = (Node*) malloc(sizeof(Node) * (Heapsize+1));
    heap->Capacity = Heapsize;
    heap->Size = 0;
    return heap;
}
void DeleteMinHeap(Heap* heap){
    free(heap->Elements);
    free(heap);
}
void insertToMinHeap(Heap* minHeap, int vertex, int distance){///////
    if (!heapCapacity(minHeap)) {
        return;
    }
    minHeap->Size++;
    minHeap->Elements[minHeap->Size].dist = distance;
    minHeap->Elements[minHeap->Size].vertex = vertex;
    int i = minHeap->Size;
    Node temp;
    while(i>1 && minHeap->Elements[i].dist < minHeap->Elements[i/2].dist){
        temp = minHeap->Elements[i];
        minHeap->Elements[i] = minHeap->Elements[i/2];
        minHeap->Elements[i/2] = temp;
        i/= 2;
    }
}
Node deleteMin(Heap* minHeap){///////////////////////////////////////
    if (minHeap->Size == 0){
        Node a;
        a.vertex = a.dist = a.prev = 0;
        return a;
    }
    Node min = minHeap->Elements[1];
    minHeap->Elements[1] = minHeap->Elements[minHeap->Size];
    minHeap->Size--;
    int i=1;
    Node temp;
    while (i*2 <= minHeap->Size){
        if (i*2 + 1 <= minHeap->Size){
            if (minHeap->Elements[i*2 + 1].dist < minHeap->Elements[i*2].dist
                && minHeap->Elements[i*2 + 1].dist < minHeap->Elements[i].dist){
                temp = minHeap->Elements[i*2 + 1];
                minHeap->Elements[i*2 + 1] = minHeap->Elements[i];
                minHeap->Elements[i] = temp;
                i = i*2 +1;
            }
            if (minHeap->Elements[i*2 + 1].dist > minHeap->Elements[i*2].dist
                && minHeap->Elements[i*2].dist < minHeap->Elements[i].dist){
                temp = minHeap->Elements[i*2];
                minHeap->Elements[i*2] = minHeap->Elements[i];
                minHeap->Elements[i] = temp;
                i = i*2;
            }else{
                break;
            }
        }else if (minHeap->Elements[i*2].dist < minHeap->Elements[i].dist){
            temp = minHeap->Elements[i*2];
            minHeap->Elements[i*2] = minHeap->Elements[i];
            minHeap->Elements[i] = temp;
            i = i*2;
        }else {
            break;
        }
    }
    return min;
}
void printShortestPath(Graph *G);

int main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1],"r");
    O = fopen(argv[2], "w");// main function modification
    Graph *g;
    int size;
    fscanf(fi, "%d\n", &size);
    g = CreateGraph(size+1);
    char temp = 0;
    while (temp != '\n'){
        int node1, node2, weight;
        fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
        g->vertices[node1][node2] = weight;
        temp = fgetc(fi);
    }
    printShortestPath(g);
    fclose(fi);// main function modification......................
    return 0;
}
void printpath_(Graph *G, Node N){
    if(N.vertex == 0){
        return;
    }
    printpath_(G, G->nodes[N.prev]);
    fprintf(O,"%d->",N.vertex);
}
void printpath(Graph *G, Node N){
    if(N.dist == MAX_DIST){
        fprintf(O, "Cannot reach to node %d\n", N.vertex);
        return;
    }
    printpath_(G, G->nodes[N.prev]);
    fprintf(O, "%d (cost: %d)\n", N.vertex, N.dist);
}
void sortHeap(Heap* heap, int index){
    Node temp;
    while(1){
        if (index *2 >= heap->Size){//child nodes don't exist
            break;
        }else if (index *2 +1 ==heap->Size){//one child
            if (heap->Elements[index*2].dist <heap->Elements[index].dist){
                temp = heap->Elements[index*2];
                heap->Elements[index*2] = heap->Elements[index];
                heap->Elements[index] = temp;
                index *= 2;
            }else{
                break;
            }
        }else {//two child
            if (heap->Elements[index*2].dist < heap->Elements[index*2+1].dist){
                if (heap->Elements[index*2].dist < heap->Elements[index].dist){
                    temp = heap->Elements[index*2];
                    heap->Elements[index*2] = heap->Elements[index];
                    heap->Elements[index] = temp;
                    index *= 2;
                }else{
                    break;
                }
            }else{
                if (heap->Elements[index*2+1].dist < heap->Elements[index].dist) {
                    temp = heap->Elements[index*2+1];
                    heap->Elements[index*2+1] = heap->Elements[index];
                    heap->Elements[index] = temp;
                    index = index*2 +1;
                }else{
                    break;
                }
            }
        }
    }
}
int  heapFind(Heap* heap, int vertex){
    int index;
    for (index=1; index <=heap->Size; index++){
        if (heap->Elements[index].vertex ==vertex){
            return index;
        }
    }
    return 0;
}
void printShortestPath(Graph *G){/////////////////////////////////////
    int i, j, k;
    G->nodes[1].vertex = 1;
    G->nodes[1].dist = G->nodes[1].prev = 0;
    for (i = 2; i < G->size; ++i) {
        G->nodes[i].vertex = i;
        G->nodes[i].dist = MAX_DIST;
        G->nodes[i].prev = 0;
    }
    Heap *heap= CreateMinHeap(G->size);
    for (j = 2; j < G->size; ++j) {//heap에 temporary를 추가시킴
        if (G->nodes[j].prev==0){
            insertToMinHeap(heap, G->nodes[j].vertex, G->nodes[j].dist);
        }
    }
    for (i = 1; i < G->size; ++i) {//distance를update
        for (j = 1; j < G->size; ++j) {
            if (G->vertices[i][j] != 0){
                if (G->vertices[i][j] + G->nodes[i].dist < G->nodes[j].dist){
                    k = heapFind(heap, j);
                    heap->Elements[k].dist = G->nodes[j].dist = G->vertices[i][j] + G->nodes[i].dist;
                    heap->Elements[k].prev = G->nodes[j].prev = i;
                    sortHeap(heap, k);
                }
            }
        }
        deleteMin(heap);
    }
    DeleteMinHeap(heap);
    for (i = 2; i < G->size; ++i) {
        printpath(G, G->nodes[i]);
    }
    DeleteGraph(G);
    fclose(O);
}
