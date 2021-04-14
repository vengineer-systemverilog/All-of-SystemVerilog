// -*- SystemC -*-
// DESCRIPTION: Verilator Example: Top level main for invoking SystemC model
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// For std::unique_ptr
#include <memory>

// SystemC global header
#include <systemc.h>

// Include common routines
#include <verilated.h>
#if VM_TRACE
#include <verilated_vcd_sc.h>
#endif

#include <sys/stat.h>  // mkdir

// Include model header, generated from Verilating "top.v"
#include "Vtop.h"

SC_MODULE(driver) {
  public:

    SC_CTOR(driver);

    sc_in<bool> clk;
    sc_out<bool> reset_l;
    sc_in<uint32_t> out_data;
    sc_out<bool> load;
    sc_out<uint32_t> in_data;
    sc_out<bool> done;

  private:
    void main(){

        reset_l = 0;
        load = 0;
        in_data = 0;
        done = 0;
        wait();
        wait();
        wait();

        reset_l = 1;
        wait();
        
        load = 1;
        in_data = 2;
        wait();

        load = 0;

        while(1){
            wait();
            if(out_data == 0xff)
                break;
        }

        done = 1;
    }
};

driver::driver(sc_module_name name) 
: sc_module(name), clk("clk"), reset_l("reset_l"), out_data("out_data"), load("load"), in_data("in_data")
{
    SC_THREAD(main);
    sensitive << clk.pos();
}

int sc_main(int argc, char* argv[]) {

    if (false && argc && argv) {}

    Verilated::mkdir("logs");
    Verilated::debug(0);
    Verilated::randReset(2);
    Verilated::commandArgs(argc, argv);

    ios::sync_with_stdio();

    sc_clock clk{"clk", 10, SC_NS, 0.5, 3, SC_NS, true};

    sc_signal<bool> reset_l;
    sc_signal<bool> load;
    sc_signal<uint32_t> in_data;
    sc_signal<uint32_t> out_data;
    sc_signal<bool> done;

    const std::unique_ptr<Vtop> top{new Vtop{"top"}};

    top->clk(clk);
    top->reset_l(reset_l);
    top->load(load);
    top->in_data(in_data);
    top->out_data(out_data);

    const std::unique_ptr<driver> drv{new driver("driver")};

    drv->clk(clk);
    drv->reset_l(reset_l);
    drv->load(load);
    drv->in_data(in_data);
    drv->out_data(out_data);
    drv->done(done);

    sc_start(1, SC_NS);

    while (!Verilated::gotFinish()) {
        sc_start(1, SC_NS);
        if(done)
            break;
    }

    // Final model cleanup
    top->final();

    // Return good completion status
    return 0;
}
