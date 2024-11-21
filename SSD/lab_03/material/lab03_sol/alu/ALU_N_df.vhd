-- Author: Paolo Camurati
-- File : ALU_N_df.vhd
-- Design units:
-- entity generic ALU_N
-- function: generic ALU on N bits 
-- input:src0, src1 (N bits), ctrl (3 bits)
-- output: result (N bits)
-- architecture ALU_N_df
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: ALU_N_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY ALU_N IS
  GENERIC (N: integer := 4);
  PORT (src0,src1: IN  std_logic_vector (N-1 DOWNTO 0);
        ctrl:      IN  std_logic_vector (2 DOWNTO 0);     
        result:    OUT std_logic_vector (N-1 DOWNTO 0));
END ALU_N;

ARCHITECTURE ALU_N_df OF ALU_N IS
BEGIN
  result <= std_logic_vector(signed(src0) + signed(src1)) WHEN (ctrl = "100") ELSE
            std_logic_vector(signed(src0) - signed(src1)) WHEN (ctrl = "101") ELSE
            src0 AND src1                                 WHEN (ctrl = "110") ELSE
            src0 OR src1                                  WHEN (ctrl = "111") ELSE
            std_logic_vector(signed(src0) +1);
END ALU_N_df;
