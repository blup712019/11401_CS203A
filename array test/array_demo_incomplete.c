#include <stdio.h>
#include <stdlib.h> //原本沒include


int main() {
    int* array;
    int n = 10;

    array = (int*)malloc(n * sizeof(int));
    if (array == NULL) { //確認是否有正確分配到記憶體
        printf("false");
    }
    for (int i = 0; i < n; i++) {
        array[i] = i + 1; 
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    n = n * 2;

    array = (int*)realloc(array, n * sizeof(int));
    if (array == NULL) { //確認是否有正確分配到記憶體
        printf("false");
    }
    for (int i = n / 2; i < n; i++) {
        array[i] = i + 1;   // initialize new elements
    }

} // no main
