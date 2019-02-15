#include "life.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * @author Ashley Hendrickson, Jake Miller
 * methods used in the game of life
 */

/* @param x: takes in the height of the grid
 * @param y: takes in the length of the grid
 * @return grid: returns the gride
 * get_grid creates new memory for a "grid".
 */
char** get_grid(int x, int y){
	// allocates memory of size x to the grid
	char** grid = (char**) malloc(x * sizeof(char*));
	// if memory can't be allocated, fail
	if(grid == NULL){
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	// allocate memory to each column of grid
	for(int i = 0; i < x; i++){
		grid[i] = malloc(y * sizeof(int));
	// if memory can't be allocated, fail	
		if(grid[i] == NULL){
			fprintf(stderr, "out of memory\n");
			exit(1);
		}
	}
	return grid;
}

/*
 * @param x the height
 * @param y the width 
 * @param grid returns the grid 
 *
 * print_grid attempts to print out the grid of x and y
 * */
void print_grid(int x, int y, char** grid){
	printf("\n");

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			printf("%x", grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* @param x: takes in the heighth
 * @param y: takes in the width 
 * @param grid: takes the current grid 
 * @return future: returns a new grid modified to Conway's rules
 * 
 * mutate takes a grid and mutates that grid
 * according to Conway's rules.  
 */
char** mutate(int x, int y, char** grid){
	char** future = get_grid(x, y); 

  	// Loop through every cell 
        for (int l = 0; l < x; l++) 
        { 
            for (int m = 0; m < y; m++) 
            { 
                // Implementing the Rules of Life 
  
                // Cell is lonely and dies 
                if ((grid[l][m] == '\001') && (get_neighbors(l, m, x, y, grid) < 2)) 
                    future[l][m] = '\000'; 
  
                // Cell dies due to over population 
                else if ((grid[l][m] == '\001') && (get_neighbors(l, m, x, y, grid) > 3)) 
                    future[l][m] = '\000'; 
  
                // A new cell is born 
                else if ((grid[l][m] == '\000') && (get_neighbors(l, m, x, y, grid) == 3)) 
                    future[l][m] = '\001'; 
  
                // Remains the same 
                else
                    future[l][m] = grid[l][m]; 
            } 
        }
	return future;
}

/* @param i checks the element on the right
 * @param j checks the element on the left
 * @param x checks the element on the top
 * @param y checks the element on the bottom
 * @param grid takes in the grid 
 * @return -1 if the process fails otherwise return number of neighbors
 *
 * get_neighbors is a helper method that returns
 * the number of live neighbors a cell has.
 */
int get_neighbors(int i, int j, int x, int y, char** grid){
	// elements must be greater then zero and i must be greater
	// then x and j must be greater then y
	if(i >= 0 && i < x && j >= 0 && j < y){
		int count = 0;
		if(grid[i][(j+1)%y] == '\001'){
			count++;
		}
		if(grid[i][(y+j-1)%y] == '\001'){
			count++;
		}
		if(grid[(i+1)%x][j] == '\001'){
			count++;
		}
		if(grid[(x+i-1)%x][j] == '\001'){
			count++;
		}
		if(grid[(i+1)%x][(j+1)%y] == '\001'){
			count++;
		}
		if(grid[(x+i-1)%x][(j+1)%y] == '\001'){
			count++;
		}
		if(grid[(x+i-1)%x][(y+j-1)%y] == '\001'){
			count++;
		}
		if(grid[(i+1)%x][(y+j-1)%y] == '\001'){
			count++;
		}
		return count;
	}
	printf("Out of bounds!");	
	return -1;
}
