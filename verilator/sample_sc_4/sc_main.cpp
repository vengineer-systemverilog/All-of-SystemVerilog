// For std::unique_ptr
#include <memory>

// SystemC global header
#include <systemc.h>

// Include model header, generated from Verilating "top.v"
#include "Vtop.h"

SC_MODULE(driver) {
  public:

    SC_CTOR(driver) :
        clk("clk"), reset_l("reset_l"), out_data("out_data"), load("load"), in_data("in_data")
    {
        SC_THREAD(main);
        sensitive << clk.pos();
    }

    sc_in<bool> clk;
    sc_out<bool> reset_l;
    sc_in<uint32_t> out_data;
    sc_out<bool> load;
    sc_out<uint32_t> in_data;

  private:
    void main(){

        reset_l = 0;
        load = 0;
        in_data = 0;
        wait();
        wait();
        wait();

        reset_l = 1;
        wait();
        
        load = 1;
        in_data = 2;
        wait();

        load = 0;

        while(1){
            wait();
            if(out_data == 0xff)
                break;
        }

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

    sc_clock clk{"clk", 10, SC_NS, 0.5, 3, SC_NS, true};

    sc_signal<bool> reset_l;
    sc_signal<bool> load;
    sc_signal<uint32_t> in_data;
    sc_signal<uint32_t> out_data;

    const std::unique_ptr<Vtop> top{new Vtop{"top"}};

    top->clk(clk);
    top->reset_l(reset_l);
    top->load(load);
    top->in_data(in_data);
    top->out_data(out_data);

    const std::unique_ptr<driver> drv{new driver("driver")};

    drv->clk(clk);
    drv->reset_l(reset_l);
    drv->load(load);
    drv->in_data(in_data);
    drv->out_data(out_data);

    sc_start();
    
    top->final();

    cout << "done, time = " << sc_time_stamp() << endl;
    return 0;
}

#ifdef VL_USER_STOP
void vl_stop(const char *filename, int linenum, const char *hier) VL_MT_UNSAFE
{
    sc_stop();
    cout << "call vl_stop" << endl;
}
#endif

