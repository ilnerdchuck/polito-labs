.data 
V1: .double 10,20,30
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20

V2: .double 10,20,30
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20

V3: .double 10,20,30
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20,3
    .double 32,-20

V4: .space 256
V5: .space 256
V6: .space 256

m:  .word 1
a:  .double 0
b:  .double 69 

# int m=1 /* 64  bit */
# double a, b
# for (i = 31; i >= 0; i--){
# 	if (i is a multiple of 3) {
#   a = v1[i] / ((double) m<< i) /*logic shift */
#   m = (int) a
# } else {
#   a = v1[i] * ((double) m* i))
#   m = (int) a
# }	
# 	v4[i] = a*v1[i] – v2[i];
# 	v5[i] = v4[i]/v3[i] – b;
#   v6[i] = (v4[i]-v1[i])*v5[i];
# }

.text

start:  daddui R10, R0, 31 # i == 31
        daddui R11, R0, 256
        daddui R13, R0, 3
        l.d F7, a(R0)     # load V2 element
        l.d F8, a(R0)    # load V2 element
        ld R14, m(R0)
        # F7  is for a
        # R14 is for m
        
loop:   nop
        daddui R11, R11, -8
        l.d F1, V1(R11)     # load V1 element 
        l.d F2, V2(R11)     # load V2 element
        l.d F3, V3(R11)     # load V3 element
        
        
        ddivu R12, R10, R13   # if (i is a multiple of 3) 
        dmulu   R12, R12, R13
        dsubu   R13, R10, R12
        bnez  R13, else
        # if
        dsllv  R14, R14, R10 # m << i
        mtc1  R14, F8       # (double)m<<i
        cvt.d.l F8,F8       # (double)m<<i
       
        div.d F7, F1, F8
        #   a = v1[i] / ((double) m<< i) /*logic shift */
        j poi

        #else
else:   dmul  R14, R14, R10 # m * i

        mtc1  R14, F8       # (double)m*i
        cvt.d.l F8,F8       # (double)m*i
        
        #   a = v1[i] * ((double) m* i))
        mul.d F7, F1, F8

poi:    
        cvt.l.d F7, F7    #   m = (int) a
        mfc1 R14, F7      #   m = (int) a
        s.d F7, a(R0)
        sd R14, m(R0)
        mul.d F4, F4, F7
        mul.d F4, F1, F1  # a*v1[i]*v1[i] 
        sub.d F4, F4, F2  # – v2[i];

        div.d F5, F4, F3  # v5[i] = v4[i]/v3[i] 
  
        sub.d F5, F5, F8  # – b;


        sub.d F6, F4, F1  # v6[i] = (v4[i]-v1[i])
        mul.d F6, F6, F5  # *v5[i];
        
        s.d  F4, V4(R11)                  
        s.d  F5, V5(R11)                  
        s.d  F6, V6(R11)

        daddui R10, R10, -1
        bnez  R10, loop
end:
        halt
