#include "../pacman/pacman_lib.h"
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

uint8_t blinkyTmp[CELL_DIM][CELL_DIM] = {0,0,0,1,1,0,0,0,
																				 0,0,1,1,1,1,0,0,
																				 0,1,2,1,1,2,1,0,
																				 0,1,2,1,1,2,1,0,
																				 0,1,1,1,1,1,1,0,
																				 0,1,1,1,1,1,1,0,
																				 0,1,0,1,0,1,0,0,
																				 0,0,0,0,0,0,0,0};

																							 
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
	GUI_Text(20, 0, (uint8_t *) "GAME TIME", White, Black);
	//DrawTime(gameTime, White, Black);
	//Score Text
	GUI_Text(SCORE_XOFFSET, 0, (uint8_t *) "SCORE", White, Black);
	//DrawScore(playerPoints, White, Black);	
	for(i=0; i<GAME_ROWS; ++i){
		for(j=0;j<GAME_COLUMNS; ++j){
			//TODO:do a function to draw instead of this mess (DrawCell(cellType cell) e disegna tutto)
			if(GameState[i][j] == smallDot || GameState[i][j] == intersection){
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
				pacmanState.oldCell = blank;
			}else if(GameState[i][j]==blinky){
				DrawBlinky(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,pmLeft,Red,Black);
				blinkyState.pmXpos = i;
				blinkyState.pmYpos = j;
				blinkyState.pmOldXpos = i;
				blinkyState.pmOldYpos = j;
				blinkyState.pmCurrDir = pmLeft;
				blinkyState.pmNextDir = pmLeft;
				blinkyState.aFrame = 8;
				blinkyState.oldCell = blank;
			}
		}
	}
	DrawMiddleText();
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

