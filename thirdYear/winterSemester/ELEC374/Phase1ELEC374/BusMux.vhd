LIBRARY ieee;
USE ieee.std_logic_1164.all;


--  Entity Declaration

ENTITY BusMux IS
-- {{ALTERA_IO_BEGIN}} DO NOT REMOVE THIS LINE!
PORT
(
S : IN STD_LOGIC_VECTOR(4 downto 0);
-- Register Inputs
R0_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R1_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R2_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R3_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R4_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R5_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R6_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R7_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R8_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R9_BusMuxIn  : IN STD_LOGIC_VECTOR(31 downto 0);
R10_BusMuxIn : IN STD_LOGIC_VECTOR(31 downto 0);
R11_BusMuxIn : IN STD_LOGIC_VECTOR(31 downto 0);
R12_BusMuxIn : IN STD_LOGIC_VECTOR(31 downto 0);
R13_BusMuxIn : IN STD_LOGIC_VECTOR(31 downto 0);
R14_BusMuxIn : IN STD_LOGIC_VECTOR(31 downto 0);
R15_BusMuxIn : IN STD_LOGIC_VECTOR(31 downto 0);

-- Other register Inputs
BusMuxIn_HI    : IN STD_LOGIC_VECTOR(31 downto 0);
BusMuxIn_LO    : IN STD_LOGIC_VECTOR(31 downto 0);
BusMuxIn_Zhigh : IN STD_LOGIC_VECTOR(31 downto 0);
BusMuxIn_Zlow  : IN STD_LOGIC_VECTOR(31 downto 0);
BusMuxIn_MDR   : IN STD_LOGIC_VECTOR(31 downto 0);
--Program Counter Input
BusMuxIn_PC       : IN STD_LOGIC_VECTOR(31 downto 0);
--???
BusMuxIn_In_Port  : IN STD_LOGIC_VECTOR(31 downto 0);

-- Output Port (What will go on the Bus)
BusMuxOut  : OUT STD_LOGIC_VECTOR(31 downto 0)
);
-- {{ALTERA_IO_END}} DO NOT REMOVE THIS LINE!

END BusMux;

architecture BusMux_architecture of BusMux is
begin
    process(
				R0_BusMuxIn,
				R1_BusMuxIn,
				R2_BusMuxIn,
				R3_BusMuxIn,
				R4_BusMuxIn,
				R5_BusMuxIn,
				R6_BusMuxIn,
				R7_BusMuxIn,
				R8_BusMuxIn,
				R9_BusMuxIn,
				R10_BusMuxIn,
				R11_BusMuxIn,
				R12_BusMuxIn,
				R13_BusMuxIn,
				R14_BusMuxIn,
				R15_BusMuxIn,
				BusMuxIn_HI ,  
				BusMuxIn_LO ,  
				BusMuxIn_Zhigh,
				BusMuxIn_Zlow ,
				BusMuxIn_PC ,
				BusMuxIn_In_Port,
				BusMuxIn_MDR )
    begin
			case S is
				 when "00000"  => BusMuxOut <= R0_BusMuxIn;
				 when "00001"  => BusMuxOut <= R1_BusMuxIn;
				 when "00010"  => BusMuxOut <= R2_BusMuxIn;
				 when "00011"  => BusMuxOut <= R3_BusMuxIn;
				 when "00100"  => BusMuxOut <= R4_BusMuxIn;
				 when "00101"  => BusMuxOut <= R5_BusMuxIn;
				 when "00110"  => BusMuxOut <= R6_BusMuxIn;
				 when "00111"  => BusMuxOut <= R7_BusMuxIn;
				 when "01000"  => BusMuxOut <= R8_BusMuxIn;
				 when "01001"  => BusMuxOut <= R9_BusMuxIn;
				 when "01010"  => BusMuxOut <= R10_BusMuxIn;
				 when "01011"  => BusMuxOut <= R11_BusMuxIn;
				 when "01100"  => BusMuxOut <= R12_BusMuxIn;
				 when "01101"  => BusMuxOut <= R13_BusMuxIn;
				 when "01110"  => BusMuxOut <= R14_BusMuxIn;
				 when "01111"  => BusMuxOut <= R15_BusMuxIn;
				 when "10000"  => BusMuxOut <= BusMuxIn_HI;
				 when "10001"  => BusMuxOut <= BusMuxIn_LO;
				 when "10010"  => BusMuxOut <= BusMuxIn_Zhigh;
				 when "10011"  => BusMuxOut <= BusMuxIn_Zlow;
				 when "10100"  => BusMuxOut <= BusMuxIn_PC;
				 when "10101"  => BusMuxOut <= BusMuxIn_MDR;
				 when "10110"  => BusMuxOut <= BusMuxIn_In_Port;
				 when others => BusMuxOut <= "XXXXX";
			end case;
    end process;
end architecture;