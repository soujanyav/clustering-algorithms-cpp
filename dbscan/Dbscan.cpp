#include "Dbscan.h"

Dbscan::Dbscan()
{
	// do nothing
}

Dbscan::Dbscan(int minpts, double epsilon, DataSet& ds, char *clusfile)
{
	printf("Minpts: %d\tEpsilon: %lf\n", minpts, epsilon);
	this->neighbors = (int *)malloc(sizeof(int)*ds.GetNoOfPoints());
	this->ptstatus = (int *)malloc(sizeof(int)*ds.GetNoOfPoints());
	this->clusids = (int *)malloc(sizeof(int)*ds.GetNoOfPoints());

	this->num_neighbors = 0;
	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		this->ptstatus[i] = -2;
		this->neighbors[i] = -1;
	}
	this->clusterid = 0;

	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		if(this->ptstatus[i] == -2)
			FormClusters(i, epsilon, minpts, ds);
	}

	FILE *fp;
	FILE *cfp; // check cluster file
	printf("Cluster file is %s\n", clusfile);
	fp = fopen(clusfile, "w");
	
	if(fp == NULL)
		printf("file opening problem\n");

	cfp = fopen("check.txt", "w");
	if(cfp == NULL)
		printf("error while opening file check.txt\n");

	fprintf(fp, "%d\n", this->clusterid);
	int cluspoints = 0;

	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
		this->clusids[i] = -1;

	for(int j = 0; j < this->clusterid; j ++)
	{
		int num = 0;
		int minelement = INT_MAX;
		for(int i = 0; i < ds.GetNoOfPoints(); i ++)
		{
			if(this->ptstatus[i] == j)
			{
				num ++;
				if(minelement > i)
					minelement = i;
			}
		}
		printf("Minelement for cluster %d is %d\n", j, minelement); 

		cluspoints += num;
		fprintf(fp, "%d ", num);
		for(int i = 0; i < ds.GetNoOfPoints(); i ++)
		{
			//this->clusids[i] = -1;
			if(this->ptstatus[i] == j)
			{
				this->clusids[i] = minelement;
				fprintf(fp, "%d ", i);
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		fprintf(cfp, "%d\n", this->clusids[i]);
	}
	fclose(cfp);
	cfp = fopen("noise.txt", "w");
	for(int i = 0; i < ds.GetNoOfPoints(); i ++)
	{
		if(this->clusids[i] == -1)
			fprintf(cfp, "%lf %lf\n", ds.GetPoint(i).GetDims(0), ds.GetPoint(i).GetDims(1));
	}
	fclose(cfp);

	printf("No of clusters = %d\n", this->clusterid);
	printf("No of clustered points = %d\n", cluspoints);
	printf("No of noise points = %d\n", ds.GetNoOfPoints()-cluspoints);
}

int Dbscan::GetNeighborhood(int ptindex, double epsilon, int *neighbors, DataSet& ds)
{
	int num = 0;
	int noofpoints = ds.GetNoOfPoints();

	for(int i = 0; i < noofpoints; i ++)
	{
		if( (this->ptstatus[i] == -2) && ds.GetDM(ptindex, i) < epsilon)
		{
			num ++;
			neighbors[num-1] = i;
		}
	}
	return num;
}

void Dbscan::FormClusters(int ptindex, double epsilon, int minpts, DataSet& ds)
{
	int noofneighbors;
	int newneighbors[ds.GetNoOfPoints()];

	noofneighbors = GetNeighborhood(ptindex, epsilon, this->neighbors, ds);
	if(noofneighbors < minpts)
	{
		this->ptstatus[ptindex] = -1; // noise point
		return;
	}

	this->ptstatus[ptindex] = this->clusterid;
	for(int i = 0; i < noofneighbors; i ++)
	{
		this->ptstatus[this->neighbors[i]] = this->clusterid;
		int newnum = GetNeighborhood(this->neighbors[i], epsilon, newneighbors, ds);
		if(newnum > minpts)
		{
			for(int j = 0; j < newnum; j ++)
			{
				if(this->ptstatus[newneighbors[j]] == -1)
				{
					this->ptstatus[newneighbors[j]] = this->clusterid;
				}
				else if(this->ptstatus[newneighbors[j]] == -2)
				{
					this->ptstatus[newneighbors[j]] = this->clusterid;
					this->neighbors[noofneighbors] = newneighbors[j];
					noofneighbors ++;
				}
			}
		}
	}
	this->clusterid ++;
}

bool Dbscan::Initialize(void)
{
}

Dbscan::~Dbscan()
{

}
