#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printList(int *list, int size);
void merge(int *list, int left, int right);
void mergeSort(int *list, int left, int right);
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

    mergeSort(list, 0, size - 1);

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
void mergeSort(int *list, int left, int right) {
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
    mergeSort(list, left, mid);
    mergeSort(list, mid + 1, right);
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