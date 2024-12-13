module arbiter_1(
  clk,_res,r0,r1,
  g0,g1,
);
  input r0,r1,_res,clk;
  output g0,g1;

  reg [1:0] STAR;
  reg G0,G1;
  assign g0 = G0;
  assign g1 = G1; 

  parameter S0 ='B00,S1 ='B01,S2 ='B10;
  
  always @(posedge clk)begin
    case (_res)
      0:begin
        STAR <= S0;
        G0 <= 0;
        G1 <= 0;
      end
      1:begin
        casex (STAR)
          S0:
          begin
            G0 <= 0;
            G1 <= 0;
            STAR<=(r0 == 1)? S1:(r1 == 1)? S2:S0;
          end 
          S1:
          begin
            G0 <= 1;
            STAR<=(r0 == 0)? S0:S1;
          end 
          S2:
          begin
            G1 <= 1;
            STAR<=(r0 == 0)? S0:S1;
          end 
        endcase 
      end
    endcase
  end
endmodule
