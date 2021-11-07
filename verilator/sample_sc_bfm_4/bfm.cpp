#include <systemc>

#include "bfm.h"

using namespace std;
using namespace sc_core;

void set_bfm(bfm* bfm); // from bfm_api.cpp

bfm::bfm(sc_module_name name) : sc_module(name),
    clk("clk"), reset("reset"), addr("addr"), cs("cs"), rw("rw"), data_in("data_in"), 
    ready("ready"), data_out("data_out"), reset_done(false)
{
    SC_THREAD(reset_task);
    sensitive << clk.pos();

    SC_THREAD(main);
    sensitive << clk.pos();

    set_bfm(this);    
}
    
void bfm::reset_task()
{
    reset.write(true);
    for(int i=0;i<4;i++)
        wait();
    reset.write(false);
    wait();
    cout << "done reset" << endl;
    reset_done = true;
}

uint32_t bfm::read(uint32_t addr_)
{
    cs.write(true);
    rw.write(true);
    addr.write(addr_);
    while(!ready.read()){
        wait();
    }
    cs.write(false);
    addr.write(0x0);
    uint32_t data = data_in.read();
    wait();
    return data;
}

void bfm::write(uint32_t addr_, uint32_t data_){
    cs.write(true);
    rw.write(false);
    addr.write(addr_);
    data_out.write(data_);
    while(!ready.read()){
        wait();
    }
    cs.write(false);
    addr.write(0x0);
    data_out.write(0x0);
    wait();
}

void test_main();

void bfm::main(){
    cs.write(false);
    rw.write(true);
    addr.write(0x00);
    data_out.write(0x00);

    while(!reset_done)
        wait();

    test_main();

    sc_stop();
	cout << "sc_stop(), time = " << sc_time_stamp() << endl;
}

