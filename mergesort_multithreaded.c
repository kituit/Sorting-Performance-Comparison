#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_THREAD_PARTITION 500000 // Maximum subsection of array that a single thread is responsible for sorting
                                    // Can change to find optimum between parallelising work and overhead of creating threads

struct merge_sort_args {
    int *list; 
    int left;
    int right;
};

void printList(int *list, int size);
void merge(int *list, int left, int right);
void mergeSort(struct merge_sort_args *args);
bool confirmSorted(int *list, int size);

int main(void) {

    int size = 0;
    printf("Size: ");
    scanf("%d", &size);

    int *list = malloc(size * sizeof(int));
    int num = 0;
    int i = 0;
    printf("Nums: ");
    while (i < size && scanf("%d", &num) == 1) {
        list[i] = num;
        ++i;
    }

    struct merge_sort_args args;
    args.list = list;
    args.left = 0;
    args.right = size - 1;

    mergeSort(&args);

    // if (confirmSorted(list, size)) {
    //     printf("Sorted!\n");
    // }

}

void printList(int *list, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// Confirms list is sorted in ascending order. Returns true if sorted.
bool confirmSorted(int *list, int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (list[i] > list[i + 1]) return false;
    }

    return true;
}

// Merge sort list from left index to right index (inclusive)
void mergeSort(struct merge_sort_args *args) {
    int *list = args->list;
    int left = args->left;
    int right = args->right; 
    
    if (left == right) {
        return;
    } else if (left == right - 1) {
        if (list[left] > list[right]) {
            int temp = list[left];
            list[left] = list[right];
            list[right] = temp;
        }
        return;
    }

    int mid = (left + right) / 2;

    if (right - left + 1 > MAX_THREAD_PARTITION) {
        pthread_t new_thread;
        struct merge_sort_args new_args;
        new_args.list = list;
        new_args.left = left;
        new_args.right = mid;
        pthread_create(&new_thread, NULL, (void *)mergeSort, (void *)&new_args);
        
        args->left = mid + 1;
        mergeSort(args);
        
        pthread_join(new_thread, NULL);
    } else {
        args->right = mid;
        mergeSort(args);
        
        args->left = mid + 1;
        args->right = right;
        mergeSort(args);
    }

    merge(list, left, right);

}

// Merge sorted sections of list 
void merge(int *list, int left, int right) {
    int *templist = malloc((right - left + 1) * sizeof(int));

    int mid = (left + right) / 2;
    int left_i = left;
    int right_i = mid + 1; 
    int temp_i = 0;

    while (left_i <= mid && right_i <= right) {
        if (list[left_i] < list[right_i]) {
            templist[temp_i] = list[left_i];
            ++left_i;
        } else {
            templist[temp_i] = list[right_i];
            ++right_i;
        }
        ++temp_i;
    }

    while (left_i <= mid) {
        templist[temp_i] = list[left_i];
        ++left_i;
        ++temp_i;
    }
    while (right_i <= right) {
        templist[temp_i] = list[right_i];
        ++right_i;
        ++temp_i;
    }

    for (int i = 0, j = left; j <= right; i++, j++) {
        list[j] = templist[i];
    }
    free(templist);
}