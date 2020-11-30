// BSplineProject.cpp : Defines the entry point for the console application.
//


#include "ayam.h"

/////////////////////////////////////////////////////////////////////////////

/** NOTE

  w (width) = UNum-1
  h (height) = VNum-1
  p : UDegree = UOrder - 1
  q : VDegree = VOrder - 1
  P : array of control point SIZE = 3 or 4

 */

/////////////////////////////////////////////////////////////////////////////

void libAyamBasicFunction(int UNum, int UDegree, double u, double *UKnot)
{
  int span, i, k;
  double *N = NULL;
  
  
  printf("* C(u = %.2f): UNum = %d, bac p = %d, UKnot = {", u, UNum, UDegree);
  for (i = 0; i < (UNum + UDegree + 1); i++) printf("%0.2f, ", UKnot[i]); printf("\b\b}\n"); 
  
  int flag = 1;
	  
  for(k = 1; k <= UDegree; k++)
  {
	  if (N!=NULL) { delete []N; N = NULL; } 
	  N = (double*)calloc(UNum-1+UDegree-k, sizeof(double));
	  	
	  span = ay_nb_FindSpan(UNum, k, u, UKnot);
	  ay_nb_BasisFuns(span, u, k, UKnot, N);
	  
	//double Nip;
    //ay_nb_OneBasisFun(UDgree, UNum+UDgree, UKnot, span, u, Nip) 
	  
	  if (flag > 0) { printf("\n span = %d\n", span); flag = 0; };
	  for(i = 0; i <= (UNum-1+UDegree-k); i++)
	  {
	    printf(" N[%d,%d](%0.2f) = %.3f\n", i, k, u, N[i]);
  	   
	//  printf("  (u-u[i])/(u[i+k]-u[i])*N[i,k-1](u) + (u[i+k+1]-u)/(u[i+k+1]-u[i+1])*N[i+1,k-1](u)",  i, i, k, i, k,  i, k, i, i, k, i, i, k);
  	    if (k > 0) 
		{
		  	printf("\t= (u-u[%d])/(u[%d+%d]-u[%d])*N[%d,%d-1](u)+(u[%d+%d+1]-u)/(u[%d+%d+1]-u[%d])*N[%d+1,%d-1](u)\n",  
			               i,      i, k,    i,     i, k,          i, k,          i, k,      i,     i,   k);
  	 	  	printf("\t= (u-u[%d])/(u[%d]-u[%d])*N[%d,%d](u)+(u[%d]-u)/(u[%d]-u[%d])*N[%d,%d](u)\n",  
				           i,     i+k,   i,    i, k-1,      i+k+1,    i+k+1,  i,  i+1,k-1);
  	 	  	printf("\t= (u-%0.3f)/%0.3f*N[%d,%d](u)+(%0.3f-u)/%0.3f*N[%d,%d](u)\n\n",  
				         UKnot[i], UKnot[i+k]-UKnot[i], i, k-1,     UKnot[i+k+1],   UKnot[i+k+1]-UKnot[i+1],  i+1,k-1);			
	    }
		else printf("  [u[%d], u[%d+1])\n", i, i);
 
  	  }
  	  printf("\n");
  }
  free(N);
}

void libAyamCurveTesselate(int UNum, int UDegree, double *UKnot, double *m_cv3, int UTess, double* &D)
{
	if (D!=NULL) { delete []D; D = NULL; }
	D = (double*)calloc(UTess*3, sizeof(double));

	double *C=NULL; 		
	C = (double*)calloc(3, sizeof(double));

	int p = 0;
	double d = 1.0/(UTess - 1);
	double u = 0.0;
	
	printf("+ TAP DIEM DU LIEU D\n");
	for (int i=0; i<UTess; i++)
	{ 
	    ay_nb_CurvePoint3D(UNum-1, UDegree, UKnot, m_cv3, u, C);
		D[p+0] = C[0];
		D[p+1] = C[1];
		D[p+2] = C[2];	
		
	    printf("* u = %.2f, D[%d](x, y, z) = (%.2f, %.2f, %.2f)\n", u, i, D[p+0], D[p+1], D[p+2]);

		p = p + 3;
		u = u + d;
	}
		
	delete []C;
}

