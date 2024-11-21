-- Author: Paolo Camurati
-- File : Majority_ALU_struct.vhd
-- Design units:
-- entity Majority_ALU
-- function: 3 ALUs with majority vote 
-- input: A, B, C, D, E, F (8 bits), ctrl (3 bits)
-- output: decision (8 bits), valid (1 bit)
-- architecture Majority_ALU_struct
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Majority_ALU_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Majority_ALU IS
  PORT (A, B, C, D, E, F: IN std_logic_vector(7 DOWNTO 0);
        ctrl:             IN std_logic_vector(2 DOWNTO 0);
        valid:            OUT std_logic;
        decision:         OUT std_logic_vector(7 DOWNTO 0));
END Majority_ALU;

ARCHITECTURE Majority_ALU_struct OF Majority_ALU IS
  COMPONENT ALU_N IS
    GENERIC (N: integer := 4);
    PORT (src0,src1: IN  std_logic_vector (N-1 DOWNTO 0);
          ctrl:      IN  std_logic_vector (2 DOWNTO 0);     
          result:    OUT std_logic_vector (N-1 DOWNTO 0));
  END COMPONENT;
  
  COMPONENT VOTER_N IS
    GENERIC (N: integer := 4);
    PORT (src0,src1,src2: IN  std_logic_vector (N-1 DOWNTO 0);
          valid:      OUT  std_logic;     
          decision:   OUT std_logic_vector (N-1 DOWNTO 0));
  END COMPONENT;
  
  SIGNAL res0, res1, res2: std_logic_vector(7 DOWNTO 0);  

BEGIN

  ALU_0: ALU_N GENERIC MAP (8) PORT MAP (src0 => A, src1 => B, ctrl => ctrl, result => res0);
  ALU_1: ALU_N GENERIC MAP (8) PORT MAP (src0 => C, src1 => D, ctrl => ctrl, result => res1);
  ALU_2: ALU_N GENERIC MAP (8) PORT MAP (src0 => E, src1 => F, ctrl => ctrl, result => res2);

  VOTER: VOTER_N GENERIC MAP (8) PORT MAP (src0 => res0, src1 => res1, src2 => res2, valid => valid, decision => decision);
  
END Majority_ALU_struct;
