/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/
#include <stdio.h>
#include "hw5_lib.h"
#include <math.h>

void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	double c6,c5,c4,c3,c2,c1,c0;
	if(op==43){                      /* Processing is done according to the ascii equivalent of the selected operator */
		*a3=*a3+*b3;
		*a2=*a2+*b2;
		*a1=*a1+*b1;
		*a0=*a0+*b0;
	}
	else if(op==45){
		*a3=*a3-*b3;
		*a2=*a2-*b2;
		*a1=*a1-*b1;
		*a0=*a0-*b0;
	}
	else if(op==42){
		c6 = (*a3)*(*b3);                                /* Calculation of polynomial product up to maxiumum 6 degrees */
	    c5 = (*b3)*(*a2)+(*b2)*(*a3);                 
	    c4 = (*b3)*(*a1)+(*b1)*(*a3)+(*b2)*(*a2);
	    c3 = (*a3)*(*b0)+(*b3)*(*a0)+(*a2)*(*b1)+(*a1)*(*b2);
	    c2 = (*a2)*(*b0)+(*a1)*(*b1)+(*b2)*(*a0);
	    c1 = (*a1)*(*b0)+(*b1)*(*a0);
	    c0 = (*a0)*(*b0);
		
		*a3 = c6, *a2 = c5, *a1 =c4, *a0 = c3, *b3 = c2, *b2 = c1, *b1 = c0; /* Assignment is made to the values ​​to be printed on the main */              
	}	
}


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	int i;
	double d0, d1, d2, d3,d0p,d1p,d2p,d3p,euclidian_distance=0.0,max=0; /*we defined our variables */ 
	*mean_a0=0,*mean_a1=0,*mean_a2=0,*mean_a3=0;
	
	printf("Enter 1. Vector: ");
	scanf("%lf%lf%lf%lf",&d0p,&d1p,&d2p,&d3p);   /* we take the first vector outside the loop */

	if(d0p==-1 && d1p==-1 && d2p==-1 && d3p==-1)   /* Program ends when -1 -1 -1 -1 is entered */
		printf("Exiting the program...\n");
	else{

		*mean_a0+=d0p,*mean_a1+=d1p,*mean_a2+=d2p,*mean_a3+=d3p;  /* we add to the total */
		
		for(i=2;i<=N;i++){                                 /* We get other vectors up to the value of n */
			printf("Enter %d. Vector: ",i);
			scanf("%lf%lf%lf%lf",&d0,&d1,&d2,&d3);
			if(d0==-1 && d1==-1 && d2==-1 && d3==-1){
				printf("Exiting the program...\n");     /* Program ends when -1 -1 -1 -1 is entered */
				break;
			}	
			
			*mean_a0+=d0,*mean_a1+=d1,*mean_a2+=d2,*mean_a3+=d3;  /* every time we add to the collection */
			distance_between_4d_points (d0-d0p, d1-d1p, d2-d2p, d3-d3p, &euclidian_distance); /* we send the differences to the other function */
			
			if(euclidian_distance>max)  /* We check to see if the value from the function is maximum. */
				max=euclidian_distance;
			d0p=d0,d1p=d1,d2p=d2,d3p=d3; /* we are scrolling */
		}
		
		*longest_distance=max; /* We assign the max value to the required variable */
		
		if((d0p==-1 && d1p==-1 && d2p==-1 && d3p==-1) || (d0==-1 && d1==-1 && d2==-1 && d3==-1))  /* When the -1 -1 -1 -1 is entered and the program is terminated, a special calculation is made for it. */
			*mean_a0/=i-1,*mean_a1/=i-1,*mean_a2/=i-1,*mean_a3/=i-1; 

		else
		*mean_a0/=N,*mean_a1/=N,*mean_a2/=N,*mean_a3/=N; /* we calculate the averages */
    }
}


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
		*euclidian_distance = sqrt(d0*d0 + d1*d1 + d2*d2 + d3*d3);  /* The function that finds the Euclidean distance */
}


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int a_original,b_original,c_original,d_original,e_original,a_counter=0,b_counter=0,c_counter=0,d_counter=0,e_counter=0,i,j,max=0,a,b,c,d,e,a1=2,b1=2,c1=2,d1=2,e1=2,a2=3,b2=3,c2=3,d2=3,e2=3;
	char max_type; /*we defined our variables */ 
	
	a_original=*partyA,b_original=*partyB,c_original=*partyC,d_original=*partyD,e_original=*partyE;  /* I backed up the initial versions of the numbers as I will use them later. */
	
	for(i=0;i<numberOfSeats;i++){   /* I start the cycle to be the number of seats entered */

		if((*partyA)>=(*partyB)){    /* First I determine which party got the most votes and I store it in the char variable. */
			max_type='A';			/* in case of equality I gave the privilege to party A */
			max=(*partyA);
		}
		else{
			max_type='B';
			max=(*partyB);
		}
		if((*partyC)>max){
			max_type='C';
			max=(*partyC);
		}
		if((*partyD)>max){
			max_type='D';
			max=(*partyD);
		}	
		if((*partyE)>max){
			max_type='E';
			max=(*partyE);
		}
	
		if(max_type==65){                            /* According to the result of the char variable, I am in the condition of that party */
			for(a=a1;a<a2;a++){
				a_counter++;						/* Each party has its own counter */
				*partyA=a_original;	
				(*partyA)/=a;
			}
				a1++,a2++;	
		}
		else if(max_type==66){
			for(b=b1;b<b2;b++){
				b_counter++;
				*partyB=b_original;	           /* Since we will do the operations on the original number, I make the original number each time */
				(*partyB)/=b;
			}
				b1++,b2++;	
		}
		else if(max_type==67){
			for(c=c1;c<c2;c++){
				c_counter++;
				*partyC=c_original;	
				(*partyC)/=c;
			}
				c1++,c2++;	      /* and I increase my variables that keep the loop running */
		}
		else if(max_type==68){
			for(d=d1;d<d2;d++){
				d_counter++;
				*partyD=d_original;	
				(*partyD)/=d;
			}
				d1++,d2++;	
		}
		else if(max_type==69){
			for(e=e1;e<e2;e++){
				e_counter++;
				*partyE=e_original;	
				(*partyE)/=e;
			}
				e1++,e2++;	
		}   	
	}    	
		*partyA=a_counter;     /* I equate the results to party variables */
		*partyB=b_counter;
		*partyC=c_counter;
		*partyD=d_counter;
		*partyE=e_counter;
}

