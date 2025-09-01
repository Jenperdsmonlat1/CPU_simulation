#ifndef _MONITOR_H
#define _MONITOR_H


#include <iostream>
#include <systemc.h>


SC_MODULE(Monitor) {

    sc_in<sc_uint<32>> pc_output;
    sc_in<sc_uint<32>> im_output;
    sc_in<bool> clk;

    void process(void) {

        std::cout << "PC: " << pc_output.read() << " Instruction: " << std::hex << im_output.read() << std::endl;
    }

    SC_CTOR(Monitor) {

        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

#endif
