library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity manchester is
  port (
    n_res: IN std_logic;
    clk: IN std_logic;
    data: IN std_logic;
    valid: IN std_logic;
    output:  OUT std_logic
  );
end entity manchester;

architecture beh of manchester is
  type STAR_type is (S0,S1,S2,S4,S4);
  signal curr_STAR, next_STAR : STAR_type;

begin

  STAR_proc: process(clk)
  begin
    if rising_edge(clk) then
      if n_rst = 0 then
        curr_STAR <= S0;
        output <= 'Z';
      else
        curr_STAR <= next_STAR;
      end if;
    end if;
  end process STAR_proc;
  
  comb_logic: process(curr_STAR, data, valid)
  begin
    case curr_STAR is
      when S0 =>
        output <= 'Z';
        next_STAR <= S1 when (valid = '1' AND data = '0') else
                     S3 when (valid = '1' AND data = '1') else
                     S0;
      when S1 =>
        output<='0';
        next_STAR <= S2;
      when S2 =>
        output <= '1';
        next_STAR <= S1 when (valid = '1' AND data = '0') else
                     S3 when (valid = '1' AND data = '1') else
                     S0 when (valid = '0'); 
                     -- maybe i can remove the condition
      when S3 =>
        output <= '1';
        next_STAR <= S4;
      when S4 =>
        output <= '0';
        next_STAR <= S1 when (valid = '1' AND data = '0') else
                     S3 when (valid = '1' AND data = '1') else
                     S0 when (valid = '0');
    end case;
  end process comb_logic;
end architecture beh;

architecture beh_opt of manchester is
  type STAR_type is (S0,S1,S2,S4,S4);
  signal curr_STAR, next_STAR : STAR_type;

begin

  STAR_proc: process(clk)
  begin
    if rising_edge(clk) then
      if n_rst = 0 then
        curr_STAR <= S0;
        output <= 'Z';
      else
        curr_STAR <= next_STAR;
      end if;
    end if;
  end process STAR_proc;
  
  comb_logic: process(curr_STAR, data, valid)
  begin
    case curr_STAR is
      when S0 =>
        output <= 'Z';
        next_STAR <= S1 when (valid = '1' AND data = '0') else
                     S3 when (valid = '1' AND data = '1') else
                     S0;
      when S1 =>
        output<='0';
        next_STAR <= S2 when (data = '0' OR (data = '1' and output<='1')) else
                     S0;
      when S2 =>
        output <= '1';
        next_STAR <= S1 when (data = '1' OR (data = '0' and output<='0')) else
                     S0;
    end case;
  end process comb_logic;
end architecture beh_opt;
