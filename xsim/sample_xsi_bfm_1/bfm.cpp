
#include "bfm.h"

using namespace std;

const s_xsi_vlog_logicval one_val  = {0X00000001, 0X00000000};
const s_xsi_vlog_logicval zero_val = {0X00000000, 0X00000000};
const int clock_period_2 = 5;

bfm::bfm() : xsi("xsim.dir/top/xsimk.so", "librdi_simulator_kernel.so")
{
   s_xsi_setup_info info;
   memset(&info, 0, sizeof(info));
   info.logFileName = NULL;
   char wdbName[] = "test.wdb";
   info.wdbFileName = wdbName;
   xsi.open(&info);
   xsi.trace_all();
 	      
   clock = xsi.get_port_number("clk");
   reset = xsi.get_port_number("reset");
   cs = xsi.get_port_number("cs");
   rw = xsi.get_port_number("rw");
   addr = xsi.get_port_number("addr");
   data_in = xsi.get_port_number("data_in");
   data_out = xsi.get_port_number("data_out");
   ready = xsi.get_port_number("ready");

   write_low(cs);
   write_low(rw);
   write_addr(0x00);
   write_data(0x00);
}

bfm::~bfm(){
    xsi.close();
}

void bfm::write_hi(int sig) {
    xsi.put_value(sig, &one_val);
}

void bfm::write_low(int sig) {
    xsi.put_value(sig, &zero_val);
}

void bfm::wait_hi() {
    write_hi(clock);
    xsi.run(clock_period_2);
}

void bfm::wait_low() {
    write_low(clock);
    xsi.run(clock_period_2);
}

void bfm::wait() {
    wait_hi();
    wait_low();
}

void bfm::reset_task(){
    write_hi(reset);
    for(int i=0;i<4;i++) {
        wait();
    }
    write_low(reset);
    wait();
    cout << "done reset" << endl;
}

bool bfm::read_ready() {
    s_xsi_vlog_logicval val;
    xsi.get_value(ready, &val);
    cout << "time : " << dec << xsi.get_time() << ", val.aVal(0x" << hex << val.aVal << "), val.bVal(0x" << val.bVal << ")" << endl;
    return ((val.aVal & 0x1) ? true : false);
}
    
void bfm::write_addr(uint32_t data) {
    s_xsi_vlog_logicval val = {data, 0x0};
    cout << "write_addr(0x" << hex << data << ")" << endl;
    xsi.put_value(addr, &val);
}

void bfm::write_data(uint32_t data) {
    s_xsi_vlog_logicval val = {data, 0x0};
    cout << "write_data(0x" << hex << data << ")" << endl;
    xsi.put_value(data_in, &val);
}

uint32_t bfm::read_data() {
    s_xsi_vlog_logicval val;
    xsi.get_value(data_out, &val);
    cout << "read_data : " << "val.aVal(0x" << hex << val.aVal << "), val.bVal(0x" << val.bVal << ")" << endl;
    return val.aVal;
}

uint32_t bfm::read(uint32_t addr_){
    write_hi(cs);
    write_hi(rw);
    write_addr(addr_);
    wait_hi();

    wait_low();
    while(!read_ready()){
        wait();
    }
    uint32_t data = read_data();

    write_low(cs);
    write_low(rw);
    write_addr(0x0);
    wait_hi();

    wait_low();
    return data;
}

void bfm::write(uint32_t addr_, uint32_t data_){
    write_hi(cs);
    write_low(rw);
    write_addr(addr_);
    write_data(data_);
    wait_hi();

    wait_low();
    while(!read_ready()){
        wait();
    }

    write_low(cs);
    write_low(rw);
    write_addr(0x0);
    write_data(0x0);
    wait_hi();

    wait_low();
}

void bfm::main(){
    reset_task();

    test_main();

    cout << "ime = " << xsi.get_time() << endl;
}
