-- Author: Paolo Camurati
-- File : Gray_inc_N_tb.vhd
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
  COMPONENT Gray_inc_N IS
    GENERIC (N: integer := 4);
	 PORT (input:  IN  std_logic_vector(N-1 DOWNTO 0);
	       bin:    BUFFER std_logic_vector(N-1 DOWNTO 0);
           output: OUT std_logic_vector(N-1 DOWNTO 0));
  END COMPONENT;

  SIGNAL input_s, bin_s, output_s: std_logic_vector(3 DOWNTO 0);

BEGIN
  UUT: Gray_inc_N GENERIC MAP (4) PORT MAP (input => input_s, bin => bin_s, output=> output_s);
                         
  PROCESS
  BEGIN
    input_s <= "0000";
    WAIT FOR 10 ns;
    input_s <= "0001";
    WAIT FOR 10 ns;
    input_s <= "0011";
    WAIT FOR 10 ns;
    input_s <= "0010";
    WAIT FOR 10 ns;
    input_s <= "0110";
    WAIT FOR 10 ns;
    input_s <= "0111";
    WAIT FOR 10 ns;
    input_s <= "0101";
    WAIT FOR 10 ns;
    input_s <= "0100";
    WAIT FOR 10 ns;
    input_s <= "1100";
    WAIT FOR 10 ns;
    input_s <= "1101";
    WAIT FOR 10 ns;
    input_s <= "1111";
    WAIT FOR 10 ns;
    input_s <= "1110";
    WAIT FOR 10 ns;
    input_s <= "1010";
    WAIT FOR 10 ns;
    input_s <= "1011";
    WAIT FOR 10 ns;
    input_s <= "1001";
    WAIT FOR 10 ns;
    input_s <= "1000";
    WAIT;
  END PROCESS;
END TBarch;
