#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


void generate_vector(int *v, int size) {
    for(int i = 0; i < size; i++) {
        v[i] = rand() % 10;
    }
}

void print_vector(int *v, int size) {
    for(int i = 0; i < size; i++) {
        printf("%2d ", v[i]);
    }
    printf("\n");
}

void bubble_sort(int *v, int size) {
    for(int i=0; i<size - 1; i++) {
        for(int j=0; j<size - i; j++) {
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }            
        }
    }
}

void odd_even_bubble_sort(int *v, int size) {
    for(int i=0; i<size; i++) {
        // even
        if (i % 2 == 0) {
            for(int j=2; j<size; j+=2) {
                if (v[j-1] > v[j]) {
                    int tmp = v[j-1];
                    v[j-1] = v[j];
                    v[j] = tmp;
                }            
            }    
        // odd
        } else {
            for(int j=1; j<size; j+=2) {
                if (v[j-1] > v[j]) {
                    int tmp = v[j-1];
                    v[j-1] = v[j];
                    v[j] = tmp;
                }            
            }
        }        
    }
}

int main() {
    int SIZE = 100000;
    int *vector;
    
    vector = malloc(sizeof(int) * SIZE);
    
    generate_vector(vector, SIZE);

    odd_even_bubble_sort(vector, SIZE);
    
    if (SIZE < 20) {
        print_vector(vector, SIZE);        
    }

    free(vector);
}