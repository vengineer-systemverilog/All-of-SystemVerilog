if [file exists work] {
    vdel -all
}

vlog -sv top.v
scgenmod -bool -sc_uint Vtop > Vtop.h
sccom -g sc_top.cpp bfm.cpp bfm_api.cpp test_2.cpp
sccom -link
vsim -c sc_top -do "run -all"
