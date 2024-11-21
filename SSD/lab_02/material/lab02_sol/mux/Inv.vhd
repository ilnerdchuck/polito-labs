-- Author: Paolo Camurati
-- File : Inv.vhd
-- Design units:
-- entity Inv
-- function: inverter gate 
-- input: x (1 bit)
-- output: F (1 bit)
-- architecture Inv_dataflow
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: NONE
--  Revision history
--  Version 1.0
--  Date: 20170524
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY Inv IS
  PORT (x: in std_logic;
        F: out std_logic);
END Inv;  


ARCHITECTURE Inv_dataflow OF Inv IS
BEGIN
  F <= NOT x;
END Inv_dataflow;

--ARCHITECTURE behav1 OF Inv IS
--BEGIN
--   PROCESS(x)
-- BEGIN
   -- based on truth table
--      IF ((x='1') THEN
--	    F <= '0';
--	 ELSE
--	    F <= '1';
--	 END IF;
--   END PROCESS;
--END behav1;

--ARCHITECTURE behav2 OF Inv IS
--BEGIN
--   PROCESS(x)
--   BEGIN
--      F <= NOT x;
--   END PROCESS;
--END behav2;

