-- Author: Paolo Camurati
-- File : barrelshifter_df_opt.vhd
-- Design units:
-- entity barrel
-- function: programmable barrel shifter 
-- input: lar (2 bits), amt (3 bits)
-- output: output (8 bits)
-- architecture BarrelShifter_df_opt
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: barrelshifter_tb.vhd
-- Revision history
-- Version 2.0
-- Date: 20200405
-- Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY BarrelShifter IS
  PORT (input:  IN std_logic_vector(7 DOWNTO 0);
        lar:    IN std_logic_vector(1 DOWNTO 0);
        amt:    IN std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic_vector(7 DOWNTO 0));
END BarrelShifter;

ARCHITECTURE BarrelShifter_df_opt OF BarrelShifter IS
  SIGNAL shift_in: std_logic_vector(7 DOWNTO 0);
BEGIN
  WITH lar SELECT
    shift_in <= (OTHERS =>'0')       WHEN "00",
                (OTHERS => input(7)) WHEN "01",
                 input               WHEN OTHERS;

  WITH amt SELECT
    output <= input                                    WHEN "000",
              shift_in(0)          & input(7 DOWNTO 1) WHEN "001",
              shift_in(1 DOWNTO 0) & input(7 DOWNTO 2) WHEN "010",
              shift_in(2 DOWNTO 0) & input(7 DOWNTO 3) WHEN "011",
              shift_in(3 DOWNTO 0) & input(7 DOWNTO 4) WHEN "100",
              shift_in(4 DOWNTO 0) & input(7 DOWNTO 5) WHEN "101",
              shift_in(5 DOWNTO 0) & input(7 DOWNTO 6) WHEN "110",
              shift_in(6 DOWNTO 0) & input(7)          WHEN OTHERS;
END BarrelShifter_df_opt;
