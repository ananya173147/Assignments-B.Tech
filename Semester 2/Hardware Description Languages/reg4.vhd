library ieee;
use ieee.std_logic_1164.all;

entity reg4 is
port (d: in std_logic_vector(3 downto 0);
clk,nreset,nready: in std_logic;
q:out std_logic_vector(3 downto 0));
end reg4;

architecture struct of reg4 is
    
component d_latch
port (d: in std_logic_vector (3 downto 0);
clk,nreset,enable: in std_logic;
q: out std_logic_vector(3 downto 0));
end component;

component counter8 is
port(clk : in std_logic;
nreset : in std_logic;
nready : in std_logic;
count : out std_logic_vector (2 downto 0));
end component;

component en_gen is
port(clk : in std_logic;
nreset: in std_logic;
count_in: in std_logic_vector(2 downto 0);
enable : out std_logic);
end component;

signal int_clk : std_logic;
signal counter : std_logic_vector(2 downto 0); 
signal enable_out : std_logic;
begin
DFF4 : d_latch port map(clk => clk,nreset => nreset,enable => enable_out,d => d,q => q);
unit_enable: en_gen port map(clk => clk,nreset => nreset,count_in => counter,enable => enable_out);
unit_counter: counter8 port map(clk => clk,nreset => nreset,nready => nready,count => counter);
end struct;