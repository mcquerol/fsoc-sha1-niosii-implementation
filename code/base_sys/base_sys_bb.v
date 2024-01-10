
module base_sys (
	pio_leds_export,
	pio_input_export,
	clk_0_clk,
	reset_reset_n);	

	output	[7:0]	pio_leds_export;
	input		pio_input_export;
	input		clk_0_clk;
	input		reset_reset_n;
endmodule
