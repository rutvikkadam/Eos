/*Create a thread to sort given array of 10 integers using selection sort. Main thread should print the result after sorting is completed.
Hint: Pass array to thread function (via arg4 of pthread_create()).
void* thread_func(void *param) {
int *arr = (int*)param;
// ... code to sort the array
return NULL;
}*/

#include <stdio.h>
#include <pthread.h>

// Thread function that performs selection sort
void* thread_func(void* param) {
    int *arr = (int*)param;
    int size = 10;
    int i, j, min_idx, temp;

    // Selection sort algorithm
    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element of the unsorted part
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    return NULL;
}

// Function to print the array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    pthread_t sort_tid;
    int my_array[10] = {64, 25, 12, 22, 11, 33, 90, 81, 75, 45};
    
    printf("Original array: ");
    print_array(my_array, 10);

    // Create the sorting thread, passing the array as the argument
    pthread_create(&sort_tid, NULL, thread_func, (void*)my_array);

    // Wait for the sorting thread to finish its execution
    pthread_join(sort_tid, NULL);

    printf("Sorted array: ");
    print_array(my_array, 10);

    return 0;
}

