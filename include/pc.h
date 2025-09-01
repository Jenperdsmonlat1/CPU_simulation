#ifndef _PC_H
#define _PC_H


#include <systemc.h>
#include "d_ff.h"


SC_MODULE(PC) {

    sc_in<bool> clock;
    sc_out<sc_uint<32>> output;

    sc_signal<sc_uint<32>> reg, next;

    D_FLIP_FLOP *d_ff;

    void process(void) {

        next.write(reg.read() + 1);
    }

    void update(void) {

        reg.write(output.read());
    }

    SC_CTOR(PC) {
        d_ff = new D_FLIP_FLOP("d_flip_flop");
        d_ff->d(next);
        d_ff->q(output);
        d_ff->clk(clock);

        SC_METHOD(process);
        sensitive << reg;

        SC_METHOD(update);
        sensitive << output;
    }
};

#endif
