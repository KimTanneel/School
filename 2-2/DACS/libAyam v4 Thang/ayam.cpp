  #include <limits.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* act.c */

int ay_nb_LUDecompose(int n, double *A, int *pivot);

int ay_nb_LUInvert(int n, double *inv, int *pivot);

int ay_knots_chordparam(double *Q, int Qlen, int stride, double **U);

int ay_knots_centriparam(double *Q, int Qlen, int stride, double **U);

int ay_nb_GlobalInterpolation4D(int n, double *Q, double *ub, double *Uc, int d);

int ay_act_leastSquares(double *Q, int m, int n, int p, double **U, double **P);

/* nb.c */

double CUBasicFuns(int i, double u);

double NUBasicFuns(int i, double u, double *U);

int ay_nb_FindSpan(int n, int p, double u, double *U);

void ay_nb_BasisFuns(int span, double u, int p, double *U, double *N);

int ay_nb_CurvePoint4D(int n, int p, double *U, double *Pw, double u, double *C);

int ay_nb_CurvePoint3D(int n, int p, double *U, double *P, double u, double *C);

void ay_nb_DersBasisFuns(int i, double u, int p, int n, double *U, double *ders);

void ay_nb_ComputeFirstDer3D(int n, int p, double *U, double *P, double u, double *C1);


#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


/* Definitions */

/* Return/Error Codes */
#define AY_OK          0 /* everything all right */
#define AY_ERROR       2 /* unspecified error */
#define AY_EOMEM       5 /* out of memory */
#define AY_ENULL      50 /* illegal zero pointer encountered */

#define AY_EPSILON 1.0e-06
/* Basic Vector Arithmetic */
#define AY_VLEN(x,y,z) sqrt((x*x)+(y*y)+(z*z))

// #ifdef __cplusplus
}

//#endif /* __cplusplus */
//#endif /* __ayam_h__ */


double CUBasicFuns(int i, double u) 
{
	double b03 = (u-i)*(u-i)*(u-i)/6.0f;
	double b13 = (u-i)*(u-i)*(i+2-u)/6.0f + (u-i)*(i+3-u)*(u-i-1)/6.0f + (i+4-u)*(u-i-1)*(u-i-1)/6.0f;
	double b23 = (u-i)*(i+3-u)*(i+3-u)/6.0f + (i+4-u)*(i+3-u)*(u-i-1)/6.0f +(i+4-u)*(i+4-u)*(u-i-2)/6.0f;
	double b33 = (i+4-u)*(i+4-u)*(i+4-u)/6.0f;
		
	if ((u>=i)&&(u<(i+1))) 	   return b03;
	if ((u>=(i+1))&&(u<(i+2))) return b13;
	if ((u>=(i+2))&&(u<(i+3))) return b23;
	if ((u>=(i+3))&&(u<(i+4))) {return b33;} else return 0.0f;
}

double NUBasicFuns(int i, double u, double *U) 
{
	
	double N03=(u-U[i])* (u-U[i])*(u-U[i])/((U[i+1]-U[i])* (U[i+2]-U[i])* (U[i+3]-U[i]));
	
	double N13=(u-U[i])* (u-U[i])*(U[i+2]-u)/((U[i+2]-U[i])* (U[i+2]-U[i+1])*(U[i+3]-U[i]))
				+(u-U[i])*(U[i+3]-u)*(u-U[i+1])/((U[i+2]-U[i+1])*(U[i+3]-U[i+1])*(U[i+3]-U[i]))
				+ (U[i+4]-u)*(u-U[i+1]) *(u-U[i+1])/((U[i+4]-U[i+1])*(U[i+3]-U[i+1])*(U[i+2]-U[i+1]));
		
	double N23=(u-U[i])*(U[i+3]-u)*(U[i+3]-u)/((U[i+3]-U[i])* (U[i+3]-U[i+1])*(U[i+3]-U[i+2]))
				+(U[i+4]-u)*(U[i+3]-u)*(u-U[i+1])/((U[i+4]-U[i+1])*(U[i+3]-U[i+1])*(U[i+3]-U[i+2]))
				+ (U[i+4]-u)* (U[i+4]-u)*(u-U[i+2])/((U[i+4]-U[i+1])*(U[i+4]-U[i+2])*(U[i+3]-U[i+2]));
		
	double N33=(U[i+4]-u)* (U[i+4]-u)* (U[i+4]-u)/((U[i+4]-U[i+1])*(U[i+4]-U[i+2])*(U[i+4]-U[i+3]));
		
	if  ((U[i]<=u) && (u <U[i+1])) return N03;
	if  ((U[i+1]<=u) && (u <U[i+2])) return N13;
	if  ((U[i+2]<=u) && (u <U[i+3])) return N23;
	if  ((U[i+3]<=u) && (u <U[i+4])) {return N33;}	else return 0.0f;
}

/*
 * ay_nb_FindSpan: (NURBS++)
 * changes to original FindSpan for unclamped splines
 */
int ay_nb_FindSpan(int n, int p, double u, double *U)
{
  int low, mid, high;
  if(u >= U[n]) return n;

  /* never return a span 0-p, because this would make BasisFuns() crash badly */
  if(u <= U[p])  return p;

  /* was:  if(u == U[n+1]) return(n);*/

  low = 0; /* was: low = p; */
  high = n+1;
  mid = (low+high)/2;

  while(u < U[mid] || u >= U[mid+1])
    {
      if(u < U[mid])	high = mid;
      else				low = mid;
      mid = (low+high)/2;
    } /* while */

 return(mid);
} /* ay_nb_FindSpan */


/*
 * ay_nb_BasisFuns: calculate NURBS basis functions for span i, parametric value u, degree p, knot vector U[] in N[p+1]
 */
