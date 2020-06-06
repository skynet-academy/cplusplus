#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<mpi.h>

const int INFINITY = 1000000;

void readMatrix(int local_mat[], int n, int my_rank, p, MIP_Comm comm);
void printMatrix(int local_mat[], int n, int my_rank, p, MIP_Comm comm);
void Floyd(int local_mat[], int n, int my_rank, p, MIP_Comm comm);
int owner(int k, int p, int n);
void copyRow(int local_mat[],int n, int p, int row_k[], int k);
void printRow(int local_mat[], int n, int my_rank, int i);



void readMatrix(int local_mat[], int n, int my_rank, p, MIP_Comm comm){
    int i,j;
    int * temp_mat = NULL;

    if(my_rank == 0){
        temp_mat = malloc(n*n*sizeof(int));     // what's malloc
        for(i = 0; i < n ; j++)
            for(j = 0; j < n; j++)
                scanf("%d", &temp_mat[i*n+j]);
        MPI_Scatter(temp_mat, n*n/p, MPI_INT, local_mat, n*n/p , MPI_INT, 0 , comm);
        free(temp_mat);
    }else {
        MPI_Scatter(temp_mat, n*n/p, MPI_INT, local_mat, n*n/p , MPI_INT, 0 , comm);
    }
}
void printRow(int local_mat[], int n, int my_rank, int i){
    char char_int[100];
    char char_row[1000];
    int j, offset = 0;
    for(j = 0; j < n; j++ ){
        if(local_mat[i*n + j]== INFINITY)
            sprintf(char_int, "i");
        else
            sprintf(char_int[char_int,"%d", local_mat[i*n + j]]);
        sprintf(char_row + offset, "%s", char_int);
        offset+=strlen(char_int);
    }
    printf("Pro %d > row %d = %s\n", my_rank, i , char_row);
}

void printMatrix(int local_mat[], int n, int my_rank, p, MIP_Comm comm){
    int i,j;
    int * temp_mat = NULL;
    if(my_rank==0){
        temp_mat = malloc(n*n*sizeof(int));
        MPI_Gather(local_mat, n*n/p, MPI_INT, temp_mat, n*n/p, MPI_INT, 0 , comm);
        for(i = 0; i < n; i++ ){
            if(temp_mat[i*n + j] == INFINITY)
                printf("i");
            else
                printf("%d", temp_mat[i*n + j]);
            printf("\n");
        }
        free(temp_mat);
    } else {
        MPI_Gather(local_mat, n*n/p, MPI_INT, temp_mat, n*n/p, MPI_INT, 0 , comm);
    }
}
void Floyd(int local_mat[], int n, int my_rank, p, MIP_Comm comm){
    int global_k, local_i, global_j, temp;
    int root;
    int * row_k = malloc(n*sizeof(int));
    for(global_k = 0; global_k < n ; global_k ++){
        root = owner(global_k,p,n);
        if(my_rank == root)
            copyRow(local_mat, n,p,row_k, global_k);
        MPI_Bcast(row_k, n, MPI_INT, root, comm);
        for(local_i = 0 ; local_i < n/p ; local_i ++)
            for(global_j = 0 ; global_j < n ; global_j ++){
                temp = local_mat[local_i*n + global_k] + row_k[global_j];
                if(temp < local_mat[local_i*n + global_j])
                    local_mat[local_i*n + global_j] = temp;
            }
        free(row_k);
    }
}
int owner(int k, int p, int n){
    return k/(n/p);
}
void copyRow(int local_mat[],int n, int p, int row_k[], int k){
    int  j;
    int local_k = k % (n/p);
    for(j = 0; j < n; j++ )
        row_k[j] = local_mat[local_k*n + j ];
}


int main(int argc, char* argv[]){
    int n;
    int * local_mat;
    MPI_Comm comm;
    int p, my_rank;

    MPI_INT(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &my_rank);

    if (my_rank == 0){
        printf("How many vertives ? \n");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0 , comm);
    local_mat = malloc(n*n/p*sizeof(int));

    if(my_rank == 0 ) printf("enter the local matrix\n");
    readMatrix(local_mat, n, my_rank, p, comm);
    if(my_rank == 0) printf("we got \n");
    printMatrix(local_mat, n, my_rank, p, comm);
    if(my_rank == 0) printf("\n");

    Floyd(local_mat, n, my_rank, p, comm);
    if(my_rank==0) printf("The solution is: \n");
    printMatrix(local_mat, n, my_rank, p , comm);
    free(local_mat);
    MPI_Finalize();
    return 0;

}
