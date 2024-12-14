#include "pacman/pacman_lib.h"
#include <stdio.h>

//Templates for the pixel drawing
uint8_t smallPointTmp[CELL_DIM][CELL_DIM] = {	0,0,0,0,0,0,0,0,
																							0,0,0,0,0,0,0,0,
																							0,0,0,1,1,0,0,0,
																							0,0,1,1,1,1,0,0,
																							0,0,1,1,1,1,0,0,
																							0,0,0,1,1,0,0,0,
																							0,0,0,0,0,0,0,0,
																							0,0,0,0,0,0,0,0};

uint8_t largePointTmp[CELL_DIM][CELL_DIM] = {	0,0,0,0,0,0,0,0,
																							0,0,1,1,1,1,0,0,
																							0,1,1,1,1,1,1,0,
																							0,1,1,1,1,1,1,0,
																							0,1,1,1,1,1,1,0,
																							0,1,1,1,1,1,1,0,
																							0,0,1,1,1,1,0,0,
																							0,0,0,0,0,0,0,0};


uint8_t straightWallTmp[CELL_DIM][CELL_DIM] = {	0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0,
																								0,0,0,1,1,0,0,0};

uint8_t angledWallTmp[CELL_DIM][CELL_DIM] = {	0,0,0,1,1,0,0,0,
																							0,0,0,1,1,0,0,0,
																							0,0,0,1,1,1,0,0,
																							0,0,0,1,1,1,1,1,
																							0,0,0,0,1,1,1,1,
																							0,0,0,0,0,0,0,0,
																							0,0,0,0,0,0,0,0,
																							0,0,0,0,0,0,0,0};

uint8_t pacmanTmp[CELL_DIM][CELL_DIM] = {0,0,1,1,1,1,0,0,
																				 0,1,1,1,1,1,1,0,
																				 1,1,1,1,1,0,0,0,
																				 1,1,1,0,0,0,0,0,
																				 1,1,1,0,0,0,0,0,
																				 1,1,1,1,1,0,0,0,
																				 0,1,1,1,1,1,1,0,
																				 0,0,1,1,1,1,0,0};

uint8_t pacmanFilledTmp[CELL_DIM][CELL_DIM] = {0,0,1,1,1,1,0,0,
																							 0,1,1,1,1,1,1,0,
																							 1,1,1,1,1,1,1,1,
																							 1,1,1,1,1,1,1,1,
																							 1,1,1,1,1,1,1,1,
																							 1,1,1,1,1,1,1,1,
																							 0,1,1,1,1,1,1,0,
																							 0,0,1,1,1,1,0,0};

