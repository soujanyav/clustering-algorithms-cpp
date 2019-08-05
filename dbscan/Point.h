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
			double lk = 2;
                        {
                                double tmpval;
                                ans = 0.0;
                                for(int i = 0; i < noofdims; i++)
                                {
					//lk-norm
					tmpval = pow(fabs(this->m_dims[i]-p.GetDims(i)), lk);
					ans += tmpval;
					/*
					// euclidean l2
                                        tmpval = fabs((this->m_dims[i])-(p.GetDims(i)));
                                        tmpval = tmpval * tmpval;
                                        ans += tmpval;
					*/

					/*
					 // manhat l1
                                        tmpval = fabs((this->m_dims[i])-(p.GetDims(i)));
                                        ans += tmpval;
					*/
					

/*
					 // chebyshev linf
                                        tmpval = fabs((this->m_dims[i])-(p.GetDims(i)));
					if(ans < tmpval)
						ans = tmpval;

*/

					/*
					// l3-norm
					tmpval = pow(fabs(this->m_dims[i]-p.GetDims(i)), 3.0);
					ans += tmpval;
					*/
					
					/*
					// l4-norm
					tmpval = pow(fabs(this->m_dims[i]-p.GetDims(i)), 4.0);
					ans += tmpval;
					*/

					// l5-norm
					/*
					tmpval = pow(fabs(this->m_dims[i]-p.GetDims(i)), 5.0);
					ans += tmpval;
					*/
                                }
				// lknorm
				ans = pow(ans, 1.0/lk);

				// euclidean
                                //ans = sqrt(ans);

				// l3-norm
				//ans = pow(ans, 1.0/3.0);

				// l4-norm
				//ans = pow(ans, 1.0/4.0);
				
				// l5-norm
				//ans = pow(ans, 1.0/5.0);

				//manhattan
				// do nothing

				//chebyshev
				// do nothing
                        }
                        return ans;
                }

		// Destructor
		~Point();
};

#endif
