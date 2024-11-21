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
  signal STAR: StateType;

begin 
  FSM: process(clk)
  begin
    if rising_edge(clk) then
      if rst = '0' then
        STAR <= S0;
        r <= '0';
      else  
        case STAR is
          when S0 =>
            r <= '0' 
            if p = '1' then
              STAR <= S1;
            else
              STAR <= STAR;
            end if;
          
          when S1 =>
            r <= '0' 
            if p = '1' then
              STAR <= S2;
            else
              STAR <= STAR;
            end if;
          
          when S2 =>
            r <= '0' 
            if p = '1' then
              STAR <= S3;
            else
              STAR <= STAR;
            end if;
          
          when S3 =>
            r <= '1' 
            if p = '1' then
              STAR <= S0;
            else
              STAR <= S1;
            end if;

          when others =>
            r <= 'Z';
            STAR <= STAR;

        end case;
      end if;
    end if;
  end process FSM;
end architecture beh;
