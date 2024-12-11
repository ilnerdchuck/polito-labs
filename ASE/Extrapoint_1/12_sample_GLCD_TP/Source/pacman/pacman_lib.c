#include "pacman/pacman_lib.h"

//Templates for the pixel drawing
uint8_t smallPointTmp[8][8] = {0,0,0,0,0,0,0,0,
															0,0,0,0,0,0,0,0,
															0,0,0,1,1,0,0,0,
															0,0,1,1,1,1,0,0,
															0,0,1,1,1,1,0,0,
															0,0,0,1,1,0,0,0,
															0,0,0,0,0,0,0,0,
															0,0,0,0,0,0,0,0};

uint8_t largePointTmp[8][8] = {0,0,0,0,0,0,0,0,
															0,0,1,1,1,1,0,0,
															0,1,1,1,1,1,1,0,
															0,1,1,1,1,1,1,0,
															0,1,1,1,1,1,1,0,
															0,1,1,1,1,1,1,0,
															0,0,1,1,1,1,0,0,
															0,0,0,0,0,0,0,0};


uint8_t straightWallTmp[8][8] = {0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0,
																0,0,0,1,1,0,0,0};

uint8_t angledWallTmp[8][8] = {0,0,0,1,1,0,0,0,
															0,0,0,1,1,0,0,0,
															0,0,0,1,1,1,0,0,
															0,0,0,1,1,1,1,1,
															0,0,0,0,1,1,1,1,
															0,0,0,0,0,0,0,0,
															0,0,0,0,0,0,0,0,
															0,0,0,0,0,0,0,0};

uint8_t pacmanTmp[8][8] = {0,0,1,1,1,1,0,0,
													 0,1,1,1,1,1,1,0,
													 1,1,1,1,1,1,0,0,
													 1,1,1,1,0,0,0,0,
													 1,1,1,0,0,0,0,0,
													 1,1,1,1,1,0,0,0,
													 0,1,1,1,1,1,1,0,
													 0,0,1,1,1,1,0,0};
uint8_t pacmanFilledTmp[8][8] = {0,0,1,1,1,1,0,0,
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
	//Game time text
	//TODO: function to update Time
	GUI_Text(20, 0, (uint8_t *) "GAME TIME", White, Black);
	GUI_Text(30, 16, (uint8_t *) "60s", White, Black);
	//Score Text
	//TODO: function to update the score
	GUI_Text(180, 0, (uint8_t *) "SCORE", White, Black);
	GUI_Text(180, 16, (uint8_t *) "00000", White, Black);

	int i,j;
	for(i=0; i<GAME_ROWS; ++i){
		for(j=0;j<GAME_COLUMNS; ++j){
			if(GameState[i][j]==smallDot || GameState[i][j]==largeDot){
				DrawPoint( j*8, i*8+32, GameState[i][j], White, Black);
			}else if(	GameState[i][j]==hWall || GameState[i][j]==vWall || 
								GameState[i][j]==blAngle || GameState[i][j]==brAngle|| 
								GameState[i][j]==tlAngle || GameState[i][j]==trAngle){
				DrawWall( j*8, i*8+32, GameState[i][j], Blue, Black);
			}else if(GameState[i][j]==blank){
				DrawWall( j*8, i*8+32, GameState[i][j], Black, Black);
			}else if(GameState[i][j]==teleport){
				DrawWall( j*8, i*8+32, GameState[i][j], Black, Black);
			}else if(GameState[i][j]==pacman){
				DrawPacman(j*8, i*8+32,pmLeft,Yellow,Black);
			}
		}
	}
	return 0;
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
	
	for( i=0; i<8; ++i){
		for( j=0; j<8; ++j){
			LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
		}
	}
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
		for( i=0; i<8; ++i){
			for( j=0; j<8; ++j){
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
		for( i=0,i_r=7; i<8; ++i, --i_r){
			for( j=0, j_r=7; j<8; ++j, --j_r){
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
		for( i=0,i_r=7; i<8; ++i, --i_r){
			for( j=0, j_r=0; j<8; ++j, ++j_r){
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
		for( i=0,i_r =0; i<8; ++i, ++i_r){
			for( j=0, j_r = 0; j<8; ++j, ++j_r){
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

void DrawFilledPacman( uint16_t Xpos, uint16_t Ypos,pmDir dir,uint16_t pmColor,uint16_t bkColor){
	uint8_t i, j;
	uint8_t i_r, j_r;
	//Draw pacman as needed by the orientation 	
	for( i=0; i<8; ++i){
		for( j=0; j<8; ++j){
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
	uint8_t (*pointTemplate)[8] = pointType==smallDot? smallPointTmp : pointType==largeDot? largePointTmp: 0;
	if(pointTemplate == 0){
			return -1;
	}
	//Just cicle trough the matrix and draw it
	for( i=0; i<8; ++i){
		for( j=0; j<8; ++j){
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
	uint8_t (*wallTemplate)[8] = (wallType==hWall || wallType==vWall )? straightWallTmp : 
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
		for( i=0; i<8; ++i){
			for( j=0; j<8; ++j){
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
		for( i=0,i_r =0; i<8; ++i, ++i_r){
			for( j=0, j_r = 0; j<8; ++j, ++j_r){
				if(wallTemplate[j_r][i_r] == 1){
						LCD_SetPoint( Xpos + j, Ypos + i, wallColor);
				}
				else{
						LCD_SetPoint( Xpos + j, Ypos + i, bkColor );  
				}
			}
		}
	}else if(wallType == blAngle){
		for( i=0; i<8; ++i){
			for( j=0; j<8; ++j){
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
		for( i=0,i_r =0; i<8; ++i, ++i_r){
			for( j=0, j_r = 7; j<8; ++j, --j_r){
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
		for( i=0, i_r=7; i<8; ++i, --i_r){
			for( j=0, j_r = 0; j<8; ++j, ++j_r){
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
		for( i=0, i_r=7; i<8; ++i, --i_r){
			for( j=0, j_r=7; j<8; ++j, --j_r){
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

