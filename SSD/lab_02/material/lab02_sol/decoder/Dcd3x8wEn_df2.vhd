-- Author: Paolo Camurati
-- File : Dcd3x8wEn_df2.vhd
-- Design units:
-- entity Dcd3x8wEn
-- function: 3 to 8 decoder with enable
-- input: sel (3 bits), en (1 bit)
-- output: output (8 bits)
-- architecture Dcd3x8wEn_df2 SELECTED SIGNAL ASSIGNMENT
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Dcd3x8wEn_tb.vhd
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

ARCHITECTURE Dcd3x8wEn_df2 OF Dcd3x8wEn IS
BEGIN
  WITH en&sel SELECT
    output <= "00000001" WHEN "1000",
              "00000010" WHEN "1001",
              "00000100" WHEN "1010",
              "00001000" WHEN "1011",
              "00010000" WHEN "1100",
              "00100000" WHEN "1101",
              "01000000" WHEN "1110",
              "10000000" WHEN "1111",
              -- i preffer
              -- "00000000" WHEN "---0",
              -- "ZZZZZZZZ" WHEN "OTHERS";
              "00000000" WHEN OTHERS;            
END Dcd3x8wEn_df2;
