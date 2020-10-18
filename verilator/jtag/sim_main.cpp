// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "top.v"
#include "Vtop.h"

vluint64_t main_time = 0;

void jtag_init(const int port);
int jtag_recv(int* tck, int* trstn, int* tdi, int* tms, int tdo);

int main(int argc, char** argv, char** env) {

    const int TCP_PORT = 4567;

    // See a similar example walkthrough in the verilator manpage.

    // This is intended to be a minimal example.  Before copying this to start a
    // real project, it is better to start with a more complete example,
    // e.g. examples/c_tracing.

    // Prevent unused variable warnings
    if (false && argc && argv && env) {}

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
    Verilated::debug(0);

    // Randomization reset policy
    // May be overridden by commandArgs
    Verilated::randReset(2);

    // Verilator must compute traced signals
    Verilated::traceEverOn(true);

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    Verilated::commandArgs(argc, argv);

    // Create logs/ directory in case we have traces to put under it
    Verilated::mkdir("logs");

    jtag_init(TCP_PORT);

    // Construct the Verilated model, from Vtop.h generated from Verilating "top.v"
    Vtop* top = new Vtop;

    top->clk   = 0;

    top->tck   = 0;
    top->trstn = 0;
    top->tdi   = 0;
    top->tms   = 0;            
    
    for(int n=0;n<10;n++){
      main_time++;  // Time passes...
      top->eval();
      top->clk = !top->clk;
    }

    // Simulate until $finish
    while (!Verilated::gotFinish()) {
        int changed = 0;
        main_time++;  // Time passes...

        // Toggle a fast (time/2 period) clock
        top->clk = !top->clk;

        // Toggle control signals on an edge that doesn't correspond
        // to where the controls are sampled; in this example we do
        // this only on a negedge of clk, because we know
        // reset is not sampled there.
        if (!top->clk) {
          int tck, trstn, tdi, tms, tdo;

          tdo = top->tdo;
          if(jtag_recv(&tck, &trstn, &tdi, &tms, tdo)){
            top->tck   = tck;
            top->trstn = trstn;
            top->tdi   = tdi;
            top->tms   = tms;            
            changed = 1;
          }
        }

        // Evaluate model
        // (If you have multiple models being simulated in the same
        // timestep then instead of eval(), call eval_step() on each, then
        // eval_end_step() on each.)
        top->eval();

        // Read outputs
        if(changed)
          VL_PRINTF("[%" VL_PRI64 "d] clk=%x, tck=%x trstn=%x, tms=%x, tdi=%x, tdo=%x\n",
                    main_time, top->clk, top->tck, top->trstn, top->tms, top->tdi, top->tdo);
    }

    // Final model cleanup
    top->final();

    // Destroy model
    delete top;

    // Fin
    exit(0);
}
