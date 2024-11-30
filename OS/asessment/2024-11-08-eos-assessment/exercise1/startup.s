#Write an ARM assembly program that computes the product of the elements of an array of 32bit integers stored in memory. Store the result in a specific memory location.
#Specifications:

#The array of integers is stored in memory at an address identified by the label v_int.
#The number of elements in the array is stored in memory at an address identified by the label n

#The result is stored in memory at an address identified by the label res

.data
	v_int: .word 1, 2, 3, 4, 5, 6, 7, 8, 9
	n: 	   .word 8
	res:   .word 0
.text
.global _start

_start:
	LDR R0, =v_int
	LDR R1, =n
	LDR R1, [R1]
	LDR R2, =0
	LDR R3, =res
	LDR R5, =1
loop: CMP R1, R2
	  BEQ done
	  LDR R4, [R0],#4
	  MUL R5, R5, R4
	  SUB R1, R1, #1
	  B loop
done:
	STR R2, [R3]
	B .
	