void DrawTime(uint8_t time, uint16_t textColor, uint16_t bkColor){
	uint8_t i, j;
	char timeString[] = "60s";
	sprintf(timeString,"%02ds",time);
	if(time<=10 && time%2){
		GUI_Text(TIME_XOFFSET, TIME_YOFFSET,(uint8_t*)timeString, Red, bkColor);
	}else{
		GUI_Text(TIME_XOFFSET, TIME_YOFFSET,(uint8_t*)timeString, textColor, bkColor);
	}
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

//TODO: add color input to make it sed when it is low
void DrawLives(uint8_t lives){
	int i=0;
	for(i=0; i<5;++i){
		DrawBlank(i*CELL_DIM,LIVES_OFFSET,Black);	
	}
	for(i=0; i<lives;++i){
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
	uint8_t (*pointTemplate)[CELL_DIM] = pointType==smallDot? smallPointTmp : pointType==largeDot? largePointTmp: pointType==intersection? smallPointTmp: 0;
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


/******************************************************************************
* Function Name  : DrawBlinky
* Description    : Draws PAC-MAN
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on success, -1 otherwise
* Attention		 : None
*******************************************************************************/

void DrawBlinky( uint16_t Xpos, uint16_t Ypos,pmDir dir,uint16_t pmColor,uint16_t bkColor){
	uint8_t i, j;
	uint8_t i_r, j_r;
	
	for( i=0; i<CELL_DIM; ++i){
		for( j=0; j<CELL_DIM; ++j){
			if(blinkyTmp[i][j] == 1){
					LCD_SetPoint( Xpos + j, Ypos + i, pmColor);
			}else if(blinkyTmp[i][j] == 2){
					LCD_SetPoint( Xpos + j, Ypos + i, White);  
			}else{
					LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
			}
		}
	}
}


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
			if(GameState[i][j]==smallDot || GameState[i][j]==largeDot || GameState[i][j]==intersection){
				DrawPoint(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], White, Black);
			}else if(	GameState[i][j]==hWall || GameState[i][j]==vWall || 
								GameState[i][j]==blAngle || GameState[i][j]==brAngle|| 
								GameState[i][j]==tlAngle || GameState[i][j]==trAngle){
				DrawWall(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET, GameState[i][j], Blue, Black);
			}else if(GameState[i][j]==blank || GameState[i][j]==emptyinter){
				DrawBlank(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,Black);
			}else if(GameState[i][j]==teleport){
				DrawBlank(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,Black);
			}else if(GameState[i][j]==pacman){
				DrawPacman(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,pmLeft,Yellow,Black);
			}else if(GameState[i][j]==blinky){
				DrawBlinky(j*CELL_DIM, i*CELL_DIM+TEXT_OFFSET,pmLeft,Red,Black);
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
		
			Xpos = pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET-pacmanState.aFrame;
			Ypos = pacmanState.pmOldYpos*CELL_DIM;
		}else if(dir== pmDown){
			
			Xpos = (pacmanState.pmOldXpos*CELL_DIM)+TEXT_OFFSET+pacmanState.aFrame;
			Ypos = pacmanState.pmOldYpos*CELL_DIM;
		}else if(dir == pmLeft){
			
			Xpos = pacmanState.pmOldXpos*CELL_DIM+TEXT_OFFSET;
			Ypos = pacmanState.pmOldYpos*CELL_DIM-pacmanState.aFrame;
		}else if(dir == pmRight){
			
			Xpos = (pacmanState.pmOldXpos*CELL_DIM)+TEXT_OFFSET;
			Ypos = (pacmanState.pmOldYpos*CELL_DIM)+pacmanState.aFrame;
		}
		if(pacmanState.aFrame == 1 ||pacmanState.aFrame == 2 || pacmanState.aFrame == 3 || pacmanState.aFrame == 4 ||pacmanState.aFrame == 7){
			DrawFilledPacman(Ypos, Xpos, Yellow,Black);
		}else{
			DrawPacman(Ypos,Xpos,dir,Yellow, Black);
		}
		
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

void animateBlinkyFrame(){
	
	//i take the pacman dir 
	pmDir dir = blinkyState.pmCurrDir;

	
	//TODO: maybe use the check if wall
  if(GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==smallDot || GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==largeDot|| GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==intersection){
		DrawPoint(blinkyState.pmOldYpos*CELL_DIM, blinkyState.pmOldXpos*CELL_DIM+TEXT_OFFSET, GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos], White, Black);
	}else if(	GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==hWall || GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==vWall || 
						GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==blAngle || GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==brAngle|| 
						GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==tlAngle || GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==trAngle){
		DrawWall(blinkyState.pmOldYpos*CELL_DIM, blinkyState.pmOldXpos*CELL_DIM+TEXT_OFFSET, GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos], Blue, Black);
	}else if(GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==blank || GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==emptyinter){
		DrawBlank(blinkyState.pmOldYpos*CELL_DIM, blinkyState.pmOldXpos*CELL_DIM+TEXT_OFFSET,Black);
	}else if(GameState[blinkyState.pmOldXpos][blinkyState.pmOldYpos]==teleport){
		DrawBlank(blinkyState.pmOldYpos*CELL_DIM, blinkyState.pmOldXpos*CELL_DIM+TEXT_OFFSET,Black);
	}

	uint16_t Xpos, Ypos;
	++blinkyState.aFrame;
	//i need to handle animation in the teleport also
		if(dir == pmUp){
			Xpos = blinkyState.pmOldXpos*CELL_DIM+TEXT_OFFSET-blinkyState.aFrame;
			Ypos = blinkyState.pmOldYpos*CELL_DIM;
		}else if(dir== pmDown){
			Xpos = (blinkyState.pmOldXpos*CELL_DIM)+TEXT_OFFSET+blinkyState.aFrame;
			Ypos = blinkyState.pmOldYpos*CELL_DIM;
		}else if(dir == pmLeft){
			Xpos = blinkyState.pmOldXpos*CELL_DIM+TEXT_OFFSET;
			Ypos = blinkyState.pmOldYpos*CELL_DIM-blinkyState.aFrame;
		}else if(dir == pmRight){
			Xpos = (blinkyState.pmOldXpos*CELL_DIM)+TEXT_OFFSET;
			Ypos = (blinkyState.pmOldYpos*CELL_DIM)+blinkyState.aFrame;
		}
		DrawBlinky(Ypos, Xpos,dir,Red,Black);
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
		if(pacmanState.oldCell == intersection || pacmanState.oldCell == emptyinter ){
			GameState[pacmanState.pmOldXpos][pacmanState.pmOldYpos]= emptyinter;
		}else{
			GameState[pacmanState.pmOldXpos][pacmanState.pmOldYpos]= blank;
		}
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
			pacmanState.oldCell = GameState[pacmanState.pmXpos][pacmanState.pmYpos];
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
			pacmanState.oldCell = GameState[pacmanState.pmXpos][pacmanState.pmYpos];
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacman;
		}
	}
	pacmanState.pmCurrDir = nextDir;
	pacmanState.aFrame = 0;
}
//-------------------------Fantasmino Position-------------------------------

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
cellType GetNextBlinkyCellType(pmDir nextDir){
	uint8_t nextXpos, nextYpos;
	
	if(GameState[blinkyState.pmXpos][blinkyState.pmYpos] == teleport){
		return GameState[blinkyState.pmXpos][blinkyState.pmYpos];
	}
	
	if(nextDir == pmUp){
		nextXpos = blinkyState.pmXpos - 1;
		nextYpos = blinkyState.pmYpos;
	}else if(nextDir == pmDown){
		nextXpos = blinkyState.pmXpos + 1;
		nextYpos = blinkyState.pmYpos;
	}else if(nextDir == pmLeft){
		nextYpos = blinkyState.pmYpos - 1;
		nextXpos = blinkyState.pmXpos;
	}else if(nextDir == pmRight){
		nextYpos = blinkyState.pmYpos + 1;
		nextXpos = blinkyState.pmXpos;
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

cellType _resCell;
void updateBlinkyPos(){
	
	uint8_t i, j;
	
	blinkyState.pmOldXpos = blinkyState.pmXpos;
	blinkyState.pmOldYpos = blinkyState.pmYpos;
	if(pacmanState.pmXpos == blinkyState.pmXpos && pacmanState.pmYpos == blinkyState.pmYpos && powerUP==0){
			pacmanState.aFrame = 8;
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacmanState.oldCell;
			pacmanState.oldCell = blank;
			pacmanState.pmXpos = 14;
			pacmanState.pmYpos = 13;
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacman;
			--playerLives;
			if(!playerLives){
				SetGameOver();
			}
	}else if(pacmanState.pmXpos == blinkyState.pmXpos && pacmanState.pmYpos == blinkyState.pmYpos){
			blinkyState.aFrame = 8;
			blinkyState.pmXpos = 14;
			blinkyState.pmYpos = 13;
			playerPoints += 100;
	}
	
	//faccio il check se sono ad un intersezione sennó continuo nella mia solita direzione
	if(GameState[blinkyState.pmXpos][blinkyState.pmYpos] == intersection || GameState[blinkyState.pmXpos][blinkyState.pmYpos] == emptyinter ){
		//siamo ad un itnersezione aggiornamo la nextdir
		//con qualsiasi algoritmo scegliamo e se siamo in non spauro		
		if(powerUP==0){
			//non in spauracchio uso il mio algoritmo di scelta
			//chiamo il mio fantastico algoritmo di scelta della direzione
			if((CheckIfWall(GetNextBlinkyCellType(pmUp))==-1) && blinkyState.pmXpos > pacmanState.pmXpos ){
				blinkyState.pmNextDir = pmUp;
			}else if((CheckIfWall(GetNextBlinkyCellType(pmDown)) == -1) && blinkyState.pmXpos < pacmanState.pmXpos){
				blinkyState.pmNextDir = pmDown;
			}else if((CheckIfWall(GetNextBlinkyCellType(pmRight)) ==-1) && blinkyState.pmYpos < pacmanState.pmYpos ){
				blinkyState.pmNextDir = pmRight;
			}else if((CheckIfWall(GetNextBlinkyCellType(pmLeft))==-1) && blinkyState.pmYpos > pacmanState.pmYpos ){
				blinkyState.pmNextDir = pmLeft;
			}
		}else{
			//se gioco in spauro
			//se non sono ad un angolo faccio il classico
			if(CheckIfAngle(blinkyState.pmXpos,blinkyState.pmYpos)==0){
				
				if(CheckIfWall(GameState[blinkyState.pmXpos][blinkyState.pmYpos-1])==0 && CheckIfWall(GameState[blinkyState.pmXpos+1][blinkyState.pmYpos])==0){
					if(blinkyState.pmNextDir==pmDown){
						blinkyState.pmNextDir=pmRight;
					}else{
						blinkyState.pmNextDir=pmUp;
					}
				}
				if(CheckIfWall(GameState[blinkyState.pmXpos][blinkyState.pmYpos+1])==0 && CheckIfWall(GameState[blinkyState.pmXpos+1][blinkyState.pmYpos])==0){
					if(blinkyState.pmNextDir==pmDown){
						blinkyState.pmNextDir=pmLeft;
					}else{
						blinkyState.pmNextDir=pmUp;
					}
				}
				if(CheckIfWall(GameState[blinkyState.pmXpos][blinkyState.pmYpos-1])==0 && CheckIfWall(GameState[blinkyState.pmXpos-1][blinkyState.pmYpos])==0){
					if(blinkyState.pmNextDir==pmUp){
						blinkyState.pmNextDir=pmRight;
					}else{
						blinkyState.pmNextDir=pmDown;
					}
				}	
				if(CheckIfWall(GameState[blinkyState.pmXpos][blinkyState.pmYpos+1])==0 && CheckIfWall(GameState[blinkyState.pmXpos -1][blinkyState.pmYpos])==0){
					if(blinkyState.pmNextDir==pmUp){
						blinkyState.pmNextDir=pmLeft;
					}else{
						blinkyState.pmNextDir=pmDown;
					}
				}	
			}else{
				//prendo una delle direzioni avialable
				if((CheckIfWall(GetNextBlinkyCellType(pmDown))==-1) && blinkyState.pmXpos >= pacmanState.pmXpos ){
					blinkyState.pmNextDir = pmDown;
				}else if(blinkyState.pmXpos <= pacmanState.pmXpos && (CheckIfWall(GetNextBlinkyCellType(pmUp)) == -1)){
					blinkyState.pmNextDir = pmUp;
				}else if(blinkyState.pmYpos <= pacmanState.pmYpos && (CheckIfWall(GetNextBlinkyCellType(pmLeft)) ==-1)){
					blinkyState.pmNextDir = pmLeft;
				}else if(blinkyState.pmYpos >= pacmanState.pmYpos && (CheckIfWall(GetNextBlinkyCellType(pmRight))==-1)){
					blinkyState.pmNextDir = pmRight;
				}
			}
		}
	}
	
	//effettivo  update
	if(GameState[blinkyState.pmXpos][blinkyState.pmYpos] != teleport){
		if(blinkyState.pmNextDir == pmUp){
			--blinkyState.pmXpos;
		}else if(blinkyState.pmNextDir == pmDown){
			++blinkyState.pmXpos;
		}else if(blinkyState.pmNextDir == pmLeft){
			--blinkyState.pmYpos;
		}else if(blinkyState.pmNextDir == pmRight){
			++blinkyState.pmYpos;
		}		
	}else{
		if(blinkyState.pmNextDir == pmLeft && blinkyState.pmYpos == 0){
			blinkyState.pmYpos = GAME_COLUMNS-1;
		}else if(blinkyState.pmNextDir == pmRight && blinkyState.pmYpos == GAME_COLUMNS-1){
			blinkyState.pmYpos = 0;
		}else{
			//senno sto uscendo dal teleport e quindi devo aggioranre come sopra ma solo la Y non la X
			if(blinkyState.pmNextDir == pmLeft){
				--blinkyState.pmYpos;
			}else if(blinkyState.pmNextDir == pmRight){
				++blinkyState.pmYpos;
			}	
		}
	}
	if(pacmanState.pmXpos == blinkyState.pmXpos && pacmanState.pmYpos == blinkyState.pmYpos && powerUP==0){
			pacmanState.aFrame = 8;
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacmanState.oldCell;
			pacmanState.oldCell = blank;
			pacmanState.pmXpos = 14;
			pacmanState.pmYpos = 13;
			GameState[pacmanState.pmXpos][pacmanState.pmYpos] = pacman;
			--playerLives;
			if(!playerLives){
				SetGameOver();
			}
	}else if(pacmanState.pmXpos == blinkyState.pmXpos && pacmanState.pmYpos == blinkyState.pmYpos){
			blinkyState.aFrame = 8;
			blinkyState.pmXpos = 14;
			blinkyState.pmYpos = 13;
			playerPoints += 100;
	}
	
	blinkyState.pmCurrDir = blinkyState.pmNextDir;
	blinkyState.aFrame = 0;
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
* Function Name  : CheckIfWall
* Description    : Checks if cell is a wall
* Input          : - Xpos:  
*                  - Ypos:  
*                  - Orientation: 
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

int CheckIfAngle(uint8_t Xpos, uint8_t Ypos){
	//|*
	//L_
	if(CheckIfWall(GameState[Xpos][Ypos-1])==0 && CheckIfWall(GameState[Xpos+1][Ypos])==0){
		return 0;
	}
	if(CheckIfWall(GameState[Xpos][Ypos+1])==0 && CheckIfWall(GameState[Xpos+1][Ypos])==0){
		return 0;
	}
	if(CheckIfWall(GameState[Xpos][Ypos-1])==0 && CheckIfWall(GameState[Xpos-1][Ypos])==0){
		return 0;
	}	
	if(CheckIfWall(GameState[Xpos][Ypos+1])==0 && CheckIfWall(GameState[Xpos-1][Ypos])==0){
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
			--gamePoints;
			playEat =1;
	}else if(cell == largeDot){
			powerUP = 10; //we set the 10 seconds of powerup
			playerPoints += 50;
			tmpScore += 50;
			--gamePoints;
			playEat =1;
	}
	if(!gamePoints){
		SetGameWon();
	}
	if(tmpScore>=1000){
		++playerLives;
		tmpScore = 0;
	}
	SendCanInfo();
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
		disable_timer(1);
		disable_timer(2);
		gameStatus = 1;
		disable_timer(0);
		disable_timer(3);
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
	//disable_timer(0);
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
	//disable_timer(0);
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
	
	//init_timer(0,0x001312D0); 							/* a timer																						*/
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
			if(pacmanState.pmYpos != 0 && pacmanState.pmYpos != 0 ){
				i=rand()*pacmanState.pmXpos;
				j=rand()*pacmanState.pmYpos;
			}else{
				i=rand();
				j=rand();
			}
			
			//TODO: a quanto pare % non funziona 
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
/******************************************************************************
* Function Name  : SendCanInfo
* Description    : Initialize hardware needed
* Input          : None
* Output         : None
* Return         : 0 on small dot, 1 on large dot, 2 on teleport, 3 blank ,-1 otherwise
* Attention		 : None
*******************************************************************************/

void SendCanInfo(){
	//first 16 bits are the score
	CAN_TxMsg.data[0] = ((playerPoints) & 0xFF00) >> 8;
	CAN_TxMsg.data[1] = (playerPoints) & 0xFF;
	//8bits for the lives
	CAN_TxMsg.data[2] = playerLives;
	//8bits for the time 
	CAN_TxMsg.data[3] = gameTime;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 2;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);
}
//************************END UTILITY FUNCTIONS*******************************





