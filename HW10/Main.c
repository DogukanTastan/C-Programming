#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Dogukan TASTAN 1901042627*/

typedef struct movie{
    double budget;
    int genre;
    char* name;
    double score;
    int year;
} movie;

typedef struct movielist{       /* Other structs I have defined here gave me simplicity when creating dynamic arrays. */
    movie * list;
    int size;
    int currentIndex;
}movielist;

typedef struct string{
    char * str;
    int size;
}string ;

typedef struct stringlist{
    char ** list; /* Here I have done the operations of saving the 2-dimensional array with the string. */
    int size;
}stringlist;

/************************************************************************************************************************************************/

movielist * initMovieList(int size){
    movielist * m = (struct movielist*)malloc(sizeof(movielist));  /* I made the space on my list using this function.*/
    m->list = (movie*)malloc(sizeof(movie)*size);
    m->size = size;
    m->currentIndex = -1;
    return m;
}


string * initString(){                              /* I have reserved my 2D array with this function. */
    string * s = (string*)malloc(sizeof(string));
    s->str = NULL;
    s->size = 0;
    return s;
}


stringlist * initStringList(){
    stringlist * sl = (stringlist*)malloc(sizeof(stringlist));  /* I did the string list operations in this function. */
    sl->list = NULL;
    sl->size = 0;
    return sl;
}


void resetString(string * s){  /* I did the reset here */
    s->size = 0;
}

/************************************************************************************************************************************************/

int updateMovie(movielist * m, double budget, int genre, char* name, double score, int year){
    int i;
    for(i = 0;i<m->currentIndex+1;i++){
        if(strcmp(m->list[i].name, name) == 0){     /* If there is another movie from the same movie, the update process is done here. */
            m->list[i].budget = budget;
            m->list[i].genre = genre;
            m->list[i].score = score;
            m->list[i].year = year;
            return 1;
        }
    }
    return 0;
}


void addMovie(movielist * m, double budget, int genre, char* name, double score, int year){
    if(updateMovie(m, budget, genre, name, score, year)) return;

    if(m->size > m->currentIndex+1){
        m->currentIndex++;
        m->list[m->currentIndex].budget = budget;
        m->list[m->currentIndex].genre = genre;
        m->list[m->currentIndex].name = (char*)malloc(sizeof(char)*strlen(name));   /* Adding movies is done here */
        strcpy(m->list[m->currentIndex].name, name);
        m->list[m->currentIndex].score = score;
        m->list[m->currentIndex].year = year;
    }
}


void addChar(string * s, char c){ /* this function combines chars */
   
   string temp;
   int i;

    if(c == '\0' || c == '\r' ||  c == '\n' || c == ',')  /* checking for line break or not */
        return;

    if(s->size == 0){
        s->str = (char*)calloc((s->size+1),sizeof(char));   /* required fields are reserved */
        s->str[s->size] = c;
        s->size++;
        return;
    }

    temp.str = (char*)calloc(s->size, sizeof(char));  /* required fields are reserved */

    for(i = 0;i<s->size;i++)
        temp.str[i] = s->str[i];

    s->str = (char*)calloc((s->size+1),sizeof(char));  
    for(i = 0;i<s->size;i++)
        s->str[i] = temp.str[i];

    s->str[s->size] = c;
    s->size++;
    if(temp.str != NULL)
        free(temp.str);
}


void addString(stringlist * l, char * word){ /* This function is useful for adding words to the string list. */
    
    stringlist temp;
    int i;


    if(l->size == 0){
        l->list = (char**)malloc(sizeof(char*));
        l->list[0] = (char*)calloc(strlen(word),sizeof(char)); /* the size of the list is increasing */
        strcpy(l->list[0], word);
        l->size++;
        return;
    }

    
    temp.list = (char**)calloc(l->size, sizeof(char*));  /* creating a temporary list to assist with the copying process */

    for(i = 0;i<l->size;i++){
        temp.list[i] = (char*)calloc(strlen(l->list[i])+1,sizeof(char)); /* room for word to be added */
        strcpy(temp.list[i], l->list[i]);
    }

    l->list = (char**)calloc((l->size+1),sizeof(char*));

    for(i = 0;i<l->size;i++){
        l->list[i] = (char*)calloc(strlen(temp.list[i])+1,sizeof(char));
        strcpy(l->list[i], temp.list[i]);
    }

    l->list[l->size] = (char*)calloc(strlen(word)+1,sizeof(char));
    strcpy(l->list[l->size], word);
    l->size++;
    if(temp.list != NULL)
        free(temp.list); /* temporary list is freed */
}


