#include<stdio.h>
#include<stdlib.h>

/*File IO variable*/
FILE *I, *O;
/*----------------*/
int count= 0;

/*----Code Skeleton----------------------*/
struct binarySearchTree;
typedef struct binarySearchTree* Tree;
struct binarySearchTree{
    int value;
    Tree left;
    Tree right;
};
//Node of each tree is "Tree"

Tree insertNode(Tree root, int key);
//root is highest Node

void findNode(Tree root, int key);
void printInorder(Tree root);
Tree deleteNode(Tree root, int key);
//if deleted node has children, ??????????

void deleteTree(Tree root);
//use free function
/*----Code Skeleton----------------------*/

Tree makeNode(){
    Tree T = (Tree) malloc(sizeof(struct binarySearchTree));
    T->left = T->right = NULL;
    T->value = 0;
    return T;
}
Tree insertNode(Tree root, int key){
    if(root == NULL){
        fprintf(O,"insert %d", key);
        Tree T = makeNode();
        T->value = key;
        return T;
    }
    //insert 하려는 key가 중복되지 않고 끝(NULL)까지 온 경우 : T를 만들어 리턴
    if(count ==0){
        root->value = key;
        fprintf(O,"insert %d", key);
        return NULL;
    }else if(root->value > key){
        root->left = insertNode(root->left, key);
    }else if(root->value < key){
        root->right = insertNode(root->right, key);
    }else{
        fprintf(O,"cannot insert %d", key);
    }
    return root;
    //insert하려는 키가 중복되지 않은 경우 : root 받아온 걸 그대로 리턴
    //중복된 경우 : 에러를 출력하고 root 받아온 걸 그대로 리턴
}
void findNode(Tree root, int key){
    //insert function과 같은 구조로 재귀하여 구현하자
    if(root == NULL){
        fprintf(O, "%d is not in the tree", key);
        return;
    }
    else if(root->value > key)
        findNode(root->left, key);
    else if(root->value < key)
        findNode(root->right, key);
    else
        fprintf(O, "%d is in the tree", key);
}
void printInorder(Tree root){
    if(root){
        if(root->left)
            printInorder(root->left);
        fprintf(O, "%d ", root->value);

        if(root->right)
            printInorder(root->right);
    }else
        return;
}
Tree deleteNode(Tree root, int key){
    Tree T, temp;
    
    /*delete를 실패한 경우 --------------*/
    if(root == NULL){
        fprintf(O, "cannot delete node '%d'", key);
        return NULL;
    }
    /*delete할 key의 값과 root를 비교해서 right로 갈지 left로 갈지 결정*/
    if(root->value > key){
        root->left = deleteNode(root->left, key);
        return root;
    }else if(root->value < key){
        root->right = deleteNode(root->right, key);
        return root;
    }

    else if(root->right){
        //root->value == key이고 root->right !=NULL인 경우!!!
        //T는 root->right쪽에서 가장 작은 node
        //temp는 T의 상위 node
        T = root->right;
        temp = root;
        fprintf(O, "delete %d", key);
        while(T->left){
            temp = T;
            T = T->left;
        }
        T->left = root->left;
        temp->right = T->right;
        T->right = root->right;
        
        free(root);
        return T;
    }else if (root->left){
        //root->value == key이고 root->right ==NULL, root->left !=NULL인 경우!!!
        T = root->left;
        free(root);
        fprintf(O, "delete %d", key);
        return T;
    }else{
        //root->value == key이고 root->right ==NULL, root->left ==NULL인 경우!!!
        free(root);
        fprintf(O, "delete %d", key);
        return NULL;
    }
}
void deleteTree(Tree root){
    count =0;
    if(!root)
        return;
    if(root->right)
        deleteTree(root->right);
    if(root->left)
        deleteTree(root->left);
    if(root)
        free(root);
    root= NULL;
}


int main(int argc, char* argv[]){
    I = fopen(argv[1], "r");
    O = fopen(argv[2], "wt");
    char mode[3];
    int key;
    Tree T = makeNode();
    int iii = !feof(I);
    while(iii){
        char tmpmode = mode[0];
        fscanf(I, "%s", mode);
        if(tmpmode == 'p' && mode[0] == 'p')
            break;
        switch(mode[0]){
            case 'i' :
                fscanf(I, "%d", &key);
                insertNode(T, key);
                break;
            case 'd' :
                fscanf(I, "%d", &key);
                T = deleteNode(T, key);
                break;
            case 'f' :
                fscanf(I, "%d", &key);
                findNode(T, key);
                break;
            case 'p' :
                printInorder(T);
                break;
        }
        fprintf(O,"\n");
        count++;
    }
    deleteTree(T);
    fclose(I);
    fclose(O);
    return 0;
}
