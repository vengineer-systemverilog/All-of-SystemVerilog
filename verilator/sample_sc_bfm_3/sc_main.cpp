#include <memory>
#include <systemc.h>
#include "Vtop.h"
#include "bfm.h"

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

    sc_start();
    
    top->final();

    cout << "done, time = " << sc_time_stamp() << endl;
    return 0;
}

#ifdef VL_USER_STOP
void vl_stop(const char *filename, int linenum, const char *hier) VL_MT_UNSAFE
{
    sc_stop();
    cout << "call vl_stop" << endl;
}
#endif