void ay_nb_BasisFuns(int span, double u, int p, double *U, double *N) //p >= 1
{
 double *left = NULL, *right = NULL, saved, temp;
 int j, r;

  if(!(left = (double*)calloc(p+1, sizeof(double))))   return;
  if(!(right = (double*)calloc(p+1, sizeof(double))))  {free(left); return;}

  N[0] = 1.0;
  
//printf("  + ay_nb_BasisFuns(span = %d, u = %0.2f, p = %d)\n", span, u, p);
  
  for(j=1; j<=p; j++)
  {
      left[j] = u - U[span+1-j]; 
      right[j] = U[span+j] - u;  
      saved = 0.0f;

      for(r=0; r<j; r++)
	  {
	  	temp = N[r] / (right[r+1] + left[j-r]);
	  	N[r] = saved + right[r+1] * temp;
	  	saved = left[j-r] * temp;
	  }
	
      N[j] = saved;
  //  printf("  + ay_nb_BasisFuns(N[%d,%d] = %0.3f)\n", j, p, N[j]);  
  }

  free(left);
  free(right);
  return;
  
} /* ay_nb_BasisFuns */

//m: UKnotCount; i: span
void ay_nb_OneBasisFun(int p, int m, double *U, int i, double u, double Nip) 
{  
	/*  Compute  the  basis  function  Nip  *f/
	/*  Input:  p,m,U,i,u  */
	/*  Output:  Nip  */ 
	
	if  ((i  ==  0  &&  u  ==  U[0])  || (i  ==  m-p-1  &&  u  ==  U[m])) 
	/*  Special  cases  */ 
	{ 
		Nip  =  1.0;  return; 
	} 
	if  (u  < U[i]  ||  u  >=  U[i+p+1])  /*  Local  property  */ 
	{ 
		Nip  =  0.0;  return; 
	} 
	
	double *N=NULL;
	  N = (double*)calloc(p+1, sizeof(double));
	
	int j, k;
	double Uleft, Uright, saved, temp;
	
	for  (j=0;  j<=p;  j++)  /*  Initialize  zeroth-degree  functs  */ 
	if  (u  >=  U[i+j]  &&  u < U[i+j+1])  N[j]  =  1.0; 
	else  N[j]  =  0.0; 
	
	for  (k=1;  k<=p;  k++)  /*  Compute  triangular  table  */ 
	{ 
		if  (N[0]  ==  0.0)  saved  =  0.0; 
		else  saved=  ((u-U[i])*N[0])/(U[i+k]-U[i]); 
		for  (j=0;  j<p-k+1;  j++) 
		{ 
			Uleft  = U[i+j+1]; 
			Uright  = U[i+j+k+1]; 
			if  (N[j+1]  ==  0.0) 
			{ 
				N[j]  =  saved;  saved  =  0.0; 
			} 
			else 
			{ 
				temp=  N[j+1]/(Uright-Uleft); 
				N[j]  =  saved+(Uright-u)*temp; 
				saved  =  (u-Uleft)*temp; 
			} 
		}
	}
	Nip=  N[0]; 
	delete []N;
} 


/*
 * ay_nb_CurvePoint4D:
 */
 
int ay_nb_CurvePoint4D(int n, int p, double *U, double *Pw, double u, double *C)
{
  int span, j, k;
  double *N = NULL, Cw[4] = {0};

  if(!(N = (double*)calloc(p+1, sizeof(double))))   return AY_EOMEM;

  span = ay_nb_FindSpan(n, p, u, U);
  ay_nb_BasisFuns(span, u, p, U, N);

  for(j = 0; j <= p; j++)
    {
      k = (span-p+j)*4;
      Cw[0] = Cw[0] + N[j]*Pw[k];
      Cw[1] = Cw[1] + N[j]*Pw[k+1];
      Cw[2] = Cw[2] + N[j]*Pw[k+2];
      Cw[3] = Cw[3] + N[j]*Pw[k+3];
    }

  for(j = 0; j < 4; j++)   C[j] = Cw[j]/Cw[3];
  free(N);
 return AY_OK;
 
} /* ay_nb_CurvePoint4D */


/*
 * ay_nb_CurvePoint3D:
 */
int ay_nb_CurvePoint3D(int n, int p, double *U, double *P, double u, double *C)
{
 int span, j, k;
 double *N = NULL;

 if(!(N = (double*)calloc(p+1, sizeof(double)))) return AY_EOMEM;

  span = ay_nb_FindSpan(n, p, u, U);
  ay_nb_BasisFuns(span, u, p, U, N);

  C[0] = 0.0;
  C[1] = 0.0;
  C[2] = 0.0;

  for(j = 0; j <= p; j++)
  {
      k = (span-p+j)*3;
      double x = C[0];
      C[0] = C[0] + N[j]*P[k];
      C[1] = C[1] + N[j]*P[k+1];
      C[2] = C[2] + N[j]*P[k+2];
      
      printf("  + ay_nb_CurvePoint3D: C[0] = C[0] + N[%d,%d]*P[%d] = %0.3f + %0.3f*%0.3f\n", j, p, k/3, x, N[j], P[k]);
  }//for
  
  free(N);
  return AY_OK;
} /* ay_nb_CurvePoint3D */


/*
 * ay_nb_DersBasisFuns:
 *
 */
