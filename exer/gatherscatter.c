// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int gsize,root,me,nproc,i,n,sum=0,total,low=0,high,interval,exceed=0;
	double source[10],dest[40],dest1[40],scaaray[40],desscaaray[10];
	

	MPI_Init(&argc,&argv); // initialise MPI
	//MPI_Comm comm;
	//MPI_Comm_size( comm, &gsize);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1

for (i=0;i<10;i++){
	source[i]=(((i+1)*100)+(me*10))/100.0;
}

for (i=0;i<10;i++){
//printf("%lf for thread %i\n",source[i],me);
}



	//MPI_Allreduce(&prod,&totalprod,1,MPI_DOUBLE,MPI_PROD,MPI_COMM_WORLD);
	MPI_Gather(&source,10,MPI_DOUBLE,&dest,10,MPI_DOUBLE,0,MPI_COMM_WORLD);



//printf("gather called successfully");

if (me==0)
{

for (i=0;i<40;i++){
printf("%lf for thread %i\n",dest[i],me);
}

}

MPI_Gather(&source[0],1,MPI_DOUBLE,&dest1[0],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[1],1,MPI_DOUBLE,&dest1[4],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[2],1,MPI_DOUBLE,&dest1[8],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[3],1,MPI_DOUBLE,&dest1[12],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[4],1,MPI_DOUBLE,&dest1[16],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[5],1,MPI_DOUBLE,&dest1[20],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[6],1,MPI_DOUBLE,&dest1[24],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[7],1,MPI_DOUBLE,&dest1[28],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[8],1,MPI_DOUBLE,&dest1[32],1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Gather(&source[9],1,MPI_DOUBLE,&dest1[36],1,MPI_DOUBLE,0,MPI_COMM_WORLD);


if (me==0)
{

for (i=0;i<40;i++){
//printf("%lf for thread %i\n",dest1[i],me);
}

}
if (me==0)
{
for (i=0;i<=40;i++){
	scaaray[i]=(i+1)*0.1;
}

for (i=0;i<40;i++){
//printf("%lf for thread %i\n",scaaray[i],me);
}
}

MPI_Scatter(&scaaray[0],10,MPI_DOUBLE,desscaaray,10,MPI_DOUBLE,0,MPI_COMM_WORLD);

if (me==0)
{
	for (i=0;i<10;i++){
//printf("recieved value %lf for thread %i\n",desscaaray[i],me);
}
}

if (me==1)
{
	for (i=0;i<10;i++){
//printf("recieved value %lf for thread %i\n",desscaaray[i],me);
}
}

if (me==2)
{
	for (i=0;i<10;i++){
//printf("recieved value %lf for thread %i\n",desscaaray[i],me);
}
}

if (me==3)
{
	for (i=0;i<10;i++){
//printf("recieved value %lf for thread %i\n",desscaaray[i],me);
}
}


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

