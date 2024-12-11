#pragma once
#include <stdint.h>
#include "GLCD/GLCD.h" 

//I splitted the gameboard in 8x8 pixel cells, all entities 
//and behaviour are within this drawing constraints.
#define GAME_ROWS 34
#define GAME_COLUMNS 30

//Types of map cell
typedef enum : uint8_t {
	smallDot, //Small Dot
	largeDot, //Large Dot
	vWall, 		//Vertical Wall
	hWall, 		//Horizontal Wall
	tlAngle, 	//TopLeft Corner
	trAngle, 	//TopRigth Corner
	blAngle, 	//BottomLeft Corner
	brAngle, 	//BottomRight Corner
	pacman, 	//The one and only PAC-MAN
	teleport, //The famous PAC-MAN effect tile
	blank 		//Empty cell
} cellType;

//Everyone can check the Game State with the matrix
extern cellType GameState[GAME_ROWS][GAME_COLUMNS];

//Draw functions
int initGame();
void DrawBlank( uint16_t, uint16_t, uint16_t);
int DrawPoint( uint16_t, uint16_t, cellType, uint16_t, uint16_t);
int DrawWall( uint16_t, uint16_t, cellType, uint16_t, uint16_t);