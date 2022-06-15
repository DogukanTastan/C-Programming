/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/
#include <stdio.h>
#include "hw2_lib.h"
#include <math.h>    /* i added -lm to makefile file for this library */


int find_weekday_of_data(int day, int month, int year)
{
      int a= (((month+10) / 12 * 31 +                                                                                 /* For example, if the month entered is 5, it will come as "(*month+7)" times 1 due to the integer type */
			(month+9)  / 12 * (28-((year%4-4)/4)-((year%100-100)/100)+((year%400-400)/400)-((year%4000-4000)/4000))+  /*here I wrote a special leap year formula for February*/
			(month+8)  / 12 * 31 +
		    (month+7)  / 12 * 30 +
			(month+6)  / 12 * 31 +
			(month+5)  / 12 * 30 +
			(month+4)  / 12 * 31 +
			(month+3)  / 12 * 31 +                                               /* The expression that gives which day was the January 1 is (year+(year-1)/4+5)%7 */
			(month+2)  / 12 * 30 +                                              /* (year-1)/4 allows to add 1 in leap years                                       */
		    (month+1)  / 12 * 31 +                                             /* If the reason I wrote +5 wasn't +5, Monday, January 1st,year 001 would be 0 but it's saturday so it's 5 so i added 5*/                                  
			(month+0)  / 12 * 30 + day + (year+(year-1)/4+5)%7-1)%7)+1;       /* As a result, find out which day of the year the month and day entered in this formula then I collected 
			                                                                     1 january with the formula I mentioned earlier. */ 
if(a<=0 || a>7){

	return -29; /* Error Message. I arranged main according to this value*/
}
	return a;

}


int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
	int yearCheck=365;
	int counter=0;
	int remainingFirstYear,passingEndYear,years_in_between,i,result;
	if(start_year%4==0 || start_year%400==0){                                /* I checked if the starting year is a leap year */
    		
    		if(i%100==0 && i%400==0){
    			yearCheck=366;
    		}
    		else if(i%100==0){

    			yearCheck=365;
    		}
    		
    		yearCheck=366;
    	}
    
    
    remainingFirstYear=yearCheck-((start_month+10)/ 12 * 31 +              /* I calculated how many days until the end of the first year of the date entered */                  
			(start_month+9)  / 12 * (28-((start_year%4-4)/4)-((start_year%100-100)/100)+((start_year%400-400)/400)-((start_year%4000-4000)/4000))+           
			(start_month+8)  / 12 * 31 +
		    (start_month+7)  / 12 * 30 +
			(start_month+6)  / 12 * 31 +
			(start_month+5)  / 12 * 30 +                                  /* I used the logic of the first function in these calculations */
			(start_month+4)  / 12 * 31 +
			(start_month+3)  / 12 * 31 +                                               
			(start_month+2)  / 12 * 30 +                                                                                   
		    (start_month+1)  / 12 * 31 +                                                                             
			(start_month+0)  / 12 * 30 + start_day);
      
    passingEndYear=((end_month+10)/ 12 * 31 +                             /* I calculated the day of the year in the entered year */                     
			(end_month+9)  / 12 * (28-((end_year%4-4)/4)-((end_year%100-100)/100)+((end_year%400-400)/400)-((end_year%4000-4000)/4000))+          
			(end_month+8)  / 12 * 31 +
		    (end_month+7)  / 12 * 30 +
			(end_month+6)  / 12 * 31 +
			(end_month+5)  / 12 * 30 +
			(end_month+4)  / 12 * 31 +
			(end_month+3)  / 12 * 31 +                                               
			(end_month+2)  / 12 * 30 +                                                                                   
		    (end_month+1)  / 12 * 31 +                                                                             
			(end_month+0)  / 12 * 30 + end_day);

    years_in_between=(end_year-start_year-1)*365;                   /*i calculated how many days there are between two years */

    for(i=start_year+1;i<end_year;i++){                             /*I have added Leap Years in this section */
    	if(i%4==0 || i%400==0){
    		
    		if(i%100==0 && i%400==0){
    			counter++;
    		}
    		else if(i%100==0){

    			continue;            /* I continued without a transaction */
    		}
    		
    		counter++;
    	}
    }
    
    result=remainingFirstYear+passingEndYear+years_in_between+counter-1;       /* I came to the conclusion by collecting all the data. I subtracted 1 to give the time between */

    
    if(result<0){

    	return -29;  /* Error Message. I arranged main according to this value*/
    }

    return result;
}



