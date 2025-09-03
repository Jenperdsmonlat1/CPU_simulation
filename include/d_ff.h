#ifndef _D_FF_H
#define _D_FF_H


#include <systemc.h>


template<int T>
SC_MODULE(D_FLIP_FLOP) {

    sc_in<bool> clk;
    sc_in<sc_uint<T>> d;
    sc_out<sc_uint<T>> q;


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
