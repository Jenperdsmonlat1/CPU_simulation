#ifndef _DATA_MEMORY_H
#define _DATA_MEMORY_H


#include <systemc.h>
#include "d_ff.h"


SC_MODULE(DataMemory) {

    sc_in<bool> we, clock, reset;
    sc_in<sc_uint<32>> addr_in, d_in;
    sc_out<sc_uint<32>> d_out;

    sc_signal<sc_uint<32>> d_out_ff;
    D_FLIP_FLOP<sc_uint<32>> *d_data_mem_ff;

    sc_uint<32> memory[256];

    void process(void) {

        if (we.read()) memory[addr_in.read()] = d_in.read();
        d_out_ff.write(memory[addr_in.read()]);
    }

    SC_CTOR(DataMemory) {

        d_data_mem_ff = new D_FLIP_FLOP<sc_uint<32>>("d_data_mem_ff");
        d_data_mem_ff->clk(clock);
        d_data_mem_ff->reset(reset);
        d_data_mem_ff->d(d_out_ff);
        d_data_mem_ff->q(d_out);

        SC_METHOD(process);
        sensitive << addr_in << d_in << we;
    }
};

#endif
