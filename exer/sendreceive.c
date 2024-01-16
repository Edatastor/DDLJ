#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{

    int i, nproc, n, me, local_sum=0, total_sum=0, low, high;
    const int TAG =0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    if(me==0)
    {
        printf("Enter N number to print sum: \n"); scanf("%i",&n);
    }
    
    /*
    
    if(me!=0)
    {
        for(i=1; i<=nproc; i++)
        {
            MPI_Send(n,1,MPI_INT,i,TAG,MPI_COMM_WORLD);
        }     
    }
    */

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    low = 1 + (n/nproc)*me;
    high = (me == nproc - 1) ? n : (me + 1) * (n / nproc);


    for(i=low; i<=high; i++)
    {
        local_sum=local_sum+i;
    }

    if(me==0)
    {
        total_sum=local_sum;       
        for(i=1; i< nproc; i++)
        {
            
            MPI_Recv(&local_sum,1,MPI_INT,MPI_ANY_SOURCE,TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            total_sum=local_sum+total_sum;
        }
        printf("Total sum of N number is %i : \n",total_sum);
    }
    else
    {
        MPI_Send(&local_sum,1,MPI_INT,0,TAG,MPI_COMM_WORLD);      
    }

    MPI_Finalize();

}