/* The following 3 functions are written for use in the order_2d_points_cc function */

double distance(double x, double y){  /* The function that calculates the distance to the origin */
    return sqrt(x*x+y*y);
}

double my_atan(double x) {
	
	 return 1/(1+pow(2.7182818284590,-0.1*x)); /* To make a result similar to the result of the function atan(in math) I used the sigmoid function(y=1/(1+e^(-x))) and I multiplied the x value by 0.1 to increase the precision.*/
}

double atan2(double y,double x){ /* This section controls this part since it is necessary to operate with different regions according to the logic of the atan function.
									According to the logic of this function, it first takes the variable y */					
	
	 double pi=3.1415926535; /* We defined our constant pi */

    if(x>0)
        if(y>=0)
            return (my_atan(y/x)-0.50)*180;
        else
            return (my_atan(y/x)+1.50)*180;
    else if(x<0)
        return (my_atan(y/x)+pi-2.64)*180;
    else if(y>0 && x==0)
        return (pi/2.0-2.64)*180;
    else if(y<0 && x==0)
        return (-1*pi/2.0-2.64)*180;
    else if(x==0 && y==0)
        return (0);    /* this case is actually undefined */
}

void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
		double angle1,angle2,angle3,temp;   /* we defined our variables */
		
			angle1=atan2(*y1,*x1);  /* we sent the values ​​to the atan2 function in turn */
		    angle2=atan2(*y2,*x2);
		    angle3=atan2(*y3,*x3);

	if(angle1 > angle2 || angle1 == angle2 && distance(*x1, *y1) > distance(*x2, *y2)){  /*Here we compare the values ​​we get from the function and we use the distance function even though it has the same slope.*/
        temp = *x1; *x1 = *x2; *x2 = temp;													
        temp = *y1; *y1 = *y2; *y2 = temp;												/* Temp value is a temporary value and it worked for us when changing variables. */	
        temp = angle1; angle1 = angle2; angle2 = temp;
    }
    if(angle2 > angle3 || angle2 == angle3 && distance(*x2, *y2) > distance(*x3, *y3)){      /* I used the bubblesort algorithm while sorting the locations */
        temp = *x2; *x2 = *x3; *x3 = temp;
        temp = *y2; *y2 = *y3; *y3 = temp;
        temp = angle2; angle2 = angle3; angle3 = temp;
    }
    if(angle1 > angle2 || angle1 == angle2 && distance(*x1, *y1) > distance(*x2, *y2)){
        temp = *x1; *x1 = *x2; *x2 = temp;
        temp = *y1; *y1 = *y2; *y2 = temp;
        temp = angle1; angle1 = angle2; angle2 = temp;
    }
}

void number_encrypt (unsigned char* number)  /* I didn't need any improvement in this part.Receiving and sending values */
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}

void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	int int_number=number; /* we defined our variables */

	*b7='0';*b6='0',*b5='0';*b4='0',*b3='0';*b2='0',*b1='0';*b0='0';  /*I first set all bits to 0 because of the algorithm I will use */  

/* I did the binary conversion here */
	*b0=int_number%2+48;     
	int_number/=2;
	*b1=int_number%2+48;          /* I added 48 to the remainder of the count (0 or 1) to make it 1 or 0 as the ascii */
	int_number/=2;
	*b2=int_number%2+48;
	int_number/=2;					/* I divided the number into two according to the algorithm I used. */
	*b3=int_number%2+48;
	int_number/=2;
	*b4=int_number%2+48;
	int_number/=2;
	*b5=int_number%2+48;
	int_number/=2;
	*b6=int_number%2+48;
	int_number/=2;
	*b7=int_number%2+48;
}

void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	char temp;
	int new_number,b00,b01,b02,b03,b04,b05,b06,b07;  /* we defined our variables */

	temp=b7,b7=b2,b2=temp;     /* I made the changes as stated in the pdf */
	temp=b6,b6=b3,b3=temp;
	temp=b5,b5=b0,b0=temp;
	temp=b4,b4=b1,b1=temp;

	temp=b7,b7=b6,b6=b5,b5=b4,b4=b3,b3=b2,b2=b1,b1=b0,b0=temp;   /* I swiped left twice as stated in the pdf */

	temp=b7,b7=b6,b6=b5,b5=b4,b4=b3,b3=b2,b2=b1,b1=b0,b0=temp;

	b07=b7,b06=b6,b05=b5,b04=b4,b03=b3,b02=b2,b01=b1,b00=b0;

	*number=(128*(b07-48))+(64*(b06-48))+(32*(b05-48))+(16*(b04-48))+(8*(b03-48))+(4*(b02-48))+(2*(b01-48))+(1*(b00-48));  /* and I changed the number from binary to decimal */
}
