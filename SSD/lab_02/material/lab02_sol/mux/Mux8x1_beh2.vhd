-- Author: Paolo Camurati
-- File : Mux8x1_beh2.vhd
-- Design units:
-- entity Mux8x1
-- function: 8 to 1 multiplexer 
-- input: data (8 bits), select (3 bits)
-- output: output (1 bit)
-- architecture Mux8x1_beh2 CASE-WHEN
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
        sel: IN std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic);
END Mux8x1;

ARCHITECTURE Mux8x1_beh2 OF Mux8x1 IS
BEGIN
  PROCESS(sel, data)
  BEGIN
    CASE sel IS
      WHEN "000"  => output <= data(0);
      WHEN "001"  => output <= data(1);
      WHEN "010"  => output <= data(2);
      WHEN "011"  => output <= data(3);
      WHEN "100"  => output <= data(4);
      WHEN "101"  => output <= data(5);
      WHEN "110"  => output <= data(6);
      WHEN OTHERS => output <= data(7);
    END CASE; 
  END PROCESS;
END Mux8x1_beh2;





