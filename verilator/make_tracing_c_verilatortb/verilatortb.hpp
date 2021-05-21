
#ifndef VERILATORTB_HPP
#define VERILATORTB_HPP

#include "verilated.h"

#include "Vtop.h"
#include "verilatortb.hpp"

class VerilatorTb {

  public:

    VerilatorTb(Vtop *top_, VerilatedContext *contextp_);
    ~VerilatorTb();
    bool toggleClock(vluint8_t &clk, int cnt);
    bool driveReset(vluint8_t &clk, vluint8_t &rst_n, int count);

  private:
    Vtop *top;
    VerilatedContext *contextp;
};

#endif // VERILATORTB_HPP
