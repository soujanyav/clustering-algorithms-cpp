#ifndef _POINT_H
#define _POINT_H

/* Header file for Point class
 * */

#include "header.h"
#include "error.h"

class Point
{
	private:
		char *m_name; /* Name of the Point */
		double *m_dims; /* The dimensions of the point */

	public:
		// Constructors
		Point(void); // Void Constructor
		Point(long noofdims); // Constructor with number of dimensions

		bool Initialize(long); // same as the constructor Point(long)

		// Set Methods
		bool SetName(char *);
		bool SetDims(long,double);
		bool SetDims(long,double*);

		// Get Methods
		char* GetName(void);
		double* GetDims(void);
		double GetDims(long);

		// Print Methods
		bool Print(long);
		bool Print(long,long);

		// INLINE METHOD: Method to calculate distance
                //double CalculateDistanceTo(long,Point&);
                double CalculateDistanceTo(long noofdims,Point& p)
                {
                        double ans;
                        {
                                double tmpval;
                                ans = 0.0;
                                for(int i = 0; i < noofdims; i++)
                                {
                                        tmpval = ((this->m_dims[i])-(p.GetDims(i)));
                                        tmpval = tmpval * tmpval;
                                        ans += tmpval;
                                }
                                ans = sqrt(ans);
                        }
                        return ans;
                }

		// Destructor
		~Point();
};

#endif
