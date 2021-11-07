
#include "bfm_api.h"

#include "svdpi.h"

extern "C" {
extern int direct_read(int addr_);
extern void direct_write(int addr_, int data_);
}

uint32_t direct_top_read(uint32_t addr){
    svScope scope = svSetScope(svGetScopeFromName("top.top"));
    int data = direct_read((int)addr);
    svSetScope(scope);
    return (uint32_t)data;
}

void direct_top_write(uint32_t addr, uint32_t data){
    svScope scope = svSetScope(svGetScopeFromName("top.top"));
    direct_write((int)addr, (int)data);
    svSetScope(scope);
}

void test_main(){
    uint32_t add, data;
    uint32_t exp[0x10000>>2];
    cout << "start test_main" << endl;
    for(uint32_t addr=0x0;addr<0x10000;addr+=4){
        exp[addr>>2] = rand();
        direct_top_write(addr, exp[addr>>2]);
    }
    cout << "done write" << endl;

    for(uint32_t addr=0x0;addr<0x10000;addr+=4){
        uint32_t data = direct_top_read(addr);
        if(data != exp[addr>>2])
            cout << "<<ERR>>, compare error, addr = 0x" << hex << addr << ", data = 0x" << hex << data << endl;
    }

    cout << "finish test_main" << endl;
}
