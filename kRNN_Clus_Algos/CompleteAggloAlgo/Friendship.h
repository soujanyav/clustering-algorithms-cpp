#ifndef _FRIENDS_H
#define _FRIENDS_H

#include "header.h"
#include "error.h"
#include "Point.h"
#include "DataSet.h"

class Friendship
{
	private:
		//unsigned int count; // gives the size of m_noofindvmembers
		// typically count should be k
		unsigned int *m_nooffriendsindegree; // i-th element gives the number of i-th nearest neighbors
		// the degree basically takes values from 0 to k-1
		unsigned int **m_friendsindegree; // [i][j] element gives the j-th element of i-th nearest neighbors
	public:
		Friendship();

		bool Initialize(int k);// have to call this method without fail!

		// I donot think I need this
		// Give entire array
		//bool AddFriends(unsigned int *thismembers,unsigned int noofthismembers);

		// Add this in m_members[rank][m_noofindvmembers[rank]]=value
		bool AddNeighbors(unsigned int rank,unsigned int value);
		bool AddFriendOfThisDegree(unsigned int degree, unsigned int friendly_point);

		unsigned int* GetNoOfFriendsInAllDegrees();
		unsigned int GetNoOfFriendsOfDegree(int index);
		unsigned int** GetAllFriends();
		unsigned int* GetFriendsOfDegree(int index);

		void Destroy(int k);

		~Friendship();
};
#endif
