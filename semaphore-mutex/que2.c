/*Create a thread to sort given array of "n" integers using bubble sort. Main thread should print the result after sorting is completed.
Hint: struct array { int *arr; int size; }
Pass struct address to thread function (via arg4 of pthread_create()).*/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to pass array data to the thread
struct array_data {
    int *arr;
    int size;
};

// Function to perform bubble sort
void bubble_sort(int *arr, int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Thread function that receives a pointer to the struct and sorts the array
void *sort_array_thread(void *arg) {
    struct array_data *data = (struct array_data *)arg;
    bubble_sort(data->arr, data->size);
    return NULL;
}

int main() {
    pthread_t sort_tid;
    
    // Example array to be sorted
    int my_array[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(my_array) / sizeof(my_array[0]);

    // Initialize the struct with array data
    struct array_data data;
    data.arr = my_array;
    data.size = n;
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    // Create the sorting thread, passing the address of the struct
    pthread_create(&sort_tid, NULL, sort_array_thread, &data);

    // Wait for the sorting thread to complete
    pthread_join(sort_tid, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    return 0;
}

