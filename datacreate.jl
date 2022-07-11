import Pkg
using ArgParse

function parse_commandline()
    s = ArgParseSettings()

    @add_arg_table! s begin
        "--full-path"
            help = "specifies that a path is full, not relative"
            action = :store_true
        "path"
            help = "path to a file, by default relative"
            arg_type = String
            required = true
    end

    return parse_args(s)
end

up_data = 
"""
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity data_ram is
    Port (  iCLK :  in  std_logic;
            iRST :  in  std_logic;
            iAdr :  in  std_logic_vector (7 downto 0); -- was 5 bits because the memory had 32 places
            iWD  :  in  std_logic_vector (31 downto 0);
            iWE  :  in  std_logic;
            iOE  :  in  std_logic;
            oRD  :  out  std_logic_vector (31 downto 0));
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
                rMEM(to_integer(unsigned(iAdr(7 downto 2)))) <= iWD;
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

with iOE select oRD <=
    rMEM(to_integer(unsigned(iAdr(7 downto 2))))    when '1',
    x"00000000"                         when others;

end Behavioral;
"""

parsed_args = parse_commandline()
wd = pwd()
fullp = get(parsed_args, "full-path", false)
in_path = (fullp) ? parsed_args["path"] : parsed_args["path"]

println("read from $in_path")

try
    global pseudo = open(in_path, "r")
catch
    if fullp
        println("\tno such file found: $in_path")
    else 
        println("\tno such file found: $wd/$in_path")
    end
    exit(127)
end

cnt = 0
mid_data = ""
#data part
while (line = readline(pseudo)) != ".prog"
    #println(line)
    for word in split(line, " ")            
        if tryparse(Int128, word) !== nothing
            global mid_data = string(mid_data * "\tsMEM(" * string(cnt) * ") \t<= \"" * lpad(word, 32, word[1]) * "\"; ")
            global cnt += 1
        elseif occursin(word, white)
            continue
        else
            global mid_data = string(mid_data * " -- " * word)
        end
    end
    global mid_data = string(mid_data * "\n")
end

data_file = open("example/data_file.vhd", "w")
write(data_file, up_data * mid_data * low_data)
close(data_file)

up_prog = 
"""
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_signed.all;

entity instr_rom is
    Port ( iA : in  std_logic_vector (7 downto 0);
           oQ : out  std_logic_vector (31 downto 0));
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
    #println(line)

    for word in split(line, " ")            
        if tryparse(Int128, word) !== nothing
            if cmp(word[1:6], "011011") == 0
                word = string(word[1:11] * "11111" * word[12:27])
            end
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