void ay_nb_DersBasisFuns(int i, double u, int p, int n, double *U, double *ders)
{
 double *left = NULL, *right = NULL, *ndu = NULL, *a = NULL, saved, temp, d;
 int j, j1, j2, r, k, rk, pk, s1, s2;

  if(!(left = (double*)calloc(p+1, sizeof(double)))) return;
  if(!(right = (double*)calloc(p+1, sizeof(double))))  			{free(left); return;}
  if(!(ndu = (double*)calloc((p+1)*(p+1), sizeof(double))))  	{free(left); free(right); return;}
  if(!(a = (double*)calloc(2*(p+1), sizeof(double)))) 			{free(left); free(right); free(ndu); return;}

  ndu[0] = 1.0;
  for(j = 1; j <= p; j++)
  {
      left[j] = u - U[i+1-j];
      right[j] = U[i+j] - u;
      saved = 0.0;
      
      for(r = 0; r < j; r++)
	  {
		 ndu[(j)*(p+1) + r] = right[r+1] + left[j-r];
		 temp = ndu[r*(p+1) + (j-1)] / ndu[j*(p+1) + r];
	
		 ndu[r*(p+1) + j] = saved + right[r+1] * temp;
		 saved = left[j-r] * temp;
	  }//for r
	  
      ndu[j*(p+1)+j] = saved;
  } /* for */

  for(j = 0; j <= p; j++) ders[j] = ndu[j*(p+1) + p];
  for(r = 0; r <= p; r++)
  {
    s1 = 0; s2 = 1;
    a[0] = 1.0;
    for(k = 1; k <= n; k++)
	{
	  d = 0.0;
	  rk = r-k; pk = p-k;
	  if(r >= k)
	    {
	      a[s2*(p+1)] = a[s1*(p+1)]/ndu[(pk+1)*(p+1) + rk];
	      d = a[s2*(p+1)]*ndu[rk*(p+1) + pk];
	    }

	  if(rk >= -1)  j1 = 1;
	  else		    j1 = -rk;

	  if(r-1 <= pk)	j2 = k-1;
	  else		    j2 = p-r;

	  for(j = j1; j <= j2; j++)
	  {
	     a[s2*(p+1)+j] = (a[s1*(p+1) + j]-a[s1*(p+1) + (j-1)])/ ndu[(pk+1)*(p+1) + (rk+j)];
	     d += a[s2*(p+1) + j] * ndu[(rk+j)*(p+1) + pk];
	  }

	  if(r <= pk)
	  {
	     a[s2*(p+1) + k] = -a[s1*(p+1) + (k-1)] / ndu[(pk+1)*(p+1) + r];
	     d += a[s2*(p+1) + k] * ndu[r*(p+1) + pk];
	  }
	  ders[k*(p+1)+r] = d;
	  j = s1; s1 = s2; s2 = j;
	} /* for k */
  } /* for r */
  r = p;
  for(k = 1; k <= n; k++)
    {
      for(j = 0; j <= p; j++)  ders[k*(p+1)+j] *= r;
	  r *= (p-k);
    }

  free(left);
  free(right);
  free(ndu);
  free(a);

 return;
} /* ay_nb_DersBasisFuns */


/*
 * ay_nb_ComputeFirstDer3D:
 *
 */
void ay_nb_ComputeFirstDer3D(int n, int p, double *U, double *P, double u, double *C1)
{
 int span = 0, j, r;
 double *nders = NULL;

  if(!(nders = (double*)calloc((p+1) * (p+1), sizeof(double)))) return;
  span = ay_nb_FindSpan(n, p, u, U);
  ay_nb_DersBasisFuns(span, u, p, 1, U, nders);

  C1[0] = 0.0;
  C1[1] = 0.0;
  C1[2] = 0.0;

  for(j = 0; j <= p; j++)
    {
      r = (span-p+j)*3;
      C1[0] = C1[0] + nders[(p+1)+j] * P[r];
      C1[1] = C1[1] + nders[(p+1)+j] * P[r+1];
      C1[2] = C1[2] + nders[(p+1)+j] * P[r+2];
    }

  if(nders) free(nders);

 return;
} /* ay_nb_ComputeFirstDer3D */


/* knots.c */


/* ay_knots_chordparam:
 *  create chordal parameterization in <U[Ulen]> from points in <Q[Qlen]>
 */
int ay_knots_chordparam(double *Q, int Qlen, int stride, double **U)
{
 double t, *vk = NULL, totallen = 0.0, *lens = NULL;
 int i, j;

  if(!Q || !U) return AY_ENULL;

  /* get some memory */
  if(!(vk = (double*)calloc(Qlen, sizeof(double)))) return AY_EOMEM;
  if(!(lens = (double*)calloc(Qlen-1, sizeof(double)))) { free(vk);  return AY_EOMEM; }

  /* compute total length and partial lengths */
  j = 0;
  for(i = 0; i < (Qlen-1); i++)
    {
      lens[i] = AY_VLEN((Q[j+stride] - Q[j]), (Q[j+stride+1] - Q[j+1]), (Q[j+stride+2] - Q[j+2]));
      totallen += lens[i];
      j += stride;
    }

  /* compute the chordal parameterization */
  vk[0] = 0.0;
  j = 0;
  t = 0.0;
  for(i = 1; i < (Qlen-1); i++)
    {
      t += lens[j]/totallen;
      vk[i] = t;
      /*printf("vk[%d]:%f\n",i,t);*/
      j++;
    }
  vk[Qlen-1] = 1.0;

  /* return result */
  *U = vk;

  /* clean up */
  free(lens);

 return AY_OK;
} /* ay_knots_chordparam */


/* ay_knots_centriparam:
 *  create centripetal parameterization in <U[Ulen]> from points in <Q[Qlen]>
 */
