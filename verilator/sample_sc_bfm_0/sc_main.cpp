#include <memory>
#include <systemc.h>
#include "Vmemory.h"

SC_MODULE(bfm) {
  public:

    SC_CTOR(bfm) :
        clk("clk"), reset("reset"), addr("addr"), cs("cs"), rw("rw"), data_in("data_in"), 
        ready("ready"), data_out("data_out"), reset_done(false)
    {
        SC_THREAD(reset_task);
        sensitive << clk.pos();

        SC_THREAD(main);
        sensitive << clk.pos();
    }

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

    void reset_task(){
        reset.write(true);
        for(int i=0;i<4;i++)
            wait();
        reset.write(false);
        wait();
        cout << "done reset" << endl;
        reset_done = true;
    }

    uint32_t read(uint32_t addr_){
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

    void write(uint32_t addr_, uint32_t data_){
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

    void test_main(){
        cout << "start test_main" << endl;
        write(0x200, 0x12345678);
        uint32_t data = read(0x200);
        if(data != 0x12345678)
            cout << "<<ERR>>, compare error, data = 0x" << hex << data << endl;
        cout << "finish test_main" << endl;
    }

    void main(){
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
};

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
