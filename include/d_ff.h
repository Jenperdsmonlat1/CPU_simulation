#ifndef _D_FF_H
#define _D_FF_H


#include <systemc.h>


template<typename T>
SC_MODULE(D_FLIP_FLOP) {

    sc_in<bool> clk, reset;
    sc_in<T> d;
    sc_out<T> q;


    void process(void) {
        
        if (reset.read()) q.write((T)0);
        else q.write(d.read());
    }

    SC_CTOR(D_FLIP_FLOP) {
        SC_METHOD(process);
        sensitive << clk.pos() << reset;
    }
};

#endif
