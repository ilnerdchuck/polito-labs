-- Author: Paolo Camurati
-- File : PriEnc4x2_tb.vhd
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
	COMPONENT PriEnc4x2 IS
	  PORT (req:    IN std_logic_vector(3 DOWNTO 0);
	        active: OUT std_logic;
	        code:   OUT std_logic_vector(1 DOWNTO 0)
	  );
	END COMPONENT;

    SIGNAL req_s: std_logic_vector(3 DOWNTO 0);
	SIGNAL active_s: std_logic;
	SIGNAL code_s: std_logic_vector(1 DOWNTO 0);

BEGIN
	UUT: entity work.PriEnc4x2(PriEnc4x2_df2) PORT MAP (req => req_s, active => active_s, code => code_s);
	
	PROCESS
	BEGIN
	 req_s <= "0000";
	 WAIT FOR 10 ns;
	 req_s <= "0001";
	 WAIT FOR 10 ns;
	 req_s <= "0010";
	 WAIT FOR 10 ns;
	 req_s <= "0011";
	 WAIT FOR 10 ns;
	 req_s <= "0100";
	 WAIT FOR 10 ns;
	 req_s <= "0101";
	 WAIT FOR 10 ns;
	 req_s <= "0110";
	 WAIT FOR 10 ns;
	 req_s <= "0111";
	 WAIT FOR 10 ns;
	 req_s <= "1000";
	 WAIT FOR 10 ns;
	 req_s <= "1001";
	 WAIT FOR 10 ns;
	 req_s <= "1010";
	 WAIT FOR 10 ns;
	 req_s <= "1011";
	 WAIT FOR 10 ns;
	 req_s <= "1100";
	 WAIT FOR 10 ns;
	 req_s <= "1101";
	 WAIT FOR 10 ns;
	 req_s <= "1110";
	 WAIT FOR 10 ns;
	 req_s <= "1111";
	 WAIT;
	END PROCESS;
END TBarch;