void libAyamCurvePoint4D(int UNum, int UDegree, double *UKnot, double *m_cv4, double u)
{
	double *C = NULL; 		
	C = (double*)calloc(4, sizeof(double));

	int ay_status = ay_nb_CurvePoint4D(UNum-1, UDegree, UKnot, m_cv4, u, C);
	printf("* C(%.2f)(x, y, z) = (%.2f, %.2f, %.2f)\n", u, C[0], C[1], C[2]);
	
	delete []C;
}

void libAyamCurvePoint3D(int UNum, int UDegree, double *UKnot, double *m_cv3, double u)
{
	double *C=NULL; 		
	C = (double*)calloc(3, sizeof(double));
 	int ay_status = ay_nb_CurvePoint3D(UNum-1, UDegree, UKnot, m_cv3, u, C);
	printf("* C(%.2f)(x, y, z) = (%.2f, %.2f, %.2f)\n", u, C[0], C[1], C[2]);
	delete []C;
}

void libAyamCurveLeastSquaresApproximation4D(int UNum, int UDegree, int UTess, double *D)
{
	int i, p;
	double *m_cv4 = NULL;
	double *UKnot = NULL;

    int ay_status = ay_act_leastSquares(D, UTess, UNum, UDegree, &UKnot, &m_cv4);
	
	printf("+ KET QUA TAI TAO B-spline Curve\n");
	printf("* UNum = %d, UDegree = %d\n", UNum, UDegree);
	printf("* Vecto nut UKnot = { ");
	for (i=0; i < (UNum + UDegree + 1); i++) printf("%0.2f, ", UKnot[i]); printf("\b\b}\n"); 

	printf("* Cac dinh dieu khien P[i]]: \n");
	p = 0;
	for (i=0; i<UNum; i++)
	{ 	
		printf("  P[%d] (x, y, z, w) = (%.2f, %.2f, %.2f, %.2f)\n", i, m_cv4[p+0], m_cv4[p+1], m_cv4[p+2], m_cv4[p+3]);
		p = p + 4;
	}

	delete []m_cv4;
}

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

// Minh hoa vi du trang 169 GTMHH
void libAyamCubicNonUniformBasicFuns(double u)
{
	int	UNum = 8;
 	int UDegree = 3;
	int i;
	
	double *UKnot = NULL;
	int UKnotCount = UNum + UDegree + 1;
	UKnot = (double*)malloc(UKnotCount * sizeof(double));  	
	
 	UKnot[0] = 0.0f;
	UKnot[1] = 0.0f;
	UKnot[2] = 0.0f;
	UKnot[3] = 0.0f;
	
	UKnot[4] = 1.0f;
	UKnot[5] = 2.0f;
	UKnot[6] = 3.0f;
	UKnot[7] = 4.0f;
	
	UKnot[8] = 5.0f;
	UKnot[9] = 5.0f;
    UKnot[10] = 5.0f;
    UKnot[11] = 5.0f;

	for (i=0; i<=(UNum-1 + UDegree-3); i++) printf(" N[%d,3](%0.1f) = %.3f\n", i, u, NUBasicFuns(i, u, UKnot)); 
	printf("\n");
	
	delete []UKnot;
}

