			AREA |my_code|, CODE, READONLY
				
next_state	PROC
			EXPORT next_state
			PUSH {R4-R12,LR}
			; R0 current state
			; R1 taps
			LDR R2, =0
			AND R4, R0, R1 ; R4 contains current state masked by the taps
			
			; now i shift trough carry and count if the ones are odd
			; if they are odd the next state has a 1 as a shift 0 otherwise
			
			;1
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;2
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;3
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;4
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;5
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;6
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;7
			LSRS R4, #1
			EORCS R2,R2, #1
			
			;8
			LSRS R4, #1
			EORCS R2,R2, #1
			
			LSR R0, #1
			LSL R2, #7
			
			ORR R0, R0, R2
			
			POP {R4-R12,LR}
			BX LR
			ENDP
			END