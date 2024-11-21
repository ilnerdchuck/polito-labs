-- Author: Paolo Camurati
-- File : Mux4x1.vhd
-- Design units:
-- entity Mux4x1
-- function: 4 to 1 multiplexer 
-- input: data (4 bits), sel (2 bits)
-- output: output (1 bit)
-- architecture Mux4x1_behavioral CASE-WHEN
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: NONE
--  Revision history
--  Version 1.0
--  Date: 20170524
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Mux4x1 IS
  PORT (data:   IN std_logic_vector(3 DOWNTO 0);
        sel:    IN std_logic_vector(1 DOWNTO 0);
        output: OUT std_logic);
END Mux4x1;

ARCHITECTURE Mux4x1_beh OF Mux4x1 IS
BEGIN
  PROCESS(sel, data)
  BEGIN
    CASE sel IS
      WHEN "00"   => output <= data(0);
      WHEN "01"   => output <= data(1);
      WHEN "10"   => output <= data(2);
      WHEN OTHERS => output <= data(3);
      -- I prefer
      -- WHEN "11"   => output <= data(3);
      -- WHEN OTHERS => output <= 'Z'
    END CASE; 
  END PROCESS;
END Mux4x1_beh;




