#include <stdio.h>
#include <math.h>  // I added the -lm command while compiling to use this library

int armstrong_number(int number);
void palindrome_and_Armstrong_number();    // I pre-defined the functions
void find_prime_numbers();
void write_polynomial();

int main() {

write_polynomial();

palindrome_and_Armstrong_number();    // I called the functions in main

find_prime_numbers();
}


void write_polynomial(){

int degree,i,j,check;  // I have defined the variables
float coef;

printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]:");
scanf("%d",&degree);  // first we entered is the degree of the polynomial

for(i=degree;i>=0;i--){

  scanf("%f",&coef); // other entries are received in order

 
if(0.01>=coef && coef>=-0.01)   // Check digit for %.1f
  coef=0.0; 

if(1.05>=coef && 0.96<=coef)    // Check digit for %.1f
	coef=1.0;


if(i==degree){  // Check for first term
	  
    if(coef==1.0)
	  	printf("x^%d",i);   // the case that the coefficients are 1 and -1
	  else if(coef==-1.0)
	  	printf("-x^%d",i);
	  else if(coef==0){
     printf("The highest order term coefficient cannot be 0!");  // returns an error because the first term's coefficient cannot be 0
      for(j=0;j<degree;j++)  // too many entries are taken with this loop to avoid bouncing to other functions
      scanf("%d",&check);
  		break;   // the cycle ends
    }
	  else
	  	printf("%.1fx^%d",coef,i);   // printing other statuses
}

else if(i!=1 && i!=0){  //printing other statuses

    if(coef==1.0)
    printf("+x^%d",i);
    else if(coef==-1.0)
    printf("-x^%d",i);
    else if(coef==0)
    continue;   // Does not print if the coefficient is 0
    else
    printf("%+.1fx^%d",coef,i);
}

else if(i==1){     // If x is of degree 1 control

  	if(coef==1.0)
  	printf("+x");
  	else if(coef==-1.0)
  	printf("-x");
	  else if(coef==0.0)
    continue;
    else
  	printf("%+.1fx",coef);
}

 else if(i==0){     //final term check
  	
    if(coef==1.0)
  	printf("+1");
  	else if(coef==-1.0)
  	printf("-1");
    else if(coef==0.0)
    printf(" ");
    else
  	printf("%+.1f",coef);
}
}
}



int armstrong_number(int number){   // this function is written for use in other function

int number2,digit,i,OriginalNumber,sum=0;   // we define our variables

OriginalNumber=number;  // we keep the original number for later use.

if(number<=0)
	return 0;    // negative number check
else {

digit=log10(number)+1;  // with logarithm we find the number of digits

for(i=0;i<digit;i++){   // loop by number of digits

number2=number%10;  // we take the last step
 
sum +=pow(number2,3);  // we are doing the process

number=number/10;  // we throw the step we use
}
if(sum==OriginalNumber)  // check
	return 1;
else
	return 0;
}
}



void palindrome_and_Armstrong_number(){  // part 2 function

int palindrom,number2,Original_number,p2,palindrom_check,sum=0,armstrong,i;   // we define our variables

printf("\n\nPlease enter an integer number :");

scanf("%d",&palindrom);  // we get our number

while(palindrom<0)                                  // negatif number check
{
	printf("Please Enter Positive Number!\n");
	printf("\nPlease enter an integer number :");
	scanf("%d",&palindrom);
}	



Original_number=palindrom;   // we keep the original number for later use.

p2=log10(palindrom)+1;      // with logarithm we find the number of digits

for(i=0;i<p2;i++){         // loop by number of digits

number2=palindrom%10;     // we take the last step

sum=sum*10+number2;       //we recalculate the number

palindrom=palindrom/10;   // we throw the step we use

}
if(sum==Original_number)  // check
	palindrom_check=1;
else
	palindrom_check=0;
  
armstrong=armstrong_number(Original_number);   //we send the number to the armstrong function

if(armstrong==1 && palindrom_check==1)
printf("This number is both Palindrome and Armstrong number.\n\n");      // we write the situations according to the results obtained
else if(armstrong==0 && palindrom_check==1)
printf("This number is only Palindrome number.\n\n");
else if(armstrong==1 && palindrom_check==0)
printf("This number is only Armstrong number.\n\n");
else if(armstrong==0 && palindrom_check==0)
printf("This number does not satisfy any special cases\n\n");
}



void find_prime_numbers(){   //part 3 function

int num1,num2,sum=0,i,k,max,min,non_prime_counter,result,prime;  // we define our variables

printf("Please enter first positive integer number :");
scanf("%d",&num1);                                              // we get our number
printf("Please enter second positive integer number :");
scanf("%d",&num2);

while(num1<0 || num2<0){
	printf("Please Enter positive integer number! \n"); 
	printf("Please enter first positive integer number :");
	scanf("%d",&num1);                                              // error message and retrieval for negative numbers
	printf("Please enter second positive integer number :");
	scanf("%d",&num2);
}

if(num1<=num2){       // we are comparing
	max=num2;
	min=num1;
}
else{
    max=num1;
	min=num2;
}

for(i=min+1;i<max;i++){  // cycle start

	prime=1;
	
	for(k=2;k<=i/2;k++){  // prime number check

		if(i%k==0)
		prime=0;
	}
	if(i==2)   // Special case for 2
	prime=1;

	if(i==1)   // Special case check that the number 1 is not prime
	prime=0;

	if(prime==1)
	sum +=i;      // If the value of the prime variable has not changed, the number is prime and we add it to the addition
}
printf("Sum of prime numbers between %d and %d : %d \n",min,max,sum);
}

































