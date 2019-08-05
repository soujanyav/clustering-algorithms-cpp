#ifndef _DATASET_H
#define _DATASET_H

// Header File for DataSet

#include "header.h"
#include "error.h"
#include "Point.h"

class DataSet
{
	private:
                long m_noofpoints;      // no of points in the data set
                long m_noofdims;        // no of dimensions of each point
                Point *m_points;        // points in the data set
                bool m_dmflag; 		// false --> Dont calculate Distance Matrix
                               		// true --> Calculate Distance Matrix
                double **m_distancematrix; // distance matrix size: m_noofpoints X m_noofpoints
                char *m_filename;	// Name of the file from which the data set is loaded
                bool m_imageflag; 	// true if image, else false

		double m_xmax;
		double m_xmin;

		double m_ymax;
		double m_ymin;
                //Image *m_Image;
	public:
		// Constructor
		DataSet();

		bool Initialize(void); // same as the constructor

		bool LoadDataSet(char *); // Load data set from the file
		bool LoadImageDataSet(char *); // Load Image data from the file
					       // TO BE DONE
		bool CalculateDistanceMatrix(void); // Method to calculate distance matrix

		// Print Methods
		bool Print(void);
		bool PrintDistanceMatrix(void);

		// Get Methods
		long GetNoOfPoints(void);
		long GetNoOfDimensions(void);
		Point& GetPoint(long);
		bool GetDMFlag(void);
		double GetDM(long,long);
		void GetDistanceFromPoint(long index, double ans[]);
		char* GetFileName(void);
		bool GetImageFlag(void);

		double GetXMax();
		double GetXMin();
		double GetYMax();
		double GetYMin();
		// Destructor
		~DataSet();
};

#endif
