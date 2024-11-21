-- Author: Paolo Camurati
-- File : ALU_N_tb.vhd
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
  COMPONENT ALU_N IS
    GENERIC (N: integer := 4);
    PORT (src0,src1: IN  std_logic_vector (N-1 DOWNTO 0);
          ctrl:      IN  std_logic_vector (2 DOWNTO 0);     
          result:    OUT std_logic_vector (N-1 DOWNTO 0));
  END COMPONENT;

  SIGNAL src0_s, src1_s: std_logic_vector(3 DOWNTO 0);
  SIGNAL ctrl_s: std_logic_vector(2 DOWNTO 0);
  SIGNAL result_s: std_logic_vector(3 DOWNTO 0);

BEGIN
  UUT: ALU_N GENERIC MAP (4) PORT MAP (src0 => src0_s, src1 => src1_s, ctrl => ctrl_s, result => result_s);
                         
  PROCESS
  BEGIN
    src0_s <= "0001";
    ctrl_s <= "000";
    WAIT FOR 10 ns;
    ASSERT result_s = "0010" REPORT "Increment failed"; 
    src0_s <= "0101";
    ctrl_s <= "001";
    WAIT FOR 10 ns;
    ASSERT result_s = "0110" REPORT "Increment failed"; 
    src0_s <= "1001";
    ctrl_s <= "010";
    WAIT FOR 10 ns;
    ASSERT result_s = "1010" REPORT "Increment failed"; 
    src0_s <= "1111";
    ctrl_s <= "011";
    WAIT FOR 10 ns;
    ASSERT result_s = "0000" REPORT "Increment failed"; 
    src0_s <= "0001";
    src1_s <= "1001";
    ctrl_s <= "100";
    WAIT FOR 10 ns;
    ASSERT result_s = "1010" REPORT "Sum failed"; 
    src0_s <= "0001";
    src1_s <= "1001";
    ctrl_s <= "101";
    WAIT FOR 10 ns;
    ASSERT result_s = "1000" REPORT "Subtraction failed"; 
    src0_s <= "0001";
    src1_s <= "1001";
    ctrl_s <= "110";
    WAIT FOR 10 ns;
    ASSERT result_s = "0001" REPORT "AND failed"; 
    src0_s <= "0001";
    src1_s <= "1001";
    ctrl_s <= "111";
    WAIT FOR 10 ns;
    ASSERT result_s = "1001" REPORT "OR failed"; 
    WAIT;
  END PROCESS; 
END TBarch;
