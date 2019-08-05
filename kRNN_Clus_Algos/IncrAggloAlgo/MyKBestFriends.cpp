#include "MyKBestFriends.h"

double temp;
#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
unsigned long tempindex;
#define SWPINDEX(a,b) tempindex=(a);(a)=(b);(b)=tempindex;

void quickSort(double* numbers, int* index,int array_size);

int dfs_time; //for dfs & connected components

MyKBestFriends::MyKBestFriends()
{
	this->m_k = 0;
	this->m_indvfriends = NULL;
	this->m_noOfClusters = 0;
	this->m_noOfMembersInClusters = NULL;
	this->m_membersInClusters = NULL;
	this->m_finishedtimesinDFS = NULL;
	this->m_scratchpad = NULL;
	this->m_kiter = 0;
	this->GraphTranspose = NULL;
}

		// Same as constructor
bool MyKBestFriends::Initialize() // Have to call this without fail!
{
	this->m_k = 0;
	this->m_indvfriends = NULL;	
	this->m_noOfClusters = 0;
	this->m_noOfMembersInClusters = NULL;
	this->m_membersInClusters = NULL;
	this->m_scratchpad = NULL;
	this->m_kiter = 0;
	this->m_finishedtimesinDFS = NULL;
	this->GraphTranspose = NULL;
}

bool MyKBestFriends::FindFriends(DataSet& ds,unsigned int thisk)
{
        this->m_k = thisk;
	this->m_kiter = 1;
	this->m_scratchpad = (bool *)malloc(sizeof(bool)*ds.GetNoOfPoints());
	if(this->m_scratchpad == NULL)
	{
		cerr << "Error in mem. allocation in FindFriends" << endl;
		return false;
	}
	
	this->m_finishedtimesinDFS = (unsigned int *)malloc(sizeof(unsigned int)*ds.GetNoOfPoints());
	if(this->m_finishedtimesinDFS == NULL)
	{
		cerr << "Error in mem. allocation in FindFriends" << endl;
		return false;
	}

	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
		this->m_finishedtimesinDFS[i] = 0;

	this->m_noOfClusters = 0;

	this->m_noOfMembersInClusters = (unsigned int *)malloc(sizeof(unsigned int));
	if(this->m_noOfMembersInClusters == NULL)
	{
		cerr << "Error in mem. allocation in FindFriends" << endl;
		return false;
	}

	this->m_membersInClusters = (int *)malloc(sizeof(int)*ds.GetNoOfPoints());
	if(this->m_membersInClusters == NULL)
	{
		cerr << "Error in mem. allocation in FindFriends" << endl;
		return false;
	}
	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
		this->m_membersInClusters[i] = -1;

        this->m_indvfriends = (Friendship*)malloc( sizeof(Friendship)*(ds.GetNoOfPoints()) );
        if(this->m_indvfriends == NULL)
        {
                cerr << "Error in memory allocation for the k-Nearest Neighbours" << endl;
                return false;
        }

        for(unsigned int i=0; i<ds.GetNoOfPoints(); i++)
	{
		if(!this->m_indvfriends[i].Initialize(this->m_k))
			return false;
	}

	this->GraphTranspose = (int **)malloc(sizeof(int*)*ds.GetNoOfPoints());
	if(this->GraphTranspose == NULL)
	{
		cerr << "Error in mem. allocation in FindFriends" << endl;
		return false;
	}
	for(int i=0; i < ds.GetNoOfPoints(); i++)
	{
		this->GraphTranspose[i] = (int*)malloc(sizeof(int)*this->m_k);
		if(this->GraphTranspose[i] == NULL)
		{
			cerr << "Error in mem. allocation in FindFriends" << endl;
			return false;
		}
	}

        return true;
}

