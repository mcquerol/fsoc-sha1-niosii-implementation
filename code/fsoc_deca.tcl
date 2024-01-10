
# TCL script to set the I/O standards for the FPGA user pins used in the basic FSoC Design template
# Arrow Max10 DECA board - Device 10M50DAF484C6GES
# written by C. Jakob, fbeit, h_da, December 2023, christian.jakob@h-da.de

set_global_assignment -name AUTO_RESTART_CONFIGURATION ON
set_global_assignment -name ENABLE_CONFIGURATION_PINS OFF
set_global_assignment -name ENABLE_BOOT_SEL_PIN OFF


set_global_assignment -name IOBANK_VCCIO 1.2V -section_id 3B
set_global_assignment -name IOBANK_VCCIO 2.5V -section_id 7A
set_global_assignment -name IOBANK_VCCIO 1.2V -section_id 8A

set_instance_assignment -name IO_STANDARD "2.5 V" -to clk
set_instance_assignment -name IO_STANDARD "1.2 V" -to reset_n

set_instance_assignment -name IO_STANDARD "1.2 V" -to mode[1]
set_instance_assignment -name IO_STANDARD "1.2 V" -to mode[0]
set_instance_assignment -name IO_STANDARD "1.2 V" -to mode

set_instance_assignment -name IO_STANDARD "1.2 V" -to q[7]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[6]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[5]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[4]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[3]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[2]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[1]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q[0]
set_instance_assignment -name IO_STANDARD "1.2 V" -to q