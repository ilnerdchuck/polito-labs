-- Author: Paolo Camurati
-- File : AddN_beh.vhd
-- Design units:
-- entity generic AddN
-- function: generic Adder on N bits 
-- input: A, B (N bits)
-- output: S (N+1 bits)
-- architecture AddN_beh
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: AddN_tb.vhd
--  Revision history
--  Version 1.0
--  Date: 20170526
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

-- io aggiungerei un bit di out per il carry onestamente 
-- sennó la leggibilitá diminuisce drasticamente
  
ENTITY AddN IS
  GENERIC (N: integer := 4);
  PORT (A,B: IN  std_logic_vector (N-1 DOWNTO 0);
        S:   OUT std_logic_vector (N DOWNTO 0));
END AddN;

ARCHITECTURE AddN_beh OF AddN IS
BEGIN
  PROCESS(A, B)
    VARIABLE A_N, B_N, S_N: unsigned(N DOWNTO 0);
  BEGIN
      A_N := unsigned('0' & A);
      B_N := unsigned('0' & B);
      S_N := A_N + B_N;
      S <= std_logic_vector(S_N(N DOWNTO 0));
  END PROCESS;
END AddN_beh;
