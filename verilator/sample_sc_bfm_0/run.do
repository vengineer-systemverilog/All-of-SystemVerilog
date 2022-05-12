vlog -sv top.v
scgenmod -bool -sc_uint Vtop > Vtop.h
sccom -g sc_top.cpp
sccom -link
vsim -c sc_top -do "run -all"
