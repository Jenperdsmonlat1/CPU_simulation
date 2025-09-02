#include <iostream>
#include <vector>
#include <systemc.h>
#include "pc.h"
#include "monitor.h"
#include "instruction_memory.h"
#include "instruction_register.h"



int sc_main(int argc, char **argv) {

    sc_clock clk("clock", 5, SC_MS);
    sc_signal<sc_uint<32>> output, instruction;
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<5>> rs1, rs2, rd;
    sc_signal<sc_uint<16>> immediate;

    PC pc("pc");
    Monitor monitor("monitor");
    InstructionMemory<5> im("instruction_memory");
    InstructionRegister ir("instruction_register");

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

    monitor.clk(clk);
    monitor.pc_output(output);
    monitor.im_output(instruction);
    monitor.opcode(opcode);
    monitor.rs1(rs1);
    monitor.rs2(rs2);
    monitor.rd(rd);
    monitor.immediate(immediate);

    std::vector<sc_uint<32>> program = {
        0xCCCCCCCC,
        0xAAAAAAAA,
        0xFFFFFFFF,
        0xDDDDDDDD,
        0x1D1D1d1D
    };

    im.load_instructions(program);

    sc_start(25, SC_MS);
    return EXIT_SUCCESS;
}