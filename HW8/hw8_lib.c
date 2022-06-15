/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include <stdlib.h>
#include "hw8_lib.h"
#define MAXLINE 500 /* the number of words in a line */

/* Despite my long efforts, this part has not worked properly. */


int word_length(char*word,int counter){ /* the function that gives the length of the word */

	if(*word=='\0')	/* We see if we have reached the end of the word */
		return counter;
	else
		word_length(word+1,++counter);
}

int compare_function(char word[],char*words_to_delete[WORDSIZE],int length,int i,int counter2,int counter3){  /* our comparison function */

	
	if(word==words_to_delete[i]){
		if(length!=counter2)
			if(i+1>length)
				compare_function(word+1,words_to_delete,length,i+1,++counter2,counter3);

		else if(length==counter2){
			compare_function(word,words_to_delete+1,length,0,0,++counter3);		/* Returns 1 if the word sent to this function is among those to be deleted */
			return 1;
		}
	}
	else{ 
		if(counter3==WORDSIZE)	/* If all words are checked, return 2 is done. Refers to WORKSIZE word count */
			return 2;
		compare_function(word,words_to_delete+1,length,0,0,++counter3);   
		
	}
}


void write_function(FILE* outfid,int compare,char*word){  /* The writing function performs the writing process according to the result. */

	if(compare==1) /* if the incoming value is 1, nothing will be done */
		return;
	else
		fprintf(outfid,"%s ",word); /* If not 1, it will be written */
}

int found_function(FILE* outfid,char* c,char*word,char*words_to_delete[WORDSIZE],int number_of_words){  /* find function extracts words in the line */

	int length,counter=0,counter2=0,counter3=0,i=0,compare=0;
	
	if(number_of_words==0)
		return;
	else	
	sscanf(c,"%s",word);	 /* I used sscanf to get the words from array */
	
	length=word_length(word,counter);
	compare=compare_function(word,words_to_delete,length,i,counter2,counter3);   /* required values sent to functions */
	write_function(outfid,compare,word);
	found_function(outfid,c+length,word+1,words_to_delete,number_of_words-1);
}

int delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE], int number_of_words){
	char word[50];
	char c[MAXLINE];
	
	if(feof(infid))  /* Check if the input text is finished */
		return;
	else{
		fgets(c,MAXLINE,infid);  /* Read line by line with fgets */
		found_function(outfid,c,word,words_to_delete,number_of_words);
		delete_words (infid, outfid, words_to_delete,number_of_words);
	}	
}

void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words) /* files opened in this function */
{
	FILE* infid=fopen(infile,"r");
	FILE* outfid=fopen(outfile,"w");
	
	delete_words (infid, outfid, words_to_delete, number_of_words);
	return;
	
}

int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
	
	printf("maze_move NOT IMPROVED :( !\n");    /* I could not complete this section in enough time */
												/* I made the main part */	


}



