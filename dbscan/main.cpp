#include "header.h"
#include "common_qsort.h"
#include "error.h"
#include "Point.h"
#include "DataSet.h"
#include "Dbscan.h"

unsigned int noofclusters;
unsigned int *noofmembers;
unsigned int **members;

void StoreClusters(char *filename)
{
	int i,j;
	FILE *fp;

	fp = fopen(filename,"w");
	if(fp == NULL)
	{
		printf("Unable to open %s for writing.\n");
		return;
	}

	fprintf(fp,"%d\n",noofclusters);
	for(i=0;i<noofclusters;i++)
	{
		fprintf(fp,"%d\t",noofmembers[i]);
		for(j=0;j<noofmembers[i];j++)
			fprintf(fp,"%d ",members[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}

main(int argc, char **argv)
{
	DataSet ds;
	int minpts;
	double epsilon;

	time_t start,end;
	char filename[200];

	noofclusters = 0;
	start = clock();

	if(argc != 3)
	{
		printf("Usage: %s <input> <cluster_file>\n",argv[0]);
		exit(0);
	}

	// Initialize data set
	if(!ds.Initialize())
	{
		printf("Error in initializing Data Set\n");
		exit(1);
	}

	// Load the Data Set
	if(!ds.LoadDataSet(argv[1]))
	{
		printf("Unable to load Data Set\n");
		exit(2);
	}

	printf("Enter the min. pts: ");
	scanf("%d", &minpts);

	printf("Enter the epsilon: ");
	scanf("%lf", &epsilon);

	Dbscan db(minpts, epsilon, ds, argv[2]);
/************/
}
