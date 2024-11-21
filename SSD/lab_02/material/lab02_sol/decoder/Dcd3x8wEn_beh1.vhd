-- Author: Paolo Camurati
-- File : Dcd3x8wEn_beh1.vhd
-- Design units:
-- entity Dcd3x8wEn
-- function: 3 to 8 decoder with enable
-- input: sel (3 bits), en (1 bit)
-- output: output (8 bits)
-- architecture Dcd3x8wEn_beh1 IF-THEN-ELSE
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench:
--  Revision history
--  Version 1.0
--  Date: 20170525
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Dcd3x8wEn IS
  PORT (sel:    IN std_logic_vector(2 DOWNTO 0);
        en:     IN std_logic;
        output: OUT std_logic_vector(7 DOWNTO 0));
END Dcd3x8wEn;

ARCHITECTURE Dcd3x8wEn_beh1 OF Dcd3x8wEn IS
BEGIN
  PROCESS(sel, en)
  BEGIN  
    IF (en = '0') THEN
	   output <= "00000000"; 
    ELSIF (sel = "000") THEN
      output <= "00000001";
    ELSIF (sel = "001") THEN
      output <= "00000010";
    ELSIF (sel = "010") THEN
      output <= "00000100";
    ELSIF (sel = "011") THEN
      output <= "00001000";
    ELSIF (sel = "100") THEN
      output <= "00010000";
    ELSIF (sel = "101") THEN
      output <= "00100000";
    ELSIF (sel = "110") THEN
      output <= "01000000";
    ELSE
      output <= "10000000";
    END IF;
  END PROCESS;
END Dcd3x8wEn_beh1;

