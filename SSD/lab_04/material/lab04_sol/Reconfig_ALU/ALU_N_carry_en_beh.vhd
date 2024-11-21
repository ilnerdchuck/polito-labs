-- Author: Paolo Camurati
-- File : ALU_N_carry_en_beh.vhd
-- Design units:
-- entity generic ALU_N_carry_en 
-- function: generic ALU on N bits with c_in, c_out and enable 
-- input: src0, src1 (N bits), ctrl (3 bits), 
-- c_in (1 bit), en (1 bit)
-- output: result (N bits), c_out (1 bit)
-- architecture ALU_N_carry_en_beh
-- Library/package:ieee.std_logic_ll64, ieee.numeric_std: to
-- use std-logic and numeric
-- Synthesis and verification (optional):
-- Synthesis software: . . .
--  Options/script: . . .
--  Target technology: . . .
--  Testbench: ALU_N_carry_en_tb.vhd
--  Revision history
--  Version 1.0
--  Date: 20170606
--  Comments:

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY ALU_N_carry_en IS
  GENERIC (N: integer := 4);
  PORT (src0,src1: IN  std_logic_vector (N-1 DOWNTO 0);
        ctrl:      IN  std_logic_vector (2 DOWNTO 0);
        c_in:      IN std_logic;
        en:        IN std_logic;
        c_out:     OUT std_logic;     
        result:    OUT std_logic_vector (N-1 DOWNTO 0));
END ALU_N_carry_en;

ARCHITECTURE ALU_N_carry_en_beh OF ALU_N_carry_en IS
BEGIN
  PROCESS(src0, src1, ctrl, c_in, en)
    VARIABLE tmp: signed(N DOWNTO 0);
  BEGIN
    IF (en = '1') THEN
      CASE ctrl IS
        WHEN "100" =>
          tmp := signed('0'&src0) + signed('0'&src1) + ('0'&c_in);
          result <= std_logic_vector(tmp(N-1 DOWNTO 0));
          c_out <= tmp(N);
        WHEN "101" =>
          tmp := signed('0'&src0) - signed('0'&src1) - ('0'&c_in);
          result <= std_logic_vector(tmp(N-1 DOWNTO 0));
          c_out <= tmp(N);
        WHEN "110" =>
          result <= src0 AND src1;
          c_out <= '0';
        WHEN "111" =>
          result <= src0 OR src1;
          c_out <= '0';
        WHEN OTHERS =>
          tmp := signed('0'&src0) + 1 + ('0'&c_in);
          result <= std_logic_vector(tmp(N-1 DOWNTO 0));
          c_out <= tmp(N);
      END CASE;
    ELSE
      result <= (OTHERS => '0');
      c_out <= '0';
    END IF;
  END PROCESS;
END ALU_N_carry_en_beh;