int ay_knots_centriparam(double *Q, int Qlen, int stride, double **U)
{
 double t, *vk = NULL, totallen = 0.0, *lens = NULL;
 int i, j;

  if(!Q || !U) return AY_ENULL;

  /* get some memory */
  if(!(vk = (double*)calloc(Qlen, sizeof(double)))) return AY_EOMEM;
  if(!(lens = (double*)calloc(Qlen-1, sizeof(double))))  { free(vk); return AY_EOMEM; }

  /* compute total length and partial lengths */
  j = 0;
  for(i = 0; i < (Qlen-1); i++)
  {
      lens[i] = AY_VLEN((Q[j+stride] - Q[j]), (Q[j+stride+1] - Q[j+1]), (Q[j+stride+2] - Q[j+2]));
      totallen += lens[i];
      j += stride;
  }

  /* compute the centripetal parameterization */
  vk[0] = 0.0;
  j = 0;
  t = 0.0;
  for(i = 1; i < (Qlen-1); i++)
  {
      t += lens[j]/totallen;
      vk[i] = t;
      /*printf("vk[%d]:%f\n",i,t);*/
      j++;
  }
  vk[Qlen-1] = 1.0;

  /* return result */
  *U = vk;

  /* clean up */
  free(lens);

 return AY_OK;
} /* ay_knots_centriparam */


/* nb.c - various NURBS related functions */

/*
 * ay_nb_LUDecompose: (NURBS++)
 * Although taken from NURBS++, this code is originally
 * from Skip Carters "Kalman library":
 * ftp://usc.edu/pub/C-numanal/kalman.tar.gz ;
 * it does the LU decomposition of the nxn matrix A;
 * pivot[n] has to be allocated outside! and fed into the
 * inversion below.
 */

int ay_nb_LUDecompose(int n, double *A, int *pivot)
{
 int errval, i, j, k, l, kp1, nm1, sign;
 double t, q;
 double den = 0.0, ten = 0.0;
 double *elem = NULL;

  if(!(elem = (double*)calloc(n*n, sizeof(double)))) return AY_EOMEM;
  memcpy(elem, A, n*n*sizeof(double));

  errval = 0;
  nm1 = n - 1;
  for(k = 0; k < n; k++)   pivot[k] = k;

  sign = 1;

  if(nm1 >= 1)	/* non-trivial problem */
  {
   for(k = 0; k < nm1; k++)
   {
	  kp1 = k + 1;
	  /* partial pivoting ROW exchanges */
	  /* -- search over column          */

	  ten = fabs(A[k*n+k]);
	  l = k;
	  for(i = kp1; i < n; i++)
	  {
	    den = fabs(A[i*n+k]);
	    if(den > ten)  { ten = den;	l = i; }
	  }
	  pivot[k] = l;

	  if(elem[l*n+k] != 0.0)
	  {
	      /* nonsingular pivot found */
	      /* interchange needed */
	      if(l != k)
		  {
		    for(i = k; i < n; i++)
		    {
		      t = elem[l*n+i];
		      elem[l*n+i] = elem[k*n+i];
		      elem[k*n+i] = t;
		    }
		    sign = -sign;
		  } //if l
		  
	      q =  elem[k*n+k];	/* scale row */
	      for(i = kp1; i < n; i++)
		  {
			 t = - elem[i*n+k]/q;
			 elem[i*n+k] = t;
			 for(j = kp1; j < n; j++)    elem[i*n+j] += (t * elem[k*n+j]);
		  }
	  }
	  else	errval = k;	/* pivot singular */
	    
   } //for k

  }//if

  pivot[nm1] = nm1;
  if(elem[nm1*n+nm1] == 0.0)    errval = nm1;

  memcpy(A, elem, n*n*sizeof(double));
  free(elem);
  return AY_OK;
  
} /* ay_nb_LUDecompose */


/*
 * ay_nb_LUInvert: (NURBS++)
 * Although taken from NURBS++, this code is originally
 * from Skip Carters "Kalman library":
 * ftp://usc.edu/pub/C-numanal/kalman.tar.gz ;
 * it does the inversion of the nxn matrix inv;
 * pivot[n] has to be allocated outside! and fed with
 * data by the LU decomposition above.
 */
int ay_nb_LUInvert(int n, double *inv, int *pivot)
{
 double ten, *work = NULL;
 int i, j, k, l = 0, kb, kp1, nm1, coln;

  if(!(work = (double*)calloc(n, sizeof(double))))  return AY_EOMEM;

  coln = n;
  nm1 = n - 1;

  /* inverse U */
  for(k = 0; k < n; k++)
  {
      ten = 1.0 / inv[k*n+k];
      inv[k*n+k] = ten;
      ten = -ten;
      
      for(i = 0; i < k; i++)	inv[i*n+k] *= ten;
      kp1 = k + 1;
      
      if(nm1 >= kp1)
	    for(j = kp1; j < n; j++)
	    {
	      ten = inv[k*n+j];
	      inv[k*n+j] = 0.0;
	      for(i = 0; i < kp1; i++)	inv[i*n+j] += (ten * inv[i*n+k]);
	    }

  }// for k

  /* INV(U) * INV(L) */
  if(nm1 >= 1)
  {
    for(kb = 0; kb < nm1; kb++)
	{
	  k = nm1 - kb - 1;
	  kp1 = k + 1;
	  for(i = kp1; i < n; i++)
	  {
	      work[i] = inv[i*n+k];
	      inv[i*n+k] = 0.0;
	  }
	  for(j = kp1; j < n; j++)
	  {
	      ten = work[j];
	      for(i = 0; i < n; i++) inv[i*n+k] += (ten * inv[i*n+j]);
	  }
	  l = pivot[k];
	  
	  if(l != k)
	  for(i = 0; i < n; i++)
	  {
		  ten = inv[i*n+k];
		  inv[i*n+k] = inv[i*n+l];
		  inv[i*n+l] = ten;
	  }

	} /* for */

  } /* if(nm >= 1) */

  free(work);

 return AY_OK;
} /* ay_nb_LUInvert */



