#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 20

int *copy_arr(int *arr, int n)
{
    int *ret_arr = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        ret_arr[i] = arr[i];
    }
    return ret_arr;
}

void print_arr(int *arr, int n)
{
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap_element(int *i, int *j)
{
    int tmp;

    tmp = *i;
    *i = *j;
    *j = tmp;
}

// -----------------------------------------------------------------------------

int *bubble_sort(int *arr, int n)
{
    printf("%s: ", __func__);

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]) swap_element(&arr[j], &arr[j+1]);
        }
    }
    return arr;
}

int *selection_sort(int *arr, int n)
{
    int min_idx;

    printf("%s: ", __func__);

    for(int i = 0; i < n-1; i++){
        min_idx = i;

        for(int j = i+1; j < n; j++){
            if(arr[j] < arr[min_idx]) min_idx = j;
        }

        swap_element(&arr[min_idx], &arr[i]);
    }
    return arr;
}

int *insertion_sort(int *arr, int n)
{
    printf("%s: ", __func__);

    for(int i = 0; i < n-1; i++){
        if(arr[i] > arr[i+1]){
            swap_element(&arr[i], &arr[i+1]);
            for(int j = i; j > 0; j--){
                if(arr[j] < arr[j-1]) swap_element(&arr[j], &arr[j-1]);
            }
        }
    }

    return arr;
}

// Hope this has no memory leak
int *quick_sort(int *arr, int n)
{
    if(n <= 1) return arr;

    int tmp_iter = 0;

    int pivot = arr[0];

    int *high = (int *)malloc((n-1) * sizeof(int));
    int *low = (int *)malloc((n-1) * sizeof(int));

    int high_iter = 0;
    int low_iter = 0;

    for(int i = 1; i < n; i++){
        if(arr[i] <= pivot){
            low[low_iter] = arr[i];
            low_iter++;
        }
        else{
            high[high_iter] = arr[i];
            high_iter++;
        }
    }

    high = quick_sort(high, high_iter);
    low = quick_sort(low, low_iter);

    for(int i = 0; i < low_iter; i++){
        arr[tmp_iter] = low[i];
        tmp_iter++;
    }
    arr[tmp_iter] = pivot;
    tmp_iter++;
    for(int i = 0; i < high_iter; i++){
        arr[tmp_iter] = high[i];
        tmp_iter++;
    }

    free(high);
    free(low);

    return arr;
}

// Hope this also has no memory leak
int *merge_sort(int *arr, int n)
{
    if(n <= 1) return arr;

    int half = n/2;

    int *first_half = merge_sort(copy_arr(arr, half), half);
    int *last_half = merge_sort(copy_arr(&arr[half], n-half), n-half);


    int f_iter = 0;
    int l_iter = 0;
    int ret_iter = 0;
    // merge
    while(f_iter < half && l_iter < n-half){
        if(first_half[f_iter] > last_half[l_iter]){
            arr[ret_iter] = last_half[l_iter];
            l_iter++;
        }
        else{
            arr[ret_iter] = first_half[f_iter];
            f_iter++;
        }
        ret_iter++;
    }

    while(f_iter < half){
        arr[ret_iter] = first_half[f_iter];
        ret_iter++;
        f_iter++;
    }
    while(l_iter < n-half){
        arr[ret_iter] = last_half[l_iter];
        ret_iter++;
        l_iter++;
    }

    free(first_half);
    free(last_half);
    
    return arr;
}

// -----------------------------------------------------------------------------

void check_algo(int* (*sort)(int*, int), int *to_be_sorted, int *ground_truth, int n)
{
    int *sorted_arr = (*sort)(copy_arr(to_be_sorted, n), n);

    for(int i = 0; i < n; i++){
        if(sorted_arr[i] != ground_truth[i]){
            printf("No Good\n");
            free(sorted_arr);
            return;
        }
    }
    printf("Ok Good\n");
    free(sorted_arr);
}

int main()
{
    // Repeating numb
    int init_arr[ARR_SIZE] = {
        26, 28, 3, 57, 34, 8, 3, 12, 15, 85,
        99, 42, 82, 15, 94, 15, 62, 49, 28, 29
    };
    int sorted_arr[ARR_SIZE] = {
        3, 3, 8, 12, 15, 15, 15, 26, 28, 28,
        29, 34, 42, 49, 57, 62, 82, 85, 94, 99
    };

    // int init_arr[ARR_SIZE] = {7, 3, 9, 2, 4, 1, 6, 10, 8, 5};
    // int sorted_arr[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10};

    // int init_arr[ARR_SIZE] = {12, 11, 13, 5, 6};
    // int sorted_arr[ARR_SIZE] = {5, 6, 11, 12, 13};

    check_algo(bubble_sort, init_arr, sorted_arr, ARR_SIZE);

    check_algo(selection_sort, init_arr, sorted_arr, ARR_SIZE);

    check_algo(insertion_sort, init_arr, sorted_arr, ARR_SIZE);

    printf("quick_sort: ");
    check_algo(quick_sort, init_arr, sorted_arr, ARR_SIZE);

    printf("merge_sort: ");
    check_algo(merge_sort, init_arr, sorted_arr, ARR_SIZE);

    return 0;
}