/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"



void test_clean_file () 
{
	char* infile="infile.txt";
	char* outfile="outfile.txt";
	char* words_to_delete[WORDSIZE]={"deneme","araba"};   /* we pass the required variables */
	int number_of_words=2;

	clean_file(infile,outfile,words_to_delete,number_of_words);
}


void test_maze_move ()
{
	cell_type maze[][8]={

		{cell_wall,    cell_wall,  cell_wall,    cell_wall,    cell_wall,    cell_wall,   cell_wall,    cell_wall},
		{cell_wall,    cell_target,cell_free,    cell_free,    cell_wall,    cell_free,   cell_free,    cell_wall},
		{cell_wall,    cell_free,  cell_wall,    cell_free,    cell_wall,    cell_free,   cell_wall,    cell_wall},
		{cell_wall,    cell_free,  cell_wall,    cell_free,    cell_wall,    cell_free,   cell_free,    cell_wall},
		{cell_wall,    cell_free,  cell_wall,    cell_free,    cell_free,    cell_wall,   cell_free,    cell_wall},
		{cell_wall,    cell_free,  cell_wall,    cell_wall,    cell_free,    cell_wall,   cell_free,    cell_wall},
		{cell_wall,    cell_free,  cell_free,    cell_p1,      cell_free,    cell_free,   cell_p2,      cell_wall},
		{cell_wall,    cell_wall,  cell_wall,    cell_wall,    cell_wall,    cell_wall,   cell_wall,    cell_wall}
	};
	printf("%d",maze_move(maze,cell_p2,move_left));  /* I created the maze map but could not find enough time */
}



void test_towers_of_hanoi ()
{
	 int i;
	  for(i = 0;i<N;i++){   /* I fill the first tower as 1234567 and call all the others 000000 */
        tower[0][i] = N-i;
        tower[1][i] = 0;
        tower[2][i] = 0;
    }
    towers_of_hanoi('S', 'E', 'A', N);
   
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
