LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY fulladder IS
    PORT (a, b, cin: IN std_logic;
          sum, cout: OUT std_logic);
END fulladder;


ARCHITECTURE Behav OF fulladder IS
BEGIN
   PROCESS(a, b, cin)
   BEGIN
      sum <= (a XOR b) XOR cin;
      cout <= (b AND cin) OR (a AND cin) OR (a AND b);
   END PROCESS;
END Behav;

-- ARCHITECTURE Datafl OF fulladder IS
-- BEGIN
--    sum <= (a XOR b) XOR cin;
--    cout <= (b AND cin) OR (a AND cin) OR (a AND b);
-- END Datafl;

