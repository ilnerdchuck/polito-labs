library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity FSM_2 is
  port (
    ctr: IN std_logic;
    count: OUT std_logic_vector(3 downto 0);
  end
  );
end entity FSM_2;


architecture beh of FSM_2 is
  type STARTtype is (
    S0,S1,S2,S3
  );

  signal curr_STAR, next_STAR : STARTtype;

begin
  -- D:Posso avere anche un solo process con Mealy 
  -- basta che nella sensitivity list ci sia clk e anche gli input
  -- cosi che quando cambiano gli input aggiorno la rete
  -- D: ma in modello di moore é corretto mettere solo il clock
  -- nella sensitivity list? secondo me si tanto é il produttore
  -- che deve tener conto delle reti che ci sono, inoltre moore
  -- é sensibile solo  ai cambiamenti a ridosso del clock
  STAR: process(clk, _res)
  begin
      if(_res = '0')then
        curr_STAR <= S0;
        -- Ma dal reset e in S0 quanto  deve valere count????
        count <= "0000";
      end if;

    if rising_edge(clk) then
      curr_STAR <= next_STAR;
    end if;
  end process STAR;

  mealy_logic: process(curr_STAR, ctr)
  begin
    case curr_STAR is
      when S0 =>
        if ctr = '1' then
          count <= "0100";
          next_STAR <= S1;
        else
          count <= "0001";
          next_STAR <= S3;
        end if;
        -- aggiungere il mantenimento dello stato

      when S1 =>
          if ctr = '1' then
          count <= "0010";
          next_STAR <= S2;
        else
          count <= "1000";
          next_STAR <= S1;
        end if;

      when S2 =>
        if ctr = '1' then
          count <= "0001";
          next_STAR <= S3;
        else
          count <= "0100";
          next_STAR <= S1;
        end if;

      when S3 =>
        if ctr = '1' then
          count <= "1000";
          next_STAR <= S0;
        else
          count <= "0010";
          next_STAR <= S2;
        end if;

    end case; 
  end process mealy_logic;
  
end architecture beh;
