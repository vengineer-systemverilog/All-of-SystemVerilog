#!/bin/bash

TEST=$1

if [ ! -e ${TEST}.cpp ]; then
  echo "can't find ${TEST}.cpp"
fi

#VIVADO_BIN_DIR to the directory which has vivado executable

#VIVADO_BIN_DIR="$RDI_ROOT/prep/rdi/vivado/bin"
VIVADO_BIN_DIR="$XILINX_VIVADO/bin"

OUT_SIM_SNAPSHOT="top"
XSI_INCLUDE_DIR="$VIVADO_BIN_DIR/../data/xsim/include"
GCC_COMPILER="/usr/bin/g++"
XSIM_ELAB="xelab"
OUT_EXE="run_simulation"
export LD_LIBRARY_PATH="$XILINX_VIVADO/lib/lnx64.o"

# Start clean
#rm -rf xsim.dir xsim.log xelab* $OUT_EXE

# Compile the HDL design into a simulatable Shared Library
$XSIM_ELAB work.top -prj top.prj -dll -s $OUT_SIM_SNAPSHOT -debug wave

# Compile the C++ code that interfaces with XSI of ISim
$GCC_COMPILER -I$XSI_INCLUDE_DIR  -O3 -c -o xsi_loader.o xsi_loader.cpp

# Compile the program that needs to simulate the HDL design
$GCC_COMPILER -I$XSI_INCLUDE_DIR  -O3 -c -o bfm.o bfm.cpp
$GCC_COMPILER -I$XSI_INCLUDE_DIR  -O3 -c -o bfm_api.o bfm_api.cpp
$GCC_COMPILER -I$XSI_INCLUDE_DIR  -O3 -c -o test.o ${TEST}.cpp
$GCC_COMPILER -I$XSI_INCLUDE_DIR  -O3 -c -o testbench.o testbench.cpp

$GCC_COMPILER -o $OUT_EXE bfm.o bfm_api.o test.o testbench.o xsi_loader.o -ldl -lrt

# Run the program
./$OUT_EXE
