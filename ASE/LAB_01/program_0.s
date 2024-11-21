.data

v1:	.byte		2, 6, -3, 11, 9, 18, -13, 16, 5, 1
v2:	.byte	 	4, 2, -13, 3, 9, 9, 7, 16, 4, 7
v3:	.space	10  		

#### FLAGS ####
flag1: .byte 1 
flag2: .byte 0 
flag3: .byte 0


.text
main:       daddui R1, R0, 10	  # iteration counter 
            xor R2, R2, R2      # V1 index
            xor R3, R3, R3	  # V2 Index
            xor R4, R4, R4	  # V3 Index
            
            xor R8, R8,  R8     # last v3 element
            daddui R9, R0, 10   # 10 register
            xor R10, R10, R10   # skip flags register
            daddui R11, R0, 1   # tmp flag
            daddui R12, R0, 1   # dec/inc flag if 1 i was going up if 0 i was going down

loop1:      lb R5, v1(R2)       # Load V1 element 
            lb R6, v2(R3)       # Load V2 element 
            beq R5,R6, store
      
iter2:      daddui R3, R3, 1    # Increment v2 counter
            beq  R3,R9, iter    # If i ended the V2 iteration i go to the next V1 element
            lb R6, v2(R3)       # Load V2 element 
            bne R5,R6, iter2    # If not found continue to iter in V2 vector
      
store:      sb R6, v3(R4)       # Store value in V3
            ## before the next iteration i check if the element is increasing or decreasing 
            bnez R10, snext     # If R10 is 1 the v3 vector has no ordered numbers so skip the flag checks until the end
            slt  R11,R6,R8      # Checks if V3[i-1] > V3[i]
            bne  R11,R0,less    # if V3[i-1] >  V3[i], decreasing value
            beq  R11,R0,more    # if V3[i-1] <  V3[i], increasing value
            j snext             # SLT sets to 0 if they are equal (i guessed i shoud not touch the flags), 
                                # just in case the program skips the two check i jump to the next iteration 
less:       bnez R4, lnext      # On the first iteration i set the tmp flag to an increasing vector so i change it to a decreasing series
            xor R12, R12, R12    

lnext:      bne R12, R0, freset # I was increasing but i found a decreasing value so i interrupt the flag checks 
            j snext
more:       beq R12, R0, freset # I was decreasing but i found a increasing value so i interrupt the flag checks
            j snext
freset:     daddui R10, R0, 1   # Sets to 1 to skip flags check

snext:      daddui R8, R6, 0    # Sets new last v3 element
            daddui R4, R4, 1    # V3 index increment
            sb R0, flag1(R0)    # Set empty V3 flag to 0
      
iter:       daddui R1, R1, -1   # Decrement total iter counter
            xor R3, R3, R3      # Reset V2 iterator
            daddui R2, R2, 1    # Inc V1 iterator
            bnez R1, loop1      

            ### Flags update ###
            bne R10, R0, end    # If i had set the skip flag i end the program leaving flag 2&3 to 0
            bne R12, R0, f2     # If set to 1 i have an increasing V3 so i set the flag2 
            daddui R12, R0, 1
            sb R12, flag3(R0)   # If set to 0 i have an decreasing V3 so i set the flag2
            j end
f2:         sb R12, flag2(R0) 
end:        HALT