int getGenreCode(stringlist * l, char * word){  /*Genre is calculating the code, if it is not in the list, it generates a new number.*/
    int i;
    for(i = 0;i<l->size;i++)
        if(strcmp(l->list[i], word) == 0)
            return i+1;
    addString(l,word);
    return i+1;
}


void readAllData(movielist ** movies, stringlist ** genres, char * filename){
    
    FILE * fp = fopen(filename, "r");            /* opening file */
    string * token = initString();                 
    stringlist * columnnames = initStringList();  /* structs get the necessary settings by going to the appropriate functions */
   
    char character;
    int movie_count = 0,temp_year,k=0;
    char * temp_name;
    double temp_budget,temp_score;  /* variables are defined*/
    char * temp_genre;
    
    while(!feof(fp)){
        fscanf(fp,"%c",&character);  /* the lines are counting */
        if(character == '\n'){
            movie_count++;
        }
    }
    
    movie_count -= 1; /* for first line */
    if(character == '\n') /*for empty last line */
        movie_count--;

    *movies = initMovieList(movie_count);
    *genres = initStringList();
    
    fseek(fp, 0, SEEK_SET); /* bringing the file to its starting location */
    while(!feof(fp)){
        character = ' ';
        resetString(token);
        while(character != ',' && character != '\n' && !feof(fp)){ /* words are created according to the comma and \n */
            fscanf(fp, "%c", &character);
            addChar(token, character); /* sent to the attach function */
        }
        addChar(token, '\0'); /* adding \ 0 to the end of words */

        if(k <= 4){
            addString(columnnames, token->str); /* Arrangements are made according to the place of the column names in the function. */
            k++;
            continue;
        }

        if(strcmp(columnnames->list[k%5], "budget") == 0){
            if(strcmp(token->str, "unknown") == 0)  /* Assigning -1 to the value unknown */
                temp_budget = -1;
            else
                sscanf(token->str, "%lf",&temp_budget);
        }else if(strcmp(columnnames->list[k%5], "genre") == 0){
            temp_genre = (char*)malloc(sizeof(char)*(strlen(token->str)));
            sscanf(token->str, "%s",temp_genre);
        }else if(strcmp(columnnames->list[k%5], "name") == 0){
            temp_name = (char*)malloc(sizeof(char)*(strlen(token->str)));
            strcpy(temp_name, token->str);
        }else if(strcmp(columnnames->list[k%5], "score") == 0){
            sscanf(token->str, "%lf",&temp_score);
        }else if(strcmp(columnnames->list[k%5], "year") == 0){
            sscanf(token->str, "%d",&temp_year);
        }

        if(k%5 == 4)
            addMovie(*movies, temp_budget, getGenreCode(*genres, temp_genre), temp_name, temp_score, temp_year);
        k++;
    }
}

/************************************************************************************************************************************************/

