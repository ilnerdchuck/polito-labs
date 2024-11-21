-- Author: Paolo Camurati
-- File : Mux8x1_tb.vhd
-- Design units:
-- entity Testbench
-- function: 
-- input: 
-- output: 
-- architecture component + stimuli process
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

ENTITY Testbench IS
END Testbench;

ARCHITECTURE TBarch OF Testbench IS
  COMPONENT Mux8x1 IS
    PORT (data:   IN std_logic_vector(7 DOWNTO 0);
          sel: IN std_logic_vector(2 DOWNTO 0);
          output: OUT std_logic);
  END COMPONENT;

  SIGNAL output_s: std_logic;
  SIGNAL data_s: std_logic_vector(7 DOWNTO 0);
  SIGNAL sel_s: std_logic_vector(2 DOWNTO 0);

BEGIN
  UUT: entity work.Mux8x1(Mux8x1_struct) PORT MAP (data => data_s, sel => sel_s, output=> output_s);

  PROCESS
  BEGIN
  -- Enumerate selection input combinations
    data_s <= "10001111";
    sel_s <= "000";
    WAIT FOR 10 ns;
    sel_s <= "001";
    WAIT FOR 10 ns;
    sel_s <= "010";
    WAIT FOR 10 ns;
    sel_s <= "011";
    WAIT FOR 10 ns;
    sel_s <= "100";
    WAIT FOR 10 ns;
    sel_s <= "101";
    WAIT FOR 10 ns;
    sel_s <= "110";
    WAIT FOR 10 ns;
    sel_s <= "111";
    WAIT;
  END PROCESS;
END TBarch;
