library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity arbiter is
  port (
    rst: IN std_logic;
    clk: IN std_logic;
    r0: IN std_logic;
    r1: IN std_logic;
    g0: OUT std_logic;
    g1: OUT std_logic;
  );
end entity arbiter;


architecture fixed of arbiter is
  type StateType is (
      S0,S1,S2
  );
  signal curr_STAR, nex_STAR: StateType;
begin
  FSM_star: process(clk, rst)
  begin
    if rst = '0' then
      curr_STAR<=S0;
      g1<='0';
      g2<='0';
    elsif rising_edge(clk) then
      curr_STAR<=nex_STAR;
    end if;
  end process FSM_star;
  
  FSM_comb: process(curr_STAR,r0,r1)
  begin
    case curr_STAR is
      when S0 =>
        g0<='0';
        g1<='0';
        if (r1 = '1') then
          nex_STAR<=S1;
          g1<='1';
        elsif (NOT(r1) AND r0 = '1') then
          nex_STAR<=S2;
          g0<='1';
        end if;
      when S1 =>
        g1<='1';
        g0<='0';
        if (r1 = '0') then
          nex_STAR<=S0;
          g1<='0';
        end if;
      when S2 =>
        g1<='0';
        g0<='1';
        if (r0 = '0') then
          nex_STAR<=S0;
          g0<='0';
        end if;
    end case;
  end process FSM_comb; 
end architecture fixed;


architecture stored of arbiter is
  type StateType is (
      S0,S1,S2
  );
  signal curr_STAR, nex_STAR: StateType;
  signal prev_system : std_logic;
begin
  FSM_star: process(clk, rst)
  begin
    if rst = '0' then
      curr_STAR<=S0;
      g1<='0';
      g2<='0';
      prev_system<='0';
    elsif rising_edge(clk) then
      curr_STAR<=nex_STAR;
    end if;
  end process FSM_star;
  
  FSM_comb: process(curr_STAR,r0,r1)
  begin
    case curr_STAR is
      when S0 =>
        g0<='0';
        g1<='0';
        if (r1 = '1' AND NOT(prev_system)) then
          nex_STAR<=S1;
          g1<='1';
        elsif (r0 = '1' AND prev_system) then
          nex_STAR<=S2;
          g0<='1';
        end if;
      when S1 =>
        g1<='1';
        g0<='0';
        prev_system<='1';
        if (r1 = '0') then
          nex_STAR<=S0;
          g1<='0';
        end if;
      when S2 =>
        g1<='0';
        g0<='1';
        prev_system<='0';
        if (r0 = '0') then
          nex_STAR<=S0;
          g0<='0';
        end if;
    end case;
  end process FSM_comb; 
end architecture stored;
