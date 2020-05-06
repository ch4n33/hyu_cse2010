#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SQUARE (sets->size_maze * sets->size_maze)
#define SIZE (sets->size_maze)
//#define TEST

struct _DisjointSet{
    int size_maze;
    int *ptr_arr;
};
typedef struct _DisjointSet DisjointSets;

void init(DisjointSets *sets, DisjointSets* maze_print, int num);
void union_(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *maze_print, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);
FILE *I, *O;//file io
void init(DisjointSets *sets, DisjointSets* maze_print, int num) {
    sets->size_maze = num;
    sets->ptr_arr = (int*) malloc(sizeof(int) * (SQUARE + 1));
    maze_print->ptr_arr = (int*) malloc(sizeof(int) * (2*SQUARE + 2*SIZE + 1));
    int i;
    for (i = 0; i < SQUARE; i++) {
        sets->ptr_arr[i+1] = 0;
    }
    for (i = 0; i < SQUARE + SIZE; i++){
        maze_print->ptr_arr[i+1 + SQUARE+SIZE] = 1;/// |
        maze_print->ptr_arr[i+1] = 1;/// -
    }
    maze_print->ptr_arr[1+SIZE+SQUARE] = 0;
    maze_print->ptr_arr[2*SQUARE + 2*SIZE] = 0;
}
void union_(DisjointSets *sets, int i, int j){
    if (!sets){
        return;
    }
    while (sets->ptr_arr[i] > 0){
        i = sets->ptr_arr[i];
    }
    while (sets->ptr_arr[j] > 0){
        j = sets->ptr_arr[j];
    }
    if (!(i-j)){
        return;
    }
    sets->ptr_arr[i] = j;
}
void breakWall(DisjointSets *sets, DisjointSets *maze_print, int i){
    if (!sets || !maze_print){
        return;
    }
    if (rand()%2){
        if (i > SIZE && (find(sets, i)) != find(sets, i - SIZE)){//up -
            union_(sets, i, i - SIZE);
            maze_print->ptr_arr[i] = 0;
            return;
        }
        if ((i-1)%SIZE != 0 &&(find(sets, i) != find(sets, i-1))){//left |
            union_(sets, i, i-1);
            maze_print->ptr_arr[1 + ((i-1)%SIZE)*SIZE + ((i-1)/SIZE) + SQUARE+SIZE] = 0;
            return;
        }
    }else {
        if ((i - 1) % SIZE != 0 && (find(sets, i) != find(sets, i - 1))) {//left |
            union_(sets, i, i - 1);
            maze_print->ptr_arr[1 + ((i - 1) % SIZE) * SIZE + ((i - 1) / SIZE) + SQUARE + SIZE] = 0;
            return;
        }
        if (i > SIZE && (find(sets, i)) != find(sets, i - SIZE)) {//up -
            union_(sets, i, i - SIZE);
            maze_print->ptr_arr[i] = 0;
            return;
        }
    }
}
int find(DisjointSets *sets, int i){
    if (!sets){
        return 0;
    }
    while(sets->ptr_arr[i] > 0){
        i = sets->ptr_arr[i];
    }
    if (sets->ptr_arr[i] <= 0){
        return i;
    }
    return sets->ptr_arr[i] = find(sets, sets->ptr_arr[i]);
}
char isEnd(DisjointSets *sets){
    int i=1 , count = 0;
    while (i<SQUARE){
        if (sets->ptr_arr[i]==0){
            count++;
        }
        if (count ==2){
            return 0;
        }
        i++;
    }
    return 1;
}
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
    while(!isEnd(sets) || find(sets, 1)!=find(sets, SQUARE)){
        breakWall(sets, maze_print, 1+ rand()%(num*num));
#ifdef TEST
        printMaze(maze_print, num);
        fprintf(O,"\n");
#endif
    }
}

void printMaze(DisjointSets *maze_print, int num){
    if (!maze_print){
        return;
    }
    int i,j;
#define VERT fprintf(O, "|")
#define HORZ fprintf(O, "-")
#define SPACE fprintf(O, " ")
    for (i = 0; i < num; i++) {//i : row
        for (j = 0; j < num; j++) {//j : column
            fprintf(O, "+");
            if(maze_print->ptr_arr[i*num + j + 1]){
                HORZ;
            }else{
                SPACE;
            }//horizontal
        }
        fprintf(O, "+\n");

        for (j = 0; j < num; j++) {
            if (maze_print->ptr_arr[i + j*num + 1 + num*num+num]){
                VERT;
            }else{
                SPACE;
            }//vertical
            SPACE;
        }
        if (maze_print->ptr_arr[i+ j*num + 1 +num*num+num]){
            VERT;
        }else{
            SPACE;
        }//vertical
        fprintf(O,"\n");
    }
    for (int j = 0; j < num; j++) {
        fprintf(O, "+-");
    }
    fprintf(O, "+\n");
}
void freeMaze(DisjointSets *sets, DisjointSets *maze_print){
    if (!sets || !maze_print){
        return;
    }
    free(sets->ptr_arr);
    free(maze_print->ptr_arr);
    free(sets);
    free(maze_print);
}

int main(int argc, char*argv[]) {
    srand((unsigned int)time(NULL));
    I = fopen(argv[1], "r");
    O = fopen(argv[2], "wt");
    ///code starts here..
    int num;
    fscanf(I, "%d", &num);
    fclose(I);
    DisjointSets *sets, *maze_print;
    sets = (DisjointSets*) malloc(sizeof(DisjointSets));
    maze_print = (DisjointSets*) malloc(sizeof(DisjointSets));
    init(sets,maze_print,num);
    createMaze(sets, maze_print, num);
    printMaze(maze_print, num);
    freeMaze(sets, maze_print);
    ///code ends here..
    fclose(O);
    return 0;
}
