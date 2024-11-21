-- Author: Paolo Camurati
-- File : Or2.vhd
-- Design units:
-- entity Or2
-- function: 2-input logic OR gate 
-- input: x, y (1 bit)
-- output: F (1 bit)
-- architecture Or2_dataflow
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

ENTITY Or2 IS
  PORT (x: in std_logic;
        y: in std_logic;
        F: out std_logic);
END Or2;  

ARCHITECTURE Or2_dataflow OF Or2 IS
BEGIN
  F <= x OR y;
END Or2_dataflow;


--ARCHITECTURE behav1 OF Or2 IS
--BEGIN
--   PROCESS(x, y)
--   BEGIN
   -- based on truth table
--      IF ((x='0') AND (y='0')) THEN
--	    F <= '0';
--	 ELSE
--	    F <= '1';
--	 END IF;
--   END PROCESS;
--END behav1;

--ARCHITECTURE behav2 OF Or2 IS
--BEGIN
--   PROCESS(x, y)
--   BEGIN
--      F <= x OR y;
--   END PROCESS;
--END behav2;