/* act.c - approximating curve tools */

/* ay_act_svd:
 *  singular value decomposition of matrix <a[m][n]> into <q>, <u> and <v>
 *  <withu> and <withv> should be 1, <eps>, and <tol> >= AY_EPSILON
 */
int ay_act_svd(int m, int n, int withu, int withv, double eps, double tol, double *a, double *q, double *u, double *v)
{
 int i, j, k, l, l1, iter, retval;
 double c, f, g, h, s, x, y, z;
 double *e;

  e = (double *)calloc(n, sizeof(double));
  retval = 0;

  /* Copy 'a' to 'u' */
  for(i = 0; i < m; i++)
  for(j = 0; j < n; j++)  u[i*m+j] = a[i*m+j]; /*u[i][j] = a[i][j];*/

  /* Householder's reduction to bidiagonal form. */
  g = x = 0.0;
  for(i = 0; i < n; i++)
    {
      e[i] = g;
      s = 0.0;
      l = i+1;
      for(j = i; j < m; j++) s += (u[j*m+i]*u[j*m+i]);
      if(s < tol) { g = 0.0; }
      else
	  {
		  f = u[i*m+i];
		  g = (f < 0) ? sqrt(s) : -sqrt(s);
		  h = f * g - s;
		  u[i*m+i] = f - g;
		  for(j = l; j < n; j++)
		  {
		      s = 0.0;
		      for(k = i; k < m; k++) s += (u[k*m+i] * u[k*m+j]);
		      f = s / h;
		      for(k = i; k < m; k++) u[k*m+j] += (f * u[k*m+i]);
		  } /* for */
	  } /* if */
	
      q[i] = g;
      s = 0.0;
      for(j = l; j < n; j++) s += (u[i*m+j] * u[i*m+j]);
      
      if(s < tol) { g = 0.0; }
      else
	  {
		  f = u[i*m+i+1];
		  g = (f < 0) ? sqrt(s) : -sqrt(s);
		  h = f * g - s;
		  u[i*m+i+1] = f - g;
		  
		  for(j=l;j<n;j++) e[j] = u[i*m+j]/h;
		  for(j=l;j<m;j++)
		  {
		      s = 0.0;
		      for(k = l; k < n; k++)  s += (u[j*m+k] * u[i*m+k]);
		      for(k = l; k < n; k++)  u[j*m+k] += (s * e[k]);
		  } /* for */
	  } /* if */
	
      y = fabs(q[i]) + fabs(e[i]);
      if(y > x)	x = y;
      
    } /* end i */

  /* accumulation of right-hand transformations */
  if(withv)
  {
    for(i = n-1; i >= 0; i--)
	{
	  if(g != 0.0)
	  {
	      h = u[i*m+i+1] * g;
	      for(j = l; j < n; j++) v[j*m+i] = u[i*m+j]/h;
	      for(j = l; j < n; j++)
		  {
			s = 0.0;
			for(k = l; k < n; k++) s += (u[i*m+k] * v[k*m+j]);
			for(k = l; k < n; k++) v[k*m+j] += (s * v[k*m+i]);
		  } /* for */
	  } /* if */
	    
	  for(j = l; j < n; j++) v[i*m+j] = v[j*m+i] = 0.0;
	  v[i*m+i] = 1.0;
	  g = e[i];
	  l = i;
	  
	} /* for */
  } /* end withv, parens added for clarity */

  /* accumulation of left-hand transformations */
  if(withu)
    {
      for(i = n; i < m; i++)
	  {
		 for(j = n; j < m; j++) u[i*m+j] = 0.0;
		 u[i*m+i] = 1.0;
	  }

      for(i = n-1; i >= 0; i--)
	  {
		  l = i + 1;
		  g = q[i];
		  
		  for(j = l; j < m; j++) u[i*m+j] = 0.0;  /* upper limit was 'n' */
		  if(g != 0.0)
		  {
		      h = u[i*m+i] * g;
		      for(j = l; j < m; j++) /* upper limit was 'n' */
			  {
				  s = 0.0;
				  for(k = l; k < m; k++) s += (u[k*m+i] * u[k*m+j]);
				  f = s / h;
				  for(k = i; k < m; k++) u[k*m+j] += (f * u[k*m+i]);
			  } /* end j */
			  
		      for(j = i; j < m; j++) u[j*m+i] /= g;
		  } /* end g */
		  else  { for(j = i; j < m; j++) u[j*m+i] = 0.0; }
		  u[i*m+i] += 1.0;
	  
	  } /* for i*/
    } /* end withu, parens added for clarity */

  /* diagonalization of the bidiagonal form */
  eps *= x;
  for(k = n-1; k >= 0; k--)
    {
      iter = 0;
test_f_splitting:
      for(l = k; l >= 0; l--)
	  {
		 if(fabs(e[l]) <= eps) goto test_f_convergence;
		 if(fabs(q[l-1]) <= eps) goto cancellation;
	  } /* end l */

      /* cancellation of e[l] if l > 0 */
cancellation:
      c = 0.0;
      s = 1.0;
      l1 = l - 1;
      for(i = l; i <= k; i++)
	  {
		  f = s * e[i];
		  e[i] *= c;
		  if(fabs(f) <= eps) goto test_f_convergence;
		  g = q[i];
		  h = q[i] = sqrt(f*f + g*g);
		  c = g / h;
		  s = -f / h;
		  if(withu)
		  {
		      for(j = 0; j < m; j++)
			  {
				y = u[j*m+l1];
				z = u[j*m+i];
				u[j*m+l1] = y * c + z * s;
				u[j*m+i] = -y * s + z * c;
			  } /* end j */
		  } /* end withu, parens added for clarity */
	  } /* end for i */
	  
test_f_convergence:
	
      z = q[k];
      if(l == k) goto convergence;

    /* shift from bottom 2x2 minor */
      iter++;
      if(iter > 30) { retval = k; break; }
      x = q[l];
      y = q[k-1];
      g = e[k-1];
      h = e[k];
      f = ((y-z)*(y+z) + (g-h)*(g+h)) / (2*h*y);
      g = sqrt(f*f + 1.0);
      f = ((x-z)*(x+z) + h*(y/((f<0)?(f-g):(f+g))-h))/x;
      /* next QR transformation */
      c = s = 1.0;
      for(i = l+1; i <= k; i++)
	  {
		  g = e[i];
		  y = q[i];
		  h = s * g;
		  g *= c;
		  e[i-1] = z = sqrt(f*f+h*h);
		  c = f / z;
		  s = h / z;
		  f = x * c + g * s;
		  g = -x * s + g * c;
		  h = y * s;
		  y *= c;
		  if(withv)
		  {
		    for(j = 0; j < n; j++)
			{
				x = v[j*m+i-1];
				z = v[j*m+i];
				v[j*m+i-1] = x * c + z * s;
				v[j*m+i] = -x * s + z * c;
			} /* end for j */
		  } /* end withv, parens added for clarity */
		    
		  q[i-1] = z = sqrt(f*f + h*h);
		  c = f/z;
		  s = h/z;
		  f = c * g + s * y;
		  x = -s * g + c * y;
		  if(withu)
		  {
		    for(j = 0; j < m; j++)
			{
			  y = u[j*m+i-1];
			  z = u[j*m+i];
			  u[j*m+i-1] = y * c + z * s;
			  u[j*m+i] = -y * s + z * c;
			} /* end j */
		  } /* end withu, parens added for clarity */
		  
	  } /* for i */
	
	  e[l] = 0.0;
	  e[k] = f;
	  q[k] = x;
	  goto test_f_splitting;
    
convergence:
      if(z < 0.0)
	  {
		 /* q[k] is made non-negative */
		 q[k] = - z;
		 if(withv)  {   for(j = 0; j < n; j++)	v[j*m+k] = -v[j*m+k];   } 
		 /* end withv, parens added for clarity */
	  } /* end z */
    } /* end k */

  free(e);

 return retval;
} /* ay_act_svd */


