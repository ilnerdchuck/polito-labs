-- Author: Paolo Camurati
-- File : And2.vhd
-- Design units:
-- entity And2
-- function: 2-input logic AND gate 
-- input: x, y (1 bit)
-- output: F (1 bit)
-- architecture And2_dataflow
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

ENTITY And2 IS
  PORT (x: in std_logic;
        y: in std_logic;
        F: out std_logic);
END And2;  

ARCHITECTURE And2_dataflow OF And2 IS
BEGIN
  F <= x AND y;
END And2_dataflow;


--ARCHITECTURE behav1 OF And2 IS
--BEGIN
--   PROCESS(x, y)
--   BEGIN
   -- based on truth table
--      IF ((x='1') AND (y='1')) THEN
--	    F <= '1';
--	 ELSE
--	    F <= '0';
--	 END IF;
--   END PROCESS;
--END behav1;

--ARCHITECTURE behav2 OF And2 IS
--BEGIN
--   PROCESS(x, y)
--   BEGIN
--      F <= x AND y;
--   END PROCESS;
--END behav2;

