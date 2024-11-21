----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 30.09.2019 13:56:17
-- Design Name: 
-- Module Name: myfulladder_tb - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity myfulladder_tb is
--  Port ( );
end myfulladder_tb;

architecture Behavioral of myfulladder_tb is
    COMPONENT myfulladder
    PORT(
         a : IN  std_logic;
         b : IN  std_logic;
         cin : IN  std_logic;
         sum : OUT  std_logic;
         cout : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal a : std_logic := '0';
   signal b : std_logic := '0';
   signal cin : std_logic := '0';

  --Outputs
   signal sum : std_logic;
   signal cout : std_logic;
begin
    -- Instantiate the Unit Under Test (UUT)
   uut: myfulladder PORT MAP (
          a => a,
          b => b,
          cin => cin,
          sum => sum,
          cout => cout
        );

   stim_proc: process
   begin    
      -- Test all possible input  combinations
      a <= '0'; b <= '0'; cin <= '0';      
      WAIT FOR 10 ns;
      
      a <= '0'; b <= '0'; cin <= '1';      
      WAIT FOR 10 ns;
      
      a <= '0'; b <= '1'; cin <= '0';      
      WAIT FOR 10 ns;
      
      a <= '0'; b <= '1'; cin <= '1';      
      WAIT FOR 10 ns;
      
      a <= '1'; b <= '0'; cin <= '0';      
      WAIT FOR 10 ns;
      
      a <= '1'; b <= '0'; cin <= '1';      
      WAIT FOR 10 ns;
      
      a <= '1'; b <= '1'; cin <= '0';      
      WAIT FOR 10 ns;
      
      a <= '1'; b <= '1'; cin <= '1';      
      WAIT;
   end process;
end Behavioral;
