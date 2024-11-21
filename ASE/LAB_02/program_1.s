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

# for (i = 31; i >= 0; i--){	
#	  v4[i] = v1[i]*v1[i] – v2[i];
# 	v5[i] = v4[i]/v3[i] – v2[i];
#   v6[i] = (v4[i]-v1[i])*v5[i];
#}


.text

start:  daddui R10, R0, 31 # i == 31
        daddui R11, R0, 256 

loop:   l.d F1, V1(R11)   # load V1 element 
        
        mul.d F4, F1, F1  # v1[i]*v1[i] 
        
        l.d F2, V2(R11)   # load V2 element
        l.d F3, V3(R11)   # load V3 element
        
        sub.d F4, F4, F2  # – v2[i];

        div.d F5, F4, F3  # v5[i] = v4[i]/v3[i] 
        
        sub.d F6, F4, F1  # v6[i] = (v4[i]-v1[i])
        
        
        s.d  F4, V4(R11)                  
        
        sub.d F5, F5, F2  # – v2[i];
        
        daddui R10, R10, -1
        
        mul.d F6, F6, F5  # *v5[i];

        s.d  F5, V5(R11)                  

        daddui R11, R11, -8

        s.d  F6, V6(R11) 
        bnez  R10, loop
end:
        halt
