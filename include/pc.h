#ifndef _PC_H
#define _PC_H


#include <systemc.h>
#include "d_ff.h"


SC_MODULE(PC) {

    sc_in<bool> clock, reset;
    sc_out<sc_uint<32>> output;

    sc_signal<sc_uint<32>> next;

    D_FLIP_FLOP<sc_uint<32>> *d_ff;

    void process(void) {

        next.write(output.read() + 1);
    }

    SC_CTOR(PC) {
        d_ff = new D_FLIP_FLOP<sc_uint<32>>("d_flip_flop");
        d_ff->d(next);
        d_ff->q(output);
        d_ff->clk(clock);
        d_ff->reset(reset);

        SC_METHOD(process);
        sensitive << output;
    }
};

#endif