bool MyKBestFriends::BuildFriendship(DataSet& ds)
{
        // for finding the top k friends

        unsigned long i, ir, j, l, mid, a_index;
	unsigned int noofpoints = ds.GetNoOfPoints();
        double a, temp;
        double *arr;
	double *sorted_arr;
	unsigned long *arr_index;
	int *sortedarr_index;

        arr = (double *)malloc(sizeof(double)*(noofpoints));
        arr_index = (unsigned long*)malloc(sizeof(unsigned long)*(noofpoints));
        sorted_arr = (double *)malloc(sizeof(double)*(this->m_k));
        sortedarr_index = (int *)malloc(sizeof(int)*(this->m_k));

	for(int index = 0; index < noofpoints; index ++)
	{
		ds.GetDistanceFromPoint(index, arr);

		for(i = 0; i < noofpoints; i ++)
		{
			arr_index[i] = i;
		}
		l = 0;
		ir = noofpoints-1;
		for(;;)
		{
			if(ir <= l+1)
			{
				if(ir == l+1 && arr[ir] < arr[l])
				{
					SWAP(arr[l], arr[ir]);
					SWPINDEX(arr_index[l], arr_index[ir]);
				}
				break;
			}
			else
			{
				mid=(l+ir) >> 1;
				SWAP(arr[mid],arr[l+1]);
				SWPINDEX(arr_index[mid], arr_index[l+1]);

				if (arr[l] > arr[ir])
				{
					SWAP(arr[l],arr[ir]);
					SWPINDEX(arr_index[l], arr_index[ir]);
				}
				if (arr[l+1] > arr[ir])
				{
					SWAP(arr[l+1],arr[ir]);
					SWPINDEX(arr_index[l+1], arr_index[ir]);
				}
				if (arr[l] > arr[l+1])
				{
					SWAP(arr[l],arr[l+1]);
					SWPINDEX(arr_index[l], arr_index[l+1]);
				}
				i=l+1; // Initialize pointers for partitioning.
				j=ir;
				a=arr[l+1]; //Partitioning element.
				a_index = arr_index[l+1];
				for (;;)
				{ 
					//Beginning of innermost loop.
					do i++; while (arr[i] < a); 
						//Scan up to ^Lnd element > a.
					do j--; while (arr[j] > a); 
						//Scan down to ^Lnd element < a.
					if (j < i) break; 
						//Pointers crossed. Partitioning complete.
					SWAP(arr[i],arr[j]);
					SWPINDEX(arr_index[i], arr_index[j]);
				} 
				//End of innermost loop.
				arr[l+1]=arr[j]; //Insert partitioning element.
				arr[j]=a;

				arr_index[l+1] = arr_index[j];
				arr_index[j] = a_index;

				if (j >= this->m_k) ir=j-1; 
					//Keep active the partition that contains the kth element.
				if (j <= this->m_k) l=i;
			}
		}
		for(i = 0; i < this->m_k; i ++)
		{
			sorted_arr[i] = arr[i];
			sortedarr_index[i] = (int)arr_index[i];
		}	
		quickSort(sorted_arr, sortedarr_index,this->m_k);

		for(i = 0; i < this->m_k ; i ++)
		{
                        if(!this->m_indvfriends[(unsigned long)sortedarr_index[i]].AddFriendOfThisDegree(i, index))
	                                return false;
                        else
	                                this->GraphTranspose[index][i] = sortedarr_index[i];
		}
	}

	free(sorted_arr);
	sorted_arr = NULL;
	free(sortedarr_index);
	sortedarr_index = NULL;

	free(arr);
	arr = NULL;
	free(arr_index);
	arr_index = NULL;
}

bool MyKBestFriends::FindSCC_Part1(unsigned int point, unsigned int kvalue, DataSet& ds, unsigned int **finishtime)
{	
	int i, j, k;
	unsigned int *friends;
	unsigned int nooffriends;
	bool isPresent;

	if(kvalue > this->m_k)
		kvalue = this->m_k;

	this->m_membersInClusters[point] = this->m_noOfClusters;
	this->m_noOfMembersInClusters[this->m_noOfClusters] ++;
	dfs_time ++;

	this->m_scratchpad[point] = true;

	for(i = 0; i < kvalue; i ++)
	{
		nooffriends = this->m_indvfriends[point].GetNoOfFriendsOfDegree(i);
		if(nooffriends == 0)
			continue;
		friends = this->m_indvfriends[point].GetFriendsOfDegree(i);
		for(j = 0; j < nooffriends; j ++)
		{
			if(this->m_scratchpad[friends[j]] == false)
				FindSCC_Part1(friends[j], kvalue, ds, finishtime);
		}
	}
	dfs_time++;
	(*finishtime)[point] = dfs_time;
	return true;
}

bool MyKBestFriends::FindSCC_Part2(unsigned int point, DataSet& ds, unsigned int **finishtime, int kvalue)
{	
	int i, j, k;
	bool isPresent;
	int noofpoints = ds.GetNoOfPoints();

	this->m_membersInClusters[point] = this->m_noOfClusters;
	this->m_noOfMembersInClusters[this->m_noOfClusters] ++;
	dfs_time ++;
	
	this->m_scratchpad[point] = true;

	for(i = 0; i < kvalue; i ++)
	{
		if(this->m_scratchpad[this->GraphTranspose[point][i]] == false)
			FindSCC_Part2(this->GraphTranspose[point][i], ds, finishtime, kvalue);
	}
	dfs_time++;
	(*finishtime)[point] = dfs_time;
	return true;
}

