LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY Testbench IS
END Testbench;

ARCHITECTURE TBarch OF Testbench IS

   COMPONENT fulladder IS
       PORT (a, b, cin: IN std_logic;
             sum, cout: OUT std_logic);
   END COMPONENT;

   SIGNAL a_s, b_s, cin_s, sum_s, cout_s: std_logic;

BEGIN
   CompToTest: fulladder PORT MAP (a_s, b_s, cin_s, sum_s, cout_s);

   PROCESS
   BEGIN
      -- Test all possible input  combinations
      a_s <= '0'; b_s <= '0'; cin_s <= '0';      
      WAIT FOR 10 ns;
      
      a_s <= '0'; b_s <= '0'; cin_s <= '1';      
      WAIT FOR 10 ns;
      
      a_s <= '0'; b_s <= '1'; cin_s <= '0';      
      WAIT FOR 10 ns;
      
      a_s <= '0'; b_s <= '1'; cin_s <= '1';      
      WAIT FOR 10 ns;
      
      a_s <= '1'; b_s <= '0'; cin_s <= '0';      
      WAIT FOR 10 ns;
      
      a_s <= '1'; b_s <= '0'; cin_s <= '1';      
      WAIT FOR 10 ns;
      
      a_s <= '1'; b_s <= '1'; cin_s <= '0';      
      WAIT FOR 10 ns;
      
      a_s <= '1'; b_s <= '1'; cin_s <= '1';      
      WAIT;
   END PROCESS;
END TBarch;