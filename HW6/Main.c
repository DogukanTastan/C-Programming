#include <stdio.h>
#include <stdlib.h>
#define N 4           /* I define constant N */

/* I used /*  in the comment lines to prevent the program from failing when compiled as gcc -ansi -pedantic-errors 1901042627.c */

enum{
    UP, DOWN, RIGHT, LEFT    /* I have defined an enum that indicates the directions of motion */
};


void move(int map[N][N], int x, int y, int move){   /* Motion function for 4 different directions.The function contains the map array as input, the coordinates of the selected point,and the command */

    int i;
    int pivot;  /* We use the pivot to find the empty value in the map */

    if(move == UP){ /* UP */
        pivot = -1;
        for(i = 1;i<=y;i++){
            if(map[y-i][x] == N*N){   /* I took the N * N value as the value of the space in the map */
                pivot = y-i;  /* we equate the pivot to the distance of the gap to the point we have chosen.*/
            }
        }

        if(pivot != -1){  /* If the pivot is not -1, then we found the gap.We can do the scrolling */
            for(i = pivot;i<y;i++){
                map[i][x] = map[i+1][x];
            }
            map[i][x] = N*N;
        }else printf("Invalid command ! \n\n"); /* If the pivot is still -1, we print an error message */

    }else if(move == DOWN){ /* DOWN */
        pivot = -1;					   /* operations here are similar to the above */
        for(i = 1;i<N-y;i++){
            if(map[y+i][x] == N*N){   /* I took the N * N value as the value of the space in the map */
                pivot = y+i;
            }
        }

        if(pivot != -1){
            for(i = pivot;i>y;i--){
                map[i][x] = map[i-1][x];
            }
            map[i][x] = N*N;
        }else printf("Invalid command ! \n\n");  /* If the pivot is not -1, then we found the gap.We can do the scrolling */

    }else if(move == RIGHT){ /* RIGHT */
        pivot = -1;

        for(i = 1;i<N-x;i++){
            if(map[y][x+i] == N*N){   /* Since we are looking to the right and left, it is enough to search the gap on a single axis. */
                pivot = x+i;
            }
        }

        if(pivot != -1){                      /*  other operations are similar */
            for(i = pivot;i>x;i--){
                map[y][i] = map[y][i-1];
            }
            map[y][i] = N*N;
        }else printf("Invalid command ! \n\n");

    }else if(move == LEFT){ /* LEFT */
        pivot = -1;
        for(i = 1;i<=x;i++){
            if(map[y][x-i] == N*N){
                pivot = x-i;
            }
        }

        if(pivot != -1){
            for(i = pivot;i<x;i++){
                map[y][i] = map[y][i+1];
            }
            map[y][i] = N*N;
        }else printf("Invalid command ! \n\n");

    }

}


void random_place(int map[N][N]){  /* in this function we are scrambling the map */
    
    int i, random;
    int x = N-1, y = N-1;

    for(i = 0;i<N*N;i++)
        map[i/N][i%N] = (i/N)*N+i%N+1;  /*  Here, we fill the arrays up to N * N with the formula I developed. */

    for(i = 0;i<2048;i++){  /*  we manually mix.I chose to shuffle 2048 times */
        random = rand()%4;  /* we select the order of the operation with the rand function. However,the values of this function do not change without turning off the computer. */
        if(random == UP){
            if(y-1 >= 0) {
                move(map, x, y - 1, DOWN);
                y--;
            }
        }else if(random == DOWN){
            if(y+1 < N){
                move(map, x, y+1, UP);                   /* we ship to functions according to different directions for mixing */
                y++;
            }
        }else if(random == RIGHT){
            if(x+1 < N){
                move(map, x+1, y, LEFT);
                x++;
            }
        }else if(random == LEFT){
            if(x-1 >= 0){
                move(map, x-1, y, RIGHT);
                x--;
            }
        }
    }
}


void show(int map[N][N]){     /* this is the function we print the map */
    int i, j;
    for(i = 0;i<N;i++){
        for(j= 0;j<6*N+1;j++) printf("*");   /*  we print * s based on N for our table shape */
        	printf("\n*");
        for(j = 0;j<N;j++){
            if(map[i][j] == N*N)    /* we check the gap value */
                printf("  x  *");  
            else
                printf("%3d  *",map[i][j]);  /* We print the elements of the map */
        }
        printf("\n");
    }
    for(j= 0;j<6*N+1;j++) printf("*");   /* we print * s based on N for our table shape */
    printf("\n");
}


int solve_check(int map[N][N]){  /* In this function, we check whether the puzzle is solved or not.This function only returns 1 and 0 */

	int i,solved;
	solved = 1;
	
	for(i = 0;i<N*N;i++){
    	if(map[i/N][i%N] != i+1) solved=0;  /* If the order of the values does not match in this function that I have shortened, the value to return will be 0. */
	}
    return solved; /* return the value */
}


int main() {  /* main function */
    
    int map[N][N],check,x,y,command;  /* defined variables */
    random_place(map);   /*  We are confusing the map */
    show(map);   /* And printing the map */
    
    while(1){  /* The loop that will keep the program running continuously */

	    check=solve_check(map);
	    if(check==1)			/*We check the unwinding status of the puzzle. If it is solved, the value coming will be 1 and the loop will break */
	    	break;

	    printf("\nEnter the x coordinate (Starting from 0): ");    /* we get the values from the user. x value increases towards the right */
	    scanf("%d",&x);

	    printf("Enter the y coordinate (Starting from 0): ");     /*we get the values from the user. y value increases as it goes down */
	    scanf("%d",&y);
	    
	    printf("Enter command: Up=0, Down=1, Right=2, Left=3: \n");
	    scanf("%d",&command);

		if(command==0){
			move(map,x,y,command);     
			show(map);
		}
		else if(command==1){
			move(map,x,y,command);		/* We send it to the function according to the command value we receive. */
			show(map);					
		}
		else if(command==2){
			move(map,x,y,command);
			show(map);					/* After sending, we print the changed map (show(map)) */
		}
		else if(command==3){
			move(map,x,y,command);
			show(map);	
		}
		else
		printf("\nYou made the wrong choice!\n");   /* If the entered value does not match, we print the error message */
    }
    printf("Congratulations! Solved the puzzle \n");  /* If the loop is exited, the puzzle is solved, congratulations message is printed. */
    return 0;
}