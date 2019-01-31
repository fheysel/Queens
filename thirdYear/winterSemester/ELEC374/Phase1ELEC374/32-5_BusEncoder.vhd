library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity encoder is
 port(
	a : in STD_LOGIC_VECTOR(23 downto 0);
	BusMuxOut : out STD_LOGIC_VECTOR(4 downto 0);
 
	-- Register Inputs
	R0_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R1_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R2_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R3_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R4_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R5_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R6_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R7_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R8_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R9_BusMuxOut  : IN STD_LOGIC_VECTOR(31 downto 0);
	R10_BusMuxOut : IN STD_LOGIC_VECTOR(31 downto 0);
	R11_BusMuxOut : IN STD_LOGIC_VECTOR(31 downto 0);
	R12_BusMuxOut : IN STD_LOGIC_VECTOR(31 downto 0);
	R13_BusMuxOut : IN STD_LOGIC_VECTOR(31 downto 0);
	R14_BusMuxOut : IN STD_LOGIC_VECTOR(31 downto 0);
	R15_BusMuxOut : IN STD_LOGIC_VECTOR(31 downto 0);
	
	HIout         : IN STD_LOGIC_VECTOR(31 downto 0);
	LOout         : IN STD_LOGIC_VECTOR(31 downto 0);
	Zhighout      : IN STD_LOGIC_VECTOR(31 downto 0);
	Zlowout       : IN STD_LOGIC_VECTOR(31 downto 0);
	PCout         : IN STD_LOGIC_VECTOR(31 downto 0);
	MDRout        : IN STD_LOGIC_VECTOR(31 downto 0);
	In_Portout    : IN STD_LOGIC_VECTOR(31 downto 0);
	Cout          : IN STD_LOGIC_VECTOR(31 downto 0)
 );
end encoder;

architecture bhv of encoder is
begin

process(a,
				R0_BusMuxOut ,
				R1_BusMuxOut ,
				R2_BusMuxOut ,
				R3_BusMuxOut ,
				R4_BusMuxOut ,
				R5_BusMuxOut ,
				R6_BusMuxOut ,
				R7_BusMuxOut ,
				R8_BusMuxOut ,
				R9_BusMuxOut ,
				R10_BusMuxOut,
				R11_BusMuxOut,
				R12_BusMuxOut,
				R13_BusMuxOut,
				R14_BusMuxOut,
				R15_BusMuxOut,
				HIout,   
				LOout,     
				Zhighout,  
				Zlowout,   
				PCout,     
				MDRout,    
				In_Portout)
				    
begin
 case a is
	 when R0_BusMuxOut => BusMuxOut <= "00000";
	 when R1_BusMuxOut    => BusMuxOut <= "00001";
	 when R2_BusMuxOut    => BusMuxOut <= "00010";
	 when R3_BusMuxOut    => BusMuxOut <= "00011";
	 when R4_BusMuxOut    => BusMuxOut <= "00100";
	 when R5_BusMuxOut    => BusMuxOut <= "00101";
	 when R6_BusMuxOut    => BusMuxOut <= "00110";
	 when R7_BusMuxOut    => BusMuxOut <= "00111";
	 when R8_BusMuxOut    => BusMuxOut <= "01000";
	 when R9_BusMuxOut    => BusMuxOut <= "01001";
	 when R10_BusMuxOut   => BusMuxOut <= "01010";
	 when R11_BusMuxOut   => BusMuxOut <= "01011";
	 when R12_BusMuxOut   => BusMuxOut <= "01100";
	 when R13_BusMuxOut   => BusMuxOut <= "01101";
	 when R14_BusMuxOut   => BusMuxOut <= "01110";
	 when R15_BusMuxOut   => BusMuxOut <= "01111";
	 when HIout           => BusMuxOut <= "10000";
	 when LOout           => BusMuxOut <= "10001";
	 when Zhighout        => BusMuxOut <= "10010";
	 when Zlowout         => BusMuxOut <= "10011";
	 when PCout           => BusMuxOut <= "10100";
	 when MDRout          => BusMuxOut <= "10101";    
	 when In_Portout      => BusMuxOut <= "10110";
	 when others => BusMuxOut <= "XXXXX";
	 
 end case;
end process;

end bhv;