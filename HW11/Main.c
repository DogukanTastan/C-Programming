#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ATTENTION ! All checks of this assignment have been made. It is compiled without any problems according to Ansi c90 standards. */

/* Dogukan TASTAN 1901042627 */

/************************************************************************************************************************************************/

typedef struct Movie_Budget{
    double budget;
    char * name;
    int year;
    struct Movie_Budget * next;   /* I created the necessary structs */
} movie_budget;


typedef struct Movie_Name{
    char * genre;
    char * name;
    double score;
    struct Movie_Name * next;
} movie_name;


typedef struct movie_b_ll{     /* The purpose of these structs is to provide convenience in dynamic structures and linked lists. */
    movie_budget * root;
    int size;
}movie_b_ll;


typedef struct movie_n_ll{
    movie_name * root;
    int size;
}movie_n_ll;


typedef struct string{
    char * str;
    int size;
}string ;


typedef struct stringlist{
    char ** list;
    int size;
}stringlist;

/************************************************************************************************************************************************/

movie_b_ll * initMovie_b_ll(){
    movie_b_ll * m = (struct movie_b_ll*)malloc(sizeof(movie_b_ll));
    m->root = NULL;
    m->size = 0;                                                        /* In this section, the allocation of structs is done. */
    return m;
}


movie_n_ll * initMovie_n_ll(){
    movie_n_ll * m = (struct movie_n_ll*)malloc(sizeof(movie_n_ll));
    m->root = NULL;
    m->size = 0;
    return m;
}


string * initString(){
    string * s = (string*)malloc(sizeof(string));
    s->str = NULL;
    s->size = 0;
    return s;
}


stringlist * initStringList(){
    stringlist * sl = (stringlist*)malloc(sizeof(stringlist));
    sl->list = NULL;
    sl->size = 0;
    return sl;
}

/************************************************************************************************************************************************/

void resetString(string * s){     /* reset function */
    s->size = 0;
}


void removeMovie(movie_b_ll * bll, movie_n_ll * nll, char* name){
    
    movie_budget * temp_budget;     
    movie_budget * iter_b;          /* According to c90 standards, variables must be defined at the beginning of the function. */
    movie_name * temp_name;
    movie_name * iter_n;

    if(nll->root == NULL)  /* If the value is NULL, nothing is done. */
        return;

    if(strcmp(nll->root->name, name) == 0){     /* If it is from the same movie, it will be deleted */
        nll->root = nll->root->next;
        bll->root = bll->root->next;
        return;
    }

    iter_b = bll->root;
    iter_n = nll->root;

    while(iter_n->next != NULL){
        if(strcmp(iter_n->next->name, name) == 0){          /* The delete function works on the principle of changing links in linked lists. */
            temp_budget = iter_b->next;
            temp_name = iter_n->next;
            iter_b->next = iter_b->next->next;
            iter_n->next = iter_n->next->next;
            free(temp_budget);
            free(temp_name);
            nll->size--;
            bll->size--;
            return;
        }
        iter_b = iter_b->next;
        iter_n = iter_n->next;
    }
}

/************************************************************************************************************************************************/

