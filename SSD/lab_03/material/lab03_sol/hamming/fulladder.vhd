LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY fulladder  IS
  PORT (data1, data2: IN std_logic_vector(0 DOWNTO 0);
        sum: OUT std_logic_vector(1 DOWNTO 0));
END fulladder;

ARCHITECTURE fulladder_struct OF fulladder IS
  COMPONENT AddN IS
    GENERIC (N: integer := 4);
    PORT (A,B: IN  std_logic_vector (N-1 DOWNTO 0);
          S:   OUT std_logic_vector (N DOWNTO 0));
  END COMPONENT;

BEGIN
  comp: AddN GENERIC MAP (1) PORT MAP (A=>data1, B=>data2, S=>sum);

END fulladder_struct;