bool MyKBestFriends::FormClusters(DataSet& ds, unsigned int kvalue)
{
	int i, j;
	char outlierfile[256];
	FILE *fp;
	int tempcnt;
	int friends_count;

	if(kvalue > this->m_k)
	{
		cerr << "Error kvalue more than " << this->m_k << " !!!" << endl;
		return false;
	}
	this->m_kiter = kvalue;

	sprintf(outlierfile, "%s_%d.txt", this->m_outlier_file, this->m_kiter);
	fp = fopen(outlierfile,"w");
	tempcnt = 0;
	for(i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		friends_count = 0;
		for(j = 0; j < kvalue; j ++)
			friends_count += this->m_indvfriends[i].GetNoOfFriendsOfDegree(j);
		if(friends_count < kvalue) 
		{
			fprintf(fp,"%d\n",i);
			this->m_scratchpad[i] = true; // outlier
			tempcnt++;
		}
		else
			this->m_scratchpad[i] = false; // not visited yet
	}
	fprintf(fp,"No Of Outliers: %d\n",tempcnt);
	fprintf(this->m_summary_fp,"No Of Outliers at k=%d : %d\n", this->m_kiter, tempcnt);
	fclose(fp);

	this->m_noOfClusters = 0;
	dfs_time = 0;

	for(i = 0; i < ds.GetNoOfPoints(); i++)
	{
		if(this->m_scratchpad[i] == false)
		{
			this->m_noOfMembersInClusters = (unsigned int *)realloc(this->m_noOfMembersInClusters, sizeof(unsigned int)*(this->m_noOfClusters+1));
			if(this->m_noOfMembersInClusters == NULL)
				printf("Error!!!\n");
			this->m_noOfMembersInClusters[this->m_noOfClusters] = 0;

			dfs_time = 0;
			this->FindSCC_Part1(i, kvalue, ds, &(this->m_finishedtimesinDFS));
			this->m_noOfClusters ++;
		}
	}

	/// Freeing up cluster memory
	for(i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		this->m_membersInClusters[i] = -1;
	}
	free(this->m_noOfMembersInClusters);
	this->m_noOfMembersInClusters = NULL;

	// Re-Initializing the variables

	this->m_noOfMembersInClusters = (unsigned int *)malloc(sizeof(unsigned int));
	this->m_noOfClusters = 0;

	dfs_time = 0;

	int* arr_index;
	double* sorted_arr;
	arr_index = (int *)malloc(sizeof(int)*ds.GetNoOfPoints());
	sorted_arr = (double *)malloc(sizeof(double)*ds.GetNoOfPoints());
	for(i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		this->m_scratchpad[i] = false;
		arr_index[i] = i;
		sorted_arr[i] = (double)this->m_finishedtimesinDFS[i];
	}
	quickSort(sorted_arr, arr_index, ds.GetNoOfPoints());

	/* to eliminate outliers again */
	tempcnt = 0;
	for(i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		friends_count = 0;
		for(j = 0; j < kvalue; j ++)
			friends_count += this->m_indvfriends[i].GetNoOfFriendsOfDegree(j);
		if(friends_count < kvalue) 
			// we should have atleast kvalue-1 friends
		{
			this->m_scratchpad[i] = true; // outlier
			tempcnt++;
		}
		else
			this->m_scratchpad[i] = false; // not visited yet
	}

	for(i = 0; i < ds.GetNoOfPoints(); i ++)
		this->m_finishedtimesinDFS[i] = 0;

	// After having them sorted, take the last point and start
	for(i = ds.GetNoOfPoints()-1; i >= 0 ; i --)
	{
		if(this->m_scratchpad[arr_index[i]] == false)
		{
			this->m_noOfMembersInClusters = (unsigned int *)realloc(this->m_noOfMembersInClusters, sizeof(unsigned int)*(this->m_noOfClusters+1));
			if(this->m_noOfMembersInClusters == NULL)
				printf("Error!!!\n");
			this->m_noOfMembersInClusters[this->m_noOfClusters] = 0;
			FindSCC_Part2(arr_index[i], ds, &(this->m_finishedtimesinDFS), kvalue); 
			this->m_noOfClusters ++;
		}
	}
	free(sorted_arr);
	sorted_arr = NULL;
	free(arr_index);
	arr_index = NULL;
	fprintf(this->m_summary_fp, "Total number of clusters formed with k=%d : %d\n", kvalue, this->m_noOfClusters);

	return true;
}

