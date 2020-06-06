#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void generate_matrix(int *m, int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            m[i*size+j] = rand();            
        }
    }
}

void print_matrix(int *m, int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("%d ", m[i*size + j] % 10);
        }
        printf("\n");
    }
}

int main() {
    int SIZE = 10;
    int matrix[SIZE*SIZE];

    generate_matrix(matrix, SIZE);
    print_matrix(matrix, SIZE);
}
