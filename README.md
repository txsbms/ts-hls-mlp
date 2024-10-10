Ensure that “cppvars.dat” is included with the project. 
If it is not included, a valid “cppvars.dat” file has been provided to include manually. 
Running “mlp_data.py” will also generate this file. 
Once the file is included, the project can be run normally, and the testbench results will output during cosimulation.
All include files should be located in /Vitis_Project/_mlp_includes.

The HLS project is contained within /Vitis_Project. The top-level function is /Vitis_Project/_mlp_includes/mlp.cpp.

MLP implemented by importing weights from separately-trained neural network in Python. The weights are stored as local variables (seen as "const weight_t weights_1 [784][25]", etc. in /Vitis_Project/_mlp_includes/mlp.h). The top-level function takes in an array of 784 values (ie. pixels on an image), and outputs an array of 10 values (ie. output layer output).

The testbench (/Vitis_Project/_mlp_includes/tb.cpp) imports image data through /Vitis_Project/_mlp_includes/cppvars.dat, which contains flattened images and tags associated with those images. The index of the MLP's output which contains the maximum value is compared to the tag associated with the given image input. Total pass rate is output at the end of the testbench (~98%).