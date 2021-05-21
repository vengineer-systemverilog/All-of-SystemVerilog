
#include "verilatortb.hpp"

VerilatorTb::VerilatorTb(Vtop *top_, VerilatedContext *contextp_)
  : top(top_), contextp(contextp_)
{
#if VM_TRACE
    Verilated::mkdir("logs");
#endif

    contextp->debug(0);
    contextp->randReset(2);
#if VM_TRACE
    contextp->traceEverOn(true);
#endif
}

VerilatorTb::~VerilatorTb()
{  
#if VM_COVERAGE
    Verilated::mkdir("logs");
    contextp->coveragep()->write("logs/coverage.dat");
#endif
}

bool VerilatorTb::toggleClock(vluint8_t &clk, int cnt)
{
    for(int n=0 ; n<cnt ; n++){
        clk = (clk) ? 0 : 1;

	top->eval();

        contextp->timeInc(1);

        if(contextp->gotFinish())
  	    return true;
    }

    return false;
}

bool VerilatorTb::driveReset(vluint8_t &clk, vluint8_t &rst_n, int count)
{
    rst_n = 0;

    if( toggleClock(clk, count) ) {
        return true;
    }

    
    rst_n = 1;

    return false;
}


