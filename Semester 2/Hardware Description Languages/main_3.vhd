library ieee;
use ieee.std_logic_1164.all;

entity main_3 is
port (d: in std_logic_vector(3 downto 0);
clk,nreset,nready: in std_logic;
q_odd: out std_logic_vector(3 downto 0);
q_even:out std_logic_vector(3 downto 0));
end main_3;

architecture struct3 of main_3 is
    
component d_latch_3
port (d: in std_logic_vector (3 downto 0);
clk,nreset : in std_logic;
enable: in std_logic_vector (1 downto 0);
q_odd: out std_logic_vector(3 downto 0);
q_even: out std_logic_vector(3 downto 0));
end component;

component counter16 is
port(clk : in std_logic;
nreset : in std_logic;
nready : in std_logic;
count : out std_logic_vector (3 downto 0));
end component;

component en_gen3 is
port(clk : in std_logic;
nreset: in std_logic;
count_in: in std_logic_vector(3 downto 0);
enable : out std_logic_vector (1 downto 0));
end component;

signal int_clk : std_logic;
signal counter : std_logic_vector(3 downto 0); 
signal enable_out : std_logic_vector (1 downto 0);
begin
DFF_3 : d_latch_3 port map(clk => clk,nreset => nreset,enable => enable_out,d => d,q_odd => q_odd,q_even => q_even);
unit_enable: en_gen3 port map(clk => clk,nreset => nreset,count_in => counter,enable => enable_out);
unit_counter: counter16 port map(clk => clk,nreset => nreset,nready => nready,count => counter);
end struct3;
