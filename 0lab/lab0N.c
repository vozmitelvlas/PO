#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char* argv[]){ 
    int ProcNum, ProcRank, RecvRank; 
    MPI_Status Status;
    double start, end;

    MPI_Init(&argc, &argv); 

    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum); 
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); 

    start = MPI_Wtime();
    if (ProcRank == 0){ // Действия, выполняемые только процессом с рангом 0 
        printf("\n Hello from process %3d", ProcRank); 
        for (int i = 1; i < ProcNum; i++){ 
                MPI_Recv(&RecvRank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
                printf("\n Hello from process %3d", RecvRank); 
        } 
    } else // Сообщение, отправляемое всеми процессами, // кроме процесса с рангом 0 
        MPI_Send(&ProcRank,1,MPI_INT,0,0,MPI_COMM_WORLD); 

    end = MPI_Wtime();
    MPI_Finalize();
    printf("%.4f ms, process №%d\n", (end-start)*1000, ProcRank);

    return 0; 
    }
