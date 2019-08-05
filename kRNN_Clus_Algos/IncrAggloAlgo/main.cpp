#include "header.h"
#include "common_qsort.h"
#include "error.h"
#include "Point.h"
#include "DataSet.h"
#include "Friendship.h"
#include "MyKBestFriends.h"

/*
unsigned int noofclusters;
unsigned int *noofmembers;
unsigned int **members;
unsigned int *cluster_gravity;
*/

main(int argc, char **argv)
{
	DataSet ds;
	MyKBestFriends bestfrs;
	int k;
	time_t start,end;
	unsigned int bfsordfs;
	int stopflag;
	char nextiterflag;
	int tempcnt;
	char filename[200];
	char dirname[200];
	char summary_file[200];
	char outlier_file[200];
	double alpha;

	//noofclusters = 0;
	start = clock();

	if(argc != 6)
	{
		printf("Usage: %s <input> <target_directory> <kvalue> <startk> <alpha>\n",argv[0]);
		// a.out (0), input(1), dirname(2), kvalue(3), startingk(4), alpha(5)
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

	k = atoi(argv[3]);
	/*
	if(k > 250)
	{
		printf("Too large k value\n");
		exit(0);
	}
	*/

        /* ONLY FOR THE FIRST TIME TO STORE FRIENDS IN FILES*/
        bestfrs.FindFriends(ds, k);
        bestfrs.BuildFriendship(ds);

	tempcnt = atoi(argv[4]);
	alpha = atof(argv[5]);

	sprintf(summary_file, "mkdir %s", argv[2]);
	system(summary_file);

	sprintf(summary_file,"%s/summary.txt",argv[2]);
	bestfrs.SetSummaryFpOpen(summary_file);
	sprintf(outlier_file,"%s/outlier",argv[2]);
	bestfrs.SetOutlierFile(outlier_file);

	bestfrs.FormClusters(ds, tempcnt);
	bestfrs.ExecuteHierarchical(ds, argv[2], alpha);

	bestfrs.SetSummaryFpClose();
}
