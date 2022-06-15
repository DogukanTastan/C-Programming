/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

#include <stdio.h>
#include "hw1_lib.h"


double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
    int j;
    double xj,result;
	double sum=0;
	double n =(xe-xs)/delta;   /* I found the number of rectangles using the riemann formula */
	
	
	for(j = 0;j<n;j++){
		
		xj = (xs+delta/2+delta*j);    /* Riemann sum with respect to the midpoint of the interval */
		
		sum += a0*(xj*xj*xj)+a1*(xj*xj)+a2*xj+a3;
	
	}
	
	result = sum*delta;
	
	return result;

}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
    int j;
    double xj,result;
	double sum=0;
	double n =(xe-xs)/delta;   /* I found the number of rectangles using the riemann formula */
	
	
	for(j = 0;j<n;j++){
		
		xj = (xs+delta/2+delta*j);   /* Riemann sum with respect to the midpoint of the interval */
		
		sum += a0*(xj*xj*xj*xj)+a1*(xj*xj*xj)+a2*(xj*xj)+a3*xj+a4;
	
	}
	
	result = sum*delta;
	
	return result;

}


double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
    
      double j;

      for(j=xs;j<=xe;j+=0.0001){

      	if(((a0*j*j*j)+(a1*j*j)+(a2*j)+(a3))<0.0001 && ((a0*j*j*j)+(a1*j*j)+(a2*j)+(a3))>-0.0001){            /* brute force algorithm */

      		return j;
      		
      	}

      }
 }


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{
    double j;

      for(j=xs;j<=xe;j+=0.0001){

      	if(((a0*j*j*j*j)+(a1*j*j*j)+(a2*j*j)+(a3*j)+(a4))<0.0001 && ((a0*j*j*j*j)+(a1*j*j*j)+(a2*j*j)+(a3*j)+(a4)) >-0.0001){   /* brute force algorithm */

      		return j;
      		
      	}

      }
}
