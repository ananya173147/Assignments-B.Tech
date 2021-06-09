library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity en_gen2 is
port( clk : in std_logic;
nreset: in std_logic;
count_in: in std_logic_vector(2 downto 0);
enable : out std_logic
);
end entity en_gen2;
architecture en_gen_arch2 of en_gen2 is
begin
process (nreset, clk) is
begin
   if (nreset = '0') then
      enable <= '0';
   elsif (rising_edge(clk)) then
       if (count_in > "010") and (count_in(0) = '0') then
          enable <= '1';
       else
          enable <= '0';
       end if;
   end if;
end process;
end en_gen_arch2;

