#include <stdint.h>

extern int check_square(int, int, int);
extern float my_division(float, float);

// extern int *Matrix_Coordinates; ma perché cosi dá errore???
extern int Matrix_Coordinates[];
extern uint8_t ROWS;
extern uint8_t COLUMNS;
	
#define RADIUS 5

int main(void){
  int x,y;
	int i,j;
  int sum = 0;
  for (i=0; i<ROWS; ++i) {
      for (j=0; j<COLUMNS; j+=2) {
				
				__asm("MOV R0, %0\n": : "r" (Matrix_Coordinates));

				y = Matrix_Coordinates[i*ROWS*2+j];
				x = Matrix_Coordinates[i*ROWS*2+j+1];
        
        sum += check_square(x, y, RADIUS);
      }
  }
  
  __asm("MOV R0, %0\n": : "r" (sum));
	float result = my_division((float)sum, (float) RADIUS*RADIUS);	
	__asm("MOV R0, %0\n": : "r" (result));
	
	while(1);
}
