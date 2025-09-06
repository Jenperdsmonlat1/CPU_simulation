#ifndef _REGISTER_FILE_H
#define _REGISTER_FILE_H


#include <systemc.h>
#include "mux.h"
#include "d_ff.h"
#include "opcode.h"



SC_MODULE(RegisterFile) {

    sc_in<sc_uint<5>> address_in_1, address_in_2, rd;
    sc_in<sc_uint<32>> d_in;
    sc_in<sc_uint<6>> opcode;
    sc_in<bool> clock, we, reset;
    sc_out<sc_uint<32>> d_out_1, d_out_2;

    sc_uint<32> regs[32] = {0};

    sc_signal<bool> selected_port;
    sc_signal<sc_uint<5>> one_mux, zero_mux, addr_selected, q1, q2, addr_3_sig;
    sc_signal<sc_uint<32>> d_out_1_intermediate, d_out_2_intermediate;

    D_FLIP_FLOP<sc_uint<32>> *rs_ff, *rd_ff;

    void process_read(void) {

        d_out_1.write(regs[address_in_1.read()]);
        d_out_2.write(regs[address_in_2.read()]);
    }

    void process_write(void) {

        // && (opcode.read() == ADD || opcode.read() == LOAD)
        if (we.read()) regs[addr_selected.read()] = d_in.read();
    }

    void process_select_port(void) {

        selected_port.write((opcode.read() == ADD) ? true : false);
    }

    void update_mux_inputs() {
    
        one_mux.write(rd.read());
        zero_mux.write(address_in_2.read());
    }


    Mux<sc_uint<5>> *mux;
    D_FLIP_FLOP<sc_uint<5>> *d_ff[3];

    SC_CTOR(RegisterFile) {

        mux = new Mux<sc_uint<5>>("multiplexer");
        d_ff[0] = new D_FLIP_FLOP<sc_uint<5>>("d_ff_1");
        d_ff[1] = new D_FLIP_FLOP<sc_uint<5>>("d_ff_2");
        d_ff[2] = new D_FLIP_FLOP<sc_uint<5>>("d_ff_3");

        rs_ff = new D_FLIP_FLOP<sc_uint<32>>("rs_ff");
        rs_ff->clk(clock);
        rs_ff->d(d_out_1_intermediate);
        rs_ff->q(d_out_1);
        rs_ff->reset(reset);

        rd_ff = new D_FLIP_FLOP<sc_uint<32>>("rd_ff");
        rd_ff->clk(clock);
        rd_ff->d(d_out_2_intermediate);
        rd_ff->q(d_out_2);
        rd_ff->reset(reset);

        mux->one(one_mux);
        mux->zero(zero_mux);
        mux->select_add_port(selected_port);
        mux->port_selected(addr_selected);

        d_ff[0]->clk(clock);
        d_ff[0]->d(addr_selected);
        d_ff[0]->q(q1);

        d_ff[1]->clk(clock);
        d_ff[1]->d(q1);
        d_ff[1]->q(q2);

        d_ff[2]->clk(clock);
        d_ff[2]->d(q2);
        d_ff[2]->q(addr_3_sig);

        SC_METHOD(process_read);
        sensitive << address_in_1 << address_in_2;

        SC_METHOD(process_write);
        sensitive << clock.pos();

        SC_METHOD(process_select_port);
        sensitive << opcode;

        SC_METHOD(update_mux_inputs);
        sensitive << rd << address_in_2;
    }
};


#endif
