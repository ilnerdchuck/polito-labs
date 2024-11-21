-- Author: Paolo Camurati
-- File : Mult8opt.vhd
-- Design units:
-- entity Mult8opt
-- function: optimized 8-bit multiplier for unsigned integers
-- input: A, B (8 bits)
-- output: result (16 bits)
-- architecture Mult8opt_dataflow
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Mult8_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Mult8opt IS
  PORT (A, B:   IN  std_logic_vector (7 DOWNTO 0);
        result: OUT std_logic_vector (15 DOWNTO 0));
END Mult8opt;

ARCHITECTURE Mult8opt_df OF Mult8opt IS
  SIGNAL A_unsign, B_0, B_1, B_2, B_3, B_4, B_5, B_6, B_7: unsigned(7 DOWNTO 0);
  SIGNAL P_0, P_1, P_2, P_3, P_4, P_5, P_6, P_7: unsigned(8 DOWNTO 0);
  SIGNAL prod: unsigned(15 DOWNTO 0);

BEGIN
  A_unsign <= unsigned(A);
  -- can't i just assign B_0 <= B(0)
  B_0 <=  (OTHERS => B(0));
  B_1 <=  (OTHERS => B(1));
  B_2 <=  (OTHERS => B(2));
  B_3 <=  (OTHERS => B(3));
  B_4 <=  (OTHERS => B(4));
  B_5 <=  (OTHERS => B(5));
  B_6 <=  (OTHERS => B(6));
  B_7 <=  (OTHERS => B(7));

  P_0 <= "0"  & (A_unsign AND B_0); 
  P_1 <= ("0" & P_0(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_1)); 
  P_2 <= ("0" & P_1(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_2)); 
  P_3 <= ("0" & P_2(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_3)); 
  P_4 <= ("0" & P_3(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_4)); 
  P_5 <= ("0" & P_4(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_5)); 
  P_6 <= ("0" & P_5(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_6)); 
  P_7 <= ("0" & P_6(8 DOWNTO 1)) +  ("0" & (A_unsign AND B_7)); 
  
  prod <= P_7 & P_6(0) & P_5(0) & P_4(0) & P_3(0) & P_2(0) & P_1(0) & P_0(0);

  result <= std_logic_vector(prod);

END Mult8opt_df;
