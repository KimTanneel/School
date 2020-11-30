// BSplineProject.cpp : Defines the entry point for the console application.
//


#include "ayam.h"

/////////////////////////////////////////////////////////////////////////////

/* NOTE

  w (width) = UNum-1
  h (height) = VNum-1
  p : UDegree = UOrder - 1
  q : VDegree = VOrder - 1
  P : array of control point SIZE = 3 or 4

 */

/////////////////////////////////////////////////////////////////////////////

void libAyamGlobalInterpolation4D()
{
	int UTess = 9;
	int UNum = UTess;		// So dinh dieu khien cua B-spline Curve
	int UDegree = 2;	// Bac cua B-spline Curve
	int UKnotCount, i, p;
	double *D = NULL;
	double *UKnot = NULL;
				
//	if (D != NULL) { delete D; D = NULL;}

	D = (double*)calloc(UTess*4, sizeof(double));	
	p = 0;     D[p+0]=  0.0;  D[p+1]= 0.5042; D[p+2]= 0.0; D[p+3]= 1.0;		
	p = p + 4; D[p+0]= 10.0;  D[p+1]= 0.3145; D[p+2]= 0.0; D[p+3]= 1.0;		
	p = p + 4; D[p+0]= 30.0;  D[p+1]= 0.2379; D[p+2]= 0.0; D[p+3]= 1.0;
	p = p + 4; D[p+0]= 50.0;  D[p+1]= 0.2017; D[p+2]= 0.0; D[p+3]= 1.0;
	p = p + 4; D[p+0]= 100.0; D[p+1]= 0.2268; D[p+2]= 0.0; D[p+3]= 1.0;	
	p = p + 4; D[p+0]= 300.0; D[p+1]= 0.1696; D[p+2]= 0.0; D[p+3]= 1.0;
	p = p + 4; D[p+0]= 500.0; D[p+1]= 0.1552; D[p+2]= 0.0; D[p+3]= 1.0;
	p = p + 4; D[p+0]= 1000.0; D[p+1]= 0.1232; D[p+2]= 0.0; D[p+3]= 1.0;
	p = p + 4; D[p+0]= 1500.0; D[p+1]= 0.1127; D[p+2]= 0.0; D[p+3]= 1.0;

	double *T = NULL; 
	T = (double*)calloc(UTess, sizeof(double));
	
	T[0] = 0.0;
	T[1] = 187.5;
	T[2] = 375.0;
	T[3] = 562.5;
	T[4] = 750.0;
	T[5] = 937.5;
	T[6] = 1125.0;
	T[7] = 1312.5;
	T[8] = 1500.0;
			
	if (UKnot != NULL) { delete UKnot; UKnot = NULL;}
	UKnotCount = UNum + UDegree + 1;
	UKnot = (double*)calloc(UKnotCount, sizeof(double));
	
	UKnot[0] = 0.0;
	UKnot[1] = 0.0;
	UKnot[2] = 0.0; 	
	UKnot[3] = 281.25;
	UKnot[4] = 468.75;
	UKnot[5] = 656.25;
	UKnot[6] = 843.75;
	UKnot[7] = 1031.25;
	UKnot[8] = 1218.75;
	UKnot[9] = 1500.0;
	UKnot[10] = 1500.0;
	UKnot[11] = 1500.0;
				
    ay_nb_GlobalInterpolation4D(UTess-1, D, T, UKnot, UDegree);
	// int ay_nb_GlobalInterpolation4D(int n, double *Q, double *ub, double *Uc, int d) (NURBS++)
	// interpolate the n+1 4D points in Q[] with n+1 precalculated parametric values in ub[]
	// and n+d+1 knots in Uc[] with desired degree d (d <= n!)
	
	printf("+ KET QUA TAI TAO\n");
	printf("* UNum = %d, UDegree = %d\n", UNum, UDegree);
	printf("* Vecto nut UKnot = { ");
	for (i=0; i < UKnotCount; i++) printf("%0.2f, ", UKnot[i]); printf("\b\b}\n"); 

	printf("* Cac dinh dieu khien: \n");
	p = 0;
	for (i=0; i<UNum; i++) //UNum = UTess
	{ 	
		printf("P[%d](x, y, z) = (%.3f, %.3f, %.3f)\n", i, D[p+0], D[p+1], D[p+2]);
		p = p + 4;
	}

	delete []D;
	delete []T;
	delete []UKnot;
}
int main(int argc, char* argv[])
{
	printf("         PARAMETERIZATION METHOD ON B-SPLINE CURVE\n\n");

	////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("\n>> Tai tao B-spline Curve theo phuong phap Global Interpolation\n");
	libAyamGlobalInterpolation4D();

	////////////////////////////////////////////////////////////////////////////////////////////////
	
	return 0;
	exit(0);
}

