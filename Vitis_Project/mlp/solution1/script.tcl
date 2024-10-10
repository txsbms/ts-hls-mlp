############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project mlp
set_top mlp
add_files _mlp_includes/cppvars.dat
add_files _mlp_includes/mlp.cpp
add_files -tb _mlp_includes/tb.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7k160t-fbg676-2}
create_clock -period 10 -name default
config_cosim -tool xsim -trace_level all
config_export -format ip_catalog -rtl verilog -vivado_clock 10
source "./mlp/solution1/directives.tcl"
csim_design -setup
csynth_design
cosim_design -trace_level all
export_design -flow impl -rtl verilog -format ip_catalog
