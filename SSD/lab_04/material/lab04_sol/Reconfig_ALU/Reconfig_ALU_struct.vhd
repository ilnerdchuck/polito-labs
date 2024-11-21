-- Author: Paolo Camurati
-- File : Reconfig_ALU_struct.vhd
-- Design units:
-- entity Reconfig_ALU
-- function: Reconfigurable ALUs on 4  to 16-bit operands 
-- input: A, B (16 bits), ctrl (3 bits), c_in (1 bit),
-- nibble 4 bits)
-- output: result (16 bits), c_out (1 bit)
-- architecture Reconfig_ALU_struct
-- Library/package:ieee.std_logic_ll64: to use std-logic
-- Synthesis and verification (optional):
-- Synthesis software: . . .
-- Options/script: . . .
-- Target technology: . . .
-- Testbench: Reconfig_ALU_tb.vhd 
-- Revision history
-- Version 2.0
-- Date: 20200324
-- Comments:

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

ENTITY Reconfig_ALU IS
  PORT(A:      IN std_logic_vector(15 DOWNTO 0);
       B:      IN std_logic_vector(15 DOWNTO 0);
       ctrl:   IN std_logic_vector(2 DOWNTO 0);
       c_in:   IN std_logic;
       nibble: IN std_logic_vector(3 DOWNTO 0);
       c_out:  OUT std_logic;
       result: OUT std_logic_vector(15 DOWNTO 0));
END Reconfig_ALU;


ARCHITECTURE Reconfig_ALU_struct OF Reconfig_ALU IS

  COMPONENT ALU_N_carry_en IS
    GENERIC (N: integer := 16);
    PORT (src0,src1: IN  std_logic_vector (N-1 DOWNTO 0);
          ctrl:      IN  std_logic_vector (2 DOWNTO 0);
          c_in:      IN std_logic;
          en:        IN std_logic;
          c_out:     OUT std_logic;     
          result:    OUT std_logic_vector (N-1 DOWNTO 0));
    END COMPONENT;

SIGNAL c_out0, c_out1, c_out2: std_logic;

BEGIN
  ALU0: ALU_N_carry_en GENERIC MAP (N => 4)
                       PORT MAP(src0 => A(3 DOWNTO 0),
                                src1 => B(3 DOWNTO 0),
                                ctrl => ctrl,
                                c_in => c_in,
                                en   => nibble(0),
                                c_out => c_out0,
                                result => result(3 DOWNTO 0));

  ALU1: ALU_N_carry_en GENERIC MAP (N => 4)
                       PORT MAP(src0 => A(7 DOWNTO 4),
                                src1 => B(7 DOWNTO 4),
                                ctrl => ctrl,
                                c_in => c_out0,
                                en   => nibble(1),
                                c_out => c_out1,
                                result => result(7 DOWNTO 4));

  ALU2: ALU_N_carry_en GENERIC MAP (N => 4)
                       PORT MAP(src0 => A(11 DOWNTO 8),
                                src1 => B(11 DOWNTO 8),
                                ctrl => ctrl,
                                c_in => c_out1,
                                en   => nibble(2),
                                c_out => c_out2,
                                result => result(11 DOWNTO 8));

  ALU3: ALU_N_carry_en GENERIC MAP (N => 4)
                       PORT MAP(src0 => A(15 DOWNTO 12),
                                src1 => B(15 DOWNTO 12),
                                ctrl => ctrl,
                                c_in => c_out2,
                                en   => nibble(3),
                                c_out => c_out,
                                result => result(15 DOWNTO 12));

END Reconfig_ALU_struct;
