
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity M8x1 is
  Port (i: IN std_logic_vector(7 DOWNTO 0);
        s: IN std_logic_vector(2 DOWNTO 0);
        output: OUT std_logic
        );
end M8x1;

-- DATAFLOW with WHEN ELSE
architecture DATAFLOW_WHEN of M8x1 is    
begin
    output <=   i(0) WHEN s="000" ELSE
                i(1) WHEN s="001" ELSE
                i(2) WHEN s="010" ELSE
                i(3) WHEN s="011" ELSE
                i(4) WHEN s="100" ELSE
                i(5) WHEN s="101" ELSE
                i(6) WHEN s="110" ELSE
                i(7) WHEN s="111";
end DATAFLOW_WHEN;

-- DATAFLOW with WITH SELECT WHEN 

architecture DATAFLOW_SELECT_WHEN of M8x1 is
    
begin
    WITH {s,e} SELECT
    output <=   i(0) WHEN "00";
                i(1) WHEN s="001" ELSE
                i(2) WHEN s="010" ELSE
                i(3) WHEN s="011" ELSE
                i(4) WHEN s="100" ELSE
                i(5) WHEN s="101" ELSE
                i(6) WHEN s="110" ELSE
                i(7) WHEN s="111";
end DATAFLOW_SELECT_WHEN;


-- how can i group multiple signalss like in verilog with {s,e}??
-- Behavioral Always with a process with a sensitivity list
architecture BEHAVIORAL of M8x1 is
begin
    output <=   i(0) WHEN s="000" ELSE
                i(1) WHEN s="001" ELSE
                i(2) WHEN s="010" ELSE
                i(3) WHEN s="011" ELSE
                i(4) WHEN s="100" ELSE
                i(5) WHEN s="101" ELSE
                i(6) WHEN s="110" ELSE
                i(7) WHEN s="111";
end DATAFLOW_SELECT_WHEN;








