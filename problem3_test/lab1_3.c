#include <stdio.h>
#define MAX_LENGTH 30

typedef struct{
    char name[MAX_LENGTH];    
    int id;
}student;

void s_sort(student *arr, const int n);

int main(void){
    FILE *input_file;
    FILE *output_file;

    input_file = fopen("lab1_3_input.txt", "r");
    output_file = fopen("lab1_3_output.txt", "wt");
    
    student arr[10];
    int n, i;
    fscanf(input_file, "%d", &n);
    for(i = 0; i < n; i++){
        fscanf(input_file, "%s %d", arr[i].name, &arr[i].id);
    }

    s_sort(arr, n);
    for(i = 0; i < n ; i++){
        fprintf(output_file, "%s %d", arr[i].name, arr[i].id);
        if(i < n-1){
            fprintf(output_file, "\n");
        }
    }

    fclose(input_file);
    fclose(output_file);
}

void s_sort(student *arr, const int n){
    int pivot, temp, i, j;
    for(i = 0; i < n; i++){
        pivot = i;
        for(j = i+1; j < n; j++){
        if(arr[pivot].id > arr[j].id){
            pivot = j;
        }
        }
        if(pivot!= i){
            temp = arr[i].id;
            arr[i].id = arr[pivot].id;
            arr[pivot].id = temp;
        }
    }
}

