#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct{
    int Capacity;
    int Size;
    int *Element;
}Heap;
Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int find(Heap *heap, int value);
int DeleteMax(Heap *heap);
void PrintHeap(Heap *heap);
FILE *I, *O;

int main(int argc, char* argv[]){
    I = fopen(argv[1], "r");
    O = fopen(argv[2], "w");
    char c;
    int i;
    Heap* heap;
    while(EOF!=fscanf(I, "%c", &c)){
        if (c == 'n'){
            fscanf(I, "%d", &i);
            heap = CreateHeap(i);
        }else if( c == 'i'){
            fscanf(I, "%d", &i);
            Insert(heap, i);//fprint in function
            fprintf(O, "\n");
        }else if (c == 'f'){
            fscanf(I, "%d", &i);
            Find(heap, i);//fprint in function
            fprintf(O, "\n");
        }else if (c == 'd'){
            i = DeleteMax(heap);
            if (i>=0){
                fprintf(O, "delete %d", i);
            }
            fprintf(O, "\n");
        }else if (c == 'p') {
            PrintHeap(heap);//fprint in function
            fprintf(O, "\n");
        }
    }
    fclose(I);
    fclose(O);
    free(heap->Element);
    free(heap);
}

Heap* CreateHeap(int heapSize){
    Heap *H = (Heap*) malloc(sizeof(Heap));
    H->Capacity = heapSize;
    H->Size = 0;
    H->Element = (int*)malloc(sizeof(int) * (H->Capacity + 1));
    return H;
}
char heapCapacity(Heap *H){
    return H->Capacity > H->Size;
}
void Insert(Heap *heap, int value){
    if (!heapCapacity(heap)){
        fprintf(O, "Insert error : heap is full");
        return;
    }if (find(heap, value)){
        fprintf(O, "Insert error : [%d] is already in the heap", value);
        return;
    }
    fprintf(O,"insert %d", value);
    heap->Size++;
    heap->Element[heap->Size] = value;
    int i = heap->Size;
    int temp;
    while(i>1 && heap->Element[i] > heap->Element[i/2]){
        temp = heap->Element[i];
        heap->Element[i] = heap->Element[i/2];
        heap->Element[i/2] = temp;
        i /= 2;
    }
}
int find(Heap *heap, int value){
    int i;
    for (i = 1; i <= heap->Size; i++){
        if (heap->Element[i] == value){
            return 1;
        }
    }
    return 0;
}
int Find(Heap *heap, int value){
    if (find(heap, value)){
        fprintf(O, "[%d] is in the heap", value);
        return 1;
    }
    fprintf(O, "[%d] is not in the heap", value);
    return 0;
}
int DeleteMax(Heap *heap){
    if (heap->Size == 0){
        fprintf(O, "Delete error : heap is empty");
        return -1;
    }
    int max = heap->Element[1];
    heap->Element[1] = heap->Element[heap->Size];
    heap->Size--;
    int temp, i = 1;
    while (i*2  <= heap->Size){
        if (i*2 + 1 <= heap->Size){
            if (heap->Element[i*2 + 1] > heap->Element[i*2]
                    && heap->Element[i*2 + 1] > heap->Element[i]){
                temp = heap->Element[i*2 + 1];
                heap->Element[i*2 + 1] = heap->Element[i];
                heap->Element[i] = temp;
                i = i*2 +1;
            }
            if (heap->Element[i*2 + 1] < heap->Element[i*2]
                    && heap->Element[i*2] > heap->Element[i]){
                temp = heap->Element[i*2];
                heap->Element[i*2] = heap->Element[i];
                heap->Element[i] = temp;
                i = i*2;
            }
        }else if (heap->Element[i*2] > heap->Element[i]){
            temp = heap->Element[i*2];
            heap->Element[i*2] = heap->Element[i];
            heap->Element[i] = temp;
            i = i*2;
        }else {
            break;
        }
    }
    return max;
}
void PrintHeap(Heap *heap){
    int i;
    if (!heap->Size){
        fprintf(O, "Print error : heap is empty");
        return;
    }
    for (i=1; i <= heap->Size; i++){
        fprintf(O, "%d ", heap->Element[i]);
    }
}
