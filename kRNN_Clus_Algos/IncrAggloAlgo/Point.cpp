#include "Point.h"

// Void Constructor
Point::Point()
{
	this->m_name = NULL;
	this->m_dims = NULL;
}

// Constructor where memory is allocated for dimensions
Point::Point(long noofdims)
{
	this->m_name = NULL;

	// Allocate memory for dimensions
	this->m_dims = (double*)malloc(sizeof(double)*noofdims);
	if(this->m_dims == NULL)
		Error(ERROR_MEMORY,"Point::Point(noofdims)");
}

// Constructor where memory is allocated for dimensions
bool Point::Initialize(long noofdims)
{
	this->m_name = NULL;

	// Allocate memory for dimensions
	this->m_dims = (double*)malloc(sizeof(double)*noofdims);
	if(this->m_dims == NULL)
	{
		Error(ERROR_MEMORY,"Point::Point(noofdims)");
		return false;
	}

	return true;
}

// Method to Set Name
bool Point::SetName(char *name)
{
	this->m_name = (char*)malloc(sizeof(char)*(strlen(name)+1));

	if(this->m_name == NULL)
	{
		Error(ERROR_MEMORY,"Point::SetName(char*)");
		return false;
	}
	
	strcpy(this->m_name,name);
	return true;
}

// Method to Set One Dimension
bool Point::SetDims(long index,double value)
{
	this->m_dims[index] = value;
	return true;
}

// Method to Set Dimensions
bool Point::SetDims(long noofdims,double* values)
{
	if(this->m_dims == NULL)
	{
		this->m_dims = (double*)malloc(sizeof(double)*noofdims);
	}

	if(this->m_dims == NULL)
	{
		Error(ERROR_MEMORY,"Point::SetDims(long,double*)");
		return false;
	}

	for(int i=0; i<noofdims; i++)
		this->m_dims[i] = values[i];

	return true;
	
}

// Method to get name of the point
char* Point::GetName(void)
{
	return this->m_name;
}

// Method to get dimensions of the point
double* Point::GetDims(void)
{
	return this->m_dims;
}

// Method to get ONE dimension of the point
double Point::GetDims(long index)
{
	return this->m_dims[index];
}

// Print Methods
bool Point::Print(long noofdims)
{
	cout << this->m_name << " ";
	for(int i=0; i<noofdims; i++)
	{
		cout << this->m_dims[i];
		if(i != noofdims-1)
			cout << " ";
	}
	cout << "\n";

	return true;
}

bool Point::Print(long noofdims,long index)
{
	cout << this->m_dims[index] << "\n";
	return true;
}

// Destructor
Point::~Point()
{
	if(this->m_name != NULL)
	{
		free(this->m_name);
		this->m_name = NULL;
	}

	if(this->m_dims != NULL)
	{
		free(this->m_dims);
		this->m_dims = NULL;
	}
}
