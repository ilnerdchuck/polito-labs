-- Author: Paolo Camurati
-- File : Mult8_tb.vhd
-- Design units:
-- entity Testbench
-- function: 
-- input: 
-- output: 
-- architecture: component + stimuli process
-- Library/package:ieee.std_logic_ll64
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
  COMPONENT Mult8opt IS
    PORT (A, B:   IN  std_logic_vector (7 DOWNTO 0);
          result: OUT std_logic_vector (15 DOWNTO 0));
  END COMPONENT;

  SIGNAL A_s, B_s: std_logic_vector(7 DOWNTO 0);
  SIGNAL result_s: std_logic_vector(15 DOWNTO 0);

BEGIN
  CompToTest: Mult8opt PORT MAP (A_s, B_s, result_s);
                         
  PROCESS
  BEGIN
    A_s <= "00001001";
    B_s <= "00000100";
    WAIT FOR 10 ns;
    ASSERT result_s = "0000000000100100" REPORT "Product failed on result";
    A_s <= "00001111";
    B_s <= "00001100";
    WAIT FOR 10 ns;
    ASSERT result_s = "0000000010110100" REPORT "Product failed on result";
    A_s <= "11111111";
    B_s <= "11111111";
    WAIT FOR 10 ns;
    ASSERT result_s = "1111111000000001" REPORT "Product failed on result"; 
    WAIT;
  END PROCESS;
  
END TBarch;
