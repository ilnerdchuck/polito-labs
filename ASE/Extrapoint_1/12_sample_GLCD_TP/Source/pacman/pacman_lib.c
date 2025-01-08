#include "pacman/pacman_lib.h"
#include <stdio.h>
#include <stdlib.h>
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
	GUI_Text(20, 0, (uint8_t *) "GAME TIME", White, Black);
	DrawTime(gameTime, White, Black);
	//Score Text
	GUI_Text(SCORE_XOFFSET, 0, (uint8_t *) "SCORE", White, Black);
	DrawScore(playerPoints, White, Black);	
	for(i=0; i<GAME_ROWS; ++i){
		for(j=0;j<GAME_COLUMNS; ++j){
			//TODO:do a function to draw instead of this mess (DrawCell(cellType cell) e disegna tutto)
			if(GameState[i][j] == smallDot){
				gamePoints++;
				DrawPoint(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], White, Black);				
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
				pacmanState.pmOldXpos = i;
				pacmanState.pmOldYpos = j;
				pacmanState.pmCurrDir = pmLeft;
				pacmanState.pmNextDir = pmLeft;
				pacmanState.aFrame = 8;
			}
		}
	}
	DrawLives();
	DrawMiddleText();
	return 0;
}
//*****************************************************************************
//----------------------------DRAW FUNCTIONS-----------------------------------
//*****************************************************************************

