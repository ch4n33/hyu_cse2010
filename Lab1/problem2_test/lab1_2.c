#include <stdio.h>

void s_sort(int* arr, const int n);//selection sort funtion
int main(void){
    FILE *input_file;
    FILE *output_file;

    input_file = fopen("lab1_2_input.txt", "r");
    output_file = fopen("lab1_2_output.txt","wt");
    int i, n;
    int arr[100];
    fscanf(input_file, "%d", &n);
    for(i = 0; i < n; i++){
        fscanf(input_file, "%d", &arr[i]);
    }
    s_sort(arr, n);
    for(i = 0; i < n; i++){
        fprintf(output_file, "%d ", arr[i]);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
void s_sort(int *arr, const int n){
    int pivot, temp, i, j;
    for(i = 0; i < n; i++){
        pivot = i;
        for(j = i+1; j < n; j++){
            if(arr[pivot] < arr[j]){
                pivot = j;
            }
        }
        if(pivot!= i){
            temp = arr[i];
            arr[i] = arr[pivot];
            arr[pivot] = temp;
        }
    }
}
