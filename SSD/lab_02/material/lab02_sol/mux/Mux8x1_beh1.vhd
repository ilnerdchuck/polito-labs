-- Author: Paolo Camurati
-- File : Mux8x1_beh1.vhd
-- Design units:
-- entity Mux8x1
-- function: 8 to 1 multiplexer 
-- input: data (8 bits), select (3 bits)
-- output: output (1 bit)
-- architecture Mux8x1_beh1 IF-THEN-ELSIF
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

ARCHITECTURE Mux8x1_beh1 OF Mux8x1 IS
BEGIN
  PROCESS(sel, data)
  BEGIN
    IF (sel = "000") THEN
      output <= data(0);
    ELSIF (sel = "001") THEN
      output <= data(1);
    ELSIF (sel = "010") THEN
      output <= data(2);
    ELSIF (sel = "011") THEN
      output <= data(3);
    ELSIF (sel = "100") THEN
      output <= data(4);
    ELSIF (sel = "101") THEN
      output <= data(5);
    ELSIF (sel = "110") THEN
      output <= data(6);
    ELSE
      output <= data(7);
    END IF;
  END PROCESS;
END Mux8x1_beh1;