void sort_function(movielist *mlist,stringlist * genres,int start_value,int end_value,int operation,int operation2,int value){

	int i,j,unknown_counter;
	char *Unknown="Unkown";
    movielist *newlist=(movielist*)malloc(sizeof(movielist));
	movie temp;
	
	newlist->list=(movie*)malloc(((end_value-start_value)+1)*sizeof(movie));  /*I'm making a place for the list */
	
	for(i=0;i<(end_value-start_value)+1;i++){
		
		newlist->list[i].budget=mlist->list[i+start_value].budget;    /* copying values to a new list */
		newlist->list[i].genre=mlist->list[i+start_value].genre;
		newlist->list[i].name =(char*)malloc(sizeof(char)*(strlen(mlist->list[i+start_value].name)+1));
		strcpy(newlist->list[i].name,mlist->list[i+start_value].name);
		newlist->list[i].score=mlist->list[i+start_value].score;
		newlist->list[i].year=mlist->list[i+start_value].year;
	}
	newlist->size=(end_value-start_value)+1;

    if(operation==1){

		for(i = 0;i<newlist->size-1;i++){                                                    
        	for(j = 0;j<newlist->size-i-1;j++){                         
                
                /* The expression here moves the small values to the beginning, while -1 makes them stay at the end. */
        		
                if((newlist->list[j].budget > newlist->list[j+1].budget) && newlist->list[j+1].budget != -1 || newlist->list[j].budget==-1){

                    temp = newlist->list[j];
	                newlist->list[j] = newlist->list[j+1];   /* the addresses are being exchanged */     
	                newlist->list[j+1] = temp;
	            }   
        	}
        }	
        
        if(operation2==1){  /* printing single status */

            printf("%20f\t",newlist->list[value-1].budget);
            printf("%s\t",genres->list[(newlist->list[value].genre)-1]);
            printf("%s\t",newlist->list[value-1].name);
            printf("%f\t",newlist->list[value-1].score);
            printf("%d\n",newlist->list[value-1].year);
        }
        if(operation2==2){
            for(i=0;i<newlist->size;i++){   /* printing multiple states */

                if(newlist->list[i].budget!=-1){

                    printf("%20f\t",newlist->list[i].budget);
                    printf("%20s\t",genres->list[(newlist->list[i].genre)-1]);
                    printf("%-80s\t",newlist->list[i].name);
                    printf("%20f\t",newlist->list[i].score);
                    printf("%-20d\n",newlist->list[i].year);
    		    }  
            }
	    }   
    }	
	
    if(operation==2){

		for(i = 0;i<newlist->size-1;i++){                                                    
        	for(j = 0;j<newlist->size-i-1;j++){

        		if(newlist->list[j].genre > newlist->list[j+1].genre){  /* Sorting operations are in progress */

	        		temp = newlist->list[j];
	                newlist->list[j] = newlist->list[j+1];    /* the addresses are being exchanged */      
	                newlist->list[j+1] = temp;
	            }   
        	}
        }	
		if(operation2==1){

            if(newlist->list[value-1].budget==-1){
                    printf("%20s\t",Unknown);       /* Special condition for -1 cases */
                }

                else{
                    printf("%20f\t",newlist->list[value-1].budget);
                }
            printf("%s\t",genres->list[(newlist->list[value].genre)-1]);
            printf("%s\t",newlist->list[value-1].name);
            printf("%f\t",newlist->list[value-1].score);
            printf("%d\n",newlist->list[value-1].year);
        }
        if(operation2==2){
            for(i=0;i<newlist->size;i++){

                if(newlist->list[i].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20f\t",newlist->list[i].budget);
                }
                printf("%20s\t",genres->list[(newlist->list[i].genre)-1]);
                printf("%-80s\t",newlist->list[i].name);
                printf("%20f\t",newlist->list[i].score);
                printf("%-20d\n",newlist->list[i].year);
            }
        }   
	}	
	
    if(operation==3){                               /* works similarly with other options */

		for(i = 0;i<newlist->size-1;i++){                                                    
        	for(j = 0;j<newlist->size-i-1;j++){

        		if(strcmp(newlist->list[j].name,newlist->list[j+1].name)>0){

	        		temp = newlist->list[j];
	                newlist->list[j] = newlist->list[j+1];        
	                newlist->list[j+1] = temp;
	            }   
        	}
        }	
        if(operation2==1){

            if(newlist->list[value-1].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20.1f\t",newlist->list[value-1].budget);
                }
            printf("%s\t",genres->list[(newlist->list[value].genre)-1]);
            printf("%s\t",newlist->list[value-1].name);
            printf("%.2f\t",newlist->list[value-1].score);
            printf("%d\n",newlist->list[value-1].year);
        }
        if(operation2==2){
            for(i=0;i<newlist->size;i++){

                if(newlist->list[i].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20.1f\t",newlist->list[i].budget);
                }
                printf("%20s\t",genres->list[(newlist->list[i].genre)-1]);
                printf("%-80s\t",newlist->list[i].name);
                printf("%20.2f\t",newlist->list[i].score);
                printf("%-20d\n",newlist->list[i].year);
            }
        }   
	}	
	
    if(operation==4){

		for(i = 0;i<newlist->size-1;i++){                                                    
        	for(j = 0;j<newlist->size-i-1;j++){

        		if(newlist->list[j].score > newlist->list[j+1].score){

	        		temp = newlist->list[j];
	                newlist->list[j] = newlist->list[j+1];        
	                newlist->list[j+1] = temp;
	            }   
        	}
        }	
	   if(operation2==1){

            if(newlist->list[value-1].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20.1f\t",newlist->list[value-1].budget);
                }
            printf("%s\t",genres->list[(newlist->list[value].genre)-1]);
            printf("%s\t",newlist->list[value-1].name);
            printf("%.2f\t",newlist->list[value-1].score);
            printf("%d\n",newlist->list[value-1].year);
        }
        if(operation2==2){
            for(i=0;i<newlist->size;i++){

                if(newlist->list[i].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20.1f\t",newlist->list[i].budget);
                }
                printf("%20s\t",genres->list[(newlist->list[i].genre)-1]);
                printf("%-80s\t",newlist->list[i].name);
                printf("%20f\t",newlist->list[i].score);
                printf("%-20d\n",newlist->list[i].year);
            }
        }      
	}	
	
    if(operation==5){

		for(i = 0;i<newlist->size-1;i++){                                                    
        	for(j = 0;j<newlist->size-i-1;j++){

        		if(newlist->list[j].year > newlist->list[j+1].year){

	        		temp = newlist->list[j];
	                newlist->list[j] = newlist->list[j+1];        
	                newlist->list[j+1] = temp;
	            }   
        	}
        }	
		if(operation2==1){

            if(newlist->list[value-1].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20.1f\t",newlist->list[value-1].budget);
                }
            printf("%s\t",genres->list[(newlist->list[value].genre)-1]);
            printf("%s\t",newlist->list[value-1].name);
            printf("%.2f\t",newlist->list[value-1].score);
            printf("%d\n",newlist->list[value-1].year);
        }
        if(operation2==2){
            for(i=0;i<newlist->size;i++){

                if(newlist->list[i].budget==-1){
                    printf("%20s\t",Unknown);
                }

                else{
                    printf("%20.1f\t",newlist->list[i].budget);
                }
                printf("%20s\t",genres->list[(newlist->list[i].genre)-1]);
                printf("%-80s\t",newlist->list[i].name);
                printf("%20f\t",newlist->list[i].score);
                printf("%-20d\n",newlist->list[i].year);
            }
        }   
	}	
}