/*
unsigned int MyKBestFriends::getKValue(int index)
{
        int tmparray[this->m_k];
                                                                             
        for(int i = 0; i < this->m_k; i ++)
        {
                tmparray[i] = this->m_indvfriends[index].GetNoOfFriendsOfDegree(i);
        }
                                                                             
        int run, prevrun, end_index;
        int flag;
        prevrun = 0;
        for(int i = 0; i < this->m_k; i ++)
        {
                flag = 1;
                run = 0;
                while(tmparray[i] == 0)
                {
                        flag = 0;
                        i ++;
                        run ++;
                }
                if(run > prevrun)
                {
                        if(flag == 0)
                        {
                                end_index = i-run;
                                prevrun = run;
                        }
                }
        }
        //printf("End index is %d\n", end_index);
        return end_index;
}
*/


bool MyKBestFriends::ExecuteHierarchical(DataSet& ds, char* dirname, float alpha)
{
	
	char filename[128];
	FILE *levelinfofp;
	int level=1;
	int fromitoj, fromjtoi;

	sprintf(filename, "mkdir %s/levels", dirname);
	system(filename);
	sprintf(filename, "mkdir %s/clusters", dirname);
	system(filename);

	sprintf(filename, "%s/levels/info.txt", dirname);
	levelinfofp = fopen(filename, "w");

		//int **clussim;
		unsigned int *friends;
		unsigned int nooffriends;
		//int *checked;
		//int noofchecked=0;
		int *clusvalues;
		unsigned int* frlist;

	for(int min = 1; min <= this->m_k; min ++)
	{
		level = min;
		sprintf(filename, "%s/levels/level%d.txt", dirname, level);
		FILE *fp;
		fp = fopen(filename, "w");
		fprintf(fp, "%d\n", this->m_noOfClusters);
		for(int i = 0; i < this->m_noOfClusters; i ++)
		{
			int cnt = 0;
			for(int j = 0; j < ds.GetNoOfPoints(); j ++)
			{
				if(this->m_membersInClusters[j] == i)
					cnt ++;
			}
			fprintf(fp, "%d\t", cnt);
			for(int j = 0; j < ds.GetNoOfPoints(); j ++)
			{
				if(this->m_membersInClusters[j] == i)
					fprintf(fp, "%d ", j);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		fprintf(levelinfofp, "Level %d, kvalue %d\n", level, this->m_kiter);
		fprintf(this->m_summary_fp, "At level %d, value of k=%d\n", level, this->m_kiter);

		if(ds.GetNoOfDimensions() == 2)
		{
			sprintf(filename, "rm -f %s/clusters/*.txt", dirname);
			system(filename);

			FILE *newfp;
			FILE *commandfp;
			sprintf(filename, "%s/command.sh", dirname);
			commandfp = fopen(filename, "w");

			fprintf(commandfp, "set term png\n");
			fprintf(commandfp, "set output \"%s/level%d.png\"\n", dirname, level);
			fprintf(commandfp, "set title \"Agglomerative level=%d\"\n", level);
			fprintf(commandfp, "show title\n");
			fprintf(commandfp, "set nokey;\n");

			int cnt=0;

			for(int i = 0;i < this->m_noOfClusters;i ++)
			{
				sprintf(filename, "%s/clusters/cluster_%d.txt", dirname, i);
				newfp = fopen(filename, "w");
				if(cnt == 0)
				{
					fprintf(commandfp, "plot '%s'", filename);
					cnt ++;
				}
				else
					fprintf(commandfp, ", '%s' ", filename);

				for(int j=0; j < ds.GetNoOfPoints(); j++)
					if(this->m_membersInClusters[j] == i)
						fprintf(newfp, "%lf\t%lf\n", ds.GetPoint(j).GetDims(0), ds.GetPoint(j).GetDims(1));
				fclose(newfp);
			}
			fprintf(commandfp, ";\n");
			fclose(commandfp);
			sprintf(filename, "gnuplot < %s/command.sh", dirname);
			system(filename);
		}
		
		if(this->m_noOfMembersInClusters != NULL)
		{
			free(this->m_noOfMembersInClusters);
			this->m_noOfMembersInClusters = NULL;
		}

		this->m_noOfClusters = 0;
		this->m_noOfMembersInClusters = (unsigned int *)malloc(sizeof(int));
		if(this->m_noOfMembersInClusters == NULL)
		{
			cerr << "Error in mem. allocation in FindFriends" << endl;
			return false;
		}
		for(int i = 0; i < ds.GetNoOfPoints(); i ++)
			this->m_membersInClusters[i] = -1;

		if(min > this->m_k)
			break;
		FormClusters(ds, min);

		clusvalues = (int *)malloc(sizeof(int)*this->m_noOfClusters);
		int outcnt=0;
		for(int i = 0; i < ds.GetNoOfPoints(); i ++)
		{
			for(int j = 0; j < this->m_noOfClusters; j ++)
				clusvalues[j] = 0;
			if(this->m_membersInClusters[i] == -1) // it is an outlier
			{
				//int end_index = getKValue(i);
				int end_index = min;
				for(int j = 0; j < end_index; j ++)
				{
					nooffriends = this->m_indvfriends[i].GetNoOfFriendsOfDegree(j);
					frlist = this->m_indvfriends[i].GetFriendsOfDegree(j);
					for(int l = 0; l < nooffriends; l ++)
					{
						if(this->m_membersInClusters[frlist[l]] != -1)
							clusvalues[this->m_membersInClusters[frlist[l]]] ++;
					}
				}
				int maxindex=0;
				for(int l = 1; l < this->m_noOfClusters; l ++)
				{
					if(clusvalues[maxindex] < clusvalues[l])
						maxindex = l;
				}
				if(clusvalues[maxindex] > (float)end_index*alpha)
				{
					this->m_membersInClusters[i] = maxindex;
					outcnt ++;
				}
			}
		}
		fprintf(this->m_summary_fp, "No of local outliers incorporated: %d\n", outcnt);

		free(clusvalues);
		clusvalues = NULL;

		level ++;
	}
	fclose(levelinfofp);
}

unsigned int MyKBestFriends::GetNoOfClusters()
{
	return this->m_noOfClusters;
}

unsigned int* MyKBestFriends::GetNoOfMembersInClusters()
{
	return this->m_noOfMembersInClusters;
}

unsigned int* MyKBestFriends::GetMembersInClusters()
{
	return NULL;
	//return this->m_membersInClusters;
}

unsigned int* MyKBestFriends::GetGravity()
{
	return NULL;
	//return this->m_gravity;
}

// Set Functions
bool MyKBestFriends::SetK(unsigned int thisk)
{
        this->m_k = thisk;
}

bool MyKBestFriends::SetOutlierFile(char *filename)
{
	strcpy(this->m_outlier_file,filename);
	return true;
}
		
bool MyKBestFriends::SetSummaryFpOpen(char *filename)
{
	this->m_summary_fp = fopen(filename,"w");
	if(this->m_summary_fp == NULL)
	{
		printf("file is %s\n", filename);
		printf("Couldn't open summary file\n");
		return false;
	}
	return true;
}

bool MyKBestFriends::SetSummaryFpClose()
{
	fclose(this->m_summary_fp);
	return true;
}

// Get Functions
Friendship* MyKBestFriends::GetMyFriends()
{
        return this->m_indvfriends;
}

Friendship MyKBestFriends::GetMyIthFriend(int i)
{
        return this->m_indvfriends[i];
}
	
unsigned int MyKBestFriends::GetK()
{
        return this->m_k;
}

void MyKBestFriends::PrintFriends(DataSet& ds)
{
	unsigned int *friends;
	int nooffriends;
	int noofpoints = ds.GetNoOfPoints();
	fflush(stdout);
	for(int i = 0; i < noofpoints; i ++)
	{
		printf("%d\n", i);
		for(int j = 0; j < this->m_k; j ++)
		{
			printf( "Point %d degree %d ", i , j) ;
			friends = this->m_indvfriends[i].GetFriendsOfDegree(j);
			nooffriends = this->m_indvfriends[i].GetNoOfFriendsOfDegree(j);
			for(int k = 0; k < nooffriends; k ++)
				printf(" %d", friends[k]);
			printf("\n");
		}
	}
}

void MyKBestFriends::PrintGraphTranspose(DataSet& ds)
{
	cout << "Printing Graph Transpose" << endl;
	long noofpts;
	noofpts = ds.GetNoOfPoints();
	for(int i=0; i<noofpts; i++)
	{
		for(int j=0; j<this->m_k; j++)
			cout << this->GraphTranspose[i][j] << "  ";
		cout << endl;
	}

}
		
void MyKBestFriends::Destroy(DataSet& ds)
{
	int noofpoints = ds.GetNoOfPoints();
	if(this->m_indvfriends != NULL)
	{
		for(int i = 0; i < noofpoints; i ++)
		{
			this->m_indvfriends[i].Destroy(this->m_k);
		}
		free(this->m_indvfriends);
		this->m_indvfriends = NULL;
	}
}
		// Destructor
MyKBestFriends::~MyKBestFriends()
{
        if(this->m_indvfriends != NULL)
        {
                free(this->m_indvfriends);
                this->m_indvfriends = NULL;
        }
}
