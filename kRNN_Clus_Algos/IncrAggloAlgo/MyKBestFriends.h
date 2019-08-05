#ifndef _TOP_K_NEIGHBORS_H
#define _TOP_K_NEIGHBORS_H

#include "header.h"
#include "error.h"
#include "DataSet.h"
#include "Friendship.h"

class MyKBestFriends 
{
	private:
		Friendship *m_indvfriends; // number of indvneighbors is number of points
					// denotes the friendship of each point

		unsigned int m_k; // max. value of k

		unsigned int m_noOfClusters; // total no. of clusters
		unsigned int* m_noOfMembersInClusters; // stores the number of members in clusters
		int* m_membersInClusters; // stores in the members in clusters
		unsigned int* m_finishedtimesinDFS; // finished times of each point
		bool* m_scratchpad; // used to make points visited as one
		int** GraphTranspose; // Graph to store the Transpose of G(V,E)
		unsigned int m_kiter; // for k iteration during clustering iteratively

		// for printing purpose only
		FILE *m_summary_fp;
		char m_outlier_file[256];

	public:
		// Constructor
		MyKBestFriends();

		// Same as constructor
		bool Initialize(); // Have to call this without fail!

		/**** METHODS FOR FRIENDS ****/
		bool FindFriends(DataSet& ds,unsigned int thisk);

		bool BuildFriendship(DataSet& ds); 

		bool ExecuteHierarchical(DataSet& ds, char* dirname, float alpha);
		bool FormClusters(DataSet& ds, unsigned int kvalue);
			// Form clusters using strongly connected components approach, using Transpose of G
			// This function calls the below two methods for the same.

		bool FindSCC_Part1(unsigned int point, unsigned int kvalue, DataSet& ds, unsigned int **finishtime);
			// For 1st time dfs on G(V,E) and find the finishing times of vertices

		bool FindSCC_Part2(unsigned int point, DataSet& ds, unsigned int **finishtime, int kvalue);
			// For the 2nd DFS on Transpose of G(V, E) and find strongly connected components


		/**** ACCESS FUNCTIONS ****/
		unsigned int GetNoOfClusters();
		unsigned int* GetNoOfMembersInClusters();
		unsigned int* GetMembersInClusters();
		unsigned int* GetGravity();
		Friendship* GetMyFriends();
		Friendship GetMyIthFriend(int i);
		unsigned int GetK();

		/**** SET FUNCTIONS ****/
		bool SetK(unsigned int thisk);
		bool SetOutlierFile(char *filename);
		bool SetSummaryFpOpen(char *filename);
		bool SetSummaryFpClose();

		
		/**** PRINT FUNCTIONS ****/
		void PrintGraphTranspose(DataSet& ds);
		void PrintFriends(DataSet& ds);
		void Destroy(DataSet& ds);

		~MyKBestFriends();
};

#endif
