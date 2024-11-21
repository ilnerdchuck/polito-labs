-- Author: Paolo Camurati
-- File : Gray_inc_N_df.vhd
-- Design units:
-- entity generic Gray_inc_N
-- function: generic Gray code incrementor N bits 
-- input: input (N bits)
-- output: output (N bits)
-- architecture Gray_inc_N_df
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Gray_inc_N_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Gray_inc_N IS
  GENERIC (N: integer := 4);
  PORT (input:  IN  std_logic_vector (N-1 DOWNTO 0);
        bin:    BUFFER std_logic_vector(N-1 DOWNTO 0);
        output: OUT std_logic_vector (N-1 DOWNTO 0));
END Gray_inc_N;

ARCHITECTURE Gray_inc_N_df OF Gray_inc_N IS
  SIGNAL bin_inc: std_logic_vector (N-1 DOWNTO 0);
BEGIN
  bin <= input XOR ('0' & bin(N-1 DOWNTO 1));
  bin_inc <= std_logic_vector(unsigned(bin) + 1);
  output <= bin_inc XOR ('0' & bin_inc(N-1 DOWNTO 1));
END Gray_inc_N_df;
