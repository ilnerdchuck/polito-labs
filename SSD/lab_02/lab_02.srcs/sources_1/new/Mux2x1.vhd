----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10/04/2024 04:30:13 PM
-- Design Name: 
-- Module Name: Mux2x1 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY Mux2x1 IS
PORT (  i1, i0: IN std_logic;
        s0: IN std_logic;
        d: OUT std_logic);
END Mux2x1;


architecture Behavioral of Mux2x1 is
    
begin
    d <= (i1 AND (s0)) OR (i0 AND (NOT s0)); 
end Behavioral;
