library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity pulse_generator is
  port (
    res: std_logic;
    clk: std_logic;
    go: std_logic;
    stop: std_logic;
    pulse: std_logic
  );
end entity pulse_generator; 


architecture beh of pulse_generator is
  type STAR_type is (
    S0,S1,S2  
  );
begin
  STAR_logic: process(clk)
  begin
    if rising_edge(clk) then
      if rst = '0' then
        curr_STAR <= S0;

      else
        
      end if;
    end if;
  end process STAR_logic;  
end architecture beh;
