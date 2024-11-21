-- Author: Paolo Camurati
-- File : Reconfig_ALU_tb.vhd simplified operands
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
  COMPONENT Reconfig_ALU IS
    PORT(A:      IN std_logic_vector(15 DOWNTO 0);
         B:      IN std_logic_vector(15 DOWNTO 0);
         ctrl:   IN std_logic_vector(2 DOWNTO 0);
         c_in:   IN std_logic;
         nibble: IN std_logic_vector(3 DOWNTO 0);
         c_out:  OUT std_logic;
         result: OUT std_logic_vector(15 DOWNTO 0));
  END COMPONENT;
  

  SIGNAL A_s, B_s:        std_logic_vector(15 DOWNTO 0);
  SIGNAL ctrl_s:          std_logic_vector(2 DOWNTO 0);
  SIGNAL c_in_s, c_out_s: std_logic;
  SIGNAL nibble_s:        std_logic_vector(3 DOWNTO 0);
  SIGNAL result_s:        std_logic_vector(15 DOWNTO 0);

BEGIN
  CompToTest: Reconfig_ALU 
    PORT MAP (A => A_s, B => B_s, ctrl => ctrl_s, c_in => c_in_s, nibble => nibble_s, c_out => c_out_s, result => result_s);
                         
  PROCESS
  BEGIN
    A_s <= "1111111111111111";
    B_s <= "0000000000000000";
    ctrl_s <= "000";
    nibble_s <= "1111";
    c_in_s <= '0';
    WAIT FOR 10 ns;
    ASSERT result_s = "0001000100010000" REPORT "Increment failed on result"; 
    ASSERT c_out_s = '1' REPORT "Increment failed on carry-out"; 
    A_s <= "1111111111111111";
    B_s <= "0000000000000000";
    ctrl_s <= "000";
    nibble_s <= "1000";
    c_in_s <= '0';
    WAIT FOR 10 ns;
    ASSERT result_s = "0000000000000000" REPORT "Increment failed on result"; 
    ASSERT c_out_s = '1' REPORT "Increment failed on carry-out"; 
    A_s <= "0000101011111111";
    B_s <= "0000100000000000";
    ctrl_s <= "100";
    nibble_s <= "0100";
    c_in_s <= '0';
    WAIT FOR 10 ns;
    ASSERT result_s = "0000001000000000" REPORT "Sum failed on result"; 
    ASSERT c_out_s = '0' REPORT "Sum failed on carry-out"; 
    WAIT;
  END PROCESS; 
END TBarch;
