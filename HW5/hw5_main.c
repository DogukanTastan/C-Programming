/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include "hw5_lib.h"

void test_operate_polynomials () 
{
	char op,temp;
	int dega1,dega2,dega3,dega0,dega01,dega02,dega03,dega00,i,temp1;  /* I have defined variables */
	double a3,a2,a1,a0,b3,b2,b1,b0,temp2;
	
	printf("Enter Operator(+,-,*):");
	scanf("%c",&op);
	if(op!=42 && op!=43 && op!=45)  /* I made a check according to the ascii tablo number*/
		printf("You selected the wrong operator!\n");
	
	else{	
			temp=getchar(); /* I got the program working properly with getchar */
		
		printf("Enter the first polynomial as in the format (3, a),(2, b),(1, c),(0, d): ");
		
		for(i=0;i<4;i++){
			scanf("(%d, %lf),",&temp1,&temp2);

			if(temp1==0)
				dega0=temp1,a0=temp2;
			if(temp1==1)
				dega1=temp1,a1=temp2;
			if(temp1==2)
				dega2=temp1,a2=temp2;
			if(temp1==3)
				dega3=temp1,a3=temp2;
		}
			temp=getchar();  /* I got the program working properly with getchar */
		
		printf("Enter the second polynomial as in the format (3, a),(2, b),(1, c),(0, d): ");
		for(i=0;i<4;i++){
			scanf("(%d, %lf),",&temp1,&temp2);

			if(temp1==0)
				dega00=temp1,b0=temp2;  /* I took precautions against mixed input using temp and ensured the correct distribution of variables. */
			if(temp1==1)
				dega01=temp1,b1=temp2;
			if(temp1==2)
				dega02=temp1,b2=temp2;
			if(temp1==3)
				dega03=temp1,b3=temp2;
		}
													/* I checked the error conditions */
		if(dega00>3 || dega00<0 || dega03>3 || dega03<0 || dega02>3 || dega02<0 || dega01>3 || dega01<0 || dega00==dega03 || dega00==dega02 || dega00==dega01 || dega03==dega02 || dega03==dega01 || dega02==dega01 || dega0>3 
			|| dega0<0 || dega3>3 || dega3<0 || dega2>3 || dega2<0 || dega1>3 || dega1<0 || dega0==dega3 || dega0==dega2 || dega0==dega1 || dega3==dega2 || dega3==dega1 || dega2==dega1){
			
			temp=getchar();
			printf("You entered in the wrong format!\n");
		}
		else{	
			
			operate_polynomials(&a3,&a2,&a1,&a0,&b3,&b2,&b1,&b0,op);  /* I sent the values to the function */
			if(op==42)
		    printf("%f %f %f %f %f %f %f\n",a3,a2,a1,a0,b3,b2,b1); /* I did print according to operator selection */
			else if(op!=42)
			printf("%f %f %f %f \n",a3,a2,a1,a0);	
	    }
	}   
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=3;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
