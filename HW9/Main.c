#include <stdio.h>

typedef struct customer{
	
	char name[50];   /* defined our structure that keeps customer information */
	int age;
	int label;

}customer;


void sorting_customer(customer custom[50],int i){

	customer temp;
	
	int founded=-1,j,k,p,counter=1,flag=0;  /* I have defined the variables */
	
	for(j=i-1;0<=j;j--){

		if(custom[j].label==0){		/* If the label is 0, we keep this information in the founded section and check 5 numbers of the rest of it. */
			
			founded=j;
			
			for(k=j-1;j-5<k;k--){
				if(custom[k].label==0)
					counter++;			/* If counter is not 5, then there is room for 0 to come. */
			}
			break;
		}		
	}

	if(custom[i].label==0 && counter!=5){  /* If label is 0 and counter is not 5, here is provided */

		temp=custom[i];
		
		for(p=i;p>=founded+1;p--)
			custom[p]=custom[p-1];	/* Add to the right of founded, other numbers are shifted accordingly */

		custom[founded+1]=temp;
		flag=1;
	}

	counter=1;
	
	for(j=i-1;0<=j;j--){		/* the same operations are done for other numbers */

		if(custom[j].label==1){
			
			founded=j;
			
			for(k=j-1;j-3<k;k--){ 		/* The incoming number is 1 and we check the number of removals of 3 units from the point of founded, which is the first point where we come across this 1. */
				if(custom[k].label==1)
					counter++;			/* counter starts at 1 because we have already found a number */
			}
			break;
		}		
	}

	if(custom[i].label==1 && counter!=3 && flag==0){

		temp=custom[i];
		
		for(p=i;p>=founded+1;p--)
			custom[p]=custom[p-1];

		custom[founded+1]=temp;
		flag=1;						/* flag is used to avoid some interference situations */
	}

	counter=1;

	for(j=i-1;0<=j;j--){     /* the same operations are done for other numbers */

		if(custom[j].label==2){
			
			founded=j;
			
			for(k=j-1;j-3<k;k--){
				if(custom[k].label==2)
					counter++;
			}
			break;
		}		
	}

	if(custom[i].label==2 && counter!=3 && flag==0){

		temp=custom[i];
		
		for(p=i;p>=founded+1;p--)
			custom[p]=custom[p-1];

		custom[founded+1]=temp;
		flag=1;
	}

	counter=1;

	for(j=i-1;0<=j;j--){   /* the same operations are done for other numbers */

		if(custom[j].label==3){
			
			founded=j;
			
			for(k=j-1;j-2<k;k--){
				if(custom[k].label==3)
					counter++;
			}
			break;
		}		
	}

	if(custom[i].label==3 && counter!=2 && flag==0){

		temp=custom[i];
		
		for(p=i;p>=founded+1;p--)
			custom[p]=custom[p-1];

		custom[founded+1]=temp;
		flag=1;
	}

	counter=1;
	
	for(j=i-1;0<=j;j--){  /* the same operations are done for other numbers */

		if(custom[j].label==4){
			
			founded=j;
			
			for(k=j-1;j-2<k;k--){
				if(custom[k].label==4)
					counter++;
			}
			break;
		}		
	} 

	if(custom[i].label==4 && counter!=2 && flag==0){

		temp=custom[i];
		
		for(p=i;p>=founded+1;p--)
			custom[p]=custom[p-1];

		custom[founded+1]=temp;
		flag=1;
	}
}



int main(){

	customer custom[50];  /* structure array that holds customer information */
	
	int choice,j,i=-1;
	
	printf("***********Banking System***********\n");

	while(1){
		
		printf("Current Sequence: ");
		for(j=0;j<=i;j++)
		printf("%d-",custom[j].label);		  /* the queue is printed here */
		printf("\n");
		printf("1-Add customer\n");	
		printf("2-Process customer\n");			/* getting inputs from the user */
		scanf("%d",&choice);

		if(choice!=1 && choice!=2){
			printf("You made a wrong choice !\n\n"); /* If there was a wrong selection, a new selection is requested. */
			continue;
		}	

		if(choice==1){

			i++;
			printf("Please enter the name of the customer :");		/* This section is used if additions will be made. */
			scanf("%s",custom[i].name);
			printf("Please enter the age of the customer : ");
			scanf("%d",&custom[i].age);
			printf("Please enter the label of the customer : ");
			scanf("%d",&custom[i].label);	
			
			sorting_customer(custom,i);  /* the received value is sent to the function for proper sorting */
		}
		
		if(choice==2){		/* The process process is done here. */

			if(i==-1){
				printf("There is not any customer in bank system sequence.\n\n");  /* error message is printed if there is no one */
				continue;
			}	

			printf("Proceed customer is %s \n",custom[0].name);
			
			for(j=1;j<=i;j++)
				custom[j-1]=custom[j];	/* if there is, scrolling is done and the last element is deleted */
				i--;
		}
	}
}