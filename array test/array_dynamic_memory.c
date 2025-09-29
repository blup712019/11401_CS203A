#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int n = 10;

    // Allocate memory for n integers
    array = (int *) malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Print the starting memory address
    printf("Initial memory address: %p\n", (void*)array);
    printf("Initial memory end address  : %p\n", (void*)(array + n * sizeof(int) - 1));

    // Initialize elements
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    // Print elements
    printf("Initial array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Double the size  
    n = n * 2;
    array = (int *) realloc(array, n * sizeof(int));  //第一次會一樣 後面就變不一樣
    if (array == NULL) {
        printf("Reallocation failed\n");
        return 1;
    }

    // Print the new memory address
    printf("After realloc memory address: %p\n", (void*)array);
    printf("After realloc end address   : %p\n", (void*)(array + n * sizeof(n) - 1));

    // Initialize new elements
    for (int i = n/2; i < n; i++) {
        array[i] = i + 1;
    }

    // Print all elements
    printf("Resized array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Free memory
    free(array);
    int** testary;
    int rows = 3, col = 4;
    //測試2為
    testary = (int**)malloc(rows * sizeof(int*));
    if (!testary) {
        return 0;
    }
    for (int i = 0; i < rows; i++) {
        testary[i] = (int*)malloc(col * sizeof(int));
        if (!testary[i]) return 0;
    }
    testary[2][1] = 10;
    printf("%d\n", testary[2][1]);
    return 0;
}
