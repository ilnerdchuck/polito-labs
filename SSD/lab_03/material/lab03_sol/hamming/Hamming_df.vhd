-- Author: Paolo Camurati
-- File : Hamming_df.vhd
-- Design units:
-- entity Hamming
-- function: Hamming distance evaluator 
-- input: data1, data2 (8 bits)
-- output: ham_dist (4 bits)
-- architecture Hamming_df
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: Hamming_tb.vhd
--  Revision history
--  Version 1.0
--  Date: 20170526
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Hamming IS
  PORT (data1, data2:   IN std_logic_vector(7 DOWNTO 0);
        ham_dist: OUT std_logic_vector(3 DOWNTO 0));
END Hamming;

ARCHITECTURE Hamming_df OF Hamming IS
  SIGNAL diff: unsigned(7 DOWNTO 0);
  SIGNAL twobitsum_0, twobitsum_2, twobitsum_4, twobitsum_6: unsigned(1 DOWNTO 0);
  SIGNAL threebitsum_0, threebitsum_3: unsigned(2 DOWNTO 0);
  SIGNAL fourbitsum: unsigned(3 DOWNTO 0);
BEGIN
  diff <= unsigned(data1 XOR data2);

  twobitsum_0 <= ('0'&diff(1)) + ('0'&diff(0));
  twobitsum_2 <= ('0'&diff(3)) + ('0'&diff(2));
  twobitsum_4 <= ('0'&diff(5)) + ('0'&diff(4));
  twobitsum_6 <= ('0'&diff(7)) + ('0'&diff(6));
  
  threebitsum_0 <= ('0'&twobitsum_0) + ('0'&twobitsum_2);
  threebitsum_3 <= ('0'&twobitsum_4) + ('0'&twobitsum_6);

  fourbitsum <= ('0'&threebitsum_0) + ('0'&threebitsum_3);

  ham_dist <= std_logic_vector(fourbitsum);
END Hamming_df;
