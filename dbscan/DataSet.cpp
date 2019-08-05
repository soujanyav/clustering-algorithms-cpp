#include "DataSet.h"

// Constructor
DataSet::DataSet()
{
	this->m_noofpoints = this->m_noofdims = -1;
	this->m_points = NULL;
	this->m_dmflag = false;
	this->m_distancematrix = NULL;
	this->m_filename = NULL;
	this->m_imageflag = false;

	this->m_xmax = -DBL_MAX;
	this->m_xmin = DBL_MAX;
	this->m_ymax = -DBL_MAX;
	this->m_ymin = DBL_MAX;
}

bool DataSet::Initialize(void)
{	
	this->m_noofpoints = this->m_noofdims = -1;
	this->m_points = NULL;
	this->m_dmflag = false;
	this->m_distancematrix = NULL;
	this->m_filename = NULL;
	this->m_imageflag = false;

	this->m_xmax = -DBL_MAX;
	this->m_xmin = DBL_MAX;
	this->m_ymax = -DBL_MAX;
	this->m_ymin = DBL_MAX;

	return true;
}

bool DataSet::LoadDataSet(char *filename)
{
	cout << "Loading the Data Set\n";

	time_t v_start,v_end;

	v_start = clock();
	// Copy the file name
	this->m_filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
	if(this->m_filename == NULL)
	{
		Error(ERROR_MEMORY,"DataSet::LoadDataSet(char*)");
		return false;
	}
	
	strcpy(this->m_filename,filename);

	// Open INSTREAM file
	ifstream infile(filename);
	if( !infile )
	{
		Error(ERROR_FILE_NOT_FOUND,"DataSet::LoadDataSet(char*)");
		return false;
	}

	// Read the number of points and number of dimensions
	infile >> this->m_noofpoints >> this->m_noofdims;

	// Allocate memory for points
	this->m_points = (Point*)malloc(sizeof(Point)*this->m_noofpoints);
	for(int i=0; i<this->m_noofpoints; i++)
		if(!this->m_points[i].Initialize(this->m_noofdims))
		{
			Error(ERROR_UNKNOWN,"DataSet::LoadDataSet(char*)");
			return false;
		}

	// Temporary Variables
	char *v_tempstr;
	double v_tempval;

	v_tempstr = (char*)malloc(sizeof(char)*MAXLEN);
	if(v_tempstr == NULL)
	{
		Error(ERROR_MEMORY,"DataSet::LoadDataSet(char*)");
		return false;
	}

	// Read the Points
        for(int i = 0; i < this->m_noofpoints; i++)
        {
		//cout << "\r" << (double)((double)i*100/(double)this->m_noofpoints) << " \% Completed";
		printf("\r\t%.3f%",(double)((double)i*100/(double)this->m_noofpoints));
		fflush(stdout);

                infile >> v_tempstr;

                this->m_points[i].SetName(v_tempstr);

                for(int j = 0; j < this->m_noofdims; j++)
                {
			if(j == 0)
			{
				if(this->m_xmin > v_tempval)
					this->m_xmin = v_tempval;
				else if(this->m_xmax < v_tempval)
					this->m_xmax = v_tempval;
			}
			if(j == 1)
			{
				if(this->m_ymin > v_tempval)
					this->m_ymin = v_tempval;
				else if(this->m_ymax < v_tempval)
					this->m_ymax = v_tempval;
			}
                        infile >> v_tempval;
                        this->m_points[i].SetDims(j,v_tempval);
                }
        }

	cout << "\n";

        infile.close();

	// Set DM Flag to false: Default
	// Dont Calculate Distance Matrix
	this->m_dmflag = false;
	
	if(v_tempstr != NULL)
	{
		free(v_tempstr);
		v_tempstr = NULL;
	}
	v_end = clock();

	cout << "Max in x " << this->m_xmax << " and min in x is " << this->m_xmin << endl;
	cout << "Max in y " << this->m_ymax << " and min in y is " << this->m_ymin << endl;
	cout << "Time Taken to load the data set: " << (double)((double)(v_end-v_start)/(double)CLOCKS_PER_SEC) << " Sec. \n";

	return true;
}

// TO BE DONE
bool DataSet::LoadImageDataSet(char *)
{
	return true;
}