/* ay_act_multmatrixmn:
 *  multiply two compatible rectangular matrices <M1[m][n]> and <M2[n][m]>,
 *  write result to <R[n][n]> (allocated outside!)
 *  compatibility will not be checked
 */

int ay_act_multmatrixmn(int m, int n, double *M1, double *M2, double *R)
{
 int i, j, k;
 int a, b, c = 0;
 double t;

  if(!M1 || !M2 || !R)   return AY_ENULL;

  /* M1 is mxn, M2 is nxm; R will be nxn */

  /* i shall be column number for R (and M1) */
  for(i = 0; i < n; i++)
  {
      /* j shall be row number for R (and M2) */
    for(j = 0; j < n; j++)
	{
	  /* arrange to access row j in M1 */
	  a = j;
	  /* arrange to access column i in M2 */
	  b = i*m;
	  t = 0.0;
	  for(k = 0; k < m; k++)
	  {
	      t += M1[a] * M2[b];
	      /* forward one column in M1 */
	      a += n;
	      /* forward one row in M2 */
	      b++;
	  } /* for */
	  R[c] = t;
	  /* forward one row in R */
	  c++;
	} /* for */
  } /* for */

 return AY_OK;
} /* ay_act_multmatrixmn */


/* ay_act_solve:
 *  solve the linear equation system: A*X=B
 *  (A[m*n], X[n*stride], B[n*stride], m >= n)
 *  will change A! X allocated outside!
 */
int ay_act_solve(int m, int n, double *A, double *B, double *X)
{
 int ay_status = AY_OK, svd_status = 0;
 int stride = 3, i, j, k, l;
 double t, *q = NULL, *u = NULL, *v = NULL, *tmp = NULL;
 int *pivot = NULL;

  if(!A || !B || !X) return AY_ENULL;

  if(m == n)
  {
      /* A is square => use LU decomposition to solve */
      if(!(pivot = (int*)calloc(n, sizeof(int)))){ ay_status = AY_EOMEM; goto cleanup; }

      ay_status = ay_nb_LUDecompose(n, A, pivot);
      if(ay_status)	{ goto cleanup; }
      
      ay_status = ay_nb_LUInvert(n, A, pivot);
      if(ay_status)	{ goto cleanup; }

      /* multiply through: X = A(^-1)*B, and store results */
      for(i = 0; i < n; i++)
	  for(j = 0; j < stride; j++)
	  {
	      t = 0.0;
	      for(k = 0; k < n; k++) t += (A[i*n+k] * B[k*stride+j]);
	      X[i*stride+j] = t;
	  }

  } //if m
  else
    {
      /* A is not square => use SV decomposition to solve */
      if(!(q = (double*)calloc(m, sizeof(double))))	{ ay_status = AY_EOMEM; goto cleanup; }
      if(!(u = (double*)calloc(m*m, sizeof(double)))) { ay_status = AY_EOMEM; goto cleanup; }
      if(!(v = (double*)calloc(m*m, sizeof(double)))) { ay_status = AY_EOMEM; goto cleanup; }
      if(!(tmp = (double *)calloc(m, sizeof(double))))	{ ay_status = AY_EOMEM; goto cleanup; }

      svd_status = ay_act_svd(m, n, 1, 1,
			      1.5/*AY_EPSILON*/, 0.25/*AY_EPSILON*/,   A, q, u, v);

      if(svd_status) { ay_status = AY_ERROR; goto cleanup; }
      for(l = 0; l < stride; l++)
	  {
	  for(i = 0; i < n; i++)
	    {
	      tmp[i] = 0.0;
	      if(q[i] > AY_EPSILON /* XXXX ?Use different constant/tol? */)
		  {
		  	for(j = 0; j < m; j++) tmp[i] += (u[j*m+i] * B[i*stride+l]); /* U'.b */
		  	tmp[i] /= q[i]; /* (1/q).U'.b */
		  }
	      /* XXXX ?report error? */
	      /*
	      else	{ ay_status = AY_ERROR; goto cleanup;}
	      */
	    } /* for i */
	    for(i = 0; i < n; i++)
	    {
	      X[i*stride+l] = 0.0;
	      for(j = 0; j < n; j++) X[i*stride+l] += (v[i*m+j] * tmp[j]); /* V.(1/q).U'.b */
	    }
	  } /* for l*/
    } /* if */

cleanup:

  if(pivot)    free(pivot);
  if(q)    free(q);
  if(u)    free(u);
  if(v)    free(v);
  if(tmp)    free(tmp);

 return ay_status;
} /* ay_act_solve */