/************************************************************************************************************************************************/
                                                          
void choice_1(movielist *mlist,stringlist * genres){   /* A regular code order has been provided by running the selection processes in separate functions in this area. */

    int i,operation,operation2,value;
    int start_value,end_value;
   

    while(1){
        printf("\n1.Budget\n2.Genre\n3.Name\n4.Score\n5.Year");
        printf("\nPLease Select an operation: ");
        scanf("%d",&operation);                     /* getting input from the user */
                
        if(operation>0 && operation<6){

            printf("\n1.Single Selection\n2.Multiple Selection\n");
            printf("PLease Select an operation: ");
            scanf("%d",&operation2);                    /* getting input from the user */
            if(operation2>2 || operation2<1){
                printf("\nYou made the wrong choice! \n");
                continue;
            }
            else if(operation2==1){

            	printf("Enter Value: ");
                scanf("%d",&value);                                                             /* getting input from the user*/
                sort_function(mlist,genres,0,mlist->currentIndex,operation,operation2,value);  /* the received information is sent to the sorting function */
                break;
            }        
       		else if(operation2==2){

	       			printf("Enter start value: ");
	       		 	scanf("%d",&start_value);
	       		 	printf("Enter end value: ");
	       		 	scanf("%d",&end_value);
        			sort_function(mlist,genres,start_value,end_value,operation,operation2,0); /* Since value is not required in this section, we send it as 0 */
        	        break;   
            }	
        }
  		else{
            printf("\nYou made the wrong choice! \n");  /* Error message is printed when selecting incorrect selections. */
           	continue;
       	}
  	}
}            


void choice_2(stringlist * genres){

    int i;

    for(i =0;i<genres->size;i++){
        printf("%s\n",genres->list[i]);  /* genre genres are being printed */
    }
}


void choice_3(movielist *mlist){

    int year,until_since,i,flag=0;
    
    printf("Enter a year: ");
    scanf("%d",&year);
    printf("Until(0) or Since(1)  %d:",year);   /* we receive information from the user */
    scanf("%d",&until_since);

    if(until_since==0){

        for(i=0;i<mlist->currentIndex+1;i++){

            if(mlist->list[i].year<year)
                    printf("%s\n",mlist->list[i].name);
                    flag=1;                                 /* flag used to print error message correctly */
            }
        }
    else if(until_since==1){

        for(i=0;i<mlist->currentIndex+1;i++){

            if(mlist->list[i].year>year){
                printf("%s\n",mlist->list[i].name);
                flag=1;

            }
        }
    }
    if(flag==0){
        printf("TRY AGAIN \n");  /*error message */
    }
}


