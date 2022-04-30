#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// void printList(int *list, int size);
void bubbleSort(int *list, int size);

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

    // printList(list, size);
    bubbleSort(list, size);
    // printList(list, size);
}

void bubbleSort(int *list, int size) {
    bool made_swap = true;
    
    while (made_swap) {
        made_swap = false;
        for (int i = 0; i < size - 1; ++i) {
            if (list[i] > list[i + 1]) {
                made_swap = true;
                int temp = list[i + 1];
                list[i + 1] = list[i];
                list[i] = temp;
            }
        }
    }
}

// void printList(int *list, int size) {
//     for (int i = 0; i < size; ++i) {
//         printf("%d ", list[i]);
//     }
//     printf("\n");
// }