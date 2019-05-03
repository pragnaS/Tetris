#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "Pieces.h"
#include "tetris_grid.h"

#define GRID_WIDTH 12		//board width in blocks
#define GRID_HEIGHT 16		//board height in blocks
#define FREE 0						//free position on board
#define FILLED 1						//filled position on board

int grid[GRID_WIDTH][GRID_HEIGHT];

//This function initialises the tetris grid

void Grid_Init(void)
{
	for(int i=0; i<GRID_WIDTH; i++)
	{
		for(int j=0; j<GRID_HEIGHT; j++)
		{
			grid[i][j]=FREE;
		}
	}
}

//This function stores the piece in the grid by filling the appropriate blocks with FILLED
void Store_Piece(int x, int y, int pieceType, int rotation)
{
	int pieceI=0, pieceJ=0;
	for(int i=x; i<x+3; i++)
	{
		for(int j=y; j<y+3; j++)
		{
				if(getBlockType(pieceType, rotation, pieceI, pieceJ)!=0)
					grid[i][j]=FILLED;
				
				pieceJ++;	
		}
		pieceI++;
	}
}

//This function checks if the game is over when a piece reaches the topmost row
//Output: 1 if game is over, 0 if game is not over
int isGameOver(void)
{
	for(int i=0; i<GRID_WIDTH; i++)
	{
		if(grid[i][0]==FILLED)
			return 1;
	}
	return 0;
}

//This function erases a line that is completely filled and moves all the upper rows one row down
//Inputs: Vertical position of the line to delete
void DeleteLine(int y)
{
	for(int i=y; i>0; i--)
	{
		for(int j=0; j<GRID_WIDTH; j++)
		{
			grid[j][i]=grid[j][i-1];
		}
	}
}

//This function deletes all the lines that should be removed
void DeletePossibleLines()
{
	for(int j=0; j<GRID_HEIGHT; j++)
	{
		int i=0;
		while(i<GRID_WIDTH)
		{
			if(grid[i][j]!=FILLED)
				break;
			i++;
		}
		if(i==GRID_WIDTH)
			DeleteLine(j);
	}
}

//This function checks if a block in the grid is free or not 
//Inputs: x is the horizontal cooridinate, y is the vertical coordinate
//Output: 1 if it is not a free block, 0 if it is a free block
int isFreeBlock(int x, int y)
{
	if(grid[x][y]==FREE)
		return 0;
	else
		return 1;
}


//This function checks for possible collisions
//Output: 1 if move is possible, 0 if move is not possible
int isMovePossible(int x, int y, int pieceType, int rotation)
{
	int pieceI=0, pieceJ=0;
	for(int i=x; i<x+3; i++)
	{
		for(int j=y; j<y+3; j++)
		{
			//checking if piece is outside the board
			if(i<0 || i>GRID_WIDTH || j>GRID_HEIGHT)
			{
				if(getBlockType(pieceType, rotation, pieceI, pieceJ)!=0)
					return 0; 	//move is not possible
			}
			
			//checking if piece has collisioned with a filled block
			if(j>0)
			{
				if(getBlockType(pieceType, rotation, pieceI, pieceJ)!=0 && isFreeBlock(i,j)==1)
					return 0;  //move not possible
			}
			pieceJ++;
		}
		pieceI++;
	}
	return 1; //move is possible
}

//This function returns the coordinate (in pixels) of the block
//Input: coordinate of the block in the grid
int GetPosinPixels(int pos)
{
	return(10*pos);
}




