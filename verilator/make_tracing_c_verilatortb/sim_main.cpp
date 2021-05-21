
#include <memory>
#include <verilated.h>

#include "Vtop.h"
#include "VerilatorTb.hpp"

int main(int argc, char** argv, char** env) {

    if (false && argc && argv && env) {}

    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
    contextp->commandArgs(argc, argv);

    const std::unique_ptr<Vtop> top{new Vtop{contextp.get(), "TOP"}};
    const std::unique_ptr<VerilatorTb> tb{new VerilatorTb{top.get(), contextp.get()}};


    top->clk = 0;
    top->reset_l = 0;
    top->in_small = 1;
    top->in_quad = 0x1234;
    top->in_wide[0] = 0x11111111;
    top->in_wide[1] = 0x22222222;
    top->in_wide[2] = 0x3;

    if(!tb->driveReset(top->clk, top->reset_l, 10)) {

        while (!tb->toggleClock(top->clk,1)) {

            if(!top->clk)
	        top->in_quad += 0x12;

            VL_PRINTF("[%" VL_PRI64 "d] clk=%x rstl=%x iquad=%" VL_PRI64 "x"
                      " -> oquad=%" VL_PRI64 "x owide=%x_%08x_%08x\n",
                      contextp->time(), top->clk, top->reset_l, top->in_quad, top->out_quad,
                      top->out_wide[2], top->out_wide[1], top->out_wide[0]);
        }
    }

    top->final();
	
    return 0;
}
