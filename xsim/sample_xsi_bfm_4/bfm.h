#include <cstring>
#include <iostream>

#include "xsi_loader.h"

class bfm {
  public:

    bfm();
    ~bfm();
    void main();

    uint32_t read(uint32_t addr_);
    void write(uint32_t addr_, uint32_t data_);

  private:

    Xsi::Loader xsi;

    int clock;
    int reset;
    int cs;
    int rw;
    int addr;
    int data_in;
    int data_out;
    int ready;

    void write_hi(int sig);
    void write_low(int sig);

    void wait_hi();
    void wait_low();
    void wait();

    void reset_task();

    bool read_ready();
    void write_addr(uint32_t data);
    void write_data(uint32_t data);
    uint32_t read_data();
};