void addMovie(int sort_selection, movie_b_ll * bll, movie_n_ll * nll, double budget, char * genre, char* name, double score, int year){
    
    movie_budget * new_b;
    movie_budget * iter_b;  /* According to c90 standards, variables must be defined at the beginning of the function. */ 
    movie_name * new_n;
    movie_name * iter_n;
    
    removeMovie(bll, nll, name); /* If a movie is wanted to be added, it first goes to the delete movie function */
                                /* The reason for this is to check if there is any from the same movie and to delete if there is. */                        
   
    nll->size++;                    
    bll->size++;

    /* UNNECESSARY BRACES TO SHORTEN THE CODE */
    /* THAT PART WILL INITIALIZE NEW MOVIE NODES TO ADD LINKED LISTS */
    new_b = (movie_budget *) malloc(sizeof(movie_budget));
    new_n = (movie_name *) malloc(sizeof(movie_name));
    {
        new_b->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(new_b->name, name);
        new_b->year = year;
        new_b->budget = budget;


        new_n->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(new_n->name, name);
        new_n->genre = (char *) malloc(sizeof(char) * (strlen(genre) + 1));
        strcpy(new_n->genre, genre);
        new_n->score = score;

        new_n->next = NULL;
        new_b->next = NULL;
    }

    if(nll->root == NULL){
        nll->root = (movie_name*)malloc(sizeof(movie_name));  /* if root is NULL, space allocation is done */
        nll->root = new_n;
        bll->root = (movie_budget*)malloc(sizeof(movie_budget));
        bll->root = new_b;
        return;
    }

    iter_b = bll->root;
    iter_n = nll->root;

    if(sort_selection == 0 && (iter_b->year < year || (iter_b->year == year && iter_b->budget < budget)) ||
            sort_selection == 1 && (iter_b->budget < budget)||
            sort_selection == 2 && (iter_n->score < score)||
            sort_selection == 3 && (strcmp(iter_n->name, name) > 0)||
            sort_selection == 4 && (strcmp(iter_n->genre, genre) > 0)){     /* sequential additions */
        new_b->next = bll->root;
        new_n->next = nll->root;
        bll->root = new_b;
        nll->root = new_n;
        return;
    }

    while(iter_b != NULL){
        if(iter_b->next == NULL){
            iter_b->next = new_b;
            iter_n->next = new_n;
            return;
        }else{
            if(sort_selection == 0 && (iter_b->next->year < year || (iter_b->next->year == year && iter_b->next->budget < budget))||
                    sort_selection == 1 && (iter_b->next->budget < budget)||
                    sort_selection == 2 && (iter_n->next->score < score)||
                    sort_selection == 3 && (strcmp(iter_n->name, name) > 0)||
                    sort_selection == 4 && (strcmp(iter_n->genre, genre) > 0)){ 	/* sequential additions, according to conditions */
                new_b->next = iter_b->next; 
                new_n->next = iter_n->next;
                iter_b->next = new_b;
                iter_n->next = new_n;
                return;
            }
            iter_b = iter_b->next;
            iter_n = iter_n->next;
        }
    }
}

/************************************************************************************************************************************************/

void printLL(movie_b_ll * bll, movie_n_ll * nll){
    movie_budget * movie_b = bll->root;             /* According to c90 standards, variables must be defined at the beginning of the function. */ 
    movie_name * movie_n = nll->root;

    int i = 0;
    while(movie_n != NULL){
        printf("Mov %d:\n",++i);
        printf("\tBudget: %f\n", movie_b->budget);  /* this function is a print function, it prints from the incoming data */
        printf("\tGenre: %s\n", movie_n->genre);
        printf("\tName: '%s'\n", movie_n->name);
        printf("\tScore: %f\n", movie_n->score);
        printf("\tYear: %d\n", movie_b->year);

        movie_b = movie_b->next;
        movie_n = movie_n->next;
    }
}

/************************************************************************************************************************************************/

