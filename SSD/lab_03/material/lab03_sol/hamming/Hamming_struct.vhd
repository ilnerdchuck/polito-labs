-- Author: Paolo Camurati
-- File : Hamming_struct.vhd
-- Design units:
-- entity Hamming
-- function: Hamming distance evaluator 
-- input: data1, data2 (8 bits)
-- output: ham_dist (4 bits)
-- architecture Hamming_struct
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Hamming_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Hamming IS
  PORT (data1, data2: IN std_logic_vector(7 DOWNTO 0);
        ham_dist: OUT std_logic_vector(3 DOWNTO 0));
END Hamming;

ARCHITECTURE Hamming_struct OF Hamming IS
  COMPONENT Xor2 IS
    PORT (x: in std_logic;
          y: in std_logic;
	  F: out std_logic);
  END COMPONENT;

  COMPONENT AddN IS
    GENERIC (N: integer := 4);
    PORT (A,B: IN  std_logic_vector (N-1 DOWNTO 0);
          S:   OUT std_logic_vector (N DOWNTO 0));
  END COMPONENT;

  SIGNAL diff: std_logic_vector(7 DOWNTO 0);  
  SIGNAL twobitsum_0, twobitsum_2, twobitsum_4, twobitsum_6: std_logic_vector(1 DOWNTO 0);
  SIGNAL threebitsum_0, threebitsum_3: std_logic_vector(2 DOWNTO 0);


BEGIN

  XORS: FOR i IN 0 TO 7 GENERATE 
    X0: Xor2 PORT MAP (x=>data1(i), y=>data2(i), F=>diff(i));
  END GENERATE XORS;

  Sum2_0: AddN GENERIC MAP (1) 
               PORT MAP (A(0)=>diff(0), B(0)=>diff(1), S=>twobitsum_0);
  Sum2_2: AddN GENERIC MAP (1) 
               PORT MAP (A(0)=>diff(2), B(0)=>diff(3), S=>twobitsum_2);
  Sum2_4: AddN GENERIC MAP (1) 
               PORT MAP (A(0)=>diff(4), B(0)=>diff(5), S=>twobitsum_4);
  Sum2_6: AddN GENERIC MAP (1) 
               PORT MAP (A(0)=>diff(6), B(0)=>diff(7), S=>twobitsum_6);
  
  Sum3_0: AddN GENERIC MAP (2) 
               PORT MAP (twobitsum_0, twobitsum_2, threebitsum_0);
  Sum3_3: AddN GENERIC MAP (2) 
               PORT MAP (twobitsum_4, twobitsum_6, threebitsum_3);

   Sum4: AddN GENERIC MAP (3) 
               PORT MAP (threebitsum_0, threebitsum_3, ham_dist);

END Hamming_struct;
