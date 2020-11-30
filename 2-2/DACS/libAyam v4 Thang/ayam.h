
#ifndef __ayam_h__
#define __ayam_h__

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

#ifdef __cplusplus
}

#endif /* __cplusplus */
#endif /* __ayam_h__ */


