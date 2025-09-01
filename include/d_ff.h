#ifndef _D_FF_H
#define _D_FF_H


#include <systemc.h>



SC_MODULE(D_FLIP_FLOP) {

    sc_in<bool> clk;
    sc_in<sc_uint<32>> d;
    sc_out<sc_uint<32>> q;


    void process(void) {
        if (clk.posedge()) q.write(d.read());
        return;
    }

    SC_CTOR(D_FLIP_FLOP) {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

#endif
