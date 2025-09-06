#ifndef _INSTRUCTION_REGISTER_H
#define _INSTRUCTION_REGISTER_H


#include <systemc.h>


SC_MODULE(InstructionRegister) {

    sc_in<sc_uint<32>> instruction_in;
    sc_out<sc_uint<6>> opcode;
    sc_out<sc_uint<5>> rs1, rs2, rd;
    sc_out<sc_uint<16>> immediate;


    void process(void) {

        opcode.write((sc_uint<6>)instruction_in.read().range(31, 26));
        rs1.write((sc_uint<5>)instruction_in.read().range(25, 21));
        rs2.write((sc_uint<5>)instruction_in.read().range(20, 16));
        rd.write((sc_uint<5>)instruction_in.read().range(15, 11));
        immediate.write((sc_uint<16>)instruction_in.read().range(15, 0));
    }

    SC_CTOR(InstructionRegister) {
        SC_METHOD(process);
        sensitive << instruction_in;
    }
};

#endif
