#include <memory>
#include <systemc.h>
#include "Vtop.h"
#include "bfm.h"

SC_MODULE(sc_top) {

    sc_clock clk;

    sc_signal<bool>     reset;
    sc_signal<bool>     cs;
    sc_signal<bool>     rw;
    sc_signal<bool>     ready;
#ifdef VERILATOR
    sc_signal<uint32_t> addr;
    sc_signal<uint32_t> data_in;
    sc_signal<uint32_t> data_out;
#else
    sc_signal<sc_uint<16>> addr;
    sc_signal<sc_uint<32>> data_in;
    sc_signal<sc_uint<32>> data_out;
#endif

    Vtop *u_top;
    bfm *u_bfm;
    
    SC_CTOR(sc_top) :     
        clk("clk", 10, SC_NS, 0.5, 5, SC_NS, true),
        reset("reset"), cs("cs"), rw("rw"), addr("addr"), ready("ready"), data_in("data_in"), data_out("data_out") {

#ifdef VERILATOR
        u_top = new Vtop{"top"};
#else
        u_top = new Vtop{"top", "Vtop", 0, NULL};
#endif

        u_top->clk(clk);
        u_top->reset(reset);
        u_top->cs(cs);
        u_top->rw(rw);
        u_top->addr(addr);
        u_top->data_in(data_in);
        u_top->ready(ready);
        u_top->data_out(data_out);

        u_bfm = new bfm("bfm");

        u_bfm->clk(clk);
        u_bfm->reset(reset);
        u_bfm->cs(cs);
        u_bfm->rw(rw);
        u_bfm->addr(addr);
        u_bfm->data_in(data_out);
        u_bfm->ready(ready);
        u_bfm->data_out(data_in);
    }

    ~sc_top() {
#ifdef VERILATOR
        u_top->final();
#endif
        delete u_top;
        delete u_bfm;
    }
};
