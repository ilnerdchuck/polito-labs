  .data

v1:	.byte		2, 6, -3, 11, 9, 18, -13, 16, 5, 1
v2:	.byte	 	4, 2, -13, 3, 9, 9, 7, 16, 4, 7
v3:	.space	10  		

#### FLAGS

flag1: .byte 1 
flag2: .byte 0 
flag3: .byte 0


  .text
main: 
      daddui R1, R0, 10	  # V1 Index 
	    daddui R3, R0, 10		# V2 Index
	    daddui R4, R0, 0		# V3 Index
      
      daddui R2, R0, 0    # Last V3 element

      daddui R10, R0, 0   # flag reset 
      daddui R11, R0, 1   # flag set
      daddui R12, R0, 1   # tmp flag
      daddui R13, R0, 1   # dec/inc flag if 1 i was going up if 0 i was going down
loop1:  
      daddui R5, v1(R2)   # V1 element 
      daddui R6, v2(R3)   # V2 element 
      beq R5,R6, store
      
iter2:
      daddui R3, R3, -1   # decrement v2 counter
      bnze  R3, iter      # if i ended the v2 iteration i go to the next v1 element
      daddui R6, v2(R3)   # V2 element 
      bneq R5,R6, iter2   # if not found continue to iter in second vector
      
store:
      sb R6, v3(R4)       # Store value in V3
      ## prima di metterlo dentro vedo se l'elemento precedente é piu grande o piú piccolo
      slt  R12,R6,R2      # checks if R2 > R6
      bne  R12,R10,more   # if $s0 >  $s1, goes to more
      beq  R12,R10,less   # if $s0 <  $s1, goes to label3
      j snext              # il valore é uguale e non devo fare niente? coome tratto i flag?
less:
      bnze R4, lnext
      andi R13, R13, 0
lnext:
      bneq R13, R12
      
      

      j snext
more:
      
snext:
      daddui R2, R6, 0    # set new last v3 element
      daddui R4, R4, 1    # V3 index increment
      sb R10, flag1(R0)   # set empty flag to 0
      
iter:
	    daddui R1, R1, -1       # decrement total counter
      daddui R3, R0, 10       # reset v2 iterator
	    bnze R1, loop1

      daddui R2, R0, 0    #

loopf2:
        




  HALT
