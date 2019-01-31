LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

entity mux is port
( in1	:in std_logic_vector(31 downto 0);
  in2	:in std_logic_vector(31 downto 0);
  cs:in std_logic;
  output :OUT std_logic_vector(31 downto 0)
);
END mux;

ARCHITECTURE description OF mux IS

BEGIN
    process(in1, in2, cs)
    begin
        if cs = '0' then
            output <= in1;
        elsif cs = '1' then
            output <= in2;
        end if;
    end process;
END description;