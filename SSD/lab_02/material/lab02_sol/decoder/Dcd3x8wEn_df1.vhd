-- Author: Paolo Camurati
-- File : Dcd3x8wEn_df1.vhd
-- Design units:
-- entity Dcd3x8wEn
-- function: 3 to 8 decoder with enable
-- input: sel (3 bits), en (1 bit)
-- output: output (8 bits)
-- architecture Dcd3x8wEn_df1 CONDITIONAL SIGNAL 
-- ASSIGNMENT
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: 
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

--ENTITY Dcd3x8wEn IS
--  PORT (sel:    IN std_logic_vector(2 DOWNTO 0);
--        en:     IN std_logic;
--        output: OUT std_logic_vector(7 DOWNTO 0));
--END Dcd3x8wEn;

ARCHITECTURE Dcd3x8wEn_df1 OF Dcd3x8wEn IS
BEGIN
  output <= "00000001" WHEN (en&sel = "1000") ELSE
            "00000010" WHEN (en&sel = "1001") ELSE
            "00000100" WHEN (en&sel = "1010") ELSE
            "00001000" WHEN (en&sel = "1011") ELSE
            "00010000" WHEN (en&sel = "1100") ELSE
            "00100000" WHEN (en&sel = "1101") ELSE
            "01000000" WHEN (en&sel = "1110") ELSE
            "10000000" WHEN (en&sel = "1111") ELSE
            "00000000";            
END Dcd3x8wEn_df1;