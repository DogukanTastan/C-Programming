#include <stdio.h>
#include <math.h>   /* I added -lm when compiling for this library */

void decide_perfect_harmonic_number();
void difference_max_min ();                   /* I pre-defined the functions */
void bmi_calculation () ;
void calculate_fibonacci_sequence();

int main(){

calculate_fibonacci_sequence();             /* here is the main function I have called other functions here */

decide_perfect_harmonic_number();

difference_max_min();

bmi_calculation();

}



void calculate_fibonacci_sequence() 
{
	char term;       /* I created variables */
	int terms=1;
	
	printf("Please enter term(s) number:");
	  
	while(1)   /* infinite loop for continuous running of the program */
 {
	int i,f1=1,f2=1,f3;      /* I created variables that I will use for fibonacci */

	scanf("%d",&terms);     /* I got the number with scanf and got the char with getchar */
	term=getchar();
		
	if(term=='*')
	    break;     /* When the character * comes, the infinite loop ends with the break command */

	else if(terms<=0){
			printf("Please enter “positive” term(s) number:");
			terms=1;  /* we equalize the value to 1 again to avoid problems */
			continue;
	}

	else if(term=='\n'){     /* When the char value is EOF I started my process */

	printf("Fibonacci Sequence:\n");
	  
	  for(i=1;i<=terms;i++)   /* classical fibonacci processes */
	  {
	
	printf("%d\n",f1);         /* I would print the first value */
		f3 = f1+f2;            /* i transferred the first and second numbers to another value */
        f1 = f2;               /* I assign the second value to the first value */
        f2 = f3;               /* I transferred the third value back to the second value */
     }
	   continue;
	}
 
	else if(term>57 || term<48){                                 /* control of non-numeric situations */
		printf("Please enter “numeric” term(s) number:");
		continue;
	}
	    
   }
}



void decide_perfect_harmonic_number(){

char exit;     /* I defined my exit character */

while(1){      /* infinite loop for continuous running of the program */ 

double sum2=0,harmonic_control,j,number2,divisor=0;    /* I have defined some variables inside the loop to make it work every time. */
float harmonic; /* I float this variable because I got some large number of errors */
int  i,sum=0,number;


printf("\nPlease enter input number :");
scanf("%d",&number);
exit=getchar();                       /* I got the number with scanf and got the char with getchar */ 

if(exit=='*')         /* When the character * comes, the infinite loop ends with the break command */ 
    break;

if(number<0){                                               /* control for negative numbers */
	printf("The input must be a natural number! \n");
	continue;
}


printf("Natural Number Divisors:"); /* pre-printing */

for (i = 1;i <number;i++)              /* perfect number check */
{
	if (number%i == 0){ 
		sum = sum + i;
		printf("%d,",i); /* printing of Natural Number Divisors */
	}	
}
	printf("%d",number); /* printing of last Natural Number Divisor*/

	
	if (sum == number && number!=0) 
	printf("\nIs Perfect Number? : Yes\n");
	
	else
	printf("\nIs Perfect Number? : No\n");
	
number2=number;  /* integer to double transformation */


for(j=1.0;j<=number2;j++){                           /* Harmonic Divisor Number check */

	if (fmod(number2,j)==0.0){   /* Checking divisibility in double numbers with fmod function */
		
		sum2=sum2+(1.0/j);
		divisor++;
	}	
}

	harmonic=divisor/sum2;
	
	harmonic_control=fmod(harmonic,1.0);    /* Check with the fmod function belonging to the math library */

	if(harmonic_control==0.0)
		printf("Is Harmonic Divisor Number? : Yes\n");

	else
		printf("Is Harmonic Divisor Number? : No\n"); 
}
}



void difference_max_min (){

float n1,n2,n3,n4,n5,max,min;    /* I have defined the variables */
double difference;
int i;

printf("\nPlease enter 5 numbers:");
scanf("%f%f%f%f%f",&n1,&n2,&n3,&n4,&n5);       /* I got the numbers */

if(n1>n2){
	max=n1;
	min=n2;
}
else if(n2>n1){
	max=n2;
	min=n1;
}

if(n3>max)
	max=n3;

else if(min>n3)                             /* Finding max and min values */
	min=n3;

if(n4>max)
	max=n4;

else if(min>n4)
	min=n4;
 
if(n5>max)
	max=n5;

else if(min>n5)
	min=n5;
 
difference=(max)-(min);

printf("Maximum number is: %g\n",max);               /* I used %g to make an output suitable for the format in pdf. */
printf("Minimum number is: %g\n",min);

printf("Difference between maximum and minimum is %g",difference);    /* printing the result */
}


void bmi_calculation () {

int kg;
double bmi,m;       /* defined the variables */

printf("\n\nPlease enter weight(kg) :");

scanf("%d",&kg);   /*taking numbers */

printf("Please enter height(m):");

scanf("%lf",&m);


if(kg<=0 || m<=0)
	printf("Values ​​entered cannot be less than or equal to 0 !");

else{

bmi=kg/(m*m);               /* calculation according to the formula */

if(bmi<16)                                                               /*printing the result */
	printf("Your category: Severely Underweight\n");
else if(bmi>=16.0 && bmi<18.5)
	printf("Your category: Underweight\n");              
else if(bmi>=18.5 && bmi<25.0)
	printf("Your category: Normal\n");                                
else if(bmi>=25.0 && bmi<30.0)
	printf("Your category: Owerweight\n");
else if(bmi>=30.0)
	printf("Your category: Obese\n");
}
}











	