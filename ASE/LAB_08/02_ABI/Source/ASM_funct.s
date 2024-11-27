				
				
				AREA FUNCTIONS, CODE, READONLY				
				
check_square	PROC
				EXPORT  check_square
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
			  
				MOV R4, R0 ; x
				MOV R5, R1 ; y
				MOV R6, R2 ; radius
		  
				MUL R4, R4, R4 ;x*x
				MLA R5, R5, R5, R4 ; R5 is x²+y²  
				MUL R6, R6, R6 ;  r*r
				
				CMP R5, R6
				MOVHI R0, #0
				MOVLS R0, #1
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
				ENDP
				
				
my_division		PROC
				IMPORT  __aeabi_fdiv	
				EXPORT  my_division
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
			
				BL __aeabi_fdiv
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
				ENDP
				
				END
				
