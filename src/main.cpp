#include <iostream>
#include <vector>
#include <systemc.h>
#include "pc.h"
#include "monitor.h"
#include "instruction_memory.h"
#include "instruction_register.h"
#include "register_file.h"
#include "opcode_decoder.h"



int sc_main(int argc, char **argv) {

    /*sc_clock clk("clock", 5, SC_MS);
    sc_signal<sc_uint<32>> output, instruction;
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<5>> rs1, rs2, rd;
    sc_signal<sc_uint<16>> immediate;
    sc_signal<sc_uint<32>> d_out1, d_out2, d_in;
    sc_signal<bool> we;

    PC pc("pc");
    Monitor monitor("monitor");
    InstructionMemory<5> im("instruction_memory");
    InstructionRegister ir("instruction_register");
    RegisterFile rf("register_file");

    pc.clock(clk);
    pc.output(output);
    im.pc_output(output);
    im.im_output(instruction);
    ir.instruction_in(instruction);
    ir.opcode(opcode);
    ir.rs1(rs1);
    ir.rs2(rs2);
    ir.immediate(immediate);
    ir.rd(rd);

    rf.address_in_1(rs1);
    rf.address_in_2(rs2);
    rf.d_in(d_in);
    rf.opcode(opcode);
    rf.rd(rd);
    rf.clock(clk);
    rf.we(we);
    rf.d_out_1(d_out1);
    rf.d_out_2(d_out2);

    monitor.clk(clk);
    monitor.pc_output(output);
    monitor.im_output(instruction);
    monitor.opcode(opcode);
    monitor.rs1(rs1);
    monitor.rs2(rs2);
    monitor.rd(rd);
    monitor.immediate(immediate);
    monitor.d_out1(d_out1);
    monitor.d_out2(d_out2);
    monitor.d_in(d_in);

    we.write(true);

    std::vector<sc_uint<32>> program = {
        0xA8222800,
        0xA8222800,
        0xA8222800,
        0xA8222800,
        0xA8222800
    };

    im.load_instructions(program);


    sc_start(25, SC_MS);*/

    OpcodeDemux demux("opcode_demux");

    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_bv<4>> output;
    
    demux.opcode(opcode);
    demux.line_selected(output);

    opcode.write(ADD);
    sc_start(25, SC_MS);
    std::cout << "Output: " << output.read()[0] << std::endl;

    opcode.write(STORE);
    sc_start(25, SC_MS);
    std::cout << "Output: " << output.read()[2] << std::endl;

    opcode.write(LOAD);
    sc_start(25, SC_MS);
    std::cout << "Output: " << output.read()[1] << std::endl;

    opcode.write(MOVE);
    sc_start(25, SC_MS);
    std::cout << "Output: " << output.read()[3] << std::endl;

    return EXIT_SUCCESS;
}