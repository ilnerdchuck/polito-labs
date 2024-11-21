-- Author: Paolo Camurati
-- File : Mux8x1_df2.vhd
-- Design units:
-- entity Mux8x1
-- function: 8 to 1 multiplexer 
-- input: data (8 bits), select (3 bits)
-- output: output (1 bit)
-- architecture Mux8x1_df2 SELECTED SIGNAL ASSIGNMENT
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

ARCHITECTURE Mux8x1_df2 OF Mux8x1 IS
BEGIN
  WITH sel SELECT
    output <= data(0) WHEN "000",
              data(1) WHEN "001",
              data(2) WHEN "010",
              data(3) WHEN "011",
              data(4) WHEN "100",
              data(5) WHEN "101",
              data(6) WHEN "110",
              data(7) WHEN  OTHERS;
END Mux8x1_df2;
