// sums.c
// sums and Factorial of first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	
	int i,n, sum=0, me, nproc, total=0, low, high, range, facto=1, totalf;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    if(me==0){
        printf("Program for summing/Factorial first N integer numbers\n");
    	printf("Enter N: ");
    	scanf("%i", &n);
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

	//----------------Dividing Task Between Threads------------------
	range = n / nproc;
    low = me * range + 1;
    high = (me == nproc - 1) ? n : (me + 1) * range;
	//---------------------------------------------------------------

    for(i=0; i<=nproc; i++){
        if(i==me){
            printf("for thread; %i low: %i, high: %i \n",me,low,high);
        }
    } 

    
    for(i=low;i<=high;i=i+1) { 
        printf("for thread %i: values %i \n",me,i);
		sum=sum+i;
		facto = i*facto;
	
	}
    MPI_Reduce(&sum,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&facto,&totalf,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);


	//MPI_Allreduce(&sum,&total,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD); This also works 
	
	if (me == 0){
		printf("Sum of first %i and facatorials integers equals   : %i, %i\n",n,total,totalf);
		printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);
		
	}
	
	
	MPI_Finalize();
	return 0;
}

