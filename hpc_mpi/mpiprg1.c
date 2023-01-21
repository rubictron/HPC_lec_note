#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
int numtasks, rank, dest, source, rc, count, tag=1;
char inmsg, outmsg='x';
MPI_Status Stat;
int num = -1;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if (rank == 0) {
  dest = 1;
  source = 1;
  rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);

  printf("Inmsg:%c at rank %d rc %d\n",inmsg,rank,rc);
  }

else if (rank == 1) {
  dest = 0;
  source = 0;
  outmsg = 'y';
  num = 2;
  rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
  rc = MPI_Send(&num, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);


  printf("Inmsg:%c at rank %d rc %d\n",inmsg,rank,rc);
  }

  printf("num %d",num);

MPI_Finalize();
printf("Number of task %d \n",numtasks);
}