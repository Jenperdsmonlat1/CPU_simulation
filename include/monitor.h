#ifndef _MONITOR_H
#define _MONITOR_H


#include <iostream>
#include <systemc.h>


SC_MODULE(Monitor) {

    sc_in<sc_uint<32>> pc_output;
    sc_in<sc_uint<32>> im_output;
    sc_in<bool> clk, alu_selection, rs_selection, move_selection_port, load_selection_port, we_selection;

    sc_in<sc_uint<5>> rs1, rs2, rd;
    sc_in<sc_uint<6>> opcode;
    sc_in<sc_uint<16>> immediate;
    sc_in<sc_uint<32>> d_out1, d_out2, d_in;


    void process(void) {

        std::cout << "PC: " << pc_output.read() << " Instruction: " << std::hex << im_output.read() << std::endl;
        std::cout << "Opcode: " << opcode.read() << " RS1: " << std::hex << rs1.read() << " RS2: " << rs2.read() << " RD: " << rd.read() << " Immediate: " << immediate.read() << std::endl;
        std::cout << "D_Out1: " << d_out1.read() << " D_Out2: " << d_out2.read() << std::endl;

        std::cout << "Output from Opcode Decoder :" << std::endl;
        std::cout << "ALU Selection: " << alu_selection.read() << std::endl;
        std::cout << "RS Selection: " << rs_selection.read() << std::endl;
        std::cout << "MOVE Selection: " << move_selection_port.read() << std::endl;
        std::cout << "LOAD Selection: " << load_selection_port.read() << std::endl;
        std::cout << "WE Selection: " << we_selection.read() << std::endl;

        std::cout << std::endl;
    }

    SC_CTOR(Monitor) {

        SC_METHOD(process);
        sensitive << clk.pos();

    }
};


#endif
