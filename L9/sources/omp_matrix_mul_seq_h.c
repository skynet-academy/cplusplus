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

void mul(int *a, int *b, int *c, int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            int dot = 0;
            for(int k=0; k<size; k++) {
                dot += a[i*size+k]*b[j*size+k];
            }
            c[i*size+j] = dot;
        }
    }
}

void main() {
    int SIZE = 1000;
    int *a, *b, *c;
    
    a = malloc(sizeof(int)*SIZE*SIZE);
    b = malloc(sizeof(int)*SIZE*SIZE);
    c = malloc(sizeof(int)*SIZE*SIZE);
    
    generate_matrix(a, SIZE);
    generate_matrix(b, SIZE);
    generate_matrix(c, SIZE);
    
    mul(a, b, c, SIZE);


    free(a);
    free(b);
    free(c);
}