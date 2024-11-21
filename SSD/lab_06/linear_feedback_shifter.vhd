library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ring_counter is
  port (
    clk, _res: IN std_logic;
    o: OUT std_logic
  );
end entity ring_counter;

architecture beh of ring_counter is
  
  signal STAR : std_logic_vector;
begin
 proc_name: process(clk)
 begin
  if rising_edge(clk) then
    if rst = '0' then
      STAR <= "1000";
    elsif (e = '1') then
      STAR <= (STAR(3) XOR STAR(2)) & STAR(0) & STAR(1) & STAR(2);
    OTHERS => STAR <= STAR;  
    end if;
  end if;
  end process proc_name; 
 o <= STAR;
end architecture beh;


