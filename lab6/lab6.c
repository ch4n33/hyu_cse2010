#include <stdio.h>
#include <stdlib.h>//to use dynamic allocation functions..
#define MAX(A, B) (A>B) ? A : B

//자나깨나 NULL조심..

//CODE SKELETON------------------------------------------
struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;
typedef int ElementType;
struct AVLNode{
    ElementType Element;
    AVLTree left;
    AVLTree right;
    int height;
};
AVLTree insert(ElementType X, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
void printInorder(AVLTree T);
void deleteTree(AVLTree T);
//CODE SKELETON FIN-------------------------------------
int changeHeightOfTree(AVLTree T);
AVLTree rotation(int key, AVLTree T);
int isHeight(AVLTree T);
int heightFactor(AVLTree T);
AVLTree makeNode();
FILE *I, *O;//file io pointer variable..
int main(int argc, char* argv[]){
    I = fopen(argv[1], "r");
    O = fopen(argv[2], "wt");//fileio -open
    AVLTree T = NULL;
    int input = 0;
    int a;
    while (1){//file input iteration
        a = input;
        fscanf(I, "%d", &input);
        if(a == input){
            break;
        }//for previous 5 line, breaking iteration..
        T = insert(input, T);
        changeHeightOfTree(T);
        T = rotation(input, T);
        changeHeightOfTree(T);
        printInorder(T);
        fprintf(O, "\n");
    }
    deleteTree(T);
    fclose(I);
    fclose(O);//fileio -close
    return 0;
}///main function
AVLTree makeNode(){
    AVLTree T = (AVLTree)malloc(sizeof(struct AVLNode));
    T->right = T->left = NULL;
    T->height = 0;
    return T;
}//make empty node and alloc memory and return it.
int changeHeightOfTree(AVLTree T){//r,l이 모두 NULL이면 height가 0이 되고, r,l의 height중 높은 값+1을 height로 한다.
    //사실 insert에 성공한 경우 root에서 insert된 node로 접근하는 경로에 있는 놈들만 바꾸면 됨..
    if(!T){
        return -1;
    }
    T->height = 1 + (MAX(changeHeightOfTree(T->right), changeHeightOfTree(T->left)));
    return T->height;
}
int heightFactor(AVLTree T){
    if (!T){
        return 0;
    }
    return isHeight(T->right) - isHeight(T->left); //+2면 right가 무거운거 -2면 left가 무거운
}
AVLTree insert(ElementType X, AVLTree T){
    if (!T){
        AVLTree node = makeNode();
        node->Element = X;
        return node;
    }
    if (X > T->Element){
        T->right = insert(X, T->right);
    }else if (X < T->Element){
        T->left = insert(X, T->left);
    }else{
        fprintf(O, "[already in the tree] %d\n", X);
    }
    return T;
}
AVLTree rotation(int key, AVLTree T){
    if (key > T->Element){
        T->right = rotation(key, T->right);
    }
    if (key < T->Element){
        T->left = rotation(key, T->left);
    }
    switch (heightFactor(T)){
        case -2:{
            if (heightFactor(T->left) > 0){
                T = DoubleRotateWithLeft(T);
            }else if (heightFactor(T->left) < 0){
                T = SingleRotateWithLeft(T);
            }
            break;
        }
        case 2:{
            if (heightFactor(T->right) > 0){
                T = SingleRotateWithRight(T);
            }else if (heightFactor(T->right) < 0){
                T = DoubleRotateWithRight(T);
            }
            break;
        }
    }
    return T;
}
AVLTree SingleRotateWithLeft(Position node){//ll
    if (!node){
        return node;
    }
    Position B = node->left;
    if (!B){
        return node;
    }
    node->left = B->right;
    B->right = node;
    return B;
}
AVLTree SingleRotateWithRight(Position node){//rr
    if (!node){
        return node;
    }
    Position B = node->right;
    if (!B){
        return node;
    }
    node->right = B->left;
    B->left = node;
    return B;
}
AVLTree DoubleRotateWithLeft(Position node){//lr
    node->left = SingleRotateWithRight(node->left);
    return SingleRotateWithLeft(node);
}
AVLTree DoubleRotateWithRight(Position node){//rl
    node->right = SingleRotateWithLeft(node->right);
    return SingleRotateWithRight(node);
}
void printInorder(AVLTree T){
    if (!T){
        return;
    }
    printInorder(T->left);
    fprintf(O, "%d(%d) ", T->Element, T->height);
    printInorder(T->right);

}
void deleteTree(AVLTree T){
    if (!T){
        return;
    }
    deleteTree(T->left);
    deleteTree(T->right);
    T->left = NULL;
    T->right = NULL;
    free(T);
}
int isHeight(AVLTree T){
    if(!T){
        return -1;
    }else{
        return T->height;
    }
}
