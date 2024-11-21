-- Author: Paolo Camurati
-- File : barrelshifter_tb.vhd
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
  COMPONENT BarrelShifter IS
  PORT (input:  IN  std_logic_vector(7 DOWNTO 0);
        lar:    IN  std_logic_vector(1 DOWNTO 0);
        amt:    IN  std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic_vector(7 DOWNTO 0));
  END COMPONENT;

  SIGNAL input_s:  std_logic_vector(7 DOWNTO 0);
  SIGNAL lar_s:    std_logic_vector(1 DOWNTO 0);
  SIGNAL amt_s:    std_logic_vector(2 DOWNTO 0);
  SIGNAL output_s: std_logic_vector(7 DOWNTO 0);

BEGIN
  UUT: entity work.BarrelShifter(BarrelShifter_df_opt) PORT MAP (input => input_s, lar => lar_s, amt => amt_s, output => output_s);


  PROCESS
  BEGIN
    input_s <= "11110000";
    amt_s <= "010";
    lar_s <= "00";
    WAIT FOR 10 ns;
    input_s <= "11001100";
    amt_s <= "011";
    lar_s <= "01";
    WAIT FOR 10 ns;
    input_s <= "00001111";
    amt_s <= "110";
    lar_s <= "11";
   WAIT;
  END PROCESS;
END TBarch;
