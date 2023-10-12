#include "mpi.h"
#include <time.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
        int ProcNum, ProcRank, RecvRank;
        double start, end;
        MPI_Status Status;

        MPI_Init(&argc, &argv);
        start = MPI_Wtime();
        MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
        MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

        if (ProcRank != 0) {
                MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        else if(ProcRank == 0){
                printf("Hello from process %3d\n", ProcRank);
                for(int i=1; i<ProcNum; i++){
                        MPI_Recv(&RecvRank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
                        printf("Hello from process %3d\n", RecvRank);
                }
        }
        end = MPI_Wtime();
        MPI_Finalize();
        printf("-----Time - %.4f ms, process №%d\n", (end-start)*1000, ProcRank);

        return 0;
}
