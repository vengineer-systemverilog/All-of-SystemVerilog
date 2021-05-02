
 #include "bfm.h"

void bfm::test_main(){
    cout << "start test_main" << endl;
    write(0x200, 0x12345678);
    uint32_t data = read(0x200);
    if(data != 0x12345678)
        cout << "<<ERR>>, compare error, data = 0x" << hex << data << endl;
    cout << "finish test_main" << endl;
}
