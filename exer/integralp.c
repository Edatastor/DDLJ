// compilation: cc  -lm integral.c
// compilation: icc -lm integral.c
// compilation: icc     integral.c

//calculates integral of a function

// libraries
#include <stdio.h>
#include <math.h>
#include <mpi.h>
// global variable - to be used in main and function f
int exponent=2; // assign exponent of the power function

double f(double x) {
	return pow(x,exponent);
} // end of function

int main(int argc, char *argv[]) {
	int temp,me,nproc,npoints,i,count=0;
	double x,a,b,total,sum=0; // the variable sum is nulled before summation

	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1

	// read input data

		if(me==0){
	printf(" Input number of points for calculation of integral:\n ");
	scanf("%i", &npoints);
	printf(" Input lower/higher bound of integration: \n");
	scanf("%lf", &a);scanf("%lf", &b);
	}
	MPI_Bcast(&npoints,1,MPI_INT,0,MPI_COMM_WORLD); //broadcast the input from thread 0 to all threads
	MPI_Bcast(&a,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(&b,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	//MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);


	// loop over all interior points
	temp=me+1;
	
	for(i=me+1;i<=npoints;i+=nproc) {
		//printf("going in the loop");
		x=a+(i-1)*(b-a)/npoints; // x is the real argument, point where the function is evaluated
		//printf(" a value is %lf i value is %i b value is %lf npoints value is %i x value inside the loop equals %lf for threas %i\n",a,i,b,npoints,x,me);
		sum=sum+f(x);
		
		count+=1;
	}
	
	//printf(" value ofcount is %i by thread %i\n",count,me);
	
	printf(" Sum equals %lf for threas %i\n",sum,me);

	MPI_Allreduce(&sum,&total,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	
	if(me==3){

	

	total=total+(f(a)+f(b))/2; // add first and last points 
	total=total*(b-a)/npoints; // result of integration
	printf(" The integral equals numerically %lf \n",total);
	printf(" The integral equals analytically %lf \n",(pow(b,exponent+1)-pow(a,exponent+1))/(exponent+1));
	}

	return 0;
} // end of main