void addChar(string * s, char c){
    
    string temp;    /* According to c90 standards, variables must be defined at the beginning of the function. */ 
    int i;

    if(c == '\0' || c == '\r' ||  c == '\n' || c == ',')        /* this section combines letters read from txt */
        return;

    if(s->size == 0){
        s->str = (char*)calloc((s->size+1),sizeof(char));   
        s->str[s->size] = c;
        s->size++;
        return;
    }

    temp.str = (char*)calloc(s->size, sizeof(char));

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

/************************************************************************************************************************************************/

void addString(stringlist * l, char * word){
    
    int i;               /* According to c90 standards, variables must be defined at the beginning of the function. */ 
    stringlist temp;

    if(l->size == 0){
        l->list = (char**)malloc(sizeof(char*));				/* required fields for the list are created */
        l->list[0] = (char*)calloc(strlen(word),sizeof(char));
        strcpy(l->list[0], word);	/* the incoming word is copied to the list */
        l->size++;
        return;
    }

    temp.list = (char**)calloc(l->size, sizeof(char*));

    for(i = 0;i<l->size;i++){
        temp.list[i] = (char*)calloc(strlen(l->list[i])+1,sizeof(char));	/*Transfer of previous values is provided with temp list */
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
        free(temp.list);		/* We're freeing the temp list because we're done */
}

/************************************************************************************************************************************************/

int getGenreCode(stringlist * l, char * word){	/* This section allows us to assign genres to a unique integer variable. */
    
    int i;
    
    for(i = 0;i<l->size;i++)
        if(strcmp(l->list[i], word) == 0)
            return i+1;
    addString(l,word);
    return i+1;
}

/************************************************************************************************************************************************/

void readAllData(movie_b_ll ** bll_default, movie_n_ll ** nll_default,
                 movie_b_ll ** bll_budget, movie_n_ll ** nll_budget,
                 movie_b_ll ** bll_score, movie_n_ll ** nll_score,
                 movie_b_ll ** bll_name, movie_n_ll ** nll_name,
                 movie_b_ll ** bll_genre, movie_n_ll ** nll_genre,	/* since this is our main reading center it takes all the variables */
                 stringlist ** genres, char * filename){
    
    FILE * fp = fopen(filename, "r");  /* file is opening */
    
    stringlist * columnnames;
    string * token = initString();
    char character;
    char * temp_name;                   
    double temp_budget;
    char * temp_genre;
    char * strtodi;
    double temp_score;
    int temp_year,k=0;					/* According to c90 standards, variables must be defined at the beginning of the function. */ 

    *bll_default = initMovie_b_ll();
    *nll_default = initMovie_n_ll();
    *bll_budget  = initMovie_b_ll();
    *nll_budget  = initMovie_n_ll();
    *bll_score   = initMovie_b_ll();
    *nll_score   = initMovie_n_ll();
    *bll_name    = initMovie_b_ll();
    *nll_name    = initMovie_n_ll();
    *bll_genre    = initMovie_b_ll();
    *nll_genre    = initMovie_n_ll();

    *genres      = initStringList();
    columnnames = initStringList();

    printf("Sorting all movies PLease wait: NNNN");  /* This part is for printing the number on the screen while waiting for the lists to load. */
    fseek(fp, 0, SEEK_SET); /* we get the cursor per file */
    while(!feof(fp)){
        if(k%5 == 4){				/* we print the number of reads at the end of each line */
            printf("\b\b\b\b");	
            printf("%4d", k / 5);
        }

        character = ' ';     /* Here we set the character variable to an empty value to avoid reuse. */
        resetString(token);
        while(character != ',' && character != '\n'){
            fscanf(fp, "%c", &character);
            if(!feof(fp))
                addChar(token, character);
            else break;
        }
        addChar(token, '\0');  /* we add \0 to the end of the word at the end */

        if(k <= 4){
            addString(columnnames, token->str);
            k++;
            continue;
        }

        if(strcmp(columnnames->list[k%5], "budget") == 0){
            strtodi = NULL;
            if(strcmp(token->str, "unknown") == 0)	/* I kept unknown values as -1 */
                temp_budget = -1;
            else
                temp_budget = strtod(token->str, &strtodi);
        }else if(strcmp(columnnames->list[k%5], "genre") == 0){				/* we make it skip the first line */
            temp_genre = (char*)malloc(sizeof(char)*(strlen(token->str)));
            sscanf(token->str, "%s",temp_genre);
        }else if(strcmp(columnnames->list[k%5], "name") == 0){
            temp_name = (char*)malloc(sizeof(char)*(strlen(token->str)));
            strcpy(temp_name, token->str);
        }else if(strcmp(columnnames->list[k%5], "score") == 0){
            strtodi = NULL;
            temp_score = strtod(token->str, &strtodi);
        }else if(strcmp(columnnames->list[k%5], "year") == 0){
            strtodi = NULL;
            temp_year = (int) strtod(token->str, &strtodi);
        }

        if(k%5 == 4){
            addMovie(0, *bll_default, *nll_default, temp_budget, temp_genre, temp_name, temp_score, temp_year);
            addMovie(1, *bll_budget, *nll_budget, temp_budget, temp_genre, temp_name, temp_score, temp_year);
            addMovie(2, *bll_score, *nll_score, temp_budget, temp_genre, temp_name, temp_score, temp_year);
            addMovie(3, *bll_name, *nll_name, temp_budget, temp_genre, temp_name, temp_score, temp_year);
            addMovie(4, *bll_genre, *nll_genre, temp_budget, temp_genre, temp_name, temp_score, temp_year);

            getGenreCode(*genres, temp_genre);
        }
        k++;
    }
    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
}

/************************************************************************************************************************************************/

void interval_print(movie_b_ll * bll, movie_n_ll * nll, int a, int b){	/* intermittent printing is done here */
    int size = nll->size, i;
    movie_budget * movie_b;     
    movie_name * movie_n;		/* According to c90 standards, variables must be defined at the beginning of the function. */ 

    if(a <= 0 || b > size-1){		
        printf("IndexError");   /* error message for impossible cases */
        return;
    }
    movie_b = bll->root;
    movie_n = nll->root;
    for(i = 1;i<a;i++){
        movie_b = movie_b->next;
        movie_n = movie_n->next;
    }
    for(i = a;i<=b;i++){				/* Printing is done according to the information received. */
        printf("Mov %d:\n",i);
        printf("\tBudget: %f\n", movie_b->budget);
        printf("\tGenre: %s\n", movie_n->genre);
        printf("\tName: '%s'\n", movie_n->name);
        printf("\tScore: %f\n", movie_n->score);
        printf("\tYear: %d\n", movie_b->year);
        movie_b = movie_b->next;
        movie_n = movie_n->next;	/* the list goes on */
    }
}

/************************************************************************************************************************************************/

void choice_1(  movie_b_ll * bll_default_sorted,
                movie_n_ll * nll_default_sorted,
                movie_b_ll * bll_score_sorted,
                movie_n_ll * nll_score_sorted,
                movie_b_ll * bll_budget_sorted,
                movie_n_ll * nll_budget_sorted,
                movie_b_ll * bll_name_sorted,
                movie_n_ll * nll_name_sorted,
                movie_b_ll * bll_genre_sorted,
                movie_n_ll * nll_genre_sorted,stringlist * genres){   /* A regular code order has been provided by running the selection processes in separate functions in this area. */

    int operation,operation2,value; 
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
                scanf("%d",&value);
                switch(operation){
                    case 1: interval_print(bll_budget_sorted, nll_budget_sorted, value, value); break;  /* Calling the intermittent print function according to the selected operation */
                    case 2: interval_print(bll_genre_sorted, nll_genre_sorted, value, value); break;
                    case 3: interval_print(bll_name_sorted, nll_name_sorted, value, value); break;
                    case 4: interval_print(bll_score_sorted, nll_score_sorted, value, value); break;
                    case 5: interval_print(bll_default_sorted, nll_default_sorted, value, value); break;
                }
                break;
            }
            else if(operation2==2){

                printf("Enter start value: ");
                scanf("%d",&start_value);
                printf("Enter end value: ");
                scanf("%d",&end_value);
                switch(operation){
                    case 1: interval_print(bll_budget_sorted, nll_budget_sorted, start_value, end_value); break;	/* Calling the intermittent print function according to the selected operation */
                    case 2: interval_print(bll_genre_sorted, nll_genre_sorted, start_value, end_value); break;
                    case 3: interval_print(bll_name_sorted, nll_name_sorted, start_value, end_value); break;
                    case 4: interval_print(bll_score_sorted, nll_score_sorted, start_value, end_value); break;
                    case 5: interval_print(bll_default_sorted, nll_default_sorted, start_value, end_value); break;
                }
                break;
            }
        }
        else{
            printf("\nYou made the wrong choice! \n");  /* Error message is printed when selecting incorrect selections. */
            continue;
        }
    }
}


