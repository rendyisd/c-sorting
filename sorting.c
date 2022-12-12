#include <stdio.h>
#include <stdlib.h>

int *copy_arr(int *arr, int n)
{
    int *ret_arr = (int*)malloc(n * sizeof(int));

    for(int i = 0; i<n; i++){
        ret_arr[i] = arr[i];
    }
    return ret_arr;
}

void print_arr(int *arr, int n)
{
    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
}

// -----------------------------------------------------------------------------

int *bubble_sort(int *arr, int n)
{
    int tmp;
    int *sorted = copy_arr(arr, 10);

    printf("%s: ", __func__);

    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(sorted[j] > sorted[j+1]){
                tmp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = tmp;
            }
        }
    }
    return sorted;
}

// -----------------------------------------------------------------------------

void check_algo(int* (*sort)(int*, int), int *to_be_sorted, int *ground_truth, int n)
{
    int *sorted_arr = (*sort)(to_be_sorted, n);

    for(int i = 0; i < n; i++){
        if(sorted_arr[i] != ground_truth[i]){
            printf("No good\n");
            return;
        }
    }
    printf("Ok good\n");
    free(sorted_arr);
}

int main()
{
    int init_arr[10] = {7, 3, 9, 2, 4, 1, 6, 10, 8, 5};
    int sorted_arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10};

    check_algo(bubble_sort, init_arr, sorted_arr, 10);

    print_arr(init_arr, 10);

    return 0;
}