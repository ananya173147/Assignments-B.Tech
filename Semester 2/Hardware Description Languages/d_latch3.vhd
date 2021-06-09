library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity d_latch_3 is
port(
clk: in std_logic;
nreset: in std_logic;
enable: in std_logic_vector (1 downto 0);
d : in std_logic_vector (3 downto 0);
q_odd: out std_logic_vector(3 downto 0);
q_even: out std_logic_vector(3 downto 0)
);
end entity d_latch_3;

architecture d_arch3 of d_latch_3 is
begin
process (nreset, clk) is
begin
   if (nreset = '0') then
      q_odd <= (others=>'0');
      q_even <= (others=>'0');
      
   elsif (rising_edge(clk)) then
      if (enable = "01") then
         q_odd <= d;
      elsif (enable = "10") then 
         q_even <= d;
      end if;
      
   end if;
end process;
end d_arch3;
