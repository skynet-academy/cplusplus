#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


int main (int argc, char* argv[]) { 
  double x[100],  TotalSum, ProcSum = 0.0;
  int  ProcRank, ProcNum, N=100, i;
  MPI_Status Status;
  
  //initialization
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD,&ProcNum);
  MPI_Comm_rank (MPI_COMM_WORLD,&ProcRank);
  
  // data preparation
  if ( ProcRank == 0 ) DataInitialization (x,N);
  // data broadcast
  MPI_Bcast (x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  // computing the partial sum on each of the processes
  // vector x elements from i1 to i2 are summed at each process
  int k = N / ProcNum;
  int i1 = k *  ProcRank;
  int i2 = k * ( ProcRank + 1 );

  if ( ProcRank == ProcNum-1 ) i2 = N; 

  for (i = i1; i < i2; i++ )
    ProcSum  = ProcSum + x[i];

  // collecting partial sums on the process 0
  if ( ProcRank == 0 ) {
    TotalSum = ProcSum;

    for (i=1; i < ProcNum; i++ ) {
      MPI_Recv (&ProcSum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &Status);       
      TotalSum = TotalSum + ProcSum;
    }
  }
  else 
    // all the processes send their partial sums 
    MPI_Send (&ProcSum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  
  // result outprint 
  if ( ProcRank == 0 )
    printf ("\nTotal Sum = %10.2f\n",TotalSum);
  
  MPI_Finalize ();
} 
