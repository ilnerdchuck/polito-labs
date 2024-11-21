-- Author: Paolo Camurati
-- File : Xor2.vhd
-- Design units:
-- entity Xor2
-- function: 2-input logic XOR gate 
-- input: x, y (1 bit)
-- output: F (1 bit)
-- architecture Xor2_dataflow
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: NONE
--  Revision history
--  Version 1.0
--  Date: 20170526
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY Xor2 IS
  PORT (x: in std_logic;
        y: in std_logic;
	   F: out std_logic);
END Xor2;  

ARCHITECTURE Xor2_dataflow OF Xor2 IS
BEGIN
  F <= x XOR y;
END Xor2_dataflow;

--ARCHITECTURE behav1 OF Xor2 IS
--BEGIN
--   PROCESS(x, y)
--   BEGIN
   -- based on truth table
--      IF ((x=y) THEN
--	    F <= '0';
--	 ELSE
--	    F <= '1';
--	 END IF;
--   END PROCESS;
--END behav1;

--ARCHITECTURE behav2 OF Xor2 IS
--BEGIN
--  PROCESS(x, y)
--  BEGIN
--      F <= x XOR y;
--   END PROCESS;
--END behav2;

