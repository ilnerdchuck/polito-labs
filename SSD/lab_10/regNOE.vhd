library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
entity regNOE is
  GENERIC (N: integer := 4)
  port (
    i:  IN std_logic_vector (N-1 downto 0);
    q:  OUT std_logic_vector (N-1 downto 0);
    oe, ld, clk, rst: IN std_logic
  );
end entity regNOE;

architecture Beh of regNOE is
  signal reg : std_logic_vector (N-1 downto 0);
begin
  sync_proc: process(clk, rst)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        reg <= (others => '0');
      elsif(ld = '1') then 
        reg <= i;
      end if;
    end if;
  end process sync_proc;
  comb_logic: process(reg, oe)
  begin
    if oe = '1' then
      q <= reg;
    else 
      q <= (others=>'Z')
    end if;
  end process comb_logic; 
end Beh;
