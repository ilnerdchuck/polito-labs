-- Author: Paolo Camurati
-- File : PriEnc4x2_df2.vhd
-- Design units:
-- entity PriEnc4x2
-- function: 4  to 2 priority encoder 
-- input: req (4 bits)
-- output: code (2 bits) active (1 bit)
-- architecture PriEnc4x2_df2 SELECTED SIGNAL
-- ASSIGNMENT
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: PriEnc4x2_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY PriEnc4x2 IS
  PORT (req:    IN std_logic_vector(3 DOWNTO 0);
        active: OUT std_logic;
        code:   OUT std_logic_vector(1 DOWNTO 0));
END PriEnc4x2;

ARCHITECTURE PriEnc4x2_df2 OF PriEnc4x2 IS
BEGIN
  WITH req SELECT 
    code <= "11" WHEN "1000" | "1001" | "1010" | "1011" |
                      "1100" | "1101" | "1110" | "1111",
            "10" WHEN "0100" | "0101" | "0110" | "0111",
            "01" WHEN "0010" | "0011",  
            "00" WHEN OTHERS;             
  active <= req(3) OR req(2) OR req(1) OR req(0);  
END PriEnc4x2_df2;