double find_angle(double a, double b, double c)
{
   
   double y,t1,t2,alpha;  /* I have defined my variables */

  t1 =sqrt((((a*a)+(b*b)-(c*c/2))/2))*2/3;   /* I found the edges using the median theorem */

  t2=sqrt((((a*a)+(c*c)-(b*b/2))/2))*2/3;
 
 alpha=(t1*t1+t2*t2-a*a)/(2*t1*t2);       /* I used the cos theorem */
 
 y=acos(alpha);             /* I reached the radian value of the alpha angle with the acos function */
  
  return y;
}


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{

int l1,l2,l3,i,j;   /* I have defined the variables */

l1=log10(r11)+1;
l2=log10(r21)+1;  /* I found the length of the numbers that come with the logarithm. We will use this later to center */
l3=log10(r31)+1;



	for(i = 0;i<9;i++){                                       /* the table consists of 9 rows */
		
		if(i % 2 == 0)                                      /* row check  */
			if(border == '*'){                             /* border check */
				if(i==0)
					printf("╔*****************************************╗");    /* head of the table */
				else if(i == 8)
					printf("╚*****************************************╝");    /* end of the table */
				else
					printf("║*****************************************║");   /* other situations print the middle of the table */
			}                              
				           
					
			else{                                                             /* If the mark is not * then comes here to print */
				if(i == 0)
					printf("╔═════════════╦═════════════╦═════════════╗");    /* head of the table */
				else if(i == 8)
					printf("╚═════════════╩═════════════╩═════════════╝");    /* end of the table */
				else
					printf("╠═════════════╬═════════════╬═════════════╣");    /* other situations print the middle of the table */
			}
		
		
		else{                                                                    
			if(border == '*'){
				if(i == 1)
					printf("║   ROW 101   ║ ROW ABCDEFG ║ ROW XYZ123  ║");    /* the title is printed */
				else if(i == 3)
					printf("║%*d%*c║ %-12.3g║ %-12d║",13-(13-l1)/2,r11,(13-l1)/2,' ',r12,r13);       /* I did research to use the length data from the logarithm.I have written the number in the middle with %*d%*c   */     
				else if(i == 5)
					printf("║%*d%*c║ %-12.3g║ %-12d║",13-(13-l2)/2,r21,(13-l2)/2,' ',r22,r23);
				else if(i == 7)
					printf("║%*d%*c║ %-12.3g║ %-12d║",13-(13-l3)/2,r31,(13-l3)/2,' ',r32,r33);
			}else{
				if(i == 1)
					printf("%s   ROW 101   %s ROW ABCDEFG %s ROW XYZ123  %s","║","║","║","║");   /* the title is printed */
				else if(i == 3)
					printf("%s%*d%*s %-12.3g%s %-12d%s","║",13-(13-l1)/2,r11,(13-l1)/2+3,"║",r12,"║",r13,"║");       /* I shifted 12 units by -12% and made it left aligned with -  */
				else if(i == 5)
					printf("%s%*d%*s %-12.3g%s %-12d%s","║",13-(13-l2)/2,r21,(13-l2)/2+3,"║",r22,"║",r23,"║");       /* I provided %s%*d%*s to print in the middle in the first part */
				else if(i == 7)
					printf("%s%*d%*s %-12.3g%s %-12d%s","║",13-(13-l3)/2,r31,(13-l3)/2+3,"║",r32,"║",r33,"║");
			}	
		}
		
		 printf("\n");  /*to move to the next line */
	}
}


















