#ifndef _REGISTER_FILE_H
#define _REGISTER_FILE_H


#include <systemc.h>
#include "mux.h"


SC_MODULE(RegisterFile) {

    sc_in<sc_uint<5>> address_in_1, address_in_2, address_in_3;
    sc_in<sc_uint<32>> d_in;
    sc_out<sc_uint<32>> d_out_1, d_out_2;


    void process(void) {

        return;
    }
};

#endif
