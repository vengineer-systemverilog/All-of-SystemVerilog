#include "bfm.h"
#include "bfm_api.h"

static bfm *bfmp = nullptr;

void set_bfm(bfm* bfm) {
    bfmp = bfm;
}

bool check_bfm() {
    return (bfmp == nullptr);
}

uint32_t read(uint32_t addr_) {
    if(!check_bfm())
        return bfmp->read(addr_);
    return 0;
}

void write(uint32_t addr_, uint32_t data_) {
    if(!check_bfm())
        bfmp->write(addr_, data_);
    return;
}
