#ifndef _SCGENMOD_Vtop_
#define _SCGENMOD_Vtop_

#include "systemc.h"

class Vtop : public sc_foreign_module
{
public:
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<sc_uint<16> > addr;
    sc_in<bool> cs;
    sc_in<bool> rw;
    sc_in<sc_uint<32> > data_in;
    sc_out<bool> ready;
    sc_out<sc_uint<32> > data_out;


    Vtop(sc_module_name nm, const char* hdl_name,
       int num_generics, const char** generic_list)
     : sc_foreign_module(nm),
       clk("clk"),
       reset("reset"),
       addr("addr"),
       cs("cs"),
       rw("rw"),
       data_in("data_in"),
       ready("ready"),
       data_out("data_out")
    {
        elaborate_foreign_module(hdl_name, num_generics, generic_list);
    }
    ~Vtop()
    {}

};

#endif

