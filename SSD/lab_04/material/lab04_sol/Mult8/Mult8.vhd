-- Author: Paolo Camurati
-- File : Mult8.vhd
-- Design units:
-- entity Mult8
-- function: 8-bit multiplier for unsigned integers
-- input: A, B (8 bits)
-- output: result (16 bits)
-- architecture Mult8_df
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

ENTITY Mult8 IS
  PORT (A, B:   IN  std_logic_vector (7 DOWNTO 0);
        result: OUT std_logic_vector (15 DOWNTO 0));
END Mult8;

ARCHITECTURE Mult8_dataflow OF Mult8 IS
  SIGNAL A_unsign, B_0, B_1, B_2, B_3, B_4, B_5, B_6, B_7: unsigned(7 DOWNTO 0);
  SIGNAL P_0, P_1, P_2, P_3, P_4, P_5, P_6, P_7, prod: unsigned(15 DOWNTO 0);

BEGIN
  A_unsign <= unsigned(A);
  B_0 <=  (OTHERS => B(0));
  B_1 <=  (OTHERS => B(1));
  B_2 <=  (OTHERS => B(2));
  B_3 <=  (OTHERS => B(3));
  B_4 <=  (OTHERS => B(4));
  B_5 <=  (OTHERS => B(5));
  B_6 <=  (OTHERS => B(6));
  B_7 <=  (OTHERS => B(7));
 
  P_0 <= "00000000"  & (A_unsign AND B_0); 
  P_1 <= "0000000"  & (A_unsign AND B_1) & "0"; 
  P_2 <= "000000"  & (A_unsign AND B_2) & "00"; 
  P_3 <= "00000"  & (A_unsign AND B_3) & "000"; 
  P_4 <= "0000"  & (A_unsign AND B_4) & "0000"; 
  P_5 <= "000"  & (A_unsign AND B_5) & "00000"; 
  P_6 <= "00"  & (A_unsign AND B_6) & "000000"; 
  P_7 <= "0"  & (A_unsign AND B_7) & "0000000";
  
  prod <= ((P_0 + P_1) + (P_2 + P_3)) + ((P_4 + P_5) + (P_6 + P_7));
  result <= std_logic_vector(prod);
END Mult8_dataflow;
