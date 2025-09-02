#ifndef _MONITOR_H
#define _MONITOR_H


#include <iostream>
#include <systemc.h>


SC_MODULE(Monitor) {

    sc_in<sc_uint<32>> pc_output;
    sc_in<sc_uint<32>> im_output;
    sc_in<bool> clk;

    sc_in<sc_uint<5>> rs1, rs2, rd;
    sc_in<sc_uint<6>> opcode;
    sc_in<sc_uint<16>> immediate;


    void process(void) {

        std::cout << "PC: " << pc_output.read() << " Instruction: " << std::hex << im_output.read() << std::endl;
        std::cout << "Opcode: " << opcode.read() << " RS1: " << std::hex << rs1.read() << " RS2: " << rs2.read() << " RD: " << rd.read() << " Immediate: " << immediate.read() << std::endl;
    }

    SC_CTOR(Monitor) {

        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

#endif
