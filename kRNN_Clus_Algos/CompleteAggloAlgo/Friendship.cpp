#include "Friendship.h"

Friendship::Friendship()
{
	this->m_nooffriendsindegree = (unsigned int*)malloc(sizeof(unsigned int)*0);
	this->m_friendsindegree = (unsigned int **)malloc(sizeof(unsigned int*)*0);
}

bool Friendship::Initialize(int k)// have to call this method without fail!
{
//	this->count = k;

	this->m_nooffriendsindegree = (unsigned int*)malloc(sizeof(unsigned int)*k);
	if(this->m_nooffriendsindegree == NULL)
	{
		cerr << "Error in memory allocation" << endl;
		return false;
	}

	this->m_friendsindegree = (unsigned int **)malloc(sizeof(unsigned int*)*k);
	if(this->m_friendsindegree == NULL)
	{
		cerr << "Error in memory allocation" << endl;
		return false;
	}

	for(int i = 0; i < k; i ++)
	{
		this->m_nooffriendsindegree[i] = 0;
		this->m_friendsindegree[i] = (unsigned int *) malloc(sizeof(unsigned int)*0);
		if(this->m_friendsindegree[i] == NULL)
		{
			cerr << "Error in memory allocation" << endl;
			return false;
		}
	}
	return true;
}

		// I donot think I need this
		// Give entire array
		//bool AddFriends(unsigned int *thismembers,unsigned int noofthismembers);

		// I think I donot need this too
		// Add this in m_members[rank][m_noofindvmembers[rank]]=value
		// bool Friendship::AddNeighbors(unsigned int rank,unsigned int value);

bool Friendship::AddFriendOfThisDegree(unsigned int degree, unsigned int friendly_point)
{
	// under the assumption that degree takes the value from 0 to k-1
	this->m_friendsindegree[degree] = (unsigned int *)realloc(this->m_friendsindegree[degree], sizeof(unsigned int)*(this->m_nooffriendsindegree[degree]+1));
	if(this->m_friendsindegree[degree] == NULL)
	{
		cerr << "Error in memory allocation" << endl;
		return false;
	}
	this->m_friendsindegree[degree][this->m_nooffriendsindegree[degree]] = friendly_point;
	m_nooffriendsindegree[degree] ++;
	return true;
}

unsigned int* Friendship::GetNoOfFriendsInAllDegrees()
{
	return this->m_nooffriendsindegree;
}

unsigned int Friendship::GetNoOfFriendsOfDegree(int index)
{
	return this->m_nooffriendsindegree[index];
}

unsigned int** Friendship::GetAllFriends()
{
	return this->m_friendsindegree;
}

unsigned int* Friendship::GetFriendsOfDegree(int index)
{
	return this->m_friendsindegree[index];
}

void Friendship::Destroy(int k)
{
	for(int i = 0; i < k; i ++)
	{
		free(this->m_friendsindegree[i]);
		this->m_friendsindegree[i] = NULL;
	}
	free(this->m_nooffriendsindegree);
	this->m_nooffriendsindegree = NULL;
	free(this->m_friendsindegree);
	this->m_friendsindegree = NULL;
}

Friendship::~Friendship()
{
}
