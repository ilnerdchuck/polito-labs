-- Author: Paolo Camurati
-- File : Voter_N_df.vhd
-- Design units:
-- entity generic Voter_N
-- function: generic majority voter on N bits 
-- input:src0, src1, src2 (N bits)
-- output: decision (N bits), valid (1 bit)
-- architecture Voter_N_df
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: 
-- to use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: ALU_N_tb.vhd
--  Revision history
--  Version 1.0
--  Date: 20170605
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY VOTER_N IS
  GENERIC (N: integer := 4);
    PORT (src0, src1, src2: IN   std_logic_vector (N-1 DOWNTO 0);
          valid:            OUT  std_logic;     
          decision:         OUT std_logic_vector (N-1 DOWNTO 0));
END VOTER_N;

ARCHITECTURE Voter_N_df OF Voter_N IS
BEGIN
  valid <= '1' WHEN (signed(src0) = signed(src1)) ELSE
           '1' WHEN (signed(src0) = signed(src2)) ELSE
           '1' WHEN (signed(src1) = signed(src2)) ELSE
           '0';
  decision <=  src0  WHEN (signed(src0) = signed(src1)) ELSE
               src0  WHEN (signed(src0) = signed(src2)) ELSE
               src1  WHEN (signed(src1) = signed(src2)) ELSE
              (OTHERS => 'Z');
END Voter_N_df;