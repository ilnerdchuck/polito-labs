-- Author: Paolo Camurati
-- File : Hamming_tb.vhd
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
  COMPONENT Hamming IS
    PORT (data1, data2: IN std_logic_vector(7 DOWNTO 0);
          ham_dist:     OUT  std_logic_vector(3 DOWNTO 0));
  END COMPONENT;

  SIGNAL data1_s, data2_s: std_logic_vector(7 DOWNTO 0);
  SIGNAL ham_dist_s:       std_logic_vector(3 DOWNTO 0);

BEGIN
  UUT: entity work.Hamming(Hamming_beh) PORT MAP (data1 => data1_s, data2 => data2_s, ham_dist => ham_dist_s);

  PROCESS
  BEGIN
    data1_s <= "00000000";
    data2_s <= "00000000";
    WAIT FOR 10 ns;
    data1_s <= "01000000";
    data2_s <= "00000000";
    WAIT FOR 10 ns;
    data1_s <= "00000000";
    data2_s <= "01000010";
    WAIT FOR 10 ns;
    data1_s <= "10000010";
    data2_s <= "00001000";
    WAIT FOR 10 ns;
    data1_s <= "01000010";
    data2_s <= "00101000";
    WAIT FOR 10 ns;
    data1_s <= "10100010";
    data2_s <= "01001000";
    WAIT FOR 10 ns;
    data1_s <= "10100100";
    data2_s <= "01010001";
    WAIT FOR 10 ns;
    data1_s <= "10101010";
    data2_s <= "01010100";
    WAIT FOR 10 ns;
    data1_s <= "01010101";
    data2_s <= "10101010";
    WAIT FOR 10 ns;
    WAIT;
  END PROCESS;
END TBarch;
