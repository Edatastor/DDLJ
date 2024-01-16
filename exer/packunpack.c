// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int gsize,root,me,nproc,i,sum=0,total,low=0,high,interval,exceed=0, testsum[2];
	int m,n,position;
	float p;
	double q,r;
	char buffer[1000];
	m=1;
	n=2;
	p=1.2;
	q=1.23e10;
	r=0.456;
	position=0;
	int check=0;
	MPI_Status status;

	

	MPI_Init(&argc,&argv); // initialise MPI
	//MPI_Comm comm;
	//MPI_Comm_size( comm, &gsize);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1
	

	if(me==0){
		printf("Initial value of position is %i\n",position);

	 MPI_Pack(&m, 1, MPI_INT, buffer, 110, &position, MPI_COMM_WORLD);
	 printf("Value of position after first pack command is %i\n",position);
	 MPI_Pack(&n, 1, MPI_INT, buffer, 110, &position, MPI_COMM_WORLD);
	 printf("Value of position after second pack command is %i\n",position);
     MPI_Pack(&p, 1, MPI_FLOAT, buffer, 110, &position, MPI_COMM_WORLD);
	 printf("Value of position after third pack command is %i\n",position);
	 MPI_Pack(&q, 1, MPI_DOUBLE, buffer, 110, &position, MPI_COMM_WORLD);
	 printf("Value of position after fourth pack command is %i\n",position);
	 MPI_Pack(&r, 1, MPI_DOUBLE, buffer, 110, &position, MPI_COMM_WORLD);
	 printf("Value of position after fifth pack command is %i\n",position);
	 MPI_Send(buffer, position, MPI_PACKED, 1, 100, MPI_COMM_WORLD);
	 MPI_Send(buffer, position, MPI_PACKED, 2, 100, MPI_COMM_WORLD);
	 MPI_Send(buffer, position, MPI_PACKED, 3, 100, MPI_COMM_WORLD);
	 MPI_Send(testsum, position, MPI_PACKED, 1, 100, MPI_COMM_WORLD);

	 }

	// MPI_Bcast(buffer,1000,MPI_INT,0,MPI_COMM_WORLD);

	 if(me!=0){

		//if (me==2){

		//	sleep(10);
		//}

		//printf("Value of position before first unpack command is %i\n",position);
		
		//if(me!=2){
		 MPI_Recv(buffer, 110, MPI_PACKED, 0, 100, MPI_COMM_WORLD, &status);
		 if(me==1){
		 MPI_Recv(testsum, 110, MPI_PACKED, 0, 100, MPI_COMM_WORLD, &status);
		 }
		//}

	 MPI_Unpack(buffer, 110, &position, &m, 1, MPI_INT, MPI_COMM_WORLD);
	 printf("Value of position before second unpack command is %i\n",position);
	 MPI_Unpack(buffer, 110, &position, &n, 1, MPI_INT, MPI_COMM_WORLD);
	 printf("Value of position before third unpack command is %i\n",position);
	 MPI_Unpack(buffer, 110, &position, &p, 1, MPI_FLOAT, MPI_COMM_WORLD);
	 printf("Value of position before fourth unpack command is %i\n",position);
	 MPI_Unpack(buffer, 110, &position, &q, 1, MPI_DOUBLE, MPI_COMM_WORLD);
	 printf("Value of position before fifth unpack command is %i\n",position);
	 MPI_Unpack(buffer, 110, &position, &r, 1, MPI_DOUBLE, MPI_COMM_WORLD);
	 printf("Value of position after final unpack command is %i\n",position);

	 }
	 if(me==1){
		printf("Value of m is %i\n",m);
		printf("Value of n is %i\n",n);
		printf("Value of p is %.2f\n",p);
		printf("Value of q is %lf\n",q);
		printf("Value of r is %lf\n",r);


	 }








//printf("gather called successfully");




	//MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); //broadcast the input from thread 0 to all threads
	
	

	
	


//	MPI_Allreduce(&sum,&total,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD); //sum the partial sums from threads to total
//	MPI_Allreduce(&prod,&totalprod,1,MPI_DOUBLE,MPI_PROD,MPI_COMM_WORLD); //multiply the partial products from threads to totalprod
//	if(me==0){
//		printf("Sum of first %i integers equals   : %i\n",n,total);
//		printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);
//		printf("value of total is %i\n",total);
//		printf("value of totalprod is %lf\n",totalprod);
//	}

	MPI_Finalize(); // finalize MPI peacefully (the system would kill the processes otherwise)

	return 0;
}

