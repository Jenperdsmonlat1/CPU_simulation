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

    sc_clock clk("clock", 20, SC_MS);
    sc_signal<sc_uint<32>> output, instruction;
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<5>> rs1, rs2, rd;
    sc_signal<sc_uint<16>> immediate;
    sc_signal<sc_uint<32>> d_out1, d_out2, d_in;

    sc_signal<bool> alu_selection, rs_selection, move_selection_port, load_selection_port, we_selection;
    sc_signal<bool> we, reset;

    PC pc("pc");
    Monitor monitor("monitor");
    InstructionMemory<5> im("instruction_memory");
    InstructionRegister ir("instruction_register");
    RegisterFile rf("register_file");
    OpcodeDecoder opd("opcode_decoder");

    pc.clock(clk);
    pc.output(output);
    pc.reset(reset);
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

    opd.opcode(opcode);
    opd.alu_selection(alu_selection);
    opd.rs_selection(rs_selection);
    opd.move_selection_port(move_selection_port);
    opd.load_selection_port(load_selection_port);
    opd.we_selection(we_selection);
    opd.clk(clk);
    opd.reset(reset);

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
    monitor.alu_selection(alu_selection);
    monitor.we_selection(we_selection);
    monitor.rs_selection(rs_selection);
    monitor.move_selection_port(move_selection_port);
    monitor.load_selection_port(load_selection_port);

    std::vector<sc_uint<32>> program = {
        0x00222800,
        0x04F401FE,
        0x09261E00,
        0x0DAB0000
    };

    im.load_instructions(program);
    sc_start(120, SC_MS);

    return EXIT_SUCCESS;
}