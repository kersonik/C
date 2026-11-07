#include <stdio.h>
#define SIZE 5

int main(void) {
    int tmp;
    int a = 3, b = 5;
    printf("a = %d, b = %d\n", a, b);
    tmp = a;
    a = b;
    b = tmp;
    printf("a = %d, b = %d\n", a, b);
    int array[SIZE] = {1, 3, 6, 4, 2};
    printf("Size of int is %d bytes.\n", sizeof(int));
    printf("Size of array is %d bytes.\n", sizeof(array));
    printf("Address of the beginning of the array is %p.\n", array);

    for (int i = 0; i < SIZE; i++) {
        printf("%3d", array[i]);
    }
    printf("\n");

    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%3d", array[i]);
    }
    printf("\n");

    //OTOCENI HODNOT V POLI >:D

    for (int i = 0; i < SIZE / 2; i++) {
        tmp = array[i];
        array[i] = array[SIZE - 1 - i];
        array[SIZE - 1 - i] = tmp;
    }
    printf("Reverse elements:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%3d", array[i]);
    }
    printf("\n");

    int suma = 0;
    for (int i = 0; i < SIZE; i++) {
        suma += array[i];
    }
    printf("Sum of all elements is %d.\n", suma);

    printf("Average of all elements is %f\n", (float) suma / SIZE);

    int min = array[0];
    int max = array[0];

    for (int i = 1; i < SIZE; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }
    printf("Minimum is %d\n", min);
    printf("Maximum is %d\n", max);
    return 0;
}
