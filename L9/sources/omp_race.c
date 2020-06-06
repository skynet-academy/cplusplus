#include <omp.h>
#include <stdio.h>

void main() {
    int isComplited = 0;
    double mul_result = 1;
    int sum_result = 1;
    int size = 1000000000;

    omp_set_num_threads(2);

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for(int i=0; i<size; i++) {
                    mul_result *= 0.5;
                }

                #pragma omp critical
                {
                    if (isComplited == 0) {
                        printf("Mul first!\n");
                        isComplited = 1;
                    }
                }                
            }

            #pragma omp section
            {
                for(int i=0; i<size; i++) {
                    sum_result += 1;
                }

                #pragma omp critical
                {
                    if (isComplited == 0) {
                        printf("Sum first!\n");
                        isComplited = 1;
                    }
                }                
            }
        }
    }    
}