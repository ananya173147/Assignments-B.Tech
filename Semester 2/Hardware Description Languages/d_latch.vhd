library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity d_latch is
port(
clk: in std_logic;
nreset: in std_logic;
enable: in std_logic;
d : in std_logic_vector (3 downto 0);
q: out std_logic_vector(3 downto 0)
);
end entity d_latch;

architecture d_arch of d_latch is
begin
process (nreset, clk) is
begin
if (nreset = '0') then
q <= (others=>'0');
elsif (rising_edge(clk)) then
if (enable = '1') then
q<= d;
end if;
end if;
end process;
end d_arch;