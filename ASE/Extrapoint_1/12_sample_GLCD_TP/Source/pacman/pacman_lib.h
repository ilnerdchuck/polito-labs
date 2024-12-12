#pragma once
#include <stdint.h>
#include "GLCD/GLCD.h" 

//I splitted the gameboard in 8x8 pixel cells, all entities 
//and behaviour are within this drawing constraints.
#define GAME_ROWS 34
#define GAME_COLUMNS 30
#define SCORE_XOFFSET 180
#define SCORE_YOFFSET 16
#define TIME_XOFFSET 42
#define TIME_YOFFSET 16

#define TEXT_OFFSET 32
#define CELL_DIM 8

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

//type to handle pacman direction
typedef enum : uint8_t {
	pmUp, 		//PAC-MAN facing Up
	pmDown, 	//PAC-MAN facing Down
	pmLeft,  	//PAC-MAN facing Left
	pmRight,	//PAC-MAN facing Right
} pmDir;

typedef struct{
	uint8_t pmXpos;			//Current X position
	uint8_t pmYpos;		 	//Current Y position
	pmDir   pmCurrDir; 	//Current Direction
	pmDir   pmNextDir; 	//Next requested Direction
}pmState;

//Everyone can check the Game State with the matrix
extern cellType GameState[GAME_ROWS][GAME_COLUMNS];
extern uint16_t gamePoints;
extern pmState pacmanState;
extern uint16_t gameTime;
extern uint16_t playerPoints;

//Draw functions
int initGame();
void DrawTime(uint16_t);
void DrawScore(uint16_t);
void DrawBlank( uint16_t, uint16_t, uint16_t);
void DrawPacman( uint16_t, uint16_t, pmDir, uint16_t, uint16_t);
void DrawFilledPacman( uint16_t, uint16_t, uint16_t, uint16_t);
int DrawPoint( uint16_t, uint16_t, cellType, uint16_t, uint16_t);
int DrawWall( uint16_t, uint16_t, cellType, uint16_t, uint16_t);

//Movement functions
void updatePacmanPos(pmDir);
int CheckNextPos(pmDir);


