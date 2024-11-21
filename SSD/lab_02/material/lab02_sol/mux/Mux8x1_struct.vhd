-- Author: Paolo Camurati
-- File : Mux8x1_struct.vhd
-- Design units:
-- entity Mux8x1
-- function: 8 to 1 multiplexer 
-- input: data (8 bits), select (3 bits)
-- output: output (1 bit)
-- architecture Mux8x1_struct
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: Mux8x1_tb.vhd
--  Revision history
--  Version 1.0
--  Date: 20170524
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Mux8x1 IS
  PORT (data:   IN std_logic_vector(7 DOWNTO 0);
        sel: IN std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic);
END Mux8x1;

ARCHITECTURE Mux8x1_struct OF Mux8x1 IS
  COMPONENT Mux2x1 IS
    PORT (data: IN std_logic_vector(1 DOWNTO 0);
          sel: IN std_logic;
          output: OUT std_logic);
  END COMPONENT;
  COMPONENT Mux4x1 IS
    PORT (data: IN std_logic_vector(3 DOWNTO 0);
          sel: IN std_logic_vector(1 DOWNTO 0);
          output: OUT std_logic);
  END COMPONENT;

  SIGNAL n: std_logic_vector(1 DOWNTO 0);

BEGIN
   Mux4x1_l:Mux4x1 PORT MAP(data(3 DOWNTO 0),sel(1 DOWNTO 0), n(0));
   Mux4x1_h:Mux4x1 PORT MAP(data(7 DOWNTO 4),sel(1 DOWNTO 0), n(1));
   Mux2x1_o:Mux2x1 PORT MAP(n(1 DOWNTO 0),sel(2), output);
END Mux8x1_struct;
