library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ring_counter is
  port (
    clk, _rst: IN std_logic;
    o: OUT std_logic_vector(3 downto 0)
  );
end entity ring_counter;

architecture beh of ring_counter is
  
  -- CORRECT AND MAKE FOR N cosi

  signal STAR : std_logic_vector(3 downto 0);
begin
 proc_name: process(clk)
 begin
  if rising_edge(clk) then
    if _rst = '0' then
      STAR <= "1101";
    else
      if(STAR(3 downto 1) = "000") then
        STAR <= '1' & STAR(0) & STAR(1)& STAR(2);
      else
        STAR <= '0' & STAR(0) & STAR(1)& STAR(2);
      end if;
    end if;
  end if;
 end process proc_name; 
 o <= STAR;
end architecture beh;


