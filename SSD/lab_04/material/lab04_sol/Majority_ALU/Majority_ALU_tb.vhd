-- Author: Paolo Camurati
-- File: Majority_ALU_tb.vhd
-- Design units:
-- entity Testbench
-- function:  
-- input: 
-- output:
-- architecture: component + stimuli process
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
  COMPONENT Majority_ALU IS
    PORT (A, B, C, D, E, F: IN std_logic_vector(7 DOWNTO 0);
          ctrl:             IN std_logic_vector(2 DOWNTO 0);
          valid:            OUT std_logic;
          decision:         OUT std_logic_vector(7 DOWNTO 0));
  END COMPONENT;

  SIGNAL A_s, B_s, C_s, D_s, E_s, F_s, decision_s: std_logic_vector(7 DOWNTO 0);
  SIGNAL ctrl_s: std_logic_vector(2 DOWNTO 0);
  SIGNAL valid_s: std_logic;

BEGIN
UUT: Majority_ALU PORT MAP (A => A_s, B => B_s, C => C_s, D => D_s, E => E_s, F => F_s, ctrl => ctrl_s, valid => valid_s, decision => decision_s);
                         
  PROCESS
  BEGIN
    A_s <= "00010001";
    B_s <= "00000000";
    C_s <= "00010000";
    D_s <= "00000000";
    E_s <= "00000001";
    F_s <= "00000000";
    ctrl_s <= "100";
    WAIT FOR 10 ns;
    ASSERT valid_s='0' REPORT "Invalid sum undetected"; 
    A_s <= "00010001";
    B_s <= "00000000";
    C_s <= "00010001";
    D_s <= "00000000";
    E_s <= "00000001";
    F_s <= "00000000";
    ctrl_s <= "000";
    WAIT FOR 10 ns;
    ASSERT valid_s='1' REPORT "Invalid sum undetected"; 
    
    WAIT;
  END PROCESS; 
END TBarch;

