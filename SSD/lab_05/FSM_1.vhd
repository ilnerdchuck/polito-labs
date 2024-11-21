LIBRARY library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity FSM_1 is
  port (
      p: IN std_logic;
      r: OUT std_logic;
      clk, res: IN std_logic;
    );
end entity FSM_1;

architecture beh of FSM_1 is
  type StateType is (
      S0,S1,S2,S3
  );
  signal curr_STAR, nex_STAR: StateType;

begin 
  state_reg: process (clk, _res)
  begin 
    if (rising_edge(clk)) then
      if (res = '1') then
        curr_STAR <=S0;
      else
        curr_STAR <= nex_STAR;
      end if;
    end if;
  end process state_reg;
  
  logic: process(curr_STAR, p)
  begin
    case curr_STAR is
      when S0 =>
          r <= '0';
          if (p = '1') then 
            nex_STAR <= S1;
          else
            nex_STAR <= curr_STAR;
          end if;

      when S1 =>
          r <= '0';
          if (p = '1') then 
            nex_STAR <= S2;
          else
            nex_STAR <= curr_STAR;
          end if;

      when S2 =>
          r <= '0';
          if (p = '1') then 
            nex_STAR <= S3;
          else
            nex_STAR <= curr_STAR;
          end if;

      when S3 =>
          r <= '1';
          if (p = '0') then 
            nex_STAR <= S0;
          else if (p = '1')
            nex_STAR <= S1;
          else
            nex_STAR <= curr_STAR;
          end if;
      when others =>
        r <='Z'; 
    end case;
  end process logic;
end architecture beh;
