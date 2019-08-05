#ifndef _DBSCAN_H
#define _DBSCAN_H

// Header File for DataSet

#include "header.h"
#include "error.h"
#include "Point.h"
#include "DataSet.h"

class Dbscan
{
	private:
		int *neighbors;
		int *ptstatus;
		int *clusids;
		int clusterid;
		int num_neighbors;

	public:
		// Constructor
		Dbscan();
		Dbscan(int minpts, double epsilon, DataSet& ds, char* file);
		int GetNeighborhood(int ptindex, double epsilon, int *neighbors, DataSet& ds);
		void FormClusters(int ptindex, double epsilon, int minpts, DataSet& ds);

		bool Initialize(void); // same as the constructor

		~Dbscan();
};

#endif
