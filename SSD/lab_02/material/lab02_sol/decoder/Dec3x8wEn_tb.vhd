-- Author: Paolo Camurati
-- File : Dec3x8wEn_tb.vhd
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
  COMPONENT Dcd3x8wEn IS
    PORT (sel:    IN std_logic_vector(2 DOWNTO 0);
          en:     IN std_logic;
          output: OUT std_logic_vector(7 DOWNTO 0));
  END COMPONENT;

  SIGNAL en_s: std_logic;
  SIGNAL output_s: std_logic_vector(7 DOWNTO 0);
  SIGNAL sel_s: std_logic_vector(2 DOWNTO 0);

BEGIN
  UUT: entity work.Dcd3x8wEn(Dcd3x8wEn_df2) PORT MAP (sel => sel_s, en => en_s, output => output_s);

  PROCESS
  BEGIN
  -- Enumerate selection input combinations
    en_s <= '0';    
    sel_s <= "000";
    WAIT FOR 10 ns;
    en_s <= '0';    
    sel_s <= "111";
    WAIT FOR 10 ns;
    en_s <= '1';
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