void choice_2(stringlist * genres){		/* prints genre list */
    int i;

    printf("+-----------+\n");
    for(i = 0;i<genres->size;i++){
        printf("| %-9s |\n",genres->list[i]);
    }
    printf("+-----------+\n");
}


void choice_3(movie_b_ll * bll){

    int year,until_since,flag=0;
    movie_budget * movie_b = bll->root;

    printf("Enter a year: ");
    scanf("%d",&year);
    printf("Until(0) or Since(1)  %d:",year);   /* we receive information from the user */
    scanf("%d",&until_since);

    movie_b = bll->root;

    while(movie_b != NULL){
        if(until_since == 0 && movie_b->year < year || until_since == 1 && movie_b->year > year){
            printf("%s\n",movie_b->name);
            flag=1; /* flag used to print error message correctly */
        }
        movie_b = movie_b->next;
    }

    if(flag==0)
        printf("TRY AGAIN \n");  /*error message */
}


void choice_4(movie_n_ll * nll){
    int less_greater;
    float score;
    movie_name * movie_n = nll->root;

    printf("Enter a score: ");
    scanf("%f",&score);
    printf("Less (0) or Greater (1)  %f:",score); /* we receive information from the user */
    scanf("%d",&less_greater);

    movie_n = nll->root;

    while(movie_n != NULL){
        if(less_greater==0 && movie_n->score < score || less_greater==1 && movie_n->score > score)
            printf("%s\n",movie_n->name);  /* we print if less than the entered value */
        movie_n = movie_n->next;
    }
}


