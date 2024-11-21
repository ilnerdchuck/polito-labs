library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Dec3x8 is
  Port (i: IN std_logic_vector(2 DOWNTO 0);
        e: IN std_logic;
        output: OUT std_logic_vector(8 DOWNTO 0)
        );
end Dec3x8;
  

architecture DATAFLOW_SELECT_WHEN of Dec3x8 is
begin
    WITH i & e SELECT
        output <=   "00000001" WHEN "0001", 
                    "00000010" WHEN "0011", 
                    "00000100" WHEN "0101", 
                    "00001000" WHEN "0111", 
                    "00010000" WHEN "1001", 
                    "00100000" WHEN "1011", 
                    "01000000" WHEN "1101", 
                    "10000000" WHEN "1111", 
                    "00000000" WHEN "---0";
end DATAFLOW_SELECT_WHEN;


architecture DATAFLOW_WHEN of Dec3x8 is
begin
        output(0)<= '1' WHEN (i="000" AND e ='1') ELSE 
                    '0' WHEN (((NOT (i="000")) AND e ='1') OR e = '0') ;
        output(1)<= '1' WHEN (i="001" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="001")) AND e ='1') OR e = '0') ;
        output(2)<= '1' WHEN (i="010" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="010")) AND e ='1') OR e = '0') ;
        output(3)<= '1' WHEN (i="011" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="011")) AND e ='1') OR e = '0') ;
        output(4)<= '1' WHEN (i="100" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="100")) AND e ='1') OR e = '0') ;
        output(5)<= '1' WHEN (i="101" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="101")) AND e ='1') OR e = '0') ;
        output(6)<= '1' WHEN (i="110" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="110")) AND e ='1') OR e = '0') ;
        output(7)<= '1' WHEN (i="111" AND e = '0') ELSE 
                    '0' WHEN (((NOT (i="111")) AND e ='1') OR e = '0') ;
end DATAFLOW_WHEN;


architecture BEHAVIOURAL_CASE of Dec3x8 is
begin 
    PROCESS(i,e)
    begin
        CASE i&e IS
                WHEN "0001" => output <= "00000001"; 
                WHEN "0011" => output <= "00000010"; 
                WHEN "0101" => output <= "00000100"; 
                WHEN "0111" => output <= "00001000"; 
                WHEN "1001" => output <= "00010001"; 
                WHEN "1011" => output <= "00100001"; 
                WHEN "1101" => output <= "01000001"; 
                WHEN "1111" => output <= "10000001"; 
                WHEN "---0" => output <= "ZZZZZZZZ";
                WHEN OTHERS => output <= "ZZZZZZZZ";
        END CASE;
     END PROCESS;
end BEHAVIOURAL_CASE;


architecture BEHAVIOURAL_IF_THEN of Dec3x8 is
begin
    PROCESS(i,e)
    begin
        IF e = '1' THEN
            IF i = "000" THEN output <= "00000001"; 
            elsif i = "001" THEN output <= "00000010"; 
            elsif i = "010" THEN output <= "00000100"; 
            elsif i = "011" THEN output <= "00001000"; 
            elsif i = "100" THEN output <= "00010000"; 
            elsif i = "101" THEN output <= "00100000"; 
            elsif i = "110" THEN output <= "01000000"; 
            elsif i = "111" THEN output <= "10000000";
            END IF; 
        ELSE
            output <= "00000000";
        END IF;
        
     END PROCESS;
end BEHAVIOURAL_IF_THEN;

