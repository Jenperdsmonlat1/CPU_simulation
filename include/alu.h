#ifndef _ALU_H
#define _ALU_H


#include <systemc.h>
#include "d_ff.h"
#include "mux.h"



SC_MODULE(ALU) {

    sc_in<bool> add_select_port, load_store_add_select_port, load_add_select_port, clk, reset;
    sc_in<sc_uint<32>> imm_value, rs_register, rd_register;
    sc_out<sc_uint<32>> output;


    sc_signal<sc_uint<32>> output_alu, first_op, second_op;

    Mux<sc_uint<32>> *register_switch, *imm_rd_switch;
    D_FLIP_FLOP<sc_uint<32>> *output_ff;


    void process(void) {

        if (load_store_add_select_port.read()) output_alu.write(first_op.read() + second_op.read());
    }

    SC_CTOR(ALU) {

        register_switch = new Mux<sc_uint<32>>("register_switch_mux");
        register_switch->one(rs_register);
        register_switch->zero(rd_register);
        register_switch->select_add_port(load_add_select_port);
        register_switch->port_selected(first_op);

        imm_rd_switch = new Mux<sc_uint<32>>("immediate_rd_switch_mux");
        imm_rd_switch->one(rd_register);
        imm_rd_switch->zero(imm_value);
        imm_rd_switch->select_add_port(add_select_port);
        imm_rd_switch->port_selected(second_op);

        output_ff = new D_FLIP_FLOP<sc_uint<32>>("output_ff");
        output_ff->clk(clk);
        output_ff->d(output_alu);
        output_ff->q(output);
        output_ff->reset(reset);

        SC_METHOD(process);
        sensitive << first_op << second_op << load_store_add_select_port;
    }
};

#endif
