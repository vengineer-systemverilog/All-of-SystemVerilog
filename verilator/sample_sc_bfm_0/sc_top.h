#include <memory>
#include <systemc.h>
#include "Vtop.h"

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
    sc_out<sc_uint<16>> addr;
    sc_out<bool>     cs;
    sc_out<bool>     rw;
    sc_in<sc_uint<32>>  data_in;
    sc_in<bool>      ready;
    sc_out<sc_uint<32>> data_out;

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

SC_MODULE(sc_top) {

    sc_clock clk;

    sc_signal<bool>     reset;
    sc_signal<bool>     cs;
    sc_signal<bool>     rw;
    sc_signal<sc_uint<16>> addr;
    sc_signal<bool>     ready;
    sc_signal<sc_uint<32>> data_in;
    sc_signal<sc_uint<32>> data_out;

    Vtop *u_top;
    bfm *u_bfm;
    
    SC_CTOR(sc_top) :     
        clk("clk", 10, SC_NS, 0.5, 5, SC_NS, true),
        reset("reset"), cs("cs"), rw("rw"), addr("addr"), ready("ready"), data_in("data_in"), data_out("data_out") {

        u_top = new Vtop{"top", "Vtop", 0, NULL};

        u_top->clk(clk);
        u_top->reset(reset);
        u_top->cs(cs);
        u_top->rw(rw);
        u_top->addr(addr);
        u_top->data_in(data_in);
        u_top->ready(ready);
        u_top->data_out(data_out);

        u_bfm = new bfm("bfm");

        u_bfm->clk(clk);
        u_bfm->reset(reset);
        u_bfm->cs(cs);
        u_bfm->rw(rw);
        u_bfm->addr(addr);
        u_bfm->data_in(data_out);
        u_bfm->ready(ready);
        u_bfm->data_out(data_in);
    }

    ~sc_top() {
        delete u_top;
        delete u_bfm;
    }
};
