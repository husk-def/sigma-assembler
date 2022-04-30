
#
# todo: change to work with 32bit
#

up = 
"""
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
"""

mid = String

white = " \t\n"

low = 
"""
--- to here  ---------------------------------------------------------------
    
oQ <= rMEM(to_integer(unsigned(iA)));

end Behavioral;
"""

# open("example/pseudo-data") do data_file
#     print(read(data_file, String))
# end
lines = readlines("example/pseudo-data")

data_file = open("example/data_file.vhd", "w")

write(data_file, up)

cnt = 0



for line in lines
    for word in split(line, " ")            
        if tryparse(Int128, word) !== nothing
            write(data_file, "\tsMEM(" * string(cnt) * ") <= x\"" * string(parse(Int128, word, base=2), pad=8, base=16) * "\"; ")
        elseif occursin(word, white)
            continue
        else
            write(data_file, " -- " * word)
        end
    end
    global cnt += 1
    write(data_file, "\n")
end

write(data_file, low)
