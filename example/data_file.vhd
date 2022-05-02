library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity data_ram is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iA : in  STD_LOGIC_VECTOR (4 downto 0);
           iD : in  STD_LOGIC_VECTOR (15 downto 0);
           iWE : in  STD_LOGIC;
           oQ : out  STD_LOGIC_VECTOR (15 downto 0));
end data_ram;

architecture Behavioral of data_ram is

    type tMEM is array(0 to 31) of std_logic_vector(15 downto 0);
    signal rMEM : tMEM;
	 signal sMEM : tMEM := (others => x"0000");

begin

    process (iCLK, inRST) begin
        if (inRST = '0') then
            for i in 0 to 31 loop
                rMEM(i) <= sMEM(i); 
            end loop;
        elsif (iCLK'event and iCLK = '1') then
            if (iWE = '1') then
                rMEM(to_integer(unsigned(iA))) <= iD;
            end if;
        end if;
    end process;
-- from here ---------------------------------------------------------------
	sMEM(0) <= x"00000001";  -- _var
	sMEM(1) <= x"00000002";  -- _var2
	sMEM(2) <= x"00000040"; 
	sMEM(3) <= x"ffffffff"; 
	sMEM(4) <= x"00000000"; 
	sMEM(5) <= x"00000000"; 
	sMEM(6) <= x"00000000"; 
	sMEM(7) <= x"00000000"; 
	sMEM(8) <= x"00000000"; 
	sMEM(9) <= x"00000000"; 
	sMEM(10) <= x"00000000"; 
	sMEM(11) <= x"00000000"; 
	sMEM(12) <= x"00000000"; 
--- to here  ---------------------------------------------------------------
    
oQ <= rMEM(to_integer(unsigned(iA)));

end Behavioral;
