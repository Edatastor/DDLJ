//ordered.c in ~predota/pp/openmp
#include<omp.h>
#include<stdio.h>
#define LENGTH 200
int main(){
	int n;
	
	printf("input number of parallel threads \n");scanf("%i",&n);

	#pragma omp parallel num_threads(n)
	{
		FILE *fa, *fw;
		int me = omp_get_thread_num();
		printf("A by thread %i\n",me);
		
		#pragma omp for ordered
		for(int i=1;i<=omp_get_num_threads();i++)
		{	 
			printf("B by thread %i\n",me);
			
			#pragma omp ordered
			{   
				printf("ORDERED by thread %i\n",me);
			}
			#pragma omp ordered
			{   
				if (me==0)
				{
				fw=fopen("write.txt", "w");
				
				}
				if (me!=0)
				{
				fw=fopen("write.txt", "a");
				}
				if (me==0)
				{
			fprintf(fw,"Line added by thread %i\n",me);				
				}
				if (me!=0)
				{
				fprintf(fw,"Line appended by thread %i\n",me);
				}
				
			}
			#pragma omp ordered
			{
				if (me==0)
				{
				fclose(fw);
				}
				if (me!=0)
				{
				fclose(fw);;
				}
			}
			printf("C by thread %i\n",me);
		}
		printf("D by thread %i\n",me);
	}
	return 0;
}
