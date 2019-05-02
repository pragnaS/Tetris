//Pieces.c file
//This file describes the shapes and all possible rotations of the tetris pieces

#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "Pieces.h"

//Definition of tetris pieces

char pieces[5][4][3][3]= //5 pieces, 4 rotations, 3 by 3 shape
{
	//Square
	{
		{
		{0,0,0},
		{0,2,1},
		{0,1,1}
		},
		{
		{0,0,0},
		{0,2,1},
		{0,1,1}
		},
		{
		{0,0,0},
		{0,2,1},
		{0,1,1}
		},
		{
		{0,0,0},
		{0,2,1},
		{0,1,1}
		}
	},
	//L-piece
	{
		{
			{0,0,0},
			{0,1,0},
			{0,2,1}
		},
		{
			{0,0,0},
			{0,1,0},
			{1,2,0}
		},
		{
			{0,0,0},
			{0,1,1},
			{0,2,0}
		},
		{
			{0,0,0},
			{1,1,0},
			{0,2,0}
		}
	},
	//Z-piece
	{
		{
			{0,0,0},
			{0,2,1},
			{1,1,0}
		},
		{
			{0,0,0},
			{1,2,0},
			{0,1,1}
		},
		{
			{1,0,0},
			{1,2,0},
			{0,1,0}
		},
		{
			{0,0,1},
			{0,2,1},
			{0,1,0}
		}
	},
	//T-piece
	{
		{
			{0,0,0},
			{0,2,0},
			{1,1,1}
		},
		{
			{1,1,1},
			{0,2,0},
			{0,0,0}
		},
		{
			{0,0,1},
			{0,2,1},
			{0,0,1}
		},
		{
			{1,0,0},
			{1,2,0},
			{1,0,0}
		}
	},
	//I-piece
	{
		{
			{0,1,0},
			{0,2,0},
			{0,1,0}
		},
		{
			{0,0,0},
			{1,2,1},
			{0,0,0}
		},
		{
			{0,1,0},
			{0,2,0},
			{0,1,0}
		},
		{
			{0,0,0},
			{1,2,1},
			{0,0,0}
		}
	}
};


//This function returns the type of block in the piece
//Output: 0 if no block, 1 if it is a block, 2 if it is a pivot block
//Input: pieceType, rotation, x, y

int getBlockType(int pieceType, int rotation, int x, int y)
{
	return pieces[pieceType][rotation][x][y];
}


		