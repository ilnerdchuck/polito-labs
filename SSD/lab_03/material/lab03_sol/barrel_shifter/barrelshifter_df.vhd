-- Author: Paolo Camurati
-- File : barrelshifter_dataflow_base.vhd
-- Design units:
-- entity barrel
-- function: programmable barrel shifter 
-- input: lar (2 bits), amt (3 bits)
-- output: output (8 bits)
-- architecture BarrelShifter_df
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: barrelshifter_tb.vhd
--  Revision history
--  Version 1.0
--  Date: 20170531
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY BarrelShifter IS
  PORT (input:  IN std_logic_vector(7 DOWNTO 0);
        lar:    IN std_logic_vector(1 DOWNTO 0);
        amt:    IN std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic_vector(7 DOWNTO 0));
END barrelshifter;

ARCHITECTURE BarrelShifter_df OF BarrelShifter IS
  SIGNAL res_log, res_arith, res_rot: std_logic_vector(7 DOWNTO 0);
BEGIN
  WITH amt SELECT
    res_log <= input WHEN "000",
               "0" & input(7 DOWNTO 1) WHEN "001",
               "00" & input(7 DOWNTO 2) WHEN "010",
               "000" & input(7 DOWNTO 3) WHEN "011",
               "0000" & input(7 DOWNTO 4) WHEN "100",
               "00000" & input(7 DOWNTO 5) WHEN "101",
               "000000" & input(7 DOWNTO 6) WHEN "110",
               "0000000" & input(7)          WHEN OTHERS;

  WITH amt SELECT
    res_arith <= input WHEN "000",
               input(7) & input(7 DOWNTO 1) WHEN "001",
               input(7) & input(7) & input(7 DOWNTO 2) WHEN "010",
               input(7) & input(7) & input(7) & input(7 DOWNTO 3) WHEN "011",
               input(7) & input(7) & input(7) & input(7) & input(7 DOWNTO 4) WHEN "100",
               input(7) & input(7) & input(7) & input(7) & input(7) & input(7 DOWNTO 5) WHEN "101",
               input(7) & input(7) & input(7) & input(7) & input(7) & input(7) & input(7 DOWNTO 6) WHEN "110",
               input(7) & input(7) & input(7) & input(7) & input(7) & input(7) & input(7) & input(7)   WHEN OTHERS;

  WITH amt SELECT
    res_rot <= input WHEN "000",
               input(0) & input(7 DOWNTO 1)          WHEN "001",
               input(1 DOWNTO 0) & input(7 DOWNTO 2) WHEN "010",
               input(2 DOWNTO 0) & input(7 DOWNTO 3) WHEN "011",
               input(3 DOWNTO 0) & input(7 DOWNTO 4) WHEN "100",
               input(4 DOWNTO 0) & input(7 DOWNTO 5) WHEN "101",
               input(5 DOWNTO 0) & input(7 DOWNTO 6) WHEN "110",
               input(6 DOWNTO 0) & input(7)          WHEN OTHERS;

  WITH lar  SELECT
    output <= res_log   WHEN "00",
	      res_arith WHEN "01",
	      res_rot   WHEN OTHERS;
END BarrelShifter_df;
