-- Author: Paolo Camurati
-- File : Mux2x1.vhd
-- Design units:
-- entity Mux2x1
-- function: 2 to 1 multiplexer 
-- input: data (2 bits), sel (1 bit)
-- output: output (1 bit)
-- architecture Mux2x1_struct
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

ENTITY Mux2x1 IS
  PORT (data:   IN std_logic_vector(1 DOWNTO 0);
        sel:    IN std_logic;
        output: OUT std_logic);
END Mux2x1;

ARCHITECTURE Mux2x1_struct OF Mux2x1 IS
  COMPONENT And2 IS
    PORT (x, y: IN std_logic;
          F: OUT std_logic);
  END COMPONENT;
  COMPONENT Or2 IS
    PORT (x, y: IN std_logic;
          F: OUT std_logic);
  END COMPONENT;
  COMPONENT Inv IS
    PORT (x: IN std_logic;
          F: OUT std_logic);
  END COMPONENT;

  SIGNAL _sel, and_1, and_2: std_logic;
   
BEGIN
  Inv_1:  Inv  PORT MAP (sel, _sel);
  And2_1: And2 PORT MAP (data(0), _sel, and_1);
  And2_2: And2 PORT MAP (data(1), sel, and_2);
  Or2_1:  Or2  PORT MAP (and_1, and_2, output);
END Mux2x1_struct;
