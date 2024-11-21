library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ex1 is
  port (
    X: IN std_logic_vector(6 downto 0);
    Z: OUT std_logic_vector(2 downto 0)
  );
end entity ex1;

architecture comb of ex1 is
  
begin
  comb_rete: process
  begin
    if X = "0000000" then
      Z <= "000";      
    elsif (X = "0000001") then
      Z <= "001";      
    elsif (X = "0000011") then
      Z <= "010";      
    elsif (X = "0000111") then
      Z <= "011";      
    elsif (X = "0001111") then
      Z <= "100";      
    elsif (X = "0011111") then
      Z <= "101";      
    elsif (X = "0111111") then
      Z <= "110";      
    elsif (X = "1111111") then
      Z <= "111";      
    end if; 
  end process comb_rete;
end architecture comb;

architecture comb2 of ex1 is
  
begin
  comb2_rete: process
  begin
    case X is
      when "0000000" => 
        Z<="000";
      when "0000001" => 
        Z<="001";
      when "0000011" => 
        Z<="010";
      when "0000111" => 
        Z<="011";
      when "0001111" => 
        Z<="100";
      when "0011111" => 
        Z<="101";
      when "0111111" => 
        Z<="110";
      when "1111111" => 
        Z<="111";
      when others =>
        Z<="ZZZ";
    end case;
  end process comb2_rete;
end architecture comb2;
