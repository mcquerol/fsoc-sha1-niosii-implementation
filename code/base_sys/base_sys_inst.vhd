	component base_sys is
		port (
			pio_leds_export  : out std_logic_vector(7 downto 0);        -- export
			pio_input_export : in  std_logic                    := 'X'; -- export
			clk_0_clk        : in  std_logic                    := 'X'; -- clk
			reset_reset_n    : in  std_logic                    := 'X'  -- reset_n
		);
	end component base_sys;

	u0 : component base_sys
		port map (
			pio_leds_export  => CONNECTED_TO_pio_leds_export,  --  pio_leds.export
			pio_input_export => CONNECTED_TO_pio_input_export, -- pio_input.export
			clk_0_clk        => CONNECTED_TO_clk_0_clk,        --     clk_0.clk
			reset_reset_n    => CONNECTED_TO_reset_reset_n     --     reset.reset_n
		);