/* ay_act_leastSquares:
 *  approximate the data points in <Q[m>] with a NURBS curve of degree <p>
 *  with <n> control points, return results in <U> and <P>
 */

int ay_act_leastSquares(double *Q, int m, int n, int p, double **U, double **P)
{
 int ay_status = AY_OK;
 int a, i, i2, j, k, istride = 3, ostride = 4, span;
 double da, d, *ub = NULL;
 double *Ns = NULL, *Nt = NULL, *NN = NULL;
 double *R = NULL, *rk = NULL, *N = NULL, *X = NULL;
 double *funs = NULL;

  if(!Q || !U || !P) return AY_ENULL;
  if(n > m)  return AY_ERROR;

  ay_knots_chordparam(Q, m/*Qlen*/, istride, &ub);

  if(!ub) return AY_ERROR;
  if(!(*U = (double*)calloc(n+p+1, sizeof(double))))   		{ ay_status = AY_EOMEM;    goto cleanup;   }
  if(!(*P = (double*)calloc(n*ostride, sizeof(double))))   	{ ay_status = AY_EOMEM;    goto cleanup;  }

  /* create clamped knot vector by averaging */

  for(i = 0; i < p+1; i++) { (*U)[i] = 0.0; }

  /* from NURBS++ */
  d = m / (double)n;
  for(j = 1; j < n-p; j++)
  {
      (*U)[p+j] = 0.0;
      for(k = j; k < j+p; k++)
	  {
		  i = (int)(k*d);
		  da = k*d-i;
		  i2 = (int)((k-1)*d);
		  (*U)[p+j] += da*ub[i2] + (1.0-da)*ub[i];
	  }
      (*U)[p+j] /= p;
  }//for j

  for(i = n; i < n+p+1; i++)  { (*U)[i] = 1.0; }

  if(!(R = (double*)calloc(n*istride, sizeof(double)))) { ay_status = AY_EOMEM; goto cleanup; }
  if(!(rk = (double*)calloc(m*istride, sizeof(double)))) { ay_status = AY_EOMEM; goto cleanup; }

  /* Note well: N is nxm! (not mxn, as suggested by the NURBS book) */
  if(!(N = (double*)calloc(n*m, sizeof(double))))  { ay_status = AY_EOMEM; goto cleanup; }
  if(!(funs = (double*)calloc(p+1, sizeof(double)))) { ay_status = AY_EOMEM; goto cleanup; }

  /* set up N and rk */
  for(i = 0; i < m; i++)
  {
      span = ay_nb_FindSpan(n, p, ub[i], *U);

      /* protect BasisFuns() from bad spans */
      if(span >= n)	span = n-1;

      memset(funs, 0, (p+1)*sizeof(double));
      ay_nb_BasisFuns(span, ub[i], p, *U, funs);

      for(j = 0; j <= p; j++)
	  {
		  a = (span-p+j)*m+i;
		  N[a] = funs[j];
		  /*
		  if(isnan(N[a]))
		  {
		    ay_status = AY_ERROR; goto cleanup;
		  }
		  */
	  }
      /*rk[i] = Q[i]-N(0,i)*Q[0]-N(n-1,i)*Q[m-1];*/
      rk[i*istride]   = Q[i*istride]   - N[i] * Q[0] -	N[(n-1)*m+i] * Q[(m-1)*istride];
      rk[i*istride+1] = Q[i*istride+1] - N[i] * Q[1] -	N[(n-1)*m+i] * Q[(m-1)*istride+1];
      rk[i*istride+2] = Q[i*istride+2] - N[i] * Q[2] -	N[(n-1)*m+i] * Q[(m-1)*istride+2];
  } /* for */

  /* set up R */
  for(i = 0; i < n; i++)
  {
      /*R[i*istride] = 0.0;*/
      memset(&(R[i*istride]), 0, istride*sizeof(double));
      for(j = 0; j < m; j++)
	  {
		  /*R[i] += N(i,j)*rk[j] ;*/
		  R[i*istride]   += N[i*m+j]*rk[j*istride];
		  R[i*istride+1] += N[i*m+j]*rk[j*istride+1];
		  R[i*istride+2] += N[i*m+j]*rk[j*istride+2];
	  }
      /*
      if(R[i*istride]   * R[i*istride]   < AY_EPSILON &&
	 R[i*istride+1] * R[i*istride+1] < AY_EPSILON &&
	 R[i*istride+2] * R[i*istride+2] < AY_EPSILON)
	{
	  ay_status = AY_ERROR;
	  goto cleanup;
	}
      */
  } /* for */

  /* solve N^T*N*P = R */

  if(n > 2)
  {
      if(!(Ns = (double*)calloc((n-2)*(m-2), sizeof(double))))	{  ay_status = AY_EOMEM;  goto cleanup;	}
      if(!(Nt = (double*)calloc((m-2)*(n-2), sizeof(double))))	{  ay_status = AY_EOMEM;  goto cleanup;	}
      if(!(NN = (double*)calloc((n-2)*(n-2), sizeof(double))))	{  ay_status = AY_EOMEM;  goto cleanup;	}
      if(!(X = (double*)calloc((n-2)*istride, sizeof(double))))	{  ay_status = AY_EOMEM;  goto cleanup;	}

      /* fill Ns & Nt */
      a = 0;
      for(i = 1; i < n-1; i++)
	  for(j = 1; j < m-1; j++)
	    {
	      Ns[a] = N[i*m+j];
	      a++;
	    }
    
	  a = 0;
	  for(i = 1; i < m-1; i++)
	  for(j = 1; j < n-1; j++)
	    {
	      Nt[a] = N[j*m+i];
	      a++;
	    }

      /* do NN=N^T*N */
      ay_act_multmatrixmn(m-2, n-2, Nt, Ns, NN);

      /* solve the linear equation system NN*X=R */
      ay_status = ay_act_solve(n-2, n-2, NN, &(R[istride]), X);

      if(ay_status)	{ goto cleanup; }

      /* save results from X */
      j = 0;
      for(i = 1; i < n-1; i++)
	  {
	  	 memcpy(&((*P)[i*ostride]), &(X[j*istride]), istride*sizeof(double));
	  	 j++;
	  }

  } /* if */

  /* first and last points are data points */
  /*P[0] = Q[0];*/
  memcpy(*P, Q, istride*sizeof(double));
  /*P[n-1] = Q[m-1];*/
  memcpy(&((*P)[(n-1)*ostride]), &(Q[(m-1)*istride]), istride*sizeof(double));

  /* set weights */
  a = 3;
  for(i = 0; i < n; i++)
  {
      (*P)[a] = 1.0;
      a += ostride;
  }

cleanup:

  if(ay_status)
  {
      if(*U)  free(*U);
      *U = NULL;

      if(*P) free(*P);
      *P = NULL;
  }

  if(ub) free(ub);
  if(R) free(R);
  if(rk) free(rk);
  if(N) free(N);
  if(funs) free(funs);
  if(Ns) free(Ns);
  if(Nt) free(Nt);
  if(NN) free(NN);
  if(X) free(X);

 return ay_status;
} /* ay_act_leastSquares */