void choice_4(movielist *mlist){

    int i,less_greater;
    float score;

    printf("Enter a score: ");
    scanf("%f",&score);
    printf("Less (0) or Greater (1)  %f:",score); /* we receive information from the user */
    scanf("%d",&less_greater);

    if(less_greater==0){

        for(i=0;i<mlist->currentIndex+1;i++){

            if(mlist->list[i].score<score){
                printf("%s\n",mlist->list[i].name);  /* we print if less than the entered value */
            }
        }
    }
    if(less_greater==1){

        for(i=0;i<mlist->currentIndex+1;i++){

            if(mlist->list[i].score>score)
                printf("%s\n",mlist->list[i].name);  /* we print if greater than the entered value */
        }
    }
}


void choice_5(movielist *mlist,stringlist * genres){
    
    int i,flag=0,size;
    char *movie_name=(char*)malloc(sizeof(char)*150); /* We are opening a certain place, we will take this place and we will free it when we learn the size of the string. */
    char *movie_name2;

    printf("Please Enter the name of the movie: ");
    fflush(stdin);
    scanf(" %[^\n]%*c",movie_name);
    
    size=strlen(movie_name);
    movie_name2=(char*)malloc(sizeof(char)*size);  /* We free the first place by doing the transfer operations here. */
    strcpy(movie_name2,movie_name);
    free(movie_name);

    for(i=0;i<strlen(movie_name2);i++){

        if(movie_name2[i]>=65 && movie_name2[i]<=90){  /* we turn capital letters to small */
            movie_name2[i]=movie_name2[i]+32;
        }
    }
    for(i=0;i<mlist->currentIndex+1;i++){

        if(strcmp(mlist->list[i].name,movie_name2)==0){

            flag=1;  /* We use flag to print the error message correctly. */
                        
            if(mlist->list[i].budget==-1){
                printf("Budget:  Unkown\n");  /* Writes unknown to -1 */
            }

            else{
                printf("Budget:  %.1f\n",mlist->list[i].budget);
            }
            printf("Genre:  %s\n",genres->list[(mlist->list[i].genre)-1]);  /*  print other values */
            printf("Name:  %s\n",mlist->list[i].name);
            printf("Score:  %.3f\n",mlist->list[i].score);
            printf("Year:  %d\n",mlist->list[i].year);  
            break;
        }
    }
    if(flag==0){
        printf("No Movie Found ! \n"); /* printing the error message */
    }
}


void choice_6(movielist *mlist){

    int i;
    double sum;

    for(i=0;i<mlist->currentIndex+1;i++){

        sum+=mlist->list[i].score;    /* Finding the average by adding the values to the total and dividing the total by the number of numbers added */
    }
    sum/=mlist->currentIndex+1;
    printf("Average: %.3f\n",sum);
}


void choice_7(movielist *mlist,stringlist * genres){

	int* counter=(int*)calloc(genres->size,sizeof(int)); /* Creating a counter that will hold the number of genre types */
    int i;
    
    for(i=0;i<mlist->currentIndex+1;i++){

        counter[mlist->list[i].genre-1]++;  
    }   
    for(i =0;i<genres->size;i++){
        printf("%-20s%5d\n",genres->list[i],counter[i]); /* results are printing */
    }
}

/************************************************************************************************************************************************/

int main(){
    
    int choice,operation,operation2;
    int i,k;
    movielist * movies = NULL; /* creating variables */
    stringlist * genres = NULL;
    
    readAllData(&movies, &genres, "Movies.txt"); /* this function allows reading from the file and filling the struct */

    while(choice!=8){

        printf("\n1. List of the Sorted Data\n2. List of the Genres\n3. List of the Movie Through the Years\n4. List of the movie Through the Scores\n5. All Informations of a Single Movie \n6. Average of the IMDB Scores\n7. Frequence of the Genres\n8. Exit \n\nPlease select an operation: ");
        
        scanf("%d",&choice);

        if(choice<1 || choice>8){

            printf("\nTRY AGAIN.\n\n"); /* error message */
            continue;
        }
        
        switch(choice){     /* appropriate functions are called according to options */

            case 1:   
                choice_1(movies,genres);
                break;
            case 2: 
                choice_2(genres);
                break;
            case 3:
                choice_3(movies);
                break;
            case 4: 
                choice_4(movies);
                break;
            case 5:     
                choice_5(movies,genres);
                break;
            case 6: 
                choice_6(movies);
                break;
            case 7:
                choice_7(movies,genres);
                break;
        }       
    }
}