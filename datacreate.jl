
#
# done: change to work with 32bit
#

up_data = 
"""
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity data_ram is
    Port ( iCLK : in  STD_LOGIC;
           iRST : in  STD_LOGIC;
           iA : in  STD_LOGIC_VECTOR (7 downto 0); -- was 5 bits because the memory had 32 places
           iD : in  STD_LOGIC_VECTOR (31 downto 0);
           iWE : in  STD_LOGIC;
           oQ : out  STD_LOGIC_VECTOR (31 downto 0));
end data_ram;

architecture Behavioral of data_ram is

    type tMEM is array(0 to 255) of std_logic_vector(31 downto 0);
    signal rMEM : tMEM;
	 signal sMEM : tMEM := (others => x"00000000");

begin

    process (iCLK, iRST) begin
        if (iRST = '1') then
            for i in 0 to 255 loop
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

low_data = 
"""
--- to here  ---------------------------------------------------------------
    
oQ <= rMEM(to_integer(unsigned(iA)));

end Behavioral;
"""

pseudo = open("example/pseudo-data", "r")

cnt = 0
mid_data = ""
#data part
while (line = readline(pseudo)) != ".prog"
    println(line)
    for word in split(line, " ")            
        if tryparse(Int128, word) !== nothing
            global mid_data = string(mid_data * "\tsMEM(" * string(cnt) * ") \t<= x\"" * string(parse(Int128, word, base=2), pad=8, base=16) * "\"; ")
        elseif occursin(word, white)
            continue
        else
            global mid_data = string(mid_data * " -- " * word)
        end
    end
    global cnt += 1
    global mid_data = string(mid_data * "\n")
end

data_file = open("example/data_file.vhd", "w")
write(data_file, up_data * mid_data * low_data)
close(data_file)

up_prog = 
"""
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;

entity instr_rom is
    Port ( iA : in  STD_LOGIC_VECTOR (7 downto 0);
           oQ : out  STD_LOGIC_VECTOR (31 downto 0));
end instr_rom;

architecture Behavioral of instr_rom is
begin
"""

low_prog =
"""
end Behavioral;
------------------------------------------------------------------
"""

mid_prog = "\toQ <=\n"
cnt = 0
while (line = readline(pseudo)) != ""
    println(line)
    for word in split(line, " ")            
        if tryparse(Int128, word) !== nothing
            global mid_prog = string(mid_prog * "\t\"" * word * "\"\twhen iA(7 downto 2) = " * string(cnt) * " else\t")
        elseif occursin(word, white)
            continue
        else
            global mid_prog = string(mid_prog * " -- " * word)
        end
    end
    global cnt += 1
    global mid_prog = string(mid_prog * "\n")
end

mid_prog = string(mid_prog * "\t\"00000000000000000000000000000000\";\n")

prog_file = open("example/prog_file.vhd", "w")
write(prog_file, up_prog * mid_prog * low_prog)
close(prog_file)
