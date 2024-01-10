module fsoc_lab(

 //for use with max10 deca board
 //(* chip_pin = "M8" *) input logic clk, --50MHz input clock @ 2.5V
 //(* chip_pin = "J21" *) input logic reset_n, --slide switch
 //(* chip_pin = "H21, H22" *) input logic [1:0] mode, --2 push buttons
 //(* chip_pin = "C5, B4, A5, C4, B7, A6, C8, C7" *) output logic [7:0] q --LED[7] to LED[0]
 
 //for use with cyclone V gx starter kit
 (* chip_pin = "H12" *) input logic clk, // --50MHz input clock @ 2.5V
 (* chip_pin = "AC9" *) input logic reset_n, // --Slide switch "SW0" @ 1.2V
 (* chip_pin = "P11, P12" *) input logic [1:0] mode, // --Push buttons "KEY1, KEY2" @1.2V (debounced)
 (* chip_pin = "H9, H8, B6, A5, E9, D8, K6, L7" *) output logic [7:0] q //--8 LEDs "LEDG[7]" to "LEDG[0]" @1.2V

);

base_sys u0 (
	.clk_0_clk          (clk), 		//   	clk.clk
	.pio_input_export  (mode), 		//		pio_input.export
	.pio_leds_export   (q),  			//  	pio_leds.export
	.reset_reset_n     (reset_n)		//   	reset.reset_n
); 


endmodule