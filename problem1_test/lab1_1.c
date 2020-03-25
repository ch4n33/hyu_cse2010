#include <stdio.h>

int main(){
    FILE *input_file;
    FILE *output_file;

    input_file = fopen("lab1_1_input.txt","r");
    output_file = fopen("lab1_1_output.txt","wt");
    
    int i, n, st, ed;
    int arr[100];
    int sum=0;

    fscanf(input_file, "%d", &n);
    for(i = 0; i < n; i++){
        fscanf(input_file, "%d", &arr[i]);
    }
    fscanf(input_file, "%d %d", &st, &ed);
    for(i = st; i<=ed; i++){
        sum += arr[i];
    }
    fprintf(output_file, "%d", sum);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
