library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity reg_file_N is
  generic (regSize: std_logic := 10)
  port (
    addr: in ()
  );
end entity reg_file_N;

architecture struct of reg_file_N is
  
begin
  
  for regSize in range loop
    
  end loop;


  -- devi fare un for per dichiarare M registri e poi N lo usi per la dimensione
  -- in modo tale da avere una memoria da 2^MxN con M di indirizzamento e N 
  -- dimensione di registro 
  -- TODO: guarda sti for per generare il codice
  
  
end architecture struct;
