
#include "bfm_api.h"

void test_main(){
    uint32_t exp[0x10000>>2];
    cout << "start test_main" << endl;
    for(uint32_t addr=0x0;addr<0x10000;addr+=4){
        exp[addr>>2] = rand();
        write(addr, exp[addr>>2]);
    }
    cout << "done write" << endl;

    for(uint32_t addr=0x0;addr<0x10000;addr+=4){
        uint32_t data = read(addr);
        if(data != exp[addr>>2])
            cout << "<<ERR>>, compare error, addr = 0x" << hex << addr << ", data = 0x" << hex << data << endl;
    }

    cout << "finish test_main" << endl;
}
