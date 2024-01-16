// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int me,nproc,i,n,sum=0,total,low=0,high,interval,exceed=0;
	double prod=1,totalprod=0;

	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1

	if(me==0){
		printf("Program for SUMMING first N integer numbers\n ");
		printf("Enter N: ");scanf("%i", &n);
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); //broadcast the input from thread 0 to all threads

	low=1+(me*n)/nproc;
	high=((me+1)*n)/nproc;
	interval=high-low+1;

	printf("for thread %i interval is %i\n",me,interval);
	for(i=low;i<=high;i=i++) { 
		sum=sum+i;
	}

	for(i=low;i<=high;i=i++) { 
		prod=prod*i;
	}

	if (me!=nproc)
	{
		printf("thread %i has the sum value : %i and prod value : %f\n",me,sum,prod);
	}
	
	MPI_Allreduce(&sum,&total,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD); //sum the partial sums from threads to total
	MPI_Allreduce(&prod,&totalprod,1,MPI_DOUBLE,MPI_PROD,MPI_COMM_WORLD); //multiply the partial products from threads to totalprod
	if(me==0){
		printf("Sum of first %i integers equals   : %i\n",n,total);
		printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);
		printf("value of total is %i\n",total);
		printf("value of totalprod is %lf\n",totalprod);
	}

	MPI_Finalize(); // finalize MPI peacefully (the system would kill the processes otherwise)

	return 0;
}