bool DataSet::CalculateDistanceMatrix(void)
{
	cout << "Calculating the distance matrix\n";

	time_t v_start,v_end;

	v_start = clock();

	// Set the DM flag to true
	this->m_dmflag = true;
	
	// Allocate memory for Distance Matrix
	this->m_distancematrix = (double**)malloc(sizeof(double*)*this->m_noofpoints);
	if(this->m_distancematrix == NULL)
	{
		Error(ERROR_MEMORY,"bool DataSet::CalculateDistanceMatrix()");
		return false;
	}

	for(int i=0; i<this->m_noofpoints; i++)
	{
		this->m_distancematrix[i] = (double*)malloc(sizeof(double)*this->m_noofpoints);
		if(this->m_distancematrix[i] == NULL)
		{
			Error(ERROR_MEMORY,"bool DataSet::CalculateDistanceMatrix()");
			return false;
		}
	}

        for(int i = 0; i < this->m_noofpoints; i++)
        {
		//cout << "\r" << (double)((double)i*100/(double)this->m_noofpoints) << " \% Completed";
		printf("\r\t%.3f%",(double)((double)i*100/(double)this->m_noofpoints));
		fflush(stdout);

                for(int j = 0; j <= i ; j++)
                {
                        if(i == j)
                                this->m_distancematrix[i][j] = 0.0;
                        else
                        {
                                this->m_distancematrix[i][j] = this->m_points[i].CalculateDistanceTo(this->m_noofdims,this->m_points[j]);
                                if(this->m_distancematrix[i][j] < 0.0)
				{
					Error(ERROR_UNKNOWN,"bool DataSet::CalculateDistanceMatrix()");
					return false;
				}
                        }

                }
        }
	cout << "\n";

	v_end = clock();

	cout << "Time Taken to calculate the distance matrix: " << (double)((double)(v_end-v_start)/(double)CLOCKS_PER_SEC) << " Sec.\n";

	return true;
}

bool DataSet::Print(void)
{
        cout << "Printing the points.\n";

        cout << "No Of Points : " << this->m_noofpoints << "\t No Of Dimensions: " << this->m_noofdims << endl;

        for(int i = 0; i < this->m_noofpoints; i++)
                this->m_points[i].Print(this->m_noofdims);

	return true;
}

bool DataSet::PrintDistanceMatrix(void)
{
	time_t v_start,v_end;


	if(this->m_dmflag == true)
	{
		v_start = clock();
		cout << "Printing the distance matrix.\n";
		cout << "Size: " << this->m_noofpoints << " X " << this->m_noofpoints << "\n";

		for(int i = 0; i < this->m_noofpoints; i++)
		{
			for(int j = 0; j < this->m_noofpoints; j++)
				cout << this->GetDM(i,j) << "\t";
			cout << "\n";
		}
		v_end = clock();
		cout << "Time Taken to print the distance matrix: " << (double)((double)(v_end-v_start)/(double)CLOCKS_PER_SEC) << " Sec.\n";
	}
	else
		cout << "Distance matrix not calculated\n";


	return true;
}

long DataSet::GetNoOfPoints(void)
{
	return this->m_noofpoints;
}

long DataSet::GetNoOfDimensions(void)
{
	return this->m_noofdims;
}

Point& DataSet::GetPoint(long index)
{
	return this->m_points[index];
}

bool DataSet::GetDMFlag(void)
{
	return this->m_dmflag;
}

double DataSet::GetDM(long i,long j)
{
        if(m_dmflag == false)
        {
                return this->m_points[i].CalculateDistanceTo(this->m_noofdims,this->m_points[j]);
        }
        else
        {
                if(j <= i)
                        return this->m_distancematrix[i][j];
                else
                        return this->m_distancematrix[j][i];
        }
}

// Returns one row of the distance matrix given the row number
//double* DataSet::GetDistanceFromPoint(long index)
void DataSet::GetDistanceFromPoint(long index, double ans[])
{
	//double *ans;
	//ans = (double*)malloc(sizeof(double)*this->m_noofpoints);

	for(int i=0; i < this->m_noofpoints; i++)
	{
		ans[i] = GetDM(index,i);
		if(index == i)
			ans[i] = DBL_MAX;
	}

	//return ans;
}

double DataSet::GetXMax(void)
{
	return this->m_xmax;
}
double DataSet::GetXMin(void)
{
	return this->m_xmin;
}
double DataSet::GetYMax(void)
{
	return this->m_ymax;
}
double DataSet::GetYMin(void)
{
	return this->m_ymin;
}

char* DataSet::GetFileName(void)
{
	return this->m_filename;
}

bool DataSet::GetImageFlag(void)
{
	return this->m_imageflag;
}

// Destructor
DataSet::~DataSet()
{
	// Free points
	if(this->m_points != NULL)
	{
		free(this->m_points);
		this->m_points = NULL;
	}

	// Free Distance Matrix
	if(this->m_dmflag == true)
	{
		if(this->m_distancematrix != NULL)
		{
			for(int i=0; i<this->m_noofpoints; i++)
				if(this->m_distancematrix[i] != NULL)
				{
					free(this->m_distancematrix[i]);
					this->m_distancematrix[i] = NULL;
				}

			free(this->m_distancematrix);
			this->m_distancematrix = NULL;
		}
	}

	// Free Filename
	if(this->m_filename != NULL)
	{
		free(this->m_filename);
		this->m_filename = NULL;
	}
}
