-- Author: Paolo Camurati
-- File : PriEnc4x2_beh1.vhd
-- Design units:
-- entity PriEnc4x2
-- function: 4 to 2 priority encoder 
-- input: req (4 bits)
-- output: code (2 bits) active (1 bit)
-- architecture PriEnc4x2_beh1 IF-THEN-ELSIF
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: PriEnc4x2_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY PriEnc4x2 IS
  PORT (req:    IN std_logic_vector(3 DOWNTO 0);
        active: OUT std_logic;
        code:   OUT std_logic_vector(1 DOWNTO 0));
END PriEnc4x2;

ARCHITECTURE PriEnc4x2_beh1 OF PriEnc4x2 IS
BEGIN
  PROCESS(req)
  BEGIN
    IF (req(3) = '1') THEN
      code <= "11";
    ELSIF (req(2) = '1') THEN
      code <= "10";
    ELSIF (req(1) = '1') THEN
      code <= "01";
    ELSE
      code <= "00";
    END IF;
  END PROCESS;
  active <= req(3) OR req(2) OR req(1) OR req(0); 
END PriEnc4x2_beh1;
