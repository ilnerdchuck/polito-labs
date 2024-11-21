----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10/04/2024 05:06:28 PM
-- Design Name: 
-- Module Name: Mux4X1 - Behavioral
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Mux4X1 is
PORT (  i3, i2, i1, i0 : IN std_logic;
        s1, s0: IN std_logic;
        d: OUT std_logic);
end Mux4X1;

architecture Behavioral of Mux4X1 is
    component Mux2x1 is 
    port(   a1 ,a0: IN std_logic;
            z0: IN std_logic;
            o: IN std_logic);
    end component;
    SIGNAL n1, n2: std_logic;
begin
    M1: Mux2x1 PORT MAP (i1,i0,s0,n1);
    M2: Mux2x1 PORT MAP (i3,i2,s1,n2);
end Behavioral;
