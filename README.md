# PYNQ_Burst_Test
--
## This is a design for the test of  AXI_HP on PYNQ-Z1 (as well as Z2, maybe).
The whole design is inspired by ["Caffeine"](https://ieeexplore.ieee.org/document/7827589) in 2019  and the design [here](https://github.com/dhm2013724/yolov2_xilinx_fpga).

![image1](https://github.com/ms0488638/PYNQ_Burst_Test/blob/master/bd.png)

This IP do nothing but transmit the data (64 MB) to a 256 * 4byte buffer on FPGA.

Users can define the demanding burst length and verified the effective bandwidth of the AXI_HP.

# Tutorial
To use the testing tool

(1) Upload "Burst_IP_Backup.ipynb," "Data_Generator.ipynb," and all (*.bit) and (*.tcl) to the board.

(2) Execute "Data_Generator.ipynb" to create 64 MB dummy file for testing.

(3) Execute "Burst_IP_Backup.ipynb" and the time and bandwidth will show up after all the process is done.

(4) User can modifiy the loaded bitstream files. There are two different bitfile, which stands for 100MHz and 150MHz respectively.

P.S. The original HLS file are included.
