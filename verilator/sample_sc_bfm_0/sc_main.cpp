
#include "sc_top.h"

int sc_main(int argc, char* argv[]) {

    if (false && argc && argv) {}

    Verilated::debug(0);
    Verilated::randReset(2);
    Verilated::commandArgs(argc, argv);

    ios::sync_with_stdio();

    const std::unique_ptr<sc_top> u_sc_top{new sc_top{"sc_top"}};

    sc_start();
    
    cout << "done, time = " << sc_time_stamp() << endl;
    return 0;
}