void printTower(int step_number){ /* IMPORTANT INFORMATION! I added some variables I used here to the .h file because I have defined them globally. */
    
    int i,j,k;
    for(i = 0;i<(N*2+4)*3+3;i++)  /* We printed the = sign */
        printf("=");

    printf("\n=");
    for(i = 0;i<((N*2+4)*3+3)/2-4;i++)
        printf(" ");
    printf("Step%3d",step_number);  /* printing step */			/* In this section, I made the printing process according to the calculations I made in general. */
    for(i = 0;i<((N*2+4)*3+3)/2-4;i++)
        printf(" ");
    printf("=\n");  /* we went to the bottom line */

    for(i = 0;i<(N*2+4)*3+3;i++)
        printf("=");
    printf("\n");	/* we went to the bottom line */

    printf("%*c%*c%*c\n",N+3,'S',2*N+4,'A',2*N+4,'E');

    for(i = 0;i<N;i++){											/* How much space does a piece with the words 1,2,3 ... take up horizontally?, The answer to this question is 2*x + 3 */
        for(j = 0;j<3;j++){										/* Since the largest piece is N,2N+3 So for me to average the little pieces /*                                  */
            printf(" ");										/*  I need to leave ((2N + 3) - (2x + 3)) /2 spaces before I put the piece */
            for(k = 0;k<(N*2+3-tower[j][N-i-1]*2-3)/2;k++)		/* Likewise after putting the piece I put up this much space again*/
                printf(" ");
            if(tower[j][N-i-1] != 0)
                for(k = 0;k<tower[j][N-i-1]*2+3;k++)
                    printf("*");  /* print the * mark */
            else
                printf("   ");
            for(k = 0;k<(N*2+3-tower[j][N-i-1]*2-3)/2;k++)	/*The main purpose of this column is to leave the correct number of spaces from the right and left */	
                printf(" ");								/* and write the number and the part of the tower in the Middle. */

        }
        printf("\n");/*  went to the bottom line */
        for(j = 0;j<3;j++){
            printf(" ");
            for(k = 0;k<(N*2+3-tower[j][N-i-1]*2-3)/2;k++)
                printf(" ");
            if(tower[j][N-i-1] != 0)
                printf("*%*s%d%*s*", tower[j][N-i-1]-tower[j][N-i-1]/10+tower[j][N-i-1]/20," ", tower[j][N-i-1], tower[j][N-i-1], " "); /* this part for example to write * 5 *   */
            else
                printf("   ");
            for(k = 0;k<(N*2+3-tower[j][N-i-1]*2-3)/2;k++)		/* my printing section is basically three parts*/
                printf(" ");									/* Someone for the top of the piece, and someone for the part where the number will be written.*/
        }														/*After writing all pieces with the third For the base of the last piece */
        printf("\n");

        for(j = 0;j<3;j++){
            if(i == N-1){
                printf(" ");
                for(k = 0;k<(N*2+3-tower[j][N-i-1]*2-3)/2;k++)
                    printf(" ");
                if(tower[j][N-i-1] != 0)
                    for(k = 0;k<tower[j][N-i-1]*2+3;k++)
                        printf("*"); /*  print the * mark */
                else
                    printf("   ");
                for(k = 0;k<(N*2+3-tower[j][N-i-1]*2-3)/2;k++)
                    printf(" ");
            }
        }
    }
    printf("\n");
}


void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
	int i, j, from, to;   /* I have defined variables both outside and inside i did this because i got an error*/
	  
	  if(n==1){					/* this part is valid when n is 1 i.e. the last stage */
        int i, j, from, to;		

        if(start_peg == 'S')
            from = 0;
        else if(start_peg == 'A')  /* We match char values with their integer counterparts */
            from = 1;
        else if(start_peg == 'E')
            from = 2;
        if(end_peg == 'S')
            to = 0;
        else if(end_peg == 'A')
            to = 1;
        else if(end_peg == 'E')
            to = 2;

        for(i = N-1;i>=0;i--){		 /* We have to transfer from start to end But to make this transfer, what is at the top of the Start What is at the top of the end I need to know these.*/
            if(tower[from][i] != 0)  /*So I'm going down with i and j so they stop when I see something other than 0 */
                break;
        }
        for(j = N-1;j>=0;j--){
            if(tower[to][j-1] != 0)
                break;
        }
        if(j == -1)
            j = 0;
        tower[to][j] = tower[from][i];  /* we transfer from one tower to another */
        tower[from][i] = 0;

        ++step;				/*I incremented the step variable that holds the number of functions.*/
        printTower(step);  /* I print the step part */
        return;
    }
    
    towers_of_hanoi(start_peg, aux_peg, end_peg, n-1);  /* the part where the function recalls itself */
    
    if(start_peg == 'S')		/* this is valid when part n is not 1 */
        from = 0;
    else if(start_peg == 'A')  /* We match char values with their integer counterparts */
        from = 1;
    else if(start_peg == 'E')
        from = 2;
    if(end_peg == 'S')
        to = 0;
    else if(end_peg == 'A')
        to = 1;
    else if(end_peg == 'E')
        to = 2;

    for(i = N-1;i>0;i--){		 /* We have to transfer from start to end But to make this transfer, what is at the top of the Start What is at the top of the end I need to know these.*/
        if(tower[from][i] != 0)  /*So I'm going down with i and j so they stop when I see something other than 0 */
            break;
    }
    for(j = N-1;j>=0;j--){
        if(tower[to][j-1] != 0)
            break;
    }
    if(j == -1)
        j = 0;
    tower[to][j] = tower[from][i];  /* we transfer from one tower to another */
    tower[from][i] = 0;


    ++step;	/*I incremented the step variable that holds the number of functions.*/
    printTower(step);
    towers_of_hanoi(aux_peg, end_peg, start_peg, n-1);  /* the part where the function recalls itself */
}
