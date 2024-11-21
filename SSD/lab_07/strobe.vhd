library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity strobe is
  port (
    rst: IN std_logic;
    clk: IN std_logic;
    s: IN std_logic;
    output: OUT std_logic;
  );
end entity strobe;

architecture mealy of strobe is   
  type StateType is (
      S0,S1
  );
  signal curr_STAR, nex_STAR: StateType;

begin
  FSM_update: process(clk, rst)
  begin
    if rst = '0' then
      curr_STAR<= S0;
      output<= '0';
    elsif rising_edge(clk) then
      curr_STAR<=nex_STAR;
    end if;
  end process ;
    
  FSM_comb: process(curr_STAR,s)
  begin
    case curr_STAR is
      when S0 =>   
         if(rising_edge(s))then
           output<='1';
           nex_STAR<= S1;
         else
           output<='0';
           nex_STAR<= S0;
         end if;
      when S1 =>
          output<='1';
          nex_STAR<=S0;
    end case;
  end process FSM_comb;
end architecture mealy;

architecture moore of strobe is   
  type StateType is (
      S0,S1
  );
  signal curr_STAR, nex_STAR: StateType;

begin
  FSM_update: process(clk, rst)
  begin
    if rst = '0' then
      curr_STAR<= S0;
      output<= '0';
    elsif rising_edge(clk) then
      curr_STAR<=nex_STAR;
    end if;
  end process ;
    
  FSM_comb: process(curr_STAR,s)
  begin
    case curr_STAR is
      when S0 =>   
         if(rising_edge(s))then
           nex_STAR<= S1;
         else
           output<='0';
           nex_STAR<= S0;
         end if;
      when S1 =>
          output<='1';
          nex_STAR<=S0;
    end case;
  end process FSM_comb;
end architecture moore;


