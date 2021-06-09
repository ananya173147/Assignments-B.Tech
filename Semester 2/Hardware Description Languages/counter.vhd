library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;
entity counter8 is
--generic ( n : natural := 4);
port(
clk : in std_logic;
nreset : in std_logic;
nready : in std_logic;
count : out std_logic_vector (2 downto 0)
);
end counter8;
architecture counter8_arch of counter8 is
signal temp : unsigned (2 downto 0);
constant MAXCOUNT : unsigned (2 downto 0) := "111";
begin
p0: process (nreset, clk) is
--signal temp : unsigned (3 downto 0);
begin
if (nreset = '0') then
temp <= (others => '0');
--count <= (others => '0');
elsif (rising_edge(clk)) then
   if (nready = '1') then
   temp <= (others => '0');
   elsif (temp = MAXCOUNT) then
   temp <= (others => '0');
   else
   temp <= temp + 1;
   end if;
end if;
--count <= std_logic_vector(temp);
end process p0;
count <= std_logic_vector(temp);
end counter8_arch;
