library ieee;
use ieee.std_logic_1164.all;

entity tb2_prob2 is end tb2_prob2;

architecture test2_2 of tb2_prob2 is
component main_2
port(d: in std_logic_vector(3 downto 0);
clk,nreset,nready: in std_logic;
q:out std_logic_vector(3 downto 0));
end component;

signal clk : std_logic := '1';
signal nreset : std_logic := '1';
signal nready : std_logic;
signal d: std_logic_vector(3 downto 0) := (others=>'0');
signal q: std_logic_vector(3 downto 0);
 
begin
dut:main_2 port map(d=>d, nready=>nready, nreset=>nreset, clk=>clk, q=>q);
clock_gen: process(clk) 
begin
clk <= not clk after 10 ns; 
end process clock_gen;
wavegen_proc: process
 begin
nreset <= '0';
nready <= '1';
wait for 20 ns;
nreset <= '1';
wait for 20 ns;
nready <= '0'; 
 wait for 20 ns; d <= "1111";
 wait for 20 ns; d <= "1001";
 wait for 20 ns; d <= "1010";
 wait for 20 ns; d <= "1011";
 wait for 20 ns; d <= "1100";
 wait for 20 ns; d <= "1101";
 wait for 20 ns; d <= "1110";
 wait for 20 ns; d <= "1111";
 wait for 100 ns;
 nreset <= '0';
 wait;
 end process;
 end architecture test2_2;
