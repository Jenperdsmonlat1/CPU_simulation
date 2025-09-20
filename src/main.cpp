#include <iostream>
#include <vector>
#include <systemc.h>
#include "pc.h"
#include "monitor.h"
#include "instruction_memory.h"
#include "instruction_register.h"
#include "register_file.h"
#include "opcode_decoder.h"
#include "alu.h"
#include "d_ff.h"
#include "mux.h"
#include "data_memory.h"



int sc_main(int argc, char **argv) {

    sc_clock clk("clock", 5, SC_MS);
    sc_signal<sc_uint<32>> output, instruction;
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<5>> rs1, rs2, rd;
    sc_signal<sc_uint<16>> immediate;
    sc_signal<sc_uint<32>> d_out1, d_out2, d_in;

    sc_signal<bool> alu_selection, rs_selection, move_selection_port, load_selection_port, we_selection, add_instruction_selection;
    sc_signal<bool> we, reset;
    sc_signal<bool> we_d_mem;

    sc_signal<sc_uint<32>> immediate_32bits, immediate_32bits_output, output_alu, d_in_d_mem, d_out_d_mem, addr_in_d_mem, mux_zero_input, mux_one_input, mux_two_input, double_mux_output;

    PC pc("pc");
    Monitor monitor("monitor");
    InstructionMemory<5> im("instruction_memory");
    InstructionRegister ir("instruction_register");
    RegisterFile rf("register_file");
    OpcodeDecoder opd("opcode_decoder");
    DataMemory d_mem("data_memory");
    ALU alu("alu");
    D_FLIP_FLOP<sc_uint<32>> ff_immediate_value("ff_immediate_value");
    D_FLIP_FLOP<sc_uint<32>> d_in_ff_d_mem_1("d_in_ff_data_mem_1");
    D_FLIP_FLOP<sc_uint<32>> d_in_ff_d_mem_2("d_in_ff_data_mem_2");
    D_FLIP_FLOP<sc_uint<32>> d_in_ff_alu_out("d_in_ff_alu_out");
    DoubleMux dmux_feedback("double_mux_feedback");

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
    rf.d_in(double_mux_output);
    rf.opcode(opcode);
    rf.rd(rd);
    rf.clock(clk);
    rf.we(we);
    rf.d_out_1(d_out1);
    rf.d_out_2(d_out2);
    rf.reset(reset);

    opd.opcode(opcode);
    opd.alu_selection(alu_selection);
    opd.rs_selection(rs_selection);
    opd.move_selection_port(move_selection_port);
    opd.load_selection_port(load_selection_port);
    opd.we_selection(we_selection);
    opd.add_instruction_selection(add_instruction_selection);
    opd.clk(clk);
    opd.reset(reset);

    immediate_32bits.write(immediate.read());
    ff_immediate_value.clk(clk);
    ff_immediate_value.reset(reset);
    ff_immediate_value.d(immediate_32bits);
    ff_immediate_value.q(immediate_32bits_output);

    alu.reset(reset);
    alu.clk(clk);
    alu.load_add_select_port(rs_selection);
    alu.load_store_add_select_port(alu_selection);
    alu.add_select_port(add_instruction_selection);
    alu.imm_value(immediate_32bits_output);
    alu.rs_register(d_out1);
    alu.rd_register(d_out2);
    alu.output(output_alu);

    d_in_ff_d_mem_1.clk(clk);
    d_in_ff_d_mem_1.d(d_out1);
    d_in_ff_d_mem_1.q(d_in_d_mem);
    d_in_ff_d_mem_1.reset(reset);

    d_in_ff_d_mem_2.clk(clk);
    d_in_ff_d_mem_2.d(d_in_d_mem);
    d_in_ff_d_mem_2.reset(reset);
    d_in_ff_d_mem_2.q(mux_zero_input);

    d_in_ff_alu_out.clk(clk);
    d_in_ff_alu_out.reset(reset);
    d_in_ff_alu_out.d(output_alu);
    d_in_ff_alu_out.q(mux_two_input);

    d_mem.we(we_selection);
    d_mem.addr_in(output_alu);
    d_mem.d_in(d_in_d_mem);
    d_mem.d_out(mux_one_input);
    d_mem.clock(clk);
    d_mem.reset(reset);

    dmux_feedback.select_port_0(move_selection_port);
    dmux_feedback.select_port_1(load_selection_port);
    dmux_feedback.port_0_data(mux_zero_input),
    dmux_feedback.port_1_data(mux_one_input);
    dmux_feedback.port_2_data(mux_two_input);
    dmux_feedback.output(double_mux_output);

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

    sc_trace_file *tf = sc_create_vcd_trace_file("opd_waveform");
    sc_trace(tf, clock, "clock");
    sc_trace(tf, opcode, "opcode");
    sc_trace(tf, alu_selection, "alu_selection");
    sc_trace(tf, rs_selection, "rs_selection");
    sc_trace(tf, move_selection_port, "move_selection_port");
    sc_trace(tf, load_selection_port, "load_selection_port");
    sc_trace(tf, we_selection, "we_selection");


    std::vector<sc_uint<32>> program = {
        0x00222800,
        0x04F401FE,
        0x09261E00,
        0x0DAB0000
    };

    im.load_instructions(program);
    sc_start(25, SC_MS);

    sc_close_vcd_trace_file(tf);

    return EXIT_SUCCESS;
}