void choice_5(movie_b_ll * bll, movie_n_ll * nll,stringlist * genres){

    int i,flag=0,size;
    char name[100];
    movie_budget * movie_b = bll->root;
    movie_name * movie_n;

    printf("Please Enter the name of the movie: ");
    fflush(stdin);
    scanf(" %[^\n]%*c",name);

    for(i=0;i<strlen(name);i++)
        if(name[i]>=65 && name[i]<=90)  /* we turn capital letters to small */
            name[i] = (char) (name[i]+32);

    movie_b = bll->root;
    movie_n = nll->root;

    while(movie_b != NULL){						/* we are looking for the movie whose name is entered */
        if(strcmp(movie_n->name, name)==0){
            flag=1;  /* We use flag to print the error message correctly. */

            if(movie_b->budget == -1)
                printf("Budget:  Unknown\n");  /* Writes unknown to -1 */
            else
                printf("Budget:  %.1f\n",movie_b->budget);

            printf("Genre:  %s\n", movie_n->genre);  /*  print other values */
            printf("Name:  %s\n", movie_n->name);
            printf("Score:  %.3f\n", movie_n->score);
            printf("Year:  %d\n", movie_b->year);
            break;
        }
        movie_b = movie_b->next; /* the list goes on */
        movie_n = movie_n->next;
    }

    if(flag==0){
        printf("No Movie Found ! \n"); /* printing the error message */
    }
}


void choice_6(movie_n_ll * nll){
    double sum;

    movie_name * iter = nll->root;

    while(iter != NULL){
        sum += iter->score;	/* We print the average value by summing the scores */
        iter = iter->next;
    }
    sum /= nll->size;
    printf("Average: %.3f\n",sum);
}


void choice_7(movie_n_ll * nll,stringlist * genres){
    int* counter=(int*)calloc(genres->size,sizeof(int)); /* Creating a counter that will hold the number of genre types */
    int i;

    movie_name * iter = nll->root;

    while(iter != NULL){
        for(i = 0;i<genres->size;i++){
            if(strcmp(genres->list[i], iter->genre) == 0){
                counter[i]++;
                break;
            }
        }
        iter = iter->next;
    }
    for(i =0;i<genres->size;i++){
        printf("%-20s%5d\n",genres->list[i],counter[i]); /* results are printing */
    }
}

/************************************************************************************************************************************************/

int main(){
    int choice = 0;
    movie_b_ll * bll_default_sorted = NULL;
    movie_n_ll * nll_default_sorted = NULL;
    movie_b_ll * bll_score_sorted   = NULL;
    movie_n_ll * nll_score_sorted   = NULL;
    movie_b_ll * bll_budget_sorted  = NULL;
    movie_n_ll * nll_budget_sorted  = NULL;
    movie_b_ll * bll_name_sorted    = NULL;
    movie_n_ll * nll_name_sorted    = NULL;
    movie_b_ll * bll_genre_sorted    = NULL;
    movie_n_ll * nll_genre_sorted    = NULL;

    stringlist * genres             = NULL;			/* According to c90 standards, variables must be defined at the beginning of the function. */

    readAllData(&bll_default_sorted, &nll_default_sorted,
                &bll_budget_sorted,  &nll_budget_sorted,
                &bll_score_sorted,   &nll_score_sorted,		/* We call our function that will do the reading */
                &bll_name_sorted,    &nll_name_sorted,
                &bll_genre_sorted,    &nll_genre_sorted,
                &genres, "Movies.txt");

    while(choice!=8){
        printf("\n1. List of the Sorted Data\n2. List of the Genres\n3. List of the Movie Through the Years\n4. List of the movie Through the Scores\n5. All Informations of a Single Movie \n6. Average of the IMDB Scores\n7. Frequence of the Genres\n8. Exit \n\nPlease select an operation: ");

        scanf("%d",&choice);

        if(choice<1 || choice>8){

            printf("\nTRY AGAIN.\n\n"); /* error message */
            continue;
        }
        switch(choice){
            case 1:
                choice_1(   bll_default_sorted,
                            nll_default_sorted,
                            bll_score_sorted,
                            nll_score_sorted,
                            bll_budget_sorted,
                            nll_budget_sorted,
                            bll_name_sorted,
                            nll_name_sorted,
                            bll_genre_sorted,
                            nll_genre_sorted, genres);		/* appropriate functions are called based on choices made by the user */
                break;
            case 2:
                choice_2(genres);
                break;
            case 3:
                choice_3(bll_default_sorted);
                break;
            case 4:
                choice_4(nll_score_sorted);
                break;
            case 5:
                choice_5(bll_name_sorted, nll_name_sorted,  genres);
                break;
            case 6:
                choice_6(nll_score_sorted);
                break;
            case 7:
                choice_7(nll_default_sorted, genres);
                break;
        }
    }
}