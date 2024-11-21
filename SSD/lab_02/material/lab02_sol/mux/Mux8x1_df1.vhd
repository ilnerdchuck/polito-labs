-- Author: Paolo Camurati
-- File : Mux8x1_df1.vhd
-- Design units:
-- entity Mux8x1
-- function: 8 to 1 multiplexer 
-- input: data (8 bits), select (3 bits)
-- output: output (1 bit)
-- architecture Mux8x1_df1 CONDITIONAL SIGNAL ASSIGNMENT
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Mux8x1_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Mux8x1 IS
  PORT (data:   IN std_logic_vector(7 DOWNTO 0);
        sel:    IN std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic);
END Mux8x1;

ARCHITECTURE Mux8x1_df1 OF Mux8x1 IS
BEGIN
  output <= data(0) WHEN (sel = "000") ELSE
            data(1) WHEN (sel = "001") ELSE
            data(2) WHEN (sel = "010") ELSE
            data(3) WHEN (sel = "011") ELSE
            data(4) WHEN (sel = "100") ELSE
            data(5) WHEN (sel = "101") ELSE
            data(6) WHEN (sel = "110") ELSE
            data(7);
END Mux8x1_df1;