//TODO: maybe all draw functions add automatically CELL_DIM and TEXT OFFSET
/******************************************************************************
* Function Name  : initGame
* Description    : initialize the game
* Input          : None  
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/
int initGame(){
	int i,j;
	//TODO: try to inspect the LCD_init to see if i can init in all black
	//TODO: benchmark the LCD_Drawline besides painting pixel by pixel with LCD_SetPoint
	//init game text zone and bottom zone
	for(i=0;i<TEXT_OFFSET;++i){
		LCD_DrawLine(0,i,MAX_X,i,Black);
	}
	//bottom
	for(i=GAME_ROWS*CELL_DIM+TEXT_OFFSET;i<MAX_Y;++i){
		LCD_DrawLine(0,i,MAX_X,i,Black);
	}
	//Game time text
	//TODO: function to update Time
	GUI_Text(20, 0, (uint8_t *) "GAME TIME", White, Black);
	//GUI_Text(TIME_XOFFSET, TIME_YOFFSET, (uint8_t *) "60s", White, Black);
	DrawTime(gameTime);
	//Score Text
	//TODO: function to update the score
	GUI_Text(SCORE_XOFFSET, 0, (uint8_t *) "SCORE", White, Black);
	//GUI_Text(SCORE_XOFFSET, SCORE_YOFFSET, (uint8_t *) "00000", White, Black);
	DrawScore(playerPoints);
	for(i=0; i<GAME_ROWS; ++i){
		for(j=0;j<GAME_COLUMNS; ++j){
			if(GameState[i][j]==smallDot || GameState[i][j]==largeDot){
				DrawPoint(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], White, Black);
				++gamePoints;
			}else if(	GameState[i][j]==hWall || GameState[i][j]==vWall || 
								GameState[i][j]==blAngle || GameState[i][j]==brAngle|| 
								GameState[i][j]==tlAngle || GameState[i][j]==trAngle){
				DrawWall(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], Blue, Black);
			}else if(GameState[i][j]==blank){
				DrawBlank(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,Black);
			}else if(GameState[i][j]==teleport){
				DrawBlank(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,Black);
			}else if(GameState[i][j]==pacman){
				DrawPacman(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,pmLeft,Yellow,Black);
				pacmanState.pmXpos = i;
				pacmanState.pmYpos = j;
				pacmanState.pmCurrDir = pmLeft;
				pacmanState.pmNextDir = pmLeft;
			}
		}
	}
	return 0;
}
															
															
//****************************DRAW FUNCTIONS***********************************
/******************************************************************************
* Function Name  : DrawTime
* Description    : Draws Time
* Input          : time: time value to draw 
*				   - bkColor: Background color
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

//TODO: add color input to make it sed when it is low
void DrawTime(uint16_t time){
	uint8_t i, j;
	char timeString[] = "60s";
	//TODO:fix single digit time draws ss
	sprintf(timeString,"%ds",time);
	//Just cicle trough the matrix and draw it
	GUI_Text(TIME_XOFFSET, TIME_YOFFSET,(uint8_t*)timeString, White, Black);
}

/******************************************************************************
* Function Name  : DrawScore
* Description    : Draws Score
* Input          : Score: Score value to draw 
*				   - bkColor: Background color
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

//TODO: add color input
void DrawScore(uint16_t score){
	uint8_t i, j;
	char scoreString[] = "00000";
	if(score<10){
		sprintf(scoreString,"0000%d",score);
	}else if(score<100){
		sprintf(scoreString,"000%d",score);
	}else if(score<1000){
		sprintf(scoreString,"00%d",score);
	}else if(score<10000){
		sprintf(scoreString,"0%d",score);
	}else{
		sprintf(scoreString,"%d",score);
	}
	GUI_Text(SCORE_XOFFSET, SCORE_YOFFSET,(uint8_t*)scoreString, White, Black);
}
/******************************************************************************
* Function Name  : DrawBlank
* Description    : Draws an empty cell
* Input          : - Xpos:  
*                  - Ypos: 
*				   - bkColor: Background color
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

void DrawBlank( uint16_t Xpos, uint16_t Ypos,uint16_t bkColor){
	uint8_t i, j;
	//Just cicle trough the matrix and draw it
	
	for( i=0; i<CELL_DIM; ++i){
		for( j=0; j<CELL_DIM; ++j){
			LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
		}
	}
}

/******************************************************************************
* Function Name  : DrawSmallPoint
* Description    : Draws a small point
* Input          : - Xpos:  
*                  - Ypos: 
*				   - pointColor: Color of the point   
*				   - bkColor: Background color
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

int DrawPoint( uint16_t Xpos, uint16_t Ypos,uint8_t pointType, uint16_t pointColor, uint16_t bkColor){
	uint16_t i, j;
	// Take the correct matrix template to draw the point
	uint8_t (*pointTemplate)[CELL_DIM] = pointType==smallDot? smallPointTmp : pointType==largeDot? largePointTmp: 0;
	if(pointTemplate == 0){
			return -1;
	}
	//Just cicle trough the matrix and draw it
	for( i=0; i<CELL_DIM; ++i){
		for( j=0; j<CELL_DIM; ++j){
			if(pointTemplate[i][j] == 1){
					LCD_SetPoint( Xpos + j, Ypos + i, pointColor);
			}
			else{
					LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
			}
		}
	}
	return 0;
}
/******************************************************************************
* Function Name  : DrawWall
* Description    : Draws angled or straight wall
* Input          : - Xpos:  
*                  - Ypos: 
*				   - ASCI: 
*				   - wallColor: Wall color   
*				   - bkColor: Background color 
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

int DrawWall( uint16_t Xpos, uint16_t Ypos,uint8_t wallType, uint16_t wallColor, uint16_t bkColor){
	uint8_t i, j;
	// Take the correct matrix template to draw the correct wall
	uint8_t (*wallTemplate)[CELL_DIM] = (wallType==hWall || wallType==vWall )? straightWallTmp : 
															(wallType==blAngle || wallType==brAngle 
															||wallType==tlAngle ||wallType==trAngle)? 
															angledWallTmp : 0;
	if(wallTemplate == 0){
		return -1;
	}
	//vWall and blAngle case is the same as the template.
	//The other cases i will read the template matrix to draw the correct
	//orientation of the shape.
	if(wallType == vWall){
		for( i=0; i<CELL_DIM; ++i){
			for( j=0; j<CELL_DIM; ++j){
				if(wallTemplate[i][j] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(wallType == hWall){
		uint8_t i_r;
		uint8_t j_r;
		for( i=0,i_r =0; i<CELL_DIM; ++i, ++i_r){
			for( j=0, j_r = 0; j<CELL_DIM; ++j, ++j_r){
				if(wallTemplate[j_r][i_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(wallType == blAngle){
		for( i=0; i<CELL_DIM; ++i){
			for( j=0; j<CELL_DIM; ++j){
				if(wallTemplate[i][j] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(wallType == brAngle){
		uint8_t i_r;
		uint8_t j_r;
		for( i=0,i_r =0; i<CELL_DIM; ++i, ++i_r){
			for( j=0, j_r = CELL_DIM-1; j<CELL_DIM; ++j, --j_r){
				if(wallTemplate[i_r][j_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(wallType == tlAngle){
		uint8_t i_r;
		uint8_t j_r;
		//
		for( i=0, i_r=CELL_DIM-1; i<CELL_DIM; ++i, --i_r){
			for( j=0, j_r = 0; j<CELL_DIM; ++j, ++j_r){
				if(wallTemplate[i_r][j_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(wallType == trAngle){
		uint8_t i_r;
		uint8_t j_r;
		for( i=0, i_r=CELL_DIM-1; i<CELL_DIM; ++i, --i_r){
			for( j=0, j_r=CELL_DIM-1; j<CELL_DIM; ++j, --j_r){
				if(wallTemplate[i_r][j_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}
	return 0;
}

/******************************************************************************
* Function Name  : DrawPacman
* Description    : Draws PAC-MAN
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

void DrawPacman( uint16_t Xpos, uint16_t Ypos,pmDir dir,uint16_t pmColor,uint16_t bkColor){
	uint8_t i, j;
	uint8_t i_r, j_r;
	//Draw pacman as needed by the orientation 
	if(dir == pmRight){
		for( i=0; i<CELL_DIM; ++i){
			for( j=0; j<CELL_DIM; ++j){
				if(pacmanTmp[i][j] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, pmColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(dir == pmLeft ){
		uint8_t i_r;
		uint8_t j_r;
		for( i=0,i_r=CELL_DIM-1; i<CELL_DIM; ++i, --i_r){
			for( j=0, j_r=CELL_DIM-1; j<CELL_DIM; ++j, --j_r){
				if(pacmanTmp[i_r][j_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, pmColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(dir == pmUp){
		uint8_t i_r;
		uint8_t j_r;
		for( i=0,i_r=CELL_DIM-1; i<CELL_DIM; ++i, --i_r){
			for( j=0, j_r=0; j<CELL_DIM; ++j, ++j_r){
				if(pacmanTmp[j_r][i_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, pmColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(dir == pmDown){
		uint8_t i_r;
		uint8_t j_r;
		for( i=0,i_r =0; i<CELL_DIM; ++i, ++i_r){
			for( j=0, j_r = 0; j<CELL_DIM; ++j, ++j_r){
				if(pacmanTmp[j_r][i_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, pmColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}
}

/******************************************************************************
* Function Name  : DrawFilledPacman
* Description    : Draws a chonky PAC-MAN
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

void DrawFilledPacman( uint16_t Xpos, uint16_t Ypos, uint16_t pmColor,uint16_t bkColor){
	uint8_t i, j;
	uint8_t i_r, j_r;
	//Draw pacman as needed by the orientation 	
	for( i=0; i<CELL_DIM; ++i){
		for( j=0; j<CELL_DIM; ++j){
			if(pacmanFilledTmp[i][j] == 1){
					LCD_SetPoint( Xpos + j, Ypos + i, pmColor);
			}
			else{
					LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
			}
		}
	}
}

//**************************END DRAW FUNCTIONS*********************************
//**************************POSITION FUNCTIONS*********************************

/******************************************************************************
* Function Name  : CheckNextPos
* Description    : Checks if next position is a wall or a teleport
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

cellType GetNextCellType(pmDir nextDir){
	uint8_t nextXpos, nextYpos;
	
	if(nextDir == pmUp){
		nextXpos = pacmanState.pmXpos - 1;
		nextYpos = pacmanState.pmYpos;
	}else if(nextDir == pmDown){
		nextXpos = pacmanState.pmXpos + 1;
		nextYpos = pacmanState.pmYpos;
	}else if(nextDir == pmLeft){
		nextYpos = pacmanState.pmYpos - 1;
		nextXpos = pacmanState.pmXpos;
	}else if(nextDir == pmRight){
		nextYpos = pacmanState.pmYpos + 1;
		nextXpos = pacmanState.pmXpos;
	}
	return GameState[nextXpos][nextYpos];
}

/******************************************************************************
* Function Name  : updatePacmanPos
* Description    : Updates PAC-MAN position
* Input          : NextDir
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/

//the idea is that everything that moves has 8 keyframes i draw only the necessary 
//pixels to update less things possible

//V1.0 no key frames i delete the old update the new
void updatePacmanPos(pmDir nextDir){
	//
	uint8_t i, j;
	uint8_t i_r, j_r;
	if(nextDir == pmStuck){
		DrawFilledPacman(pacmanState.pmYpos*CELL_DIM,pacmanState.pmXpos*CELL_DIM+TEXT_OFFSET, Yellow, Black);
		return;
	}
	DrawBlank(pacmanState.pmYpos*CELL_DIM, pacmanState.pmXpos*CELL_DIM+TEXT_OFFSET,Black);
	//TODO: check if is a teleport and don't change it to blank
	//and if teleport special update
	
	GameState[pacmanState.pmXpos][pacmanState.pmYpos] = blank;
	if(nextDir == pmUp){
		--pacmanState.pmXpos;
	}else if(nextDir == pmDown){
		++pacmanState.pmXpos;
	}else if(nextDir == pmLeft){
		--pacmanState.pmYpos;
	}else if(nextDir == pmRight){
		++pacmanState.pmYpos;
	}
	
	//Draw pacman as needed by the orientation 		
	GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacman;
	pacmanState.pmCurrDir = nextDir;
	DrawPacman(pacmanState.pmYpos*CELL_DIM,pacmanState.pmXpos*CELL_DIM+TEXT_OFFSET,pacmanState.pmCurrDir,Yellow, Black);
}
//***********************END POSITION FUNCTIONS*******************************
//**************************UTILITY FUNCTIONS*********************************

/******************************************************************************
* Function Name  : CheckIfWall
* Description    : Checks if cell is a wall
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

int CheckIfWall(cellType checkWall){
	if(checkWall<=7 && checkWall>=2 ){
		return 0;
	}
	return -1;
}

/******************************************************************************
* Function Name  : Update Score
* Description    : If the cell is a point type updates and draws the score
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

int UpdateScore(cellType cell){
	if(cell == smallDot){
			playerPoints += 10;
			DrawScore(playerPoints);
	}else if(cell == largeDot){
			playerPoints += 50;
			DrawScore(playerPoints);
	}
	//TODO: add a live if reaches 1000
	return -1;
}

//************************END UTILITY FUNCTIONS*******************************