/******************************************************************************
* Function Name  : DrawTime
* Description    : Draws Time
* Input          : time: time value to draw 
*				   - bkColor: Background color
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

void DrawTime(uint16_t time, uint16_t textColor, uint16_t bkColor){
	uint8_t i, j;
	char timeString[] = "60s";
	sprintf(timeString,"%02ds",time);
	GUI_Text(TIME_XOFFSET, TIME_YOFFSET,(uint8_t*)timeString, textColor, bkColor);
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

void DrawScore(uint16_t score, uint16_t textColor, uint16_t bkColor){
	uint8_t i, j;
	char scoreString[] = "00000";
	sprintf(scoreString,"%05d",score);
	GUI_Text(SCORE_XOFFSET, SCORE_YOFFSET,(uint8_t*)scoreString, textColor, bkColor);
}

/******************************************************************************
* Function Name  : DrawLives
* Description    : Draws Time
* Input          : time: time value to draw 
*				   - bkColor: Background color
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/


void DrawLives(){
	int i=0;
	for(i=0; i<playerLives;++i){
		DrawPacman(i*CELL_DIM,LIVES_OFFSET,pmLeft,Yellow, Black);	
	}
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

/******************************************************************************
* Function Name  : PrintMiddleText
* Description    : 	Draws text in the middle of the screen maybe a can draw 
*										at the top of the screen
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

void DrawMiddleText(){
	//3 tipes of string based on gamestate
	//Pause clean and write the pause string
	if(gameStatus == 1){
		GUI_Text(12*CELL_DIM,11*CELL_DIM+TEXT_OFFSET,(uint8_t*)"PAUSE",Yellow,Black);
		return;
	}
	//Game Won
	if(gameStatus == 2){
		GUI_Text(10*CELL_DIM,11*CELL_DIM+TEXT_OFFSET,(uint8_t*)"!VICTORY!",Yellow,Black);
		return;
	}
	//Game Over
	if(gameStatus == 3){
		GUI_Text(12*CELL_DIM+4,11*CELL_DIM+TEXT_OFFSET,(uint8_t*)"GAME",Yellow,Black);
		GUI_Text(12*CELL_DIM+4,13*CELL_DIM+TEXT_OFFSET,(uint8_t*)"OVER",Yellow,Black);
		return;
	}
	
	uint8_t i,j;
	//for(i=16; i<=20; ++i){
	//	for(j=10;j<=19; ++j){
	for(i=10; i<=12; ++i){
		for(j=10;j<=16; ++j){
			//TODO:do a function to draw instead of this mess 
			if(GameState[i][j]==smallDot || GameState[i][j]==largeDot){
				DrawPoint(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], White, Black);
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
			}
		}
	}
	
	return;
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
void animateFrame(){
	
	//i take the pacman dir 
	pmDir dir = pacmanState.pmCurrDir;

	//For now we dont handle deleting back pixels
	//make a funciton to clear only the back of pacman
	DrawBlank(pacmanState.pmOldYpos*CELL_DIM, pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET,Black);
	uint16_t Xpos, Ypos;
	++pacmanState.aFrame;
	//i need to handle animation in the teleport also
		if(dir == pmUp){
			//DrawBlank(pacmanState.pmOldYpos*CELL_DIM, pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET-pacmanState.aFrame,Black);
			Xpos = pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET-pacmanState.aFrame;
			Ypos = pacmanState.pmOldYpos*CELL_DIM;
		}else if(dir== pmDown){
			//DrawBlank(pacmanState.pmOldYpos*CELL_DIM, pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET+pacmanState.aFrame,Black);
			Xpos = (pacmanState.pmOldXpos*CELL_DIM)+TEXT_OFFSET+pacmanState.aFrame;
			Ypos = pacmanState.pmOldYpos*CELL_DIM;
		}else if(dir == pmLeft){
			//DrawBlank(pacmanState.pmOldYpos*CELL_DIM-pacmanState.aFrame, pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET,Black);
			Xpos = pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET;
			Ypos = pacmanState.pmOldYpos*CELL_DIM-pacmanState.aFrame;
		}else if(dir == pmRight){
			//DrawBlank(pacmanState.pmOldYpos*CELL_DIM+pacmanState.aFrame, pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET,Black);
			Xpos = (pacmanState.pmOldXpos*CELL_DIM)+TEXT_OFFSET;
			Ypos = (pacmanState.pmOldYpos*CELL_DIM)+pacmanState.aFrame;
		}
		if(pacmanState.aFrame == 1 ||pacmanState.aFrame == 2 || pacmanState.aFrame == 3 || pacmanState.aFrame == 4 ||pacmanState.aFrame == 7){
			DrawFilledPacman(Ypos, Xpos, Yellow,Black);
		}else{
			DrawPacman(Ypos,Xpos,dir,Yellow, Black);
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
	
	if(GameState[pacmanState.pmXpos][pacmanState.pmYpos] == teleport){
		return GameState[pacmanState.pmXpos][pacmanState.pmYpos];
	}
	
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

void updatePacmanPos(pmDir nextDir){
	//
	uint8_t i, j;
	pacmanState.pmOldXpos = pacmanState.pmXpos;
	pacmanState.pmOldYpos = pacmanState.pmYpos;
	
	if(nextDir == pmStuck){
		DrawFilledPacman(pacmanState.pmYpos*CELL_DIM,pacmanState.pmXpos*CELL_DIM+TEXT_OFFSET, Yellow, Black);
		pacmanState.pmCurrDir = pmStuck;
		return;
	}
	//non serve pulire ci pensa la animateFrame
	//DrawBlank(pacmanState.pmYpos*CELL_DIM, pacmanState.pmXpos*CELL_DIM+TEXT_OFFSET,Black);
	//TODO: check if is a teleport and don't change it to blank
	//and if teleport special update
	//Ok i could not change any state of the cell if i am currently in a tp cell
	//thne if my currpos is a tp i switch drawing orientation
	//i was going right i need to teleport left and viceversa
	if(GameState[pacmanState.pmXpos][pacmanState.pmYpos] != teleport){
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
		UpdateScore(GameState[pacmanState.pmXpos][pacmanState.pmYpos]);
		//dont alter the tp cell
		if(GameState[pacmanState.pmXpos][pacmanState.pmYpos] != teleport){
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacman;
		}
	}else{
		if(nextDir == pmLeft && pacmanState.pmYpos == 0){
			pacmanState.pmYpos = GAME_COLUMNS-1;
		}else if(nextDir == pmRight && pacmanState.pmYpos == GAME_COLUMNS-1){
			pacmanState.pmYpos = 0;
		}else{
			//senno sto uscendo dal teleport e quindi devo aggioranre come sopra ma solo la Y non la X
			if(nextDir == pmLeft){
				--pacmanState.pmYpos;
			}else if(nextDir == pmRight){
				++pacmanState.pmYpos;
			}	
			//TODO: Why i do this? se sono in un teleport non devo farlo
			// ah ok uscendo la prossima posizione 'e pacman
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacman;
		}
	}
	pacmanState.pmCurrDir = nextDir;
	pacmanState.aFrame = 0;
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



uint16_t tmpScore = 0;
int UpdateScore(cellType cell){
	if(cell == smallDot){
			playerPoints += 10;
			tmpScore += 10;
			DrawScore(playerPoints, White, Black);
			--gamePoints;
	}else if(cell == largeDot){
			playerPoints += 50;
			tmpScore += 50;
			DrawScore(playerPoints, White, Black);
			--gamePoints;
	}
	if(!gamePoints){
		SetGameWon();
	}
	if(tmpScore>=1000){
		++playerLives;
		DrawLives();
		tmpScore = 0;
	}
	return -1;
}
/******************************************************************************
* Function Name  : PauseToggle
* Description    : Toggle pause
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

void PauseToggle(){
	//per pausare disablito tutti i timer ez
	if(gameStatus == 1){
		gameStatus = 0;
		enable_timer(1);
		enable_timer(2);
	}else if(gameStatus == 0){
		disable_timer(0);
		disable_timer(1);
		disable_timer(2);
		gameStatus = 1;
	}
	DrawMiddleText();
	return;
}

/******************************************************************************
* Function Name  : SetGameOver
* Description    : Toggle pause
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

void SetGameOver(){
	//per pausare disablito tutti i timer ez
	gameStatus = 3;
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_RIT();
	DrawMiddleText();
	return;
}

/******************************************************************************
* Function Name  : SetGameWon
* Description    : Toggle pause
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

void SetGameWon(){
	//per pausare disablito tutti i timer ez
	gameStatus = 2;
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_RIT();
	DrawMiddleText();
	return;
}
/******************************************************************************
* Function Name  : init_hardware
* Description    : Initialize hardware needed
* Input          : None
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

int init_hardware(){
	BUTTON_init();
	joystick_init();
	
	init_timer(0,0x001312D0); 							/* a timer																						*/
	init_timer(1,0x00051615); 						  /* 1/30Hz* 25MHz = 833333 = 0x65B9A 	Game tick timer */
	init_timer(2,0x017D7840);								/* 1s* 25MHz = 25M = 0x17D7840 				Game timer			*/
	init_RIT(0x004C4B40);
	enable_RIT();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);		
	srand(6969423);
	return 0;
}
/******************************************************************************
* Function Name  : getRandomDecision
* Description    : Initialize hardware needed
* Input          : None
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

int getRandomDecision(){
    int buff[RANDOM_BUFFER] = {0};  
		int i,j;
    for (i=0; i < RANDOM_BUFFER; ++i) {
        buff[i] = rand()%2;  
		}
    // Generate a new random decision by mixing the history values
    int decision = 0;
    for (i=1; i<=RANDOM_BUFFER; ++i) {
        decision ^= buff[i*rand()%RANDOM_BUFFER-1];  // XOR the values together
    }
		
	return decision;
}

/******************************************************************************
* Function Name  : SpawnLargeDot
* Description    : Initialize hardware needed
* Input          : None
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

void SpawnLargeDot(){
		uint16_t i,j;
		int generating =1;
		while(generating){
			i=rand()*pacmanState.pmXpos;
			j=rand()*pacmanState.pmYpos;
			i=i-((i/(GAME_ROWS-1))*(GAME_ROWS-1));
			j=j-((j/(GAME_COLUMNS-1))*(GAME_COLUMNS-1));
			
			
			if(GameState[i][j]==smallDot){
				GameState[i][j]=largeDot;
				DrawPoint(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], White, Black);
				generating =0;
				--largeDotRemaining;
			}
		}
}

//************************END UTILITY FUNCTIONS*******************************