/*
 * ay_nb_GlobalInterpolation4D: (NURBS++)
 * interpolate the n+1 4D points in Q[] with n+1 precalculated parametric values in ub[]
 * and n+d+1 knots in Uc[] with desired degree d (d <= n!)
 */

int ay_nb_GlobalInterpolation4D(int n, double *Q, double *ub, double *Uc, int d)
{
 int ay_status = AY_OK;
 int i, j, k, span, ind, *pivot = NULL;
 double t, *A = NULL, *U, *N = NULL;
 double *qq = NULL, *xx = NULL;

  if(!(A = (double*)calloc((n+1)*(n+1), sizeof(double)))) return AY_EOMEM;
  if(!(N = (double*)calloc((d+1), sizeof(double))))    { free(A); return AY_EOMEM; }
  if(!(qq = (double*)calloc((n+1)*4, sizeof(double))))    { free(A); free(N); return AY_EOMEM; }
  if(!(xx = (double*)calloc((n+1)*4, sizeof(double))))    { free(A); free(N); free(qq); return AY_EOMEM; }
  if(!(pivot = (int*)calloc(n+1, sizeof(int))))    { free(A); free(N); free(qq); free(xx); return AY_EOMEM; }

  U = Uc;

  /* Fill A */
  for(i = 1; i < n; i++)
  {
      span = ay_nb_FindSpan(n, d, ub[i], U);
      ay_nb_BasisFuns(span, ub[i], d, U, N);
      for(j = 0; j <= d; j++)
	  {
	  		ind = (i*(n+1)) + (span-d+j);
	  		A[ind] = N[j];
	  }
  }

  A[0] = 1.0;
  A[n*(n+1)+n] = 1.0;

  ay_status = ay_nb_LUDecompose(n+1, A, pivot);
  if(ay_status)  { free(A); free(N); free(qq); free(xx); free(pivot); return ay_status; }

  ay_status = ay_nb_LUInvert(n+1, A, pivot);
  if(ay_status) { free(A); free(N); free(qq); free(xx); free(pivot); return ay_status; }

  /* Init matrix for LSE */
  memcpy(qq,Q,(n+1)*4*sizeof(double));

  /* Multiply through: xx = A(^-1)*qq */
  for(i = 0; i < (n+1); i++)
  for(j = 0; j < 4; j++)
	{
	  t = 0.0;
	  for(k = 0; k < (n+1); k++)	t += (A[i*(n+1)+k] * qq[k*4+j]);
	  xx[i*4+j] = t;
	}

  /* Store the results to Q*/
  memcpy(Q,xx,(n+1)*4*sizeof(double));

  free(A);
  free(N);
  free(qq);
  free(xx);
  free(pivot);

 return AY_OK;
} /* ay_nb_GlobalInterpolation4D */



