#include <stdio.h>
#define LENGTH 200

int main()
{
	int i=0; double number;
	char line[LENGTH];
	double a, a2, a8;


	FILE *fr, *fw;
	
	fr=fopen("table.txt", "r");
	fw=fopen("tableout.txt", "w");
	
	while(1){
		if(fgets(line, LENGTH,fr)==NULL)
			break;
		if(sscanf(line, "%lf",&number)==-1) 
			break;
		
		i++;
		sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf", &a, &a2, &a, &a, &a, &a, &a, &a8);
		fprintf(fw,"%lf %lf\n",a8,a2);
	}
	
	printf("Read %i numbers\n",i);
	
	fclose(fr);
	fclose(fw);
	
	return 0;
}

