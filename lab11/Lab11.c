#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode{
    int Element;
};
typedef struct ListNode *Position;
typedef Position List;
struct HashTbl{
    int TableSize;
    List* TheLists;//null이면 비지 않은 것이고, 0이 들어있으면 delete된 것.
};
typedef struct HashTbl *HashTable;
void Insert(HashTable H, int value, int solution);
void Delete(HashTable H, int value, int solution);
int Find (HashTable H, int value, int solution);
void PrintTable(HashTable H);
int Hash(int value, int size, int i, int solution);
/* solution ==1 : linear
 * solution ==2 : Quadratic*/

HashTable makeHashTable(int size){
    HashTable H = (HashTable) malloc(sizeof(struct HashTbl));
    H->TheLists = (List*) calloc(size, size * sizeof(List));
    H->TableSize = size;
    return H;
}
void freeHashTable(HashTable H){
    int i;
    for (i = 0; i < H->TableSize; ++i) {
        free(H->TheLists[i]);
    }
    free(H->TheLists);
    free(H);
}
FILE *gI, *gO;
int main(int argc, char *argv[]){
    gI = fopen(argv[1], "r");
    gO = fopen(argv[2], "wt");
    char fin[20];

    fscanf(gI, "%s", fin);
    int solution;
    if (strcmp(fin, "Linear") == 0){
        solution = 1;
    }
    else if (strcmp(fin, "Quadratic") == 0){
        solution = 2;
    }
    else {
        fprintf(gO, "incorrect solution..[%s]", fin);
        return 0;
    }
    int n; char c;
    fscanf(gI, "%d", &n);
    HashTable H = makeHashTable(n);
    int value;
    while(EOF != fscanf(gI, "%c", &c)){
        switch(c){
            case 'i':{
                fscanf(gI, "%d", &value);
                Insert(H, value, solution);
                fprintf(gO, "\n");

                break;
            }
            case 'd':{
                fscanf(gI, "%d", &value);
                Delete(H,value, solution);
                fprintf(gO, "\n");
                break;
            }
            case 'f':{
                fscanf(gI, "%d", &value);
                Find(H, value, solution);
                fprintf(gO, "\n");
                break;
            }
            case 'p':{
                PrintTable(H);
                fprintf(gO, "\n");
                break;
            }
        }
    }
    freeHashTable(H);
    fclose(gI);
    fclose(gO);
    return 0;
}
int power(int i, int solution){
    int j, temp= i;
    for (j = 1; j < solution; ++j) {
        temp *= i;
    }
    return temp;
}
int Hash(int value, int size, int i, int solution){
    return (value + power(i, solution))%size;
}
int insertValidity(Position position){
    if (!position)
        return 1;
    if (!position->Element)
        return 1;
    return 0;
}
void Insert(HashTable H, int value, int solution){
    int i=-1, index;
    Position position;
     do{
         i++;
         index = Hash(value, H->TableSize, i, solution);
         position = H->TheLists[index];

         if (i > H->TableSize){
             fprintf(gO, "connot insert");
             return;
         }
         if (!insertValidity(position)){
             if (position->Element== value) {
                 fprintf(gO, "Already exists");
                 return;
             }
             continue;
         }
     }while (!insertValidity(position));
     position = H->TheLists[index] = (List)malloc(sizeof(struct ListNode));
     position->Element = value;
     fprintf(gO, "insert %d", value);
}
int deleteValidity(Position position){
    if (!position)
        return 0;
    if(!position->Element)
        return 0;
    return 1;
}
void Delete(HashTable H, int value, int solution){
    int i=-1, index;
    List list;
    do{
        i++;
        index = Hash(value, H->TableSize, i, solution);
        list = H->TheLists[index];
        if (i > H->TableSize){
            fprintf(gO, "i think.. ");
            break;
        }
        if (deleteValidity(list) ){
            if (list->Element == value){
                fprintf(gO, "delete %d", list->Element);
                list->Element = 0;
                return;
            }
            break;
        }
    }while (!deleteValidity(list));
    fprintf(gO, "%d not exists", value);
}
int findValidity(Position position){
    if (!position)
        return 0;
    return 1;
}
int Find (HashTable H, int value, int solution){
    int i=-1, index;
    Position position;
    do{
        i++;
        index = Hash(value, H->TableSize, i, solution);
        position = H->TheLists[index];
        if (i > H->TableSize/solution){
            break;
        }
        if (findValidity(position)){
            if (position->Element == value){
                fprintf(gO, "%d exists",value);
                return value;
            }
            continue;
        }
    }while (findValidity(position));
    fprintf(gO, "Not found");
    return 0;
}
void printNode(Position position){
    if(!position)
        fprintf(gO, "0 ");
    else
        fprintf(gO, "%d ", position->Element);

}
void PrintTable(HashTable H){
    int i;
    for (i = 0; i < H->TableSize; ++i) {
        printNode(H->TheLists[i]);
    }
}