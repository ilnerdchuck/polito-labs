#pragma once
 
#include <stdint.h>
#include "GLCD/GLCD.h" 
#include "CAN/CAN.h"
#include "../music/music.h"
#include "joystick/joystick.h"
#include "RIT/RIT.h"
#include "adc/adc.h"
#include "button_EXINT/button.h"

//I splitted the gameboard in 8x8 pixel cells, all entities 
//and behaviour are within this drawing constraints.
#define GAME_ROWS 26
#define GAME_COLUMNS 30
#define SCORE_XOFFSET 180
#define SCORE_YOFFSET 16
#define TIME_XOFFSET 42
#define TIME_YOFFSET 16
#define TEXT_OFFSET 64
#define CELL_DIM 8
#define N_LARGE_DOT 6
#define RANDOM_BUFFER 5
#define LIVES_OFFSET GAME_ROWS*CELL_DIM+TEXT_OFFSET

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
	blank, 		//Empty cell
	blinky,	  //Fantasmino
	intersection, //Intersection for blinky movement
	emptyinter //Intersection for blinky movement
} cellType;

//type to handle pacman direction
typedef enum : uint8_t {
	pmUp, 		//PAC-MAN facing Up
	pmDown, 	//PAC-MAN facing Down
	pmLeft,  	//PAC-MAN facing Left
	pmRight,	//PAC-MAN facing Right
	pmStuck		//PAC-MAN facing a wall
} pmDir;

typedef struct{
	uint8_t pmXpos;			//Current X position
	uint8_t pmYpos;		 	//Current Y position
	pmDir   pmCurrDir; 	//Current Direction
	pmDir   pmNextDir; 	//Next requested Direction
	//EXTRA for animation
	uint8_t aFrame;
	uint8_t pmOldXpos;			//Current X position
	uint8_t pmOldYpos;		 	//Current Y position
	cellType oldCell;
}pmState;

//Everyone can check the Game State with the matrix
extern cellType GameState[GAME_ROWS][GAME_COLUMNS]; //Handles the game map status
extern uint16_t gamePoints;					//Handles how many pills are in the map
extern pmState pacmanState;					//Handles pacman status
extern pmState blinkyState;					//Handles the fantasmino
extern uint8_t gameTime;						//Handles game time
extern uint16_t playerPoints;				//Handles the game score
extern uint8_t playerLives;					//Handles the amount of player lives
extern uint8_t gameStatus;					//Handles if the fame is Running-Won-Paused-Losed
extern uint8_t largeDotRemaining;		//Handels how many large dots need to spawn
extern uint8_t playEat;							//Handles the enable signal to play the sound when eating
extern uint8_t powerUP;							//Handles if the player has taken a powerup if >0 has power up
//Draw functions
int initGame();
void DrawTime(uint8_t, uint16_t, uint16_t);
void DrawScore(uint16_t, uint16_t, uint16_t);
void DrawBlank( uint16_t, uint16_t, uint16_t);
void DrawPacman( uint16_t, uint16_t, pmDir, uint16_t, uint16_t);
void DrawFilledPacman( uint16_t, uint16_t, uint16_t, uint16_t);
int DrawPoint( uint16_t, uint16_t, cellType, uint16_t, uint16_t);
int DrawWall( uint16_t, uint16_t, cellType, uint16_t, uint16_t);
void DrawMiddleText();
void DrawLives(uint8_t);
void animateFrame();

//Fantasmoni things
void DrawBlinky( uint16_t Xpos, uint16_t Ypos,pmDir dir,uint16_t pmColor,uint16_t bkColor);
void updateBlinkyPos();
//cellType GetNextBlinkyCellType(pmDir nextDir);
void animateBlinkyFrame();
int checkIntersection();
//Movement functions
cellType GetNextCellType(pmDir);
void updatePacmanPos(pmDir);

//Utility funcitons
int init_hardware();
int CheckIfWall(cellType);
int CheckIfAngle(uint8_t, uint8_t);
int UpdateScore(cellType);
void SetGameWon();
void SetGameOver();
void PauseToggle();
void SpawnLargeDot();
int getRandomDecision();
void SendCanInfo();