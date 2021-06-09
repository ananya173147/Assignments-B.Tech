library ieee;
use ieee.std_logic_1164.all;

entity tb_prob3 is end tb_prob3;

architecture test3_1 of tb_prob3 is
component main_3
port(d: in std_logic_vector(3 downto 0);
clk,nreset,nready: in std_logic;
q_odd:out std_logic_vector(3 downto 0);
q_even:out std_logic_vector(3 downto 0));
end component;

signal clk : std_logic := '1';
signal nreset : std_logic := '1';
signal nready : std_logic;
signal d: std_logic_vector(3 downto 0) := (others=>'0');
signal q_odd: std_logic_vector(3 downto 0);
signal q_even: std_logic_vector(3 downto 0);
 
begin
dut:main_3 port map(d=>d, nready=>nready, nreset=>nreset, clk=>clk, q_odd=>q_odd, q_even=>q_even);
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
 wait for 20 ns; d <= "1100";
 wait for 20 ns; d <= "0001";
 wait for 20 ns; d <= "0010";
 wait for 20 ns; d <= "0011";
 wait for 20 ns; d <= "0100";
 wait for 20 ns; d <= "0101";
 wait for 20 ns; d <= "0110";
 wait for 20 ns; d <= "0111";
 wait for 20 ns; d <= "1000";
 wait for 20 ns; d <= "1001";
 wait for 20 ns; d <= "1010";
 wait for 20 ns; d <= "1011";
 wait for 20 ns; d <= "1100";
 wait for 20 ns; d <= "1101";
 wait for 20 ns; d <= "1110";
 wait for 20 ns; d <= "1111";
 wait for 20 ns;
 wait for 40 ns;
 nreset <= '0';
 wait;
 end process;
 end architecture test3_1;
