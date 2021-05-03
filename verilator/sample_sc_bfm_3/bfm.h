#include <systemc>

#ifndef BFM_H
#define BFM_H

using namespace std;
using namespace sc_core;

SC_MODULE(bfm) {
  public:

    SC_CTOR(bfm);

    sc_in<bool>      clk;
    sc_out<bool>     reset;
    sc_out<uint32_t> addr;
    sc_out<bool>     cs;
    sc_out<bool>     rw;
    sc_out<uint32_t> data_out;
    sc_in<bool>      ready;
    sc_in<uint32_t>  data_in;

  private:
    bool reset_done;

    void reset_task();
    uint32_t read(uint32_t addr_);
    void write(uint32_t addr_, uint32_t data_);

    void test_main();
    void main();
};

#endif // BFM_H