int main(int argc, char* argv[])
{
	printf("         PARAMETERIZATION METHOD ON B-SPLINE CURVE\n\n");

	////////////////////////////////////////////////////////////////////////////////////////////////
	
	int i, p;
	int UNum; 		// So dinh dieu khien cua B-spline Curve
	int UDegree;	// Bac cua B-spline Curve
	int UKnotCount;
	int UTess;

	double *m_cv3 = NULL; // Dinh dieu khien 3D
	double *m_cv4 = NULL; // Dinh dieu khien 4D
	double *D = NULL; 
	double *UKnot = NULL; // Vector nut co UKnotCount phan tu
	double u;
/*
  // Vi du trang 169 GTMHH  (Noi suy duong cong)
	UNum = 8; UDegree = 3;
	UKnotCount = UNum + UDegree + 1;
	UKnot = (double*)calloc(UKnotCount, sizeof(double));
	
	UKnot[0] = 0.0f;
	UKnot[1] = 0.0f;
	UKnot[2] = 0.0f;
	UKnot[3] = 0.0f;
	
	UKnot[4] = 1.0f;
	UKnot[5] = 2.0f;
	UKnot[6] = 3.0f;
	UKnot[7] = 4.0f;
	
	UKnot[8] = 5.0f;
	UKnot[9] = 5.0f;
    UKnot[10] = 5.0f;
    UKnot[11] = 5.0f;
    
    u = 2.0f;
 */

/*
	UNum = 8; UDegree = 3;
	UKnotCount = UNum + UDegree + 1;
	UKnot = (double*)calloc(UKnotCount, sizeof(double));
	
 	UKnot[0] = 0.0f;
	UKnot[1] = 1.0f;
	UKnot[2] = 2.0f;
	UKnot[3] = 3.0f;	
	UKnot[4] = 4.0f;
	UKnot[5] = 5.0f;
	UKnot[6] = 6.0f;
	UKnot[7] = 7.0f;
	UKnot[8] = 8.0f;
	UKnot[9] = 9.0f;
    UKnot[10] = 10.0f;
    UKnot[11] = 11.0f;
*/


    // Vi du 3.20 page 82 GTMHH
	UNum = 4; UDegree = 2;
	UKnotCount = UNum + UDegree + 1;
	UKnot = (double*)calloc(UKnotCount, sizeof(double));
	
	UKnot[0] = 0.0f; 
	UKnot[1] = 0.0f;
	UKnot[2] = 0.0f;
	UKnot[3] = 0.5f;
	UKnot[4] = 1.0f;
	UKnot[5] = 1.0f;
	UKnot[6] = 1.0f;
	
	u = 0.45f;

 
/*
    // Vi du 2.3 page 68 The NURBS Book
	UNum = 8; UDegree = 2;
	UKnotCount = UNum + UDegree + 1;
	UKnot = (double*)calloc(UKnotCount, sizeof(double));
	
	UKnot[0] = 0.0f; 
	UKnot[1] = 0.0f;
	UKnot[2] = 0.0f;
	UKnot[3] = 1.0f;
	UKnot[4] = 2.0f;
	UKnot[5] = 3.0f;
	UKnot[6] = 4.0f;
	UKnot[7] = 4.0f;
	UKnot[8] = 5.0f;
	UKnot[9] = 5.0f;
	UKnot[10] = 5.0f;
	
	u = 2.5f;
 */
 		
	// Ma tran dinh dieu khien P 3D
	if (m_cv3 != NULL) { delete m_cv3; m_cv3 = NULL;}
	m_cv3 = (double*)calloc(UNum*3, sizeof(double));
	
	p = 0;     m_cv3[p+0]=  0.0f; m_cv3[p+1]= 10.0f; m_cv3[p+2]= 0.0f;	//P0
	p = p + 3; m_cv3[p+0]= 10.0f; m_cv3[p+1]= 40.0f; m_cv3[p+2]= 0.0f;	//P1
	p = p + 3; m_cv3[p+0]= 40.0f; m_cv3[p+1]= 40.0f; m_cv3[p+2]= 0.0f;	//P2
	p = p + 3; m_cv3[p+0]= 50.0f; m_cv3[p+1]=  0.0f; m_cv3[p+2]= 0.0f;	//P3

/*
	p = p + 3; m_cv3[p+0]= 60.0f; m_cv3[p+1]=  20.0f; m_cv3[p+2]= 0.0f;	//P4	
	p = p + 3; m_cv3[p+0]= 70.0f; m_cv3[p+1]=  50.0f; m_cv3[p+2]= 0.0f;	//P5
	p = p + 3; m_cv3[p+0]= 80.0f; m_cv3[p+1]=  30.0f; m_cv3[p+2]= 0.0f;	//P6
	p = p + 3; m_cv3[p+0]= 85.0f; m_cv3[p+1]=  75.0f; m_cv3[p+2]= 0.0f;	//P7
 */
 	
	// Ma tran dinh dieu khien P 4D
	if (m_cv4 != NULL) { delete m_cv4; m_cv4 = NULL;}
	m_cv4 = (double*)calloc(UNum*4, sizeof(double));
	
	p = 0;     m_cv4[p+0]=  0.0f; m_cv4[p+1]= 10.0f; m_cv4[p+2]= 0.0f; m_cv4[p+3]= 1.0f;		
	p = p + 4; m_cv4[p+0]= 10.0f; m_cv4[p+1]= 40.0f; m_cv4[p+2]= 0.0f; m_cv4[p+3]= 1.0f;		
	p = p + 4; m_cv4[p+0]= 40.0f; m_cv4[p+1]= 40.0f; m_cv4[p+2]= 0.0f; m_cv4[p+3]= 1.0f;
	p = p + 4; m_cv4[p+0]= 50.0f; m_cv4[p+1]=  0.0f; m_cv4[p+2]= 0.0f; m_cv4[p+3]= 1.0f;	

	////////////////////////////////////////////////////////////////////////////////////////////////
	
/*
 	double t; i = 0; t = 1.0;
	printf("N%d,3(%0.1f) = %.3f\n", i, t, CUBasicFuns(i, t)); 
 */	
 	printf(">> Tinh gia trinh ham Ni,k(u)) tai tham so u\n");
//	u = 0.45f;
	libAyamBasicFunction(UNum, UDegree, u, UKnot);

	printf("\n>> Tinh gia tri cua basic function B-spline cubic tai tham so u\n");
//	libAyamCubicNonUniformBasicFuns(u);
	
	printf("\n>> Xac dinh toa do cua mot diem 3D (x, y, z) tren B-spline Curve tai tham so u\n");
//	u = 0.45;
	libAyamCurvePoint3D(UNum, UDegree, UKnot, m_cv3, u);
		
	printf("\n>> Xac dinh toa do cua mot diem 4D (x, y, z, w) tren B-spline Curve tai tham so u\n");
//	libAyamCurvePoint4D(UNum, UDegree, UKnot, m_cv4, u);
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	// ay_act_leastSquares(double *Q, int m, int n, int p, double **U, double **P) 
	// approximate the data points in <Q[m>] with a NURBS curve of degree <p> with <n> control points, return results in <U> and <P>
	
	printf("\n>> Tai tao B-spline Curve theo phuong phap least squares\n");
	UTess = 7;
//  libAyamCurveTesselate(UNum, UDegree, UKnot, m_cv3, UTess, D);  

	UNum = 5;	// Tai tao duong cong moi co 5 dinh dieu khien
	UDegree = 2; // Duong cong moi bac = 2
//	libAyamCurveLeastSquaresApproximation4D(UNum, UDegree, UTess, D);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// ay_nb_GlobalInterpolation4D(int n, double *Q, double *ub, double *Uc, int d) (NURBS++)
	// interpolate the n+1 4D points in Q[] with n+1 precalculated parametric values in ub[]
	// and n+d+1 knots in Uc[] with desired degree d (d <= n!)
	 
	printf("\n>> Tai tao B-spline Curve theo phuong phap Global Interpolation\n");
//	libAyamGlobalInterpolation4D();

	////////////////////////////////////////////////////////////////////////////////////////////////

	delete []m_cv4;
	delete []D;
	delete []UKnot;
	delete []m_cv3;
	
	return 0;
}

