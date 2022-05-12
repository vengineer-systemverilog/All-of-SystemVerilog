#include <systemc>

#ifndef BFM_H
#define BFM_H

using namespace std;
using namespace sc_core;
using namespace sc_dt;

SC_MODULE(bfm) {
  public:

    SC_CTOR(bfm);

    sc_in<bool>      clk;
    sc_out<bool>     reset;
    sc_out<bool>     cs;
    sc_out<bool>     rw;
    sc_in<bool>      ready;
#ifdef VERILATOR
    sc_out<uint32_t> addr;
    sc_out<uint32_t> data_out;
    sc_in<uint32_t>  data_in;
#else
    sc_out<sc_uint<16>> addr;
    sc_in<sc_uint<32>>  data_in;
    sc_out<sc_uint<32>> data_out;
#endif

  private:
    bool reset_done;

    void reset_task();
    uint32_t read(uint32_t addr_);
    void write(uint32_t addr_, uint32_t data_);

    void test_main();
    void main();
};

#endif // BFM_H
