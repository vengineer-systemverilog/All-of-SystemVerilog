#include <memory>
#include <systemc.h>
#include "Vtop.h"
#include "bfm.h"

#include "verilated_vcd_sc.h"

int sc_main(int argc, char* argv[]) {

    if (false && argc && argv) {}

    Verilated::debug(0);
    Verilated::randReset(2);
    Verilated::commandArgs(argc, argv);

    ios::sync_with_stdio();

    sc_clock clk{"clk", 10, SC_NS, 0.5, 5, SC_NS, true};

    sc_signal<bool>     reset;
    sc_signal<bool>     cs;
    sc_signal<bool>     rw;
    sc_signal<uint32_t> addr;
    sc_signal<uint32_t> data_in;
    sc_signal<bool>     ready;
    sc_signal<uint32_t> data_out;

    const std::unique_ptr<Vtop> top{new Vtop{"top"}};

    top->clk(clk);
    top->reset(reset);
    top->cs(cs);
    top->rw(rw);
    top->addr(addr);
    top->data_in(data_in);
    top->ready(ready);
    top->data_out(data_out);

    const std::unique_ptr<bfm> u_bfm{new bfm("bfm")};

    u_bfm->clk(clk);
    u_bfm->reset(reset);
    u_bfm->cs(cs);
    u_bfm->rw(rw);
    u_bfm->addr(addr);
    u_bfm->data_in(data_out);
    u_bfm->ready(ready);
    u_bfm->data_out(data_in);

    Verilated::traceEverOn(true);
    // If verilator was invoked with --trace argument,
    // and if at run time passed the +trace argument, turn on tracing
    VerilatedVcdSc* tfp = NULL;
    const char* flag = Verilated::commandArgsPlusMatch("trace");
    if (flag && 0 == strcmp(flag, "+trace")) {
        tfp = new VerilatedVcdSc;
        top->trace(tfp,99);
        tfp->open("vlt_dump.vcd");
    }

    sc_start();
    
    top->final();

    if(tfp)
        tfp->flush();

    if (tfp) {
        tfp->close();
        tfp = NULL;
    }

    cout << "done, time = " << sc_time_stamp() << endl;
    return 0;
